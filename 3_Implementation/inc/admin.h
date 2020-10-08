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

int admin(char yesorno);
int admin_add_voter(char loginun[],char loginpw[]);
int admin_remove_voter(char loginun[]);
#endif /* #ifndef __ANNOUNCE_H__ */
