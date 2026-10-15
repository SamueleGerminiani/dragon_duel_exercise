#!/bin/bash
# The vault: it opens only with the 4 fragments hidden in the lab exercises.
#   Fragment #1: the demo (perm_generator)
#   Fragment #2: Mission 1 (pascal_triangle)
#   Fragment #3: Mission 2 (Dragon Duel)
#   Fragment #4: Segfault's hoard (only a debugger can see it)

cd "$(dirname "$0")" || exit 1

echo "The vault is locked: it needs 4 fragments."
password=""
for i in 1 2 3 4; do
    read -r -p "Fragment #$i: " fragment
    password="$password $fragment"
done

# Ignore quotes, extra spaces and uppercase letters
password=$(echo "$password" | tr -d '"' | tr '[:upper:]' '[:lower:]' | xargs)

treasure=$(openssl enc -d -aes-256-cbc -pbkdf2 -iter 100000 -a \
    -in treasure.enc -pass "pass:$password" 2>/dev/null)

if [ "$(echo "$treasure" | head -n 1)" = "VAULT-OK" ]; then
    echo "$treasure" | tail -n +2
else
    echo "The vault does not move... check your fragments (and their order)!"
fi
