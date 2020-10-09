/**
* @file admin.h
*
*/

#ifndef __ADMIN_H__
#define __ADMIN_H__

/**
* Admin wishing to change the state
* @param[in] yes or no
* @return confirmation if yes
* @note Notes
*/

void adminfun();
int addvoter(char loginunarg[],char loginpwarg[]);
int removevoter(char loginunarg[]);
int cstate(char yesorno);
#endif /* #ifndef __ADMIN_H__ */
