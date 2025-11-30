// main.c
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// ---------- FLAG STORAGE ----------

// Flag 1 is intentionally easy to spot in the binary
static const char *flag1 = "FLAG{easy_strings_win}";

// Flags 2–5 are XOR-encoded so they don't appear as cleartext
static const uint8_t enc_flag2[] = {
    113, 123, 118, 112, 76, 79, 7, 69, 104, 94, 68, 104, 89, 88,
    67, 104, 69, 82, 86, 91, 104, 84, 69, 78, 71, 67, 88, 74
}; // "FLAG{x0r_is_not_real_crypto}" ^ 0x37
static const uint8_t key_flag2 = 0x37;

static const uint8_t enc_flag3[] = {
    19, 25, 20, 18, 46, 54, 58, 59, 33, 39, 58, 57, 10,
    51, 57, 58, 34, 10, 60, 38, 10, 52, 39, 33, 40
}; // "FLAG{control_flow_is_art}" ^ 0x55
static const uint8_t key_flag3 = 0x55;

static const uint8_t enc_flag4[] = {
    84, 94, 83, 85, 105, 122, 115, 97, 122, 77, 127, 119,
    77, 123, 116, 77, 107, 125, 103, 77, 113, 115, 124, 111
}; // "FLAG{hash_me_if_you_can}" ^ 0x12
static const uint8_t key_flag4 = 0x12;

static const uint8_t enc_flag5[] = {
    44, 38, 43, 45, 17, 19, 5, 31, 53, 8, 15, 11,
    30, 53, 30, 2, 15, 53, 8, 3, 4, 11, 24, 19, 23
}; // "FLAG{you_beat_the_binary}" ^ 0x6A
static const uint8_t key_flag5 = 0x6A;


// ---------- UTILS ----------

static void strip_newline(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    if (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
    }
}

static void decode_and_print(const uint8_t *enc, size_t len, uint8_t key) {
    char buf[64];

    if (len >= sizeof(buf)) {
        printf("Internal error (flag too long)\n");
        return;
    }

    for (size_t i = 0; i < len; i++) {
        buf[i] = (char)(enc[i] ^ key);
    }
    buf[len] = '\0';

    printf("%s\n", buf);
}

// Simple custom hash for one of the challenges
static uint32_t simple_hash(const char *s) {
    uint32_t h = 0x12345678u;

    while (*s) {
        h = (h ^ (uint8_t)(*s)) * 0x45D9F3Bu;
        s++;
    }
    return h;
}


// ---------- CHALLENGES ----------

static void challenge1(void) {
    char buf[32];

    printf("\n[Challenge 1] Warmup PIN\n");
    printf("Enter the 4-digit PIN: ");

    if (!fgets(buf, sizeof(buf), stdin)) {
        return;
    }
    strip_newline(buf);

    // PIN = 0420 (kept simple for RE)
    if (strcmp(buf, "0420") == 0) {
        printf("Correct! Flag 1:\n%s\n", flag1);
    } else {
        printf("Nope.\n");
    }
}

static void challenge2(void) {
    char buf[64];

    printf("\n[Challenge 2] Password Check\n");
    printf("Enter the secret password: ");

    if (!fgets(buf, sizeof(buf), stdin)) {
        return;
    }
    strip_newline(buf);

    // Expected string is "reverse_me"
    if (strcmp(buf, "reverse_me") == 0) {
        printf("Nice. Flag 2:\n");
        decode_and_print(enc_flag2, sizeof(enc_flag2), key_flag2);
    } else {
        printf("Wrong password.\n");
    }
}

static void challenge3(void) {
    char line[128];
    int a, b, c;

    printf("\n[Challenge 3] Little math puzzle\n");
    printf("Enter three integers (a b c): ");

    if (!fgets(line, sizeof(line), stdin)) {
        return;
    }

    if (sscanf(line, "%d %d %d", &a, &b, &c) != 3) {
        printf("Bad input.\n");
        return;
    }

    // Conditions chosen to be easy to see in Ghidra:
    // a + b + c  = 42
    // a*a + b*b + c*c = 666
    // a * b * c  = 420
    long sum = (long)a + b + c;
    long squares = (long)a * a + (long)b * b + (long)c * c;
    long prod = (long)a * b * c;

    if (sum == 42 && squares == 666 && prod == 420) {
        printf("You solved it. Flag 3:\n");
        decode_and_print(enc_flag3, sizeof(enc_flag3), key_flag3);
    } else {
        printf("Close, but not correct.\n");
    }
}

static void challenge4(void) {
    char buf[64];

    printf("\n[Challenge 4] Hash gate\n");
    printf("Enter the magic word: ");

    if (!fgets(buf, sizeof(buf), stdin)) {
        return;
    }
    strip_newline(buf);

    // Precomputed simple_hash("ghidra_is_cool") = 409122216
    const uint32_t target = 409122216u;
    uint32_t h = simple_hash(buf);

    if (h == target) {
        printf("Hash matched. Flag 4:\n");
        decode_and_print(enc_flag4, sizeof(enc_flag4), key_flag4);
    } else {
        printf("Hash mismatch (0x%08X).\n", h);
    }
}

static void challenge5(void) {
    char buf[64];

    printf("\n[Challenge 5] Final phrase\n");
    printf("Enter the final phrase: ");

    if (!fgets(buf, sizeof(buf), stdin)) {
        return;
    }
    strip_newline(buf);

    // Expected phrase
    if (strcmp(buf, "i_will_reverse_anything") == 0) {
        printf("You cleared them all. Flag 5:\n");
        decode_and_print(enc_flag5, sizeof(enc_flag5), key_flag5);
    } else {
        printf("Not the phrase I was looking for.\n");
    }
}


// ---------- MAIN MENU ----------

static void print_menu(void) {
    printf("\n==== Flag Hunt Menu ====\n");
    printf("1) Challenge 1 - PIN\n");
    printf("2) Challenge 2 - Password\n");
    printf("3) Challenge 3 - Math puzzle\n");
    printf("4) Challenge 4 - Hash word\n");
    printf("5) Challenge 5 - Final phrase\n");
    printf("0) Exit\n");
    printf("> ");
}

int main(void) {
    char line[32];
    int choice;

    printf("Welcome to Flag Hunt!\n");
    printf("Solve the challenges or load me in Ghidra. Your call.\n");

    while (1) {
        print_menu();

        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid choice.\n");
            continue;
        }

        switch (choice) {
            case 1: challenge1(); break;
            case 2: challenge2(); break;
            case 3: challenge3(); break;
            case 4: challenge4(); break;
            case 5: challenge5(); break;
            case 0:
                printf("Goodbye.\n");
                return 0;
            default:
                printf("Unknown option.\n");
        }
    }

    return 0;
}
