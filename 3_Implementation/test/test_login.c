#include "unity.h"
#include "announce.h"
#include "polling.h"
#include "normal.h"
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
/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}

void test_admin_add_voter_normal_state(void)
{
    TEST_ASSERT_EQUAL(1,admin_add_voter("voter020","voter020pw"));
    TEST_ASSERT_EQUAL(1,admin_add_voter("voter021","voter021pw"));
    TEST_ASSERT_EQUAL(2,admin_add_voter("voter021","voter021pw"));
}
void test_admin_remove_voter_normal_state(void)
{
    TEST_ASSERT_EQUAL(1,admin_remove_voter("voter020"));
    TEST_ASSERT_EQUAL(1,admin_remove_voter("voter021"));
}
void test_admin_announcement_state_change(void)
{
    TEST_ASSERT_EQUAL(1,admin('y'));
}
void test_admin_add_voter_announcement_state(void)
{
    TEST_ASSERT_EQUAL(0,admin_add_voter("voter020","voter020pw"));
}
void test_admin_remove_voter_announcement_state(void)
{
    TEST_ASSERT_EQUAL(0,admin_remove_voter("voter020"));
    TEST_ASSERT_EQUAL(0,admin_remove_voter("voter021"));
}
void test_candidate_enlistment_yes(void)
{
    TEST_ASSERT_EQUAL(1, announce("voter001","voter001pw",'y'));
    TEST_ASSERT_EQUAL(0, announce("voter003","voter00pw",'y'));
    TEST_ASSERT_EQUAL(1, announce("voter004","voter004pw",'y'));
    TEST_ASSERT_EQUAL(1, announce("voter003","voter003pw",'y'));
}
void test_candidate_enlistment_no(void)
{
    TEST_ASSERT_EQUAL(2, announce("voter002","voter002pw",'n'));
}
void test_candidate_already_enlisted(void)
{
    TEST_ASSERT_EQUAL(3, announce("voter001","voter001pw",'y'));
}
void test_admin_polling_state_change(void)
{
    TEST_ASSERT_EQUAL(1,admin('y'));
}
void test_admin_add_voter_polling_state(void)
{
    TEST_ASSERT_EQUAL(0,admin_add_voter("voter020","voter020pw"));
}
void test_admin_remove_voter_polling_state(void)
{
    TEST_ASSERT_EQUAL(0,admin_remove_voter("voter020"));
    TEST_ASSERT_EQUAL(0,admin_remove_voter("voter021"));
}
void test_voter_polling_first_time(void)
{
    TEST_ASSERT_EQUAL(0, polling("voter01","voter00pw","voter004"));
    TEST_ASSERT_EQUAL(0, polling("voter00","voter001pw","voter001"));
    TEST_ASSERT_EQUAL(1, polling("voter001","voter001pw","voter004"));
    TEST_ASSERT_EQUAL(1, polling("voter002","voter002pw","voter001"));
    TEST_ASSERT_EQUAL(1, polling("voter003","voter003pw","voter003"));
    TEST_ASSERT_EQUAL(1, polling("voter004","voter004pw","voter003"));
    TEST_ASSERT_EQUAL(1, polling("voter007","voter007pw","voter003"));
    TEST_ASSERT_EQUAL(1, polling("voter008","voter008pw","voter003"));
    TEST_ASSERT_EQUAL(1, polling("voter009","voter009pw","voter001"));
    TEST_ASSERT_EQUAL(1, polling("voter010","voter010pw","voter001"));
    TEST_ASSERT_EQUAL(1, polling("voter011","voter011pw","voter003"));
    TEST_ASSERT_EQUAL(1, polling("voter012","voter012pw","voter001"));
}
void test_voter_polling_second_time(void)
{
    TEST_ASSERT_EQUAL(2, polling("voter003","voter003pw","voter001"));
    TEST_ASSERT_EQUAL(2, polling("voter009","voter009pw","voter004"));
}
void test_admin_normal_state_change(void)
{
    TEST_ASSERT_EQUAL(1,admin('y'));
}
void test_voter_results(void)
{
    TEST_ASSERT_EQUAL(5, normal("voter009","voter009pw"));
    TEST_ASSERT_EQUAL(0, normal("voter00","voter009pw"));
}

