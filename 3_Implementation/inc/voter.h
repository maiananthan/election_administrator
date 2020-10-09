/**
* @file voter.h
*
*/

#ifndef __VOTER_H__
#define __VOTER_H__

/**
* Voter id doing his job
* @param[in] input according to the current state
* @return confirmation if yes
* @note Notes
*/
void votersfun();
int normal();
int enlist(char yesorno,char loginunenlist[30]);
int polling(char loginunpoll[30],char tovotefor[30]);
#endif /* #ifndef __VOTER_H__ */
