#!/bin/bash
# The vault: it opens only with the 4 fragments hidden in the lab exercises.
#   Fragment #1: the demo (perm_generator)
#   Fragment #2: Mission 1 (pascal_triangle)
#   Fragment #3: Mission 2 (Dragon Duel)
#   Fragment #4: Segfault's hoard (only a debugger can see it)
# Fragments #2, #3 and #4 are bound to the user and machine that found them.

cd "$(dirname "$0")" || exit 1
export LC_ALL=C

# Same code as bind_to_user() in the exercises: FNV-1a of "word:user@host"
code_for() {
    local id="$1:${USER:-unknown}@$(uname -n)"
    local h=2166136261 c i
    for ((i = 0; i < ${#id}; i++)); do
        printf -v c '%d' "'${id:i:1}"
        h=$(( ((h ^ c) * 16777619) & 0xFFFFFFFF ))
    done
    printf '%04X' $(( h & 0xFFFF ))
}

echo "The vault is locked: it needs 4 fragments."
password=""
for i in 1 2 3 4; do
    read -r -p "Fragment #$i: " fragment
    # Ignore quotes, extra spaces and uppercase letters
    fragment=$(echo "$fragment" | tr -d '"' | tr '[:upper:]' '[:lower:]' | xargs)
    word=${fragment%%-*}
    if [ "$i" -gt 1 ] && [ "$fragment" != "$word-$(code_for "$word" | tr '[:upper:]' '[:lower:]')" ]; then
        echo "Fragment #$i was not found by you on this machine: the vault does not move."
        exit 1
    fi
    password="$password $word"
done
password=$(echo "$password" | xargs)

treasure=$(openssl enc -d -aes-256-cbc -pbkdf2 -iter 100000 -a \
    -in treasure.enc -pass "pass:$password" 2>/dev/null)

if [ "$(echo "$treasure" | head -n 1)" = "VAULT-OK" ]; then
    echo "$treasure" | tail -n +2
else
    echo "The vault does not move... check your fragments (and their order)!"
fi