int test_main(void)
{
    /* Initiate the Unity Test Framework */
    UNITY_BEGIN();
    /* Run Test functions */
    printf("ADMIN ADDING VOTER TO DATABASE DURING NORMAL STATE");
    RUN_TEST(test_admin_add_voter_normal_state);
    printf("ADMIN REMOVING VOTER FROM THE DATABASE NORMAL STATE");
    RUN_TEST(test_admin_remove_voter_normal_state);
    printf("\n      ADMIN CHANGING FROM NORMAL STATE TO ANNOUNCEMENT STATE FOR VOTERS TO ENLIST AS CANDIDATES     \n\n");
    RUN_TEST(test_admin_announcement_state_change);
    printf("ADMIN ADDING VOTER DURING ANNOUNCEMENT STATE");
    RUN_TEST(test_admin_add_voter_announcement_state);    RUN_TEST(test_admin_remove_voter_announcement_state);


    printf("\n                             VOTERS WHO WANTED TO ENLISTED AS CANDIDATE                             \n\n");
    RUN_TEST(test_candidate_enlistment_yes);
    printf("\n                           VOTERS WHO NOT WANTED TO ENLISTED AS CANDIDATE                           \n\n");
    RUN_TEST(test_candidate_enlistment_no);
    printf("\n                              VOTERS WHO ALREADY ENLISTED AS CANDIDATE                              \n\n");
    RUN_TEST(test_candidate_already_enlisted);
    printf("\n  ADMIN CHANGING FROM ANNOUNCEMENT STATE TO POLLING STATE TO CAST VOTE FOR A CANDIDATE WHO ENLISTED \n\n");
    RUN_TEST(test_admin_polling_state_change);                           //         ANNNOUNCE TEST
    printf("ADMIN ADDING VOTER DURING POLLING STATE");
    RUN_TEST(test_admin_add_voter_polling_state);
        RUN_TEST(test_admin_remove_voter_polling_state);

    FILE *fileptrres;
    rename("contest.dat","contest1.dat");
    remove("contest.dat");
    //Voter List START
    FILE *fileptr2;FILE *fileptr3;
    fileptr2=fopen("voterlist.dat","a+");fileptr3=fopen("login.dat","a+");
    while(fread(&voter,sizeof(struct unpw),1,fileptr3))
    {
        polls.polleds=0;strcpy(polls.pollun,voter.loginun);
        fwrite(&polls,sizeof(struct polled),1,fileptr2);
    }
    printf("\n - - - - - VOTER LIST PREPARED - - - - - \n");
    fclose(fileptr2);fclose(fileptr3);
    //Voter List END
    fileptr2=fopen("contest1.dat","a+");
    printf("\n - - - - - CANDIDATES LIST - - - - - \n");
    while(fread(&candidate.contestun,sizeof(struct candd),1,fileptr2))
    {
        printf("    %s\n",candidate.contestun);//contest list display
    }fclose(fileptr2);
    fileptrres=fopen("contest1.dat","r");
    printf("           BEFORE POLLING     ");
    while(fread(&candidate.contestun,sizeof(struct candd),1,fileptrres))
    {
        printf("   %s    %d\n",candidate.contestun,candidate.vote_count);//vote count display
    }
    fclose(fileptrres);
    printf("\n                                 VOTERS CASTING VOTE FOR FIRST TIME                                 \n\n");
    RUN_TEST(test_voter_polling_first_time);
    printf("\n                                VOTERS CASTING VOTE FOR SECOND TIME                                 \n\n");
    RUN_TEST(test_voter_polling_second_time);                              // ----------------------------------------------
    remove("voterlist.dat");
    printf("VOTER LIST DELETED\n   - - - - RESULTS - - - - \n");
    fileptrres=fopen("contest1.dat","r");
    while(fread(&candidate.contestun,sizeof(struct candd),1,fileptrres))
    {
        printf("   %s    %d\n",candidate.contestun,candidate.vote_count);
    }
    fclose(fileptrres);
    printf("\n       ADMIN CHANGING POLLING STATE TO NORMAL STATE (RESULTS STATE) FOR VOTERS TO SEE RESULTS       \n\n");
    RUN_TEST(test_admin_normal_state_change);
    printf("\n                                       VOTERS SEEING RESULTS                                        \n\n");
    RUN_TEST(test_voter_results);
    remove("contest1.dat");
    /* Close the Unity Test Framework */
    return UNITY_END();
}
