#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "functions.h"
#include "admin.h"
#include "voter.h"

int main()
{
    int i,j,status=0;
    char loginun[20],loginpw[20];
    printf("\n   Welcome to the election system   ");                               
    loginpage:
    printf("\n\n     - - - - - LOGIN - - - - -    \n\n Enter your User Name : ");
    scanf("%s",&loginun);
    printf(" Enter Password       : ");
    scanf("%s",&loginpw);                                  
    if(status=logincheck(loginun,loginpw))
    {
        printf("\n         LOGIN SUCCESSFULL   \n\n");
        if(status==2)
        	adminfun();
        else if (status==1)
            votersfun();
    }
    else
    	printf("   Credentials are incorrect :(");
    goto loginpage;
    return 0;
}
