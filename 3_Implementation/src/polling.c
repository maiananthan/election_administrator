#include "polling.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct candd
{
    char contestun[30];
    int vote_count;
};
struct unpw
{
    char loginun[30];
    char loginpw[30];
    int aovv;
};
struct polled
{
    char pollun[30];
    int polleds;
};
struct unpw details;
struct candd candidate;
struct polled polls;

int polling(char loginun[],char loginpw[],char voted[])
{
    int voteds;
    FILE *fileptrp,*fileptrp1,*fileptrpvc,*fileptrpt,*fileptrpsc1,*fileptrpsc2;
	int flag=0;
    fileptrp=fopen("login.dat","a+");
    while(fread(&details,sizeof(struct unpw),1,fileptrp))
    {
        if((strcmp(details.loginun,loginun)==0) && (strcmp(details.loginpw,loginpw)==0))
        {
            printf("\n   %s LOG-IN\n",details.loginun);
            voteds=0;
            fileptrpvc=fopen("voterlist.dat","a+");
            while(fread(&polls,sizeof(struct polled),1,fileptrpvc))
            {
                if( (strcmp(polls.pollun,loginun)==0) && (polls.polleds==2) )
                {
					printf("Already Voted\n");
                    voteds=1;flag=2;
                }
            }
            fclose(fileptrpvc);
            if(voteds==0)
            {
                fileptrpt=fopen("temp.dat","a+");fileptrp1=fopen("contest1.dat","r");
                while(fread(&candidate,sizeof(struct candd),1,fileptrp1))
                {
                    //printf("entering vote section\n");
                    if(strcmp(candidate.contestun,voted)==0)
                    {
                        strcpy(candidate.contestun,voted);
                        candidate.vote_count++;
                        printf("%s vote count is %d\n",candidate.contestun,candidate.vote_count);
                        fwrite(&candidate,sizeof(struct candd),1,fileptrpt);
                        printf("You voted for %s\n",candidate.contestun);
                        fileptrpsc1=fopen("temp1.dat","a+");
                        fileptrpsc2=fopen("voterlist.dat","a+");
                        while(fread(&polls,sizeof(struct polled),1,fileptrpsc2))
                        {
                            if(strcmp(polls.pollun,loginun)==0)
                            {
                                printf("Your vote got counted\n");
                                polls.polleds=2;
                                fwrite(&polls,sizeof(struct polled),1,fileptrpsc1);
                            }
                            else
                            {
                                fwrite(&polls,sizeof(struct polled),1,fileptrpsc1);
                            }
                        }
                        fclose(fileptrpsc1);fclose(fileptrpsc2);
                        remove("voterlist.dat");rename("temp1.dat","voterlist.dat");remove("temp1.dat");

                    }
                    else
                    {
                        fwrite(&candidate,sizeof(struct candd),1,fileptrpt);
                    }

                }

                fclose(fileptrp1);fclose(fileptrpt);
                remove("contest1.dat");rename("temp.dat","contest2.dat");remove("temp.dat");
                fileptrp1=fopen("contest2.dat","r");
                while(fread(&candidate.contestun,sizeof(struct candd),1,fileptrp1))
                {
                    printf("   %s    %d\n",candidate.contestun,candidate.vote_count);
                }
                fclose(fileptrp1);
                rename("contest2.dat","contest1.dat");remove("contest2.dat");
                flag=1;
			}
        }
    }
    fclose(fileptrp);
    retp:
    return flag;
}
