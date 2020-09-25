#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// byte-by-byte method
bool is_ascii_v1(const char str[], size_t size)
{
    if (size == 0)
        return false;
    for (size_t i = 0; i < size; i++) {
        printf("%x, ", (str[i] & 0x80));
        if (str[i] & 0x80) /* i.e. (unsigned) str[i] >= 128 */
            return false;
    }
    return true;
}

// vectorized version
bool is_ascii_v2(const char str[], size_t size)
{
    if (size == 0)
        return false;
    size_t i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

int main()
{
    const char s[] = {'A', 'b', '_', '!', '[', '^', 'B', 'b', 'C', '\0'};
    // const char s[] = {'A', 'B', 'b', 'c', 'D', 'E', 'f', 'g', 'H', '\0'};

    printf("input: %s\n", s);
    if (is_ascii_v2(s, 9))
        printf("all char are ascii\n");
    else
        printf("not all char are ascii\n");

    if (is_ascii_v1(s, 9))
        printf("all char are ascii\n");
    else
        printf("not all char are ascii\n");

    return 0;
}
