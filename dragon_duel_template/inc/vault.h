#ifndef _VAULT_HH
#define _VAULT_HH

#include "fighter.h"

/* Vault code: you do not need to read or modify this file :)
 *
 * vault_victory checks the result of the fight and, if the battle is the
 * right one, reveals a fragment of the vault password.
 */
void vault_victory(const Fighter *hero, const Fighter *dragon, int rounds);

#endif
