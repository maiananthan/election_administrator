/**
* @file admin.h
*
*/

#ifndef __ADMIN_H__
#define __ADMIN_H__

/**
* Entering into the adminfun function which controlls admin's function
* @param[in] Nothing
* @return Nothing
* @note
*/
void adminfun();

/**
* Adding the voter into the database
* @param[in] LOGIN username & LOGIN password
* @return confirmation status of adding the voter into database
* @note
*/
int addvoter(char loginunarg[],char loginpwarg[]);

/**
* Remove the voter from the database
* @param[in] LOGIN username which is going to be removed
* @return confirmation status of removing the voter into database
* @note
*/
int removevoter(char loginunarg[]);

/**
* Changing the current state to the next the next state
* @param[in] yes or no
* @return Returning the state status after the state changed 
* @note
*/
int cstate(char yesorno);

#endif /* #ifndef __ADMIN_H__ */
