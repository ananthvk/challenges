/*
dcl: optional *'s direct-dcl
direct-dcl  name
            (dcl)
            direct-dcl()
            direct-dcl[optional size]
*/
#include "getinput.h"
#define MAXTOKEN 100
typedef enum Token {NAME, PARENS, BRACKETS}Token;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char *line = NULL;
size_t char_ptr = 0;
size_t size = 0;

int tokentype;
int gettoken();
void dcl(void);
void dirdcl(void);

void dcl(void)
{
    int ns;
    for(ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while(ns --> 0)
        strcat(out, " pointer to");
}

void dirdcl(void)
{
    int type;
    if(tokentype == '(')
    {
        dcl();
        if(tokentype != ')')
            printf("error: missing )\n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");

    while((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if(type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
int gettoken()
{
    if()
}
int main()
{
    while(1)
    {
        printf(">>>> ");
        line = get_dyn_line(&size);
        if(size == 1)
            break;
        printf("%s", line);
        free(line);
        line = NULL;
    }
}