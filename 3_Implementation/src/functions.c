#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

FILE *fileptr;
struct unpw details;
int flag=0;
char cloginun[30];

struct unpw
{
	char loginun[30];
	char loginpw[30];
	int aovv;
};

int logincheck(char loginun[],char loginpw[])
{
    fileptr=fopen("login.dat","r");
    if(fileptr==NULL)
    {
        printf("File can't be opened\n");
        exit(1);
    }
    while(fread(&details,sizeof(struct unpw),1,fileptr))
    {
        if(strcmp(details.loginun,loginun)==0)
        {
            if(strcmp(details.loginpw,loginpw)==0)
            {
                flag=details.aovv;
                strcpy(cloginun,details.loginun);
                break;
            }
        }
        else
        {
            flag = 0;
        }
    }
    fclose(fileptr);
    return flag;
}
