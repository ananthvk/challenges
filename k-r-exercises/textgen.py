import random
from collections import Counter
import sys

escape_chars = [' ', '\n', '\t', '\\']
spl_chars = [' ', '\n', '\t']
escape_chars_nonl = [' ', '\t', '\\']

symbols = [i for i in range(33, 48)] + [i for i in range(58, 65)] + [i for i in range(91, 97)] + [i for i in range(123, 127)]
symbols = [chr(i) for i in symbols]

upperalpha = [chr(i) for i in range(65, 91)]
loweralpha = [chr(i) for i in range(97, 123)]
alpha = upperalpha + loweralpha

numbers = [chr(i) for i in range(48, 58)]

WORD_LENGTH_RANGE = (4,9)
WORDS_PER_LINE_RANGE = (70, 120) 
NUMBER_OF_LINES_RANGE = (0, 200) 
MAX_TABS_PER_LINE = 2

def gen_paragraphs():
    n = random.randint(*NUMBER_OF_LINES_RANGE)

    lines = []
    for i in range(n):
        words_per_line = random.randint(*WORDS_PER_LINE_RANGE)
        line = []
        n_tabs = 0
        for j in range(words_per_line):
            word_length = random.randint(*WORD_LENGTH_RANGE)
            word = ''
            for k in range(word_length):
                word += random.choice(loweralpha)
            line += [word]
            if(n_tabs <= MAX_TABS_PER_LINE) and random.uniform(0, 1) < 0.5:
                line += ['\t']
                n_tabs += 1
        lines += [line]

    return ('\n'.join([' '.join(line) for line in lines]))

def gen_words(n = 1000, nrand = 5):
    words = []
    wlen = 0
    for i in range(n):
        word_length = random.randint(*WORD_LENGTH_RANGE)
        word = ''
        for k in range(word_length):
            word += random.choice(loweralpha)
        words += [word]
        words += [' ']
        wlen += 1
        for j in range(random.randint(0,nrand)):
            words += random.choice(spl_chars)
    return wlen, ''.join(words)



def main():
    if(len(sys.argv) >= 2):
        if sys.argv[1] == 'test':
            print('Escape characters:', escape_chars)
            print('Symbols:', symbols)
            print('Uppercase:', upperalpha)
            print('Lowercase:', loweralpha)
            print('Numbers:', numbers)
        if sys.argv[1] == 'paragraphs':
            text = gen_paragraphs()
            print(text)

            counter = Counter(text)
            s,t,n = counter[' '], counter['\t'], counter['\n']
            # The first print adds one new line and the below print adds 
            # another newline character
            print(f'{s},{t},{n+2}')

        if sys.argv[1] == 'words':
            n, text = gen_words(n=10_000)
            print(text)
            # print(n)

        else:
            print('Usage: $ textgen.py [test|paragraphs]')


if __name__ == '__main__':
    main()
