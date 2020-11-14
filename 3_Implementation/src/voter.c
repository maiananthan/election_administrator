#include "voter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *fileptr,*fileptr1,*fileptr2,*fileptr3,*fileptr4,*fileptr5,*fileptr6,*fileptrcc,*fileptrmax;
int statevoter, contests=0,voted,i,j,k,contestcount;
char an,votervote[30];
extern char cloginun[30];

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
struct polled pollstate;
struct candd candidate;


int comparator(const void* p, const void* q)
{
    return ( ( (struct candd*) p )->vote_count < ( (struct candd*) q )->vote_count );
}
void sortcontest()
{
struct candd candi[contestcount];
    fileptr6 = fopen("contest.dat","r");
    i=0;
    while(fread(&candidate,sizeof(struct candd),1,fileptr6))
    {
        strcpy(candi[i].contestun,candidate.contestun);
        candi[i].vote_count=candidate.vote_count;
        i++;
    }
    fclose(fileptr6);
    qsort(candi, contestcount, sizeof(struct candd), comparator);
fileptrcc=fopen("results.dat","w");
for(i=0;i<contestcount;i++)
{
    strcpy(candidate.contestun,candi[i].contestun);
    candidate.vote_count=candi[i].vote_count;
    fwrite(&candidate,sizeof(struct candd),1,fileptrcc);
}
fclose(fileptrcc);

}
int normal()
{
    int max_vote=0;
    contestcount=0;
    fileptrcc = fopen("contest.dat","r");
    while(fread(&candidate,sizeof(struct candd),1,fileptrcc))
    {
        contestcount++;
    }
    fclose(fileptrcc);
    sortcontest();
    fileptrmax=fopen("results.dat","r");
    fread(&candidate,sizeof(struct candd),1,fileptrmax);
    max_vote=candidate.vote_count;
    fclose(fileptrmax);
    return max_vote;
}

int enlist(char yesorno,char loginunenlist[30])
{
    int flag=0,contests=0;
    if(yesorno=='y')
    {
        fileptr1=fopen("contest.dat","r");
        while(fread(&candidate,sizeof(struct candd),1,fileptr1))
        {
            if(strcmp(loginunenlist,candidate.contestun)==0)
            {
                contests=1;
            }
        }
        fclose(fileptr1);
        if(contests==0)
        {
            fileptr1=fopen("contest.dat","a+");
            strcpy(candidate.contestun,loginunenlist);
            candidate.vote_count=0;
            fwrite(&candidate,sizeof(struct candd),1,fileptr1);
            fclose(fileptr1);
            flag=1;
        }
        else
        {
            flag=2;
        }
    }
    else if(yesorno=='n')
    {
        flag=0;
    }
    return flag;
}


int polling(char loginunpoll[30],char tovotefor[30])
{
    int flag=0,voted=0;
    fileptr4=fopen("voterlist.dat","a+");
    while(fread(&pollstate,sizeof(struct polled),1,fileptr4))
    {
        if(strcmp(pollstate.pollun,loginunpoll)==0)
        {
            if(pollstate.polleds==2)
            {
                flag=2;
                voted=1;
            }
        }
    }
    fclose(fileptr4);
    if(voted==0)
    {
	fileptr1=fopen("contest.dat","a+");fileptr2=fopen("temp.dat","a+");
    while(fread(&candidate,sizeof(struct candd),1,fileptr1))
    {
        if(strcmp(candidate.contestun,tovotefor)==0)
        {
            candidate.vote_count++;
            fwrite(&candidate,sizeof(struct candd),1,fileptr2);
            flag=1;
            fileptr4=fopen("temp1.dat","a+");fileptr5=fopen("voterlist.dat","a+");
            while(fread(&pollstate,sizeof(struct polled),1,fileptr5))
            {
                //printf("%s\n",pollstate.pollun);
                if(strcmp(pollstate.pollun,loginunpoll)==0)
                {//printf("%s\n",pollstate.pollun);
                    pollstate.polleds=2;
                    fwrite(&pollstate,sizeof(struct polled),1,fileptr4);
                }
                else
                {
                    fwrite(&pollstate,sizeof(struct polled),1,fileptr4);
                }
            }
            fclose(fileptr4);fclose(fileptr5);
            remove("voterlist.dat");rename("temp1.dat","voterlist.dat");remove("temp1.dat");
        }
        else
        {
            fwrite(&candidate,sizeof(struct candd),1,fileptr2);
        }
    }
    fclose(fileptr1);fclose(fileptr2);
    remove("contest.dat");rename("temp.dat","contest.dat");remove("temp.dat");}
    return flag;
}


void votersfun()
{
    int status=0;char votervote[30];
    fileptr=fopen("state.txt","r");
    fscanf(fileptr,"%d",&statevoter);
    switch(statevoter)
    {
        case 1:
            {
                printf("\n - - - Normal State - - - \n      - RESULTS -     \n");
                status=normal();
                printf("\n     User Name       Votes\n     - - - - - - - - - - - ");
                fileptrcc=fopen("results.dat","r");
                while(fread(&candidate,sizeof(struct candd),1,fileptrcc))
                {
                    printf("\n     %s          %d",candidate.contestun,candidate.vote_count);
                }
                break;
            }
        case 2:
            {
                printf("Announcement State\n");
                printf("Do you want to be candidate y/n?");
                scanf(" %c",&an);
                status=enlist(an,cloginun);
                if(status==1)
                {
                    printf("You have enlisted :)\n");
                }
                else if(status==2)
                {
                    printf("%s have already enlisted",cloginun);
                }
                else if(status==0)
                {
                    printf("You are not enlisted\n");
                }
                break;
            }
        case 0:
            {
                printf("Entering polling state\n");
                printf(" - - - Polling State - - - \n");
                fileptr1=fopen("contest.dat","a+");
                printf("     - Candidates List -     \n");
                while(fread(&candidate,sizeof(struct candd),1,fileptr1))
                {
                    printf("   %s\n",candidate.contestun);
                }
                fclose(fileptr1);
                printf("Enter the candidate username you wish to vote:\n");
                scanf("%s",votervote);
                status=polling(cloginun,votervote);

                if(status==2)
                {
                    printf("Already Voted\n");
                }
                else if(status==1)
                {
                    printf("You voted for %s",votervote);
                }
                break;
            }
        default:{break;}
    }
    fclose(fileptr);
}
