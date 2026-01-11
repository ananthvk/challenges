/* Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place. */
#include <stdio.h>
#include <string.h>

#include "utest.h"

void swap(char s[], int i, int j)
{
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
}
void reverse(char s[], int i, int l)
{
    if (s[i] == '\0')
        return;
    else
        reverse(s, i + 1, l);
    if (i > ((l / 2) - 1)) return;
    // printf("%c %d %d\n", s[i], i, l - 1 - i);
    swap(s, i, l - 1 - i);
}
UTEST_MAIN();

UTEST(test_reverse, basic)
{
    char s[8000];
    // NO BUFFER OVERFLOW CHECKS HERE
    // ONLY TEST
    strcpy(s, "This is the way");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ("yaw eht si sihT", s);

    strcpy(s, "this");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ("siht", s);

    strcpy(s, "The quick brown fox jumps over the lazy dogs");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ("sgod yzal eht revo spmuj xof nworb kciuq ehT", s);

    strcpy(s,
           "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas "
           "consectetur, tellus a luctus luctus, nibh ipsum ornare massa, ac "
           "semper turpis metus vitae sem. Curabitur condimentum consectetur "
           "dapibus. Aliquam cursus ac risus ut semper.");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(
        ".repmes tu susir ca susruc mauqilA .subipad rutetcesnoc mutnemidnoc "
        "rutibaruC .mes eativ sutem siprut repmes ca ,assam eranro muspi hbin "
        ",sutcul sutcul a sullet ,rutetcesnoc saneceaM .tile gnicsipida "
        "rutetcesnoc ,tema tis rolod muspi meroL",
        s);

    strcpy(
        s,
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam "
        "rhoncus tellus lacus, nec auctor magna imperdiet at. Phasellus eget "
        "tristique tortor. Cras porta diam id metus faucibus, vel consequat "
        "metus interdum. Maecenas pulvinar leo ac vulputate facilisis. Nam "
        "egestas enim vitae justo sodales, vel aliquam diam fermentum.");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(
        ".mutnemref maid mauqila lev ,selados otsuj eativ mine satsege maN "
        ".sisilicaf etatupluv ca oel ranivlup saneceaM .mudretni sutem "
        "tauqesnoc lev ,subicuaf sutem di maid atrop sarC .rotrot euqitsirt "
        "tege sullesahP .ta teidrepmi angam rotcua cen ,sucal sullet sucnohr "
        "mauqilA .tile gnicsipida rutetcesnoc ,tema tis rolod muspi meroL",
        s);

    strcpy(s,
           "Quisque at tincidunt lectus, et sollicitudin ante. Nullam posuere "
           "eros vel ligula tempor suscipit. Fusce posuere scelerisque urna. "
           "Suspendisse id nisl pulvinar, rhoncus libero et, consequat eros.");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(
        ".sore tauqesnoc ,te orebil sucnohr ,ranivlup lsin di essidnepsuS "
        ".anru euqsirelecs ereusop ecsuF .tipicsus ropmet alugil lev sore "
        "ereusop malluN .etna niduticillos te ,sutcel tnudicnit ta euqsiuQ",
        s);

    strcpy(s,
           " Sed luctus faucibus efficitur. Pellentesque porttitor, velit id "
           "posuere tincidunt, lacus sapien egestas justo, in maximus ex "
           "lectus et elit. Donec vel odio pellentesque, pulvinar orci "
           "efficitur, consequat massa.");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(
        ".assam tauqesnoc ,ruticiffe icro ranivlup ,euqsetnellep oido lev "
        "cenoD .tile te sutcel xe sumixam ni ,otsuj satsege neipas sucal "
        ",tnudicnit ereusop di tilev ,rotittrop euqsetnelleP .ruticiffe "
        "subicuaf sutcul deS ",
        s);

    strcpy(s,
           " Sed dignissim erat sit amet ante porttitor mollis. In quis "
           "maximus nisi. Donec fringilla magna sit amet mauris congue, id "
           "rhoncus nunc faucibus. Ut suscipit erat nec lorem dictum rutrum");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(
        "murtur mutcid merol cen tare tipicsus tU .subicuaf cnun sucnohr di "
        ",eugnoc siruam tema tis angam allignirf cenoD .isin sumixam siuq nI "
        ".sillom rotittrop etna tema tis tare missingid deS ",
        s);

    strcpy(
        s,
        ". Vivamus finibus nisl quis pellentesque tempor. Proin ac velit "
        "ipsum. Praesent convallis ullamcorper erat, quis ullamcorper tellus "
        "accumsan eu. Suspendisse imperdiet id felis imperdiet scelerisque.");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(
        ".euqsirelecs teidrepmi silef di teidrepmi essidnepsuS .ue nasmucca "
        "sullet reprocmallu siuq ,tare reprocmallu sillavnoc tnesearP .muspi "
        "tilev ca niorP .ropmet euqsetnellep siuq lsin subinif sumaviV .",
        s);
    strcpy(s, "a");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(s, "a");

    strcpy(s, "ab");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(s, "ba");

    strcpy(s, "abc");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(s, "cba");

    strcpy(s, "");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ(s, "");
}
