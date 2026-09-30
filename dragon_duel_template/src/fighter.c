#include "fighter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BAR_LEN 20

void fighter_init(Fighter *f, const char *name, int hp, int min_atk, int max_atk) {
    // Copy 'name' into f->name using 'strncpy' (at most NAME_LEN - 1 chars)
    // and make sure the string is terminated with '\0'


    // Set hp, max_hp, min_atk and max_atk

}

int fighter_attack(const Fighter *attacker, Fighter *defender) {
    // Compute a random damage in [min_atk, max_atk] using 'rand' and '%'
    int damage = 0;

    // Subtract the damage from the defender's hp (hp must not go below 0)


    return damage;
}

int fighter_is_alive(const Fighter *f) {
    // Return 1 if the fighter still has some hp, 0 otherwise
    return 1 /*change this*/;
}

/* A gift from your teacher: this function is already complete :) */
void fighter_print(const Fighter *f) {
    int filled = (f->max_hp > 0) ? (f->hp * BAR_LEN) / f->max_hp : 0;

    printf("%-12s [", f->name);
    for (int i = 0; i < BAR_LEN; ++i)
        printf("%c", i < filled ? '#' : '-');
    printf("] %3d/%d\n", f->hp, f->max_hp);
}
