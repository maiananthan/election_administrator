#include "unity.h"
#include "unity_internals.h"
#include "functions.h"
#include "admin.h"
#include "voter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int aov=0;
struct unpw
{
    char loginun[30];
    char loginpw[30];
    int aovv;
};
struct unpw voter;
/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}

void test_login(void)
{
    TEST_ASSERT_EQUAL(1,logincheck("voter001","voter001pw"));
}
void test_login_fail(void)
{
    TEST_ASSERT_EQUAL(0,logincheck("voter00","voter001pw"));
}
void test_add_voter(void)
{
	TEST_ASSERT_EQUAL(1,addvoter("voter040","voter040pw"));
}
void test_add_same_voter_again(void)
{
	TEST_ASSERT_EQUAL(2,addvoter("voter040","voter040pw"));
}
void test_remove_voter(void)
{
	TEST_ASSERT_EQUAL(1,removevoter("voter040"));
}
void test_remove_same_voter_again(void)
{
	TEST_ASSERT_EQUAL(2,removevoter("voter040"));
}
void test_change_normal_state_to_announcement_state(void)
{
	TEST_ASSERT_EQUAL(2,cstate('y'));
}
void test_voter_enlist(void)
{
	TEST_ASSERT_EQUAL(1,enlist('y',"voter002"));
	TEST_ASSERT_EQUAL(1,enlist('y',"voter008"));
	TEST_ASSERT_EQUAL(0,enlist('n',"voter009"));
	TEST_ASSERT_EQUAL(1,enlist('y',"voter012"));
}
void test_voter_enlist_again(void)
{
	TEST_ASSERT_EQUAL(2,enlist('y',"voter008"));
}
void test_change_announcement_state_to_polling_state(void)
{
	TEST_ASSERT_EQUAL(0,cstate('y'));
}
void test_cast_vote(void)
{
	TEST_ASSERT_EQUAL(1,polling("voter001","voter012"));
	TEST_ASSERT_EQUAL(1,polling("voter002","voter008"));
	TEST_ASSERT_EQUAL(1,polling("voter003","voter002"));
	TEST_ASSERT_EQUAL(1,polling("voter004","voter012"));
	TEST_ASSERT_EQUAL(1,polling("voter007","voter012"));
	TEST_ASSERT_EQUAL(1,polling("voter008","voter012"));
	TEST_ASSERT_EQUAL(1,polling("voter009","voter008"));
	TEST_ASSERT_EQUAL(1,polling("voter010","voter008"));
	TEST_ASSERT_EQUAL(1,polling("voter011","voter002"));
	TEST_ASSERT_EQUAL(1,polling("voter012","voter012"));	
}
void test_cast_vote_again(void)
{
	TEST_ASSERT_EQUAL(2,polling("voter002","voter008"));
	TEST_ASSERT_EQUAL(2,polling("voter010","voter008"));
}
void test_change_polling_state_to_normal_state(void)
{
	TEST_ASSERT_EQUAL(1,cstate('y'));
}
void test_results(void)
{
	TEST_ASSERT_EQUAL(5,normal());
}
int main(void)
{
    /* Initiate the Unity Test Framework */
    UNITY_BEGIN();
    /* Run Test functions */
    RUN_TEST(test_login);
    RUN_TEST(test_login_fail);
	RUN_TEST(test_add_voter);
	RUN_TEST(test_add_same_voter_again);
	RUN_TEST(test_remove_voter);
	RUN_TEST(test_remove_same_voter_again);
	RUN_TEST(test_change_normal_state_to_announcement_state);
	RUN_TEST(test_voter_enlist);
	RUN_TEST(test_voter_enlist_again);
	RUN_TEST(test_change_announcement_state_to_polling_state);
	RUN_TEST(test_cast_vote);
	RUN_TEST(test_cast_vote_again);
	RUN_TEST(test_change_polling_state_to_normal_state);
	RUN_TEST(test_results);
    /* Close the Unity Test Framework */
    return UNITY_END();
}
