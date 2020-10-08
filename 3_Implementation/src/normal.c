#include "normal.h"
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
struct unpw details;
struct candd candidate;
FILE *fileptr6,*fileptrresults;int i,j,contestcount;
int comparator(const void* p, const void* q)
{
    return ( ( (struct candd*) p )->vote_count < ( (struct candd*) q )->vote_count );
}

void sortcontest(void)
{
    fileptrresults = fopen("contest1.dat","r");
            while(fread(&candidate,sizeof(struct candd),1,fileptrresults))
            {
                contestcount++;
            }
            fclose(fileptrresults);
    struct candd candi[contestcount];//temps={{0},{0}};
    fileptr6 = fopen("contest1.dat","r");
    i=0;
    while(fread(&candidate,sizeof(struct candd),1,fileptr6))
    {
        strcpy(candi[i].contestun,candidate.contestun);
        candi[i].vote_count=candidate.vote_count;
        i++;
    }
    fclose(fileptr6);
    qsort(candi, contestcount, sizeof(struct candd), comparator);
    printf("RESULTS FROMSSORTING");
    for(j=0;j<contestcount;j++)
    {
        printf("\nUser Name: %s Votes : %d\n",candi[j].contestun,candi[j].vote_count);
    }
}


int normal(char loginun[],char loginpw[])
{
    FILE *fileptr,*fileptr1;int flag=0,votescount=0;contestcount=0;
    fileptr=fopen("login.dat","r");
    while(fread(&details,sizeof(struct unpw),1,fileptr))
    {
        if((strcmp(details.loginun,loginun)==0) && (strcmp(details.loginpw,loginpw)==0))
        {
            sortcontest();
            fileptr1=fopen("contest1.dat","r");
            printf("        RESULTS FROM NORMAL            \n");

            while(fread(&candidate.contestun,sizeof(struct candd),1,fileptr1))
            {
                printf("   %s    %d\n",candidate.contestun,candidate.vote_count);

                if(candidate.vote_count>votescount)
                {
                    votescount=candidate.vote_count;
                }
            }
            fclose(fileptr1);
        }
    }
    fclose(fileptr);


    return votescount;
}
