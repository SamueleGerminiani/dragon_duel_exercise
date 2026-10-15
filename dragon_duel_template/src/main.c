#include <stdio.h>
#include <stdlib.h>

#include "fighter.h"
#include "vault.h"

int main(int argc, char *argv[]) {

    // Check command line input arguments using 'argc'
    if (argc != 3) {
        printf("Usage: %s heroName seed\n", argv[0]);
        return 0;
    }

    // Convert the second command-line argument (argv[2]) to an integer.
    // This integer is the seed of the random number generator.
    int seed;

    // Initialize the random number generator with the seed using 'srand'


    // Create the hero, named argv[1] (100 hp, attack 8-16),
    // and the dragon "Segfault" (120 hp, attack 4-18) using 'fighter_init'
    Fighter hero, dragon;


    printf("%s enters the cave... Segfault the dragon wakes up!\n\n", argv[1]);

    int round = 1;
    // Keep fighting while both fighters are alive using 'fighter_is_alive'
    while (0 /*change this*/) {
        printf("--- Round %d ---\n", round);

        // The hero attacks the dragon using 'fighter_attack'
        // printf("%s hits %s for %d damage!\n", ...);

        // If the dragon is still alive, it strikes back
        // printf("%s breathes fire on %s for %d damage!\n", ...);

        // Print the status of both fighters using 'fighter_print'

        ++round;
    }

    // Announce the winner
    if (1 /*change this*/) {
        // printf("\nVictory! %s slayed the dragon in %d rounds!\n", ...);

        // Already done: checks your victory and reveals a vault fragment (do not remove)
        vault_victory(&hero, &dragon, round - 1);
    } else {
        // printf("\nGame over... the dragon had %s for dinner.\n", ...);
    }

    return 0;
}
