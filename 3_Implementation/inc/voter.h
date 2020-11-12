/**
* @file voter.h
* Functions which controll the features of the voters 
*/

#ifndef __VOTER_H__
#define __VOTER_H__

/**
* Voter function for controlling voters features
* @param[in] Nothiing
* @return Nothing
* @note 
*/
void votersfun();

/**
* Voter get to see the results of pevious election
* @param[in] Nothing
* @return Maximum number of votes obtained by candidate in the election
* @note 
*/
int normal();

/**
* Voter who is wishing to enlist for upcoming election 
* @param[in] Voter who wished to enlist (yes or no)
* @param[in] Voter login username for adding voter to the contestant list
* @return Value depend on the situation
* @note Voter who already enlist can't enlist once again
*/
int enlist(char yesorno,char loginunenlist[30]);

/**
* Voters can cast their votes to a candidate  
* @param[in] Voter username who is going to vote
* @param[in] Candidate's username whom voter voted for 
* @return Value based on the whether voter who is voting for the first time or more than once
* @note Voter who already voted for more than once can't vote once more in the same election
*/
int polling(char loginunpoll[30],char tovotefor[30]);

#endif /* #ifndef __VOTER_H__ */

