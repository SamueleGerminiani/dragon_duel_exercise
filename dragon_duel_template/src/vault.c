/* Vault code: you do not need to read or modify this file :)
 *
 * The fragments are encrypted: they can only be decrypted with a key
 * computed from the result of the right battle.
 */
#include "vault.h"

#include <stdio.h>

#define FNV_START 2166136261u

static unsigned int mix(unsigned int h, unsigned int v) {
    for (int i = 0; i < 4; i++) {
        h ^= (v >> (8 * i)) & 0xff;
        h *= 16777619u;
    }
    return h;
}

static unsigned int next_byte(unsigned int *s) {
    *s ^= *s << 13;
    *s ^= *s >> 17;
    *s ^= *s << 5;
    return *s & 0xff;
}

/* Decrypts 'len' bytes of 'enc' into 'out' and returns its checksum */
static unsigned int decrypt(unsigned int key, const unsigned char *enc, int len, char *out) {
    unsigned int s = key;
    unsigned int h = FNV_START;
    for (int i = 0; i < len; i++) {
        out[i] = enc[i] ^ next_byte(&s);
        h = mix(h, (unsigned char)out[i]);
    }
    out[len] = '\0';
    return h;
}

static unsigned int fighter_key(unsigned int h, const Fighter *f) {
    h = mix(h, f->hp);
    h = mix(h, f->max_hp);
    h = mix(h, f->min_atk);
    return mix(h, f->max_atk);
}

/* Segfault keeps his treasure in memory and never shows it to anyone... */
static void segfault_hoard(unsigned int key) {
    static const unsigned char enc[] = {0xef, 0x6a, 0x4a, 0x77, 0xde, 0xf0, 0xbb, 0x83};
    char hoard[sizeof(enc) + 1];

    decrypt(mix(key, 0xD12A60), enc, sizeof(enc), hoard);

    printf("Segfault's hoard (fragment #4) hides in memory: use gdb!\n");
}

void vault_victory(const Fighter *hero, const Fighter *dragon, int rounds) {
    static const unsigned char enc[] = {0xce, 0x3b, 0x12, 0x78, 0x58, 0x52, 0x29, 0x6b};
    char fragment[sizeof(enc) + 1];

    unsigned int key = fighter_key(fighter_key(mix(FNV_START, rounds), hero), dragon);

    if (decrypt(key, enc, sizeof(enc), fragment) == 0xd5370c45u) {
        printf("\n*** Vault fragment #3 of 4: \"%s\" ***\n", fragment);
        segfault_hoard(key);
    }
}
