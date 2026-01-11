
/* So what’s the secret formula? Well, most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you can determine if a credit card number is (syntactically) valid as follows:
 *
 * Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
 * Add the sum to the sum of the digits that weren’t multiplied by 2.
 * If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
 * That’s kind of confusing, so let’s try an example with David’s Visa: 4003600000000014.
 *
 * For the sake of discussion, let’s first underline every other digit, starting with the number’s second-to-last digit:
 *
 * 4003600000000014
 *
 * Okay, let’s multiply each of the underlined digits by 2:
 *
 * 1•2 + 0•2 + 0•2 + 0•2 + 0•2 + 6•2 + 0•2 + 4•2
 *
 * That gives us:
 *
 * 2 + 0 + 0 + 0 + 0 + 12 + 0 + 8
 *
 * Now let’s add those products’ digits (i.e., not the products themselves) together:
 *
 * 2 + 0 + 0 + 0 + 0 + 1 + 2 + 0 + 8 = 13
 *
 * Now let’s add that sum (13) to the sum of the digits that weren’t multiplied by 2 (starting from the end):
 *
 * 13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20
 *
 * Yup, the last digit in that sum (20) is a 0, so David’s card is legit!
 *
 * So, validating credit card numbers isn’t hard, but it does get a bit tedious by hand. Let’s write a program.
 *  */
/*
 * PSEUDOCODE
 * ==========
 * Set checksum to 0
 * Get every digit from right to left from the cc number
 *  If the digit is at even position
 *      Multiply the digit by two and find the sum of its digits.
 *      Add this sum to checksum
 *  If the digit is at odd position
 *      Add the number to checksum
 * If checksum is divisible by 10
 *  Print that CC is valid
 * Else
 *  Print that CC is invalid
 * 
 */
#include<stdio.h>
#include<math.h>

int getLuhn(unsigned long long int ccNumber, int *length)
{
    int checksum = 0;
    int pos = 1;
    int digit;
    // Get all digits from the card number, right to left.
    while(ccNumber != 0)
    {
        // Extract a single digit
        digit = ccNumber % 10;

        // Check if the digit is in even position
        if(pos % 2 == 0)
        {
            // As the the value of digit*2 can never exceed 100 (actually 18 for digit 9),
            // I have used % 10 and / 10 to extract the digit at unit's place and tens place respectively.
            checksum += ((digit * 2) % 10) + ((digit * 2) / 10);
        }
        else
        {
            checksum += digit;
        }
        ccNumber = ccNumber / 10;
        pos++;
    }
    if(length)
        *length = pos - 1;
    return checksum;
}

void checkValidity(unsigned long long int ccNumber)
{
    int length;
    if(getLuhn(ccNumber, &length) % 10)
    {
        // return -1;
        printf("%s\n", "Luhn Number verification failed");
        printf("Luhn number: %d\n", getLuhn(ccNumber, NULL)); 
        printf("%s\n", "INVALID");
        return;
    }
    if(length != 13 && length != 15 && length != 16)
    {
        printf("%s\n", "Length requirement not reached");
        printf("%s%d\n", "Length: ", length);
        printf("%s\n", "INVALID");
        return;
    }
    // printf("%d\n", ccNumber % pow(10, length));
    int i = 1; 
    // l1 is first digit and l2 is the second digit.
    int l1 = 0, l2 = 0;
    while(ccNumber != 0)
    {
        if(i == (length - 1))
        {
            l2 = ccNumber % 10;
        }
        else if(i == length)
        {
            l1 = ccNumber % 10;
        }
        ccNumber /= 10;
        i++;
    }
    int extract = l1 * 10 + l2;
    // printf("Extract - %d\n", extract);
    if(extract == 34 || extract == 37)
        printf("%s\n", "AMEX");
    else if((extract >= 51) && (extract <= 55))
        printf("%s\n", "MASTERCARD");
    else if(l1 == 4)
        printf("%s\n", "VISA");
    else
    {
        printf("%s\n", "UNKNOWN card type - Not AMEX, VISA or MASTERCARD");
        printf("%s\n", "INVALID");
        return;
    }
}


int main()
{
    // unsigned long long int is used because credit card numbers are usually 13-16 digits long.
    unsigned long long int ccNumber = 4003600000000014;
    // Accept at most 50 numbers
    //int i = 0;
    //while(i < 50)
    //{
        // printf("%s:", "CC Number");
        // Scanf has the issue that if negative values are entered, there is no way to check error
        // as I have used unsigned integers, and this can result in undefined behaviour.
        scanf("%I64u", &ccNumber);
        checkValidity(ccNumber);
     //   i++;
    //}
}
/*
TEST RUN OUTPUT
==================
One test case failed - 4062901840 displays VISA, but is actually INVALID.
This input has length 10, so I should also add a check that the length is greater than equal to 13.
CC Number:5105105105105100
Extract - 51
MASTERCARD
CC Number:4111111111111111
Extract - 41
VISA
CC Number:4222222222222
Extract - 42
VISA
CC Number:378282246310005
Extract - 37
AMEX
CC Number:371449635398431
Extract - 37
AMEX
CC Number:5555555555554444
Extract - 55
MASTERCARD
CC Number:5105105105105100
Extract - 51
MASTERCARD
CC Number:4111111111111111
Extract - 41
VISA
CC Number:4012888888881881
Extract - 40
VISA
CC Number:4222222222222
Extract - 42
VISA
CC Number:1234567890
Luhn number = 43
INVALID
CC Number:369421438430814
Extract - 36
INVALID
CC Number:4062901840
Extract - 40
VISA
CC Number:5673598276138003
Extract - 56
INVALID
CC Number:4111111111111113
Luhn number = 32
INVALID
CC Number:4222222222223
Luhn number = 41
INVALID
CC Number:4062901840
Extract - 40
VISA
*/
