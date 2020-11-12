#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "admin.h"

FILE *fileptr,*fileptr1,*fileptr2,*fileptr3,*fileptraddvoter;
static char op; 
static char state;
int statev,found=0,statech;
char loginv[30],loginvpw[30];
struct unpw voter;
struct polled polls;

struct polled
{
    char pollun[30];
    int polleds;
};
struct unpw
{
    char loginun[30];
    char loginpw[30];
    int aovv;
};


int addvoter(char loginunarg[],char loginpwarg[])
{
    int flag=0;
    fileptr2=fopen("state.txt","r");
    fscanf(fileptr2,"%d",&statech);
    fclose(fileptr2);
    if(statech==1)
    {
    int addvoterstatus=0;
    fileptraddvoter=fopen("login.dat","r");
    while(fread(&voter,sizeof(struct unpw),1,fileptraddvoter))
    {
        if(strcmp(voter.loginun,loginunarg)==0)
        {
            addvoterstatus=1;
        }
    }
    fclose(fileptraddvoter);
    if(addvoterstatus==0)
    {

    fileptr=fopen("login.dat","a+");
    if(fileptr==NULL)
    {
        printf("File can't be opened\n");
        exit(1);
    }
    strcpy(voter.loginun,loginunarg);
    strcpy(voter.loginpw,loginpwarg);
    voter.aovv=1;
    fwrite (&voter, sizeof(struct unpw), 1, fileptr);
    flag=1;

    fclose(fileptr);
    }
    else if (addvoterstatus==1)
    {

        flag=2;
    }
    }
    else if(statech==2 || statech==0)
    {
        flag=0;
    }
    return flag;
}

int removevoter(char loginunarg[])
{
    int flag=0;
    fileptr2=fopen("state.txt","r");
    fscanf(fileptr2,"%d",&statech);
    fclose(fileptr2);

    if(statech==1)
    {
    int removevoterstatus=0;
    fileptraddvoter=fopen("login.dat","r");
    while(fread(&voter,sizeof(struct unpw),1,fileptraddvoter))
    {
        if(strcmp(voter.loginun,loginunarg)==0)
        {
            removevoterstatus=1;
        }
    }
    fclose(fileptraddvoter);
    if(removevoterstatus==1)
    {
    fileptr=fopen("login.dat","a+");
    fileptr1=fopen("temp.dat","a+");
    if(fileptr==NULL)
    {
        printf("File can't be opened\n");
        exit(1);
    }
    if(fileptr1==NULL)
    {
        printf("File can't be opened\n");
        exit(1);
    }

    while(fread(&voter,sizeof(struct unpw),1,fileptr))
    {
        if(strcmp(loginunarg,voter.loginun)==0)
        {
            found=1;
            flag=1;
        }
        else
        {
            fwrite(&voter,sizeof(struct unpw),1,fileptr1);
        }
    }
    if(!found)
    {
        //printf("No such User Name");
        //goto removevoterfun;
    }
    fclose(fileptr1);
    fclose(fileptr);remove("login.dat");rename("temp.dat","login.dat");remove("temp.dat");
    }
    else if (removevoterstatus==0)
    {
        flag=2;
    }
    return flag;
}
else if (statech==2 || statech==0)
{
    flag=0;
}
}
int cstate(char yesorno)
{
    int flag=10;
    if(yesorno=='y')
    {
        fileptr=fopen("state.txt","r");
        fscanf(fileptr,"%d",&statev);
        fclose(fileptr);
        fileptr=fopen("state.txt","w");
        statev++;
        statev=statev%3;
        fprintf(fileptr,"%d",statev);
        fclose(fileptr);
        flag=statev;
        switch(statev)
        {
            case 1:
            {

                fileptr2=fopen("voterlist.dat","w");
                fclose(fileptr2);
                break;
            }
            case 2:
            {
                fileptr2=fopen("contest.dat","w");fclose(fileptr2);
                break;
            }
            case 0:
            {
                fileptr2=fopen("voterlist.dat","a+");fileptr3=fopen("login.dat","a+");
                while(fread(&voter,sizeof(struct unpw),1,fileptr3))
                {
                    polls.polleds=0;strcpy(polls.pollun,voter.loginun);
                    fwrite(&polls,sizeof(struct polled),1,fileptr2);
                }
                fclose(fileptr2);fclose(fileptr3);
                break;
            }
            default:
                {break;}
        }
    }
    return flag;
}

