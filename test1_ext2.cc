#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

// detect the occurence of english character + punctuation
bool normal_eng(const char s[], size_t n)
{
    for (size_t j = 0; j < n; j++) {
        if (s[j] < '!' || s[j] > '~')
            return false;
    }
    return true;
}

bool normal_eng_vec(const char s[], size_t n)
{
    size_t k = n / 8;
    for (size_t i = 0; i < k; i++, s += 8) {
        uint64_t *chunk = (uint64_t *) s;
        uint64_t lower = *chunk + PACKED_BYTE(128 - '!' + 0);
        uint64_t upper = *chunk + PACKED_BYTE(128 - '~' + -1);
        uint64_t res = ((lower ^ upper) & PACKED_BYTE(0x80));
        // printf("res = %lx\n", res);
        if (res != PACKED_BYTE(0x80))
            return false;
    }

    k = n % 8;
    if (k)
        return normal_eng(s, k);

    return true;
}

int main()
{
    const char s[] = {'A', 'b', '_', '!', '[', '^', 'B', 'b', 'C', '\0'};
    // const char s[] = {'A', 'B', 'b', 'c', 'D', 'E', 'f', 'g', 'H', '\0'};

    printf("input: %s\n", s);
    if (normal_eng_vec(s, 9))
        printf("all char are valid english char + punctuation\n");
    else
        printf("not valid english char + punctuation\n");

    return 0;
}
