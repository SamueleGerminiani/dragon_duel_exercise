/* Vault code: you do not need to read or modify this file :)
 *
 * The fragments are encrypted: they can only be decrypted with a key
 * computed from the result of the right battle.
 * The revealed fragments are bound to the current user and machine.
 */
#define _POSIX_C_SOURCE 200112L

#include "vault.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

/* Appends to 'word' a code bound to the current user and machine */
static void bind_to_user(char *out, size_t size, const char *word) {
    const char *user = getenv("USER");
    char host[256] = "";
    char id[600];

    if (user == NULL || user[0] == '\0')
        user = "unknown";
    if (gethostname(host, sizeof(host)) != 0 || host[0] == '\0')
        strcpy(host, "unknown");
    host[sizeof(host) - 1] = '\0';

    snprintf(id, sizeof(id), "%s:%s@%s", word, user, host);
    unsigned int h = FNV_START;
    for (const char *c = id; *c != '\0'; c++) {
        h ^= (unsigned char)*c;
        h *= 16777619u;
    }
    snprintf(out, size, "%s-%04X", word, h & 0xffff);
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
    char word[sizeof(enc) + 1];
    char hoard[32] = "";

    decrypt(mix(key, 0xD12A60), enc, sizeof(enc), word);
    bind_to_user(hoard, sizeof(hoard), word);

    printf("Segfault's hoard (fragment #4) hides in memory: use gdb!\n");
}

void vault_victory(const Fighter *hero, const Fighter *dragon, int rounds) {
    static const unsigned char enc[] = {0xce, 0x3b, 0x12, 0x78, 0x58, 0x52, 0x29, 0x6b};
    char fragment[sizeof(enc) + 1];

    unsigned int key = fighter_key(fighter_key(mix(FNV_START, rounds), hero), dragon);

    if (decrypt(key, enc, sizeof(enc), fragment) == 0xd5370c45u) {
        char bound[32];
        bind_to_user(bound, sizeof(bound), fragment);
        printf("\n*** Vault fragment #3 of 4: \"%s\" ***\n", bound);
        segfault_hoard(key);
    }
}