void displayvoters()
{
    fileptr2=fopen("login.dat","r");
    while(fread(&voter,sizeof(struct unpw),1,fileptr2))
    {
        if(voter.aovv==1)
        {
            printf("   %s   \n",voter.loginun);
        }
    }
    fclose(fileptr2);
}

void adminfun()
{
    int option,status;
    char loginunarg[30],loginpwarg[30];
    adminpage:
    printf("   1 . . . ADD VOTER\n   2 . . . REMOVE VOTER\n   3 . . . CHANGE THE STATE\n   4 . . . SEE VOTERS LIST\n   5 . . . EXIT\nEnter your option : ");
    scanf("%d",&option);
    switch(option)
    {
        case 1:
        {
            fileptr2=fopen("state.txt","r");
            fscanf(fileptr2,"%d",&statech);
            if(statech==1)
            {
                addvoterfun:
                printf("Enter voter username : ");
                scanf("%s",&loginunarg);
                printf("Enter voter password : ");
                scanf("%s",&loginpwarg);
                status=addvoter(loginunarg,loginpwarg);
                if(status==1)
                    {printf("\nVOTER ADDED TO THE DATABASE SUCCESSFULLY\n\n");
                    printf("Add one more voter? y/n\n");
                scanf(" %c",&op);
                if(op=='y')
                    goto addvoterfun;
                else if(op=='n')
                {
                    goto adminpage;break;
                }
                    }
                else if(status==2)
                    {printf("\nVOTER HAS BEEN ALREADY ADDED TO THE DATABASE\n\n");
                    printf("Add one more voter? y/n\n");
                scanf(" %c",&op);
                if(op=='y')
                    goto addvoterfun;
                else if(op=='n')
                {
                    goto adminpage;break;
                }

                    }
                else if(status==0){
                    printf("\nVOTER ADDITION IS NOT ALLOWED");
                    goto adminpage;
                }


            }
            else
                {
                    printf("\nAdding Voter is resticted\n");goto adminpage;break;}
            fclose(fileptr2);
        }
        case 2:
        {
            fileptr2=fopen("state.txt","r");
            fscanf(fileptr2,"%d",&statech);
            fclose(fileptr2);
            if(statech==1)
            {
                removevoterfun:
                printf("Enter the username to remove : ");scanf("%s",loginunarg);
                status=removevoter(loginunarg);
                if(status==1)
                {
                    printf("VOTER REMOVED");
                    printf("Remove one more voter? y/n\n");
                scanf(" %c",&op);
                if(op=='y')
                    goto removevoterfun;
                else if(op=='n')
                {
                    goto adminpage;break;
                }
                }
                else if (status==2)
                {
                    printf("No such User Name");
                    printf("Remove one more voter? y/n\n");
                scanf(" %c",&op);
                if(op=='y')
                    goto removevoterfun;
                else if(op=='n')
                {
                    goto adminpage;break;
                }
                }
                else if(status==0){
                    printf("\nVOTER REMOVAL IS NOT ALLOWED");
                    goto adminpage;
                }


            }
            else
            {
                printf("\nRemoving Voter is resticted\n");goto adminpage;break;
            }
        }
        case 3:
        { 
            fileptr=fopen("state.txt","r");
            fscanf(fileptr,"%d",&statev);
            fclose(fileptr);
            switch(statev)
            {
                case 1:{printf("Current State --> Normal State\n");break;}
                case 2:{printf("Current State --> Announcement State\n");break;}
                case 0:{printf("Current State --> Polling State\n");break;}
                default:{break;}
            }
            printf("Change to next state y/n?\n");
            scanf(" %c",&state);
            status=cstate(state);
            fileptr=fopen("state.txt","r");
            fscanf(fileptr,"%d",&statev);
            fclose(fileptr);
            switch(status)
            {
                case 1:{printf("State changed to Normal State\n");break;}
                case 2:{printf("State changed to Announcement State\n");break;}
                case 0:{printf("State changed to Polling State\n");break;}
                default:{break;}
            }
            goto adminpage;
            break;
        }
        case 4:
            {
                displayvoters();goto adminpage;break;
            }
        case 5:
            break;
    }

}
