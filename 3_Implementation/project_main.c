#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "functions.h"
#include "admin.h"
#include "voter.h"

char userid[30],userpw[30];
void adminfun();
int main()
{
    int i,j,status=0;//aov=0;

    char *weln,loginun[20],loginpw[20],*weln1,*weln0;
    weln = (char*)malloc (200);
    weln = strcpy(weln,"Welcome to the election system");
    weln0 = (char*)malloc (200);
    weln0 = strcpy(weln0,"\n  - - - - - LOGIN - - - - - \nEnter your User Name: ");
    weln1 = (char*)malloc (200);
    weln1=strcpy(weln1,"\nEnter Password: ");
    for(i=0;i<strlen(weln);i++)
    {
       //delay(1);
        printf("%c",weln[i]);                               //printing welcome note
    }
    loginpage:
    //login:                                                 //getting login page
    for(i=0;i<strlen(weln0);i++)
    {
        //delay(1);
        printf("%c",weln0[i]);                              //printing username
    }
    scanf("%s",&loginun);
    for(i=0;i<strlen(weln1);i++)
    {
        //delay(1);
        printf("%c",weln1[i]);                              //printing username
    }
    scanf("%s",&loginpw);                                  //getting login username
    if(status=logincheck(loginun,loginpw))                             //checking for username
    {
        printf("LOGIN SUCCESSFULL\n\n");
        for(j=0;j<strlen(weln1);j++)
        {
            //delay(1);
            //printf("%c",weln1[j]);                           //printing login password
        }
        //scanf("%s",&loginpw);                              //getting login password
        //if(loginpwcheck(loginpw))
        //{
//        printf("%d",aov);
            if(status==2)
            {
                adminfun();
                //printf("admin00");
            }
            else if (status==1)
            {
                //printf("voter");
               votersfun();
            }
        //}

    }
    else
        {
            printf("Credentials are incorrect :(");
            //goto loginpage;
            //goto loginpw;
        }/*
    else
    {
        printf("User Name doesn't exist :((");
        goto login;
    }
*/
    goto loginpage;
    return 0;
}
