#include "announce.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct unpw
{
    char loginun[30];
    char loginpw[30];
    int aovv;
};
struct candd
{
    char contestun[30];
    int vote_count;
};
struct unpw details;struct candd candidate;
int contests;
int announce(char loginun[],char loginpw[],char yorn)
{
    int flag=0;
    FILE *fileptr,*fileptr1;
    fileptr=fopen("login.dat","a+");
    fileptr1=fopen("contest.dat","a+");
    contests=0;
    while(fread(&details,sizeof(struct unpw),1,fileptr))
    {
        while(fread(&candidate,sizeof(struct candd),1,fileptr1))
        {
            if(strcmp(loginun,candidate.contestun)==0)
            {
                contests=1;goto ret1;
            }
        }
        ret1:
        if(contests==0)
        {
            if((strcmp(details.loginun,loginun)==0) && (strcmp(details.loginpw,loginpw)==0))
            {
                printf("\n     %s  LOG-IN\n",loginun);
                if(yorn=='y')
                {
                    printf("  %s WISHED TO ENLISTED\n",loginun);
                    printf("  %s GOT ENLISTED\n",loginun);
                    strcpy(candidate.contestun,loginun);
                    candidate.vote_count=0;
                    fwrite(&candidate,sizeof(struct candd),1,fileptr1);
                    flag=1;goto ret;
                }
                else
                {
                    printf("   %s NOT WISHED TO GOT ENLISTED\n",loginun);
                    flag=2;
                    goto ret;
                }
            }
        }
        else
        {
            printf("\n     %s  LOG-IN\n",loginun);
            printf("  %s WISHED TO ENLISTED\n",loginun);
            printf("    %s ALREADY GOT ENLISTED\n",loginun);
            flag=3;goto ret;
        }
    }
    ret:
    fclose(fileptr);fclose(fileptr1);
    return flag;
}
