#ifndef _FIGHTER_HH
#define _FIGHTER_HH

#define NAME_LEN 32

/* A fighter: our brave hero or the terrible dragon */
typedef struct {
    char name[NAME_LEN];
    int hp;      // current health points
    int max_hp;  // health points at the start of the fight
    int min_atk; // minimum damage of a hit
    int max_atk; // maximum damage of a hit
} Fighter;

/* fighter_init fills the fields of 'f'.
 * At the beginning of the fight, hp is equal to max_hp.
 */
void fighter_init(Fighter *f, const char *name, int hp, int min_atk, int max_atk);

/* fighter_attack makes 'attacker' hit 'defender' with a random damage
 * in the range [min_atk, max_atk]. The hp of the defender never go below 0.
 * fighter_attack returns the damage dealt.
 */
int fighter_attack(const Fighter *attacker, Fighter *defender);

/* fighter_is_alive returns 1 if the fighter has hp > 0, 0 otherwise. */
int fighter_is_alive(const Fighter *f);

/* fighter_print prints the name and a health bar, for example:
 * Link         [##########----------]  50/100
 */
void fighter_print(const Fighter *f);

#endif
