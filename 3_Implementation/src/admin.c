#include "admin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct polled
{
    char pollun[30];
    int polleds;
};
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
struct polled polls;struct unpw voter;struct candd candidate;
FILE *fileptr;
int admin(char yesorno)
{
    int state_change=0,flag=0;
    fileptr=fopen("state.txt","a+");
    fscanf(fileptr,"%d",&state_change);
    fclose(fileptr);
    fileptr=fopen("state.txt","w");
    if(yesorno=='y')
    {
        state_change++;
        state_change=state_change%3;
        switch(state_change)
        {
        case 1:
            {printf("\n                                    STATE CHANGED TO NORMAL STATE                                   \n");break;}
        case 2:
            {
                printf("\n                              STATE CHANGED TO ANNOUNCEMENT STATE                                   \n");
                rename("contest.dat","contest1.dat");
                break;
            }
        case 0:
            {printf("\n                                   STATE CHANGED TO POLLING STATE                                   \n");break;}
        }
        flag=1;
    }
    fprintf(fileptr,"%d",state_change);printf("wrote");
    fclose(fileptr);
    return flag;
}
int admin_add_voter(char loginun[],char loginpw[])
{

    FILE *fileptraddvoter,*fileptrscheck;int addvoterstatus=0,flag,statestatus;
    fileptrscheck=fopen("state.txt","r");
    fscanf(fileptrscheck,"%d",&statestatus);
    fclose(fileptrscheck);
    if(statestatus==1)
    {
    fileptraddvoter=fopen("login.dat","r");
    while(fread(&voter,sizeof(struct unpw),1,fileptraddvoter))
    {
        if(strcmp(voter.loginun,loginun)==0)
        {
            addvoterstatus=1;
        }
    }
    fclose(fileptraddvoter);
    if(addvoterstatus==0)
    {
        fileptraddvoter=fopen("login.dat","a+");
        strcpy(voter.loginun,loginun);
        strcpy(voter.loginpw,loginpw);
        voter.aovv=1;
        fwrite(&voter,sizeof(struct unpw),1,fileptraddvoter);
        printf("\nVOTER ADDED TO THE DATABASE SUCCESSFULLY\n\n");
        fclose(fileptraddvoter);
        flag=1;
    }
    else if (addvoterstatus==1)
    {
        printf("\nVOTER HAS BEEN ALREADY ADDED TO THE DATABASE\n\n");
        flag=2;
    }
    }
    else
    {
        printf("VOTER ADDITION IS NOT ALLOWED");
        flag=0;
    }
    return flag;
}
/*
admin_remove_voter(char loginun[])
{
    FILE *fileptraddvoter;int addvoterstatus;
    fileptraddvoter=fopen("login.dat","r");
    while(fread(&voter,sizeof(struct unpw),1,fileptraddvoter))
    {
        if(strcmp(voter.loginun,loginun)==0)
        {
            addvoterstatus=1;
        }
    }
    fclose(fileptraddvoter);
    if(addvoterstatus==0)
    {
        fileptraddvoter=fopen("login.dat","a+");
        strcpy(voter.loginun,loginun);
        strcpy(voter.loginpw,loginpw);
        voter.aovv=1;
        fwrite(&voter,sizeof(struct unpw),1,fileptraddvoter);
        printf("VOTER REMOVED FROM THE DATABASE SUCCESSFULLY");
        fclose(fileptraddvoter);
    }
    else
    {
        printf("VOTER HAS BEEN ALREADY REMOVED TO THE DATABASE");
    }

}*/
int admin_remove_voter(char loginun[])
{
    FILE *fileptr,*fileptr1,*fileptrscheck;int found=0,flag=0,statestatus;
    fileptrscheck=fopen("state.txt","r");
    fscanf(fileptrscheck,"%d",&statestatus);
    fclose(fileptrscheck);
    if(statestatus==1)
    {

    fileptr=fopen("login.dat","a+");
    fileptr1=fopen("templogin.dat","a+");

    while(fread(&voter,sizeof(struct unpw),1,fileptr))
    {
        if(strcmp(loginun,voter.loginun)==0)
        {
            found=1;
            flag=1;
            printf("VOTER REMOVED");
        }
        else
        {
            fwrite(&voter,sizeof(struct unpw),1,fileptr1);
        }
    }
    if(!found)
    {
        printf("No such User Name");
    }
    fclose(fileptr1);
    fclose(fileptr);remove("login.dat");rename("templogin.dat","login.dat");remove("templogin.dat");
    }
    else
    {
        printf("VOTER DELETION IS NOT ALLOWED");
        flag=0;
    }



    return flag;
}
