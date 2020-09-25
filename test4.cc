#include <stdint.h>
#include <stdio.h>

#define M ((uint64_t)(UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1))

bool divisible(uint32_t n)
{
    return n * M <= (M >> 1);
}

int main()
{
    for (int i = 0; i < 100; i++) {
        int res = divisible(i);
        printf("i=%d res=%d\n", i, res);
        printf("i*M=%lu\n", i * M);
    }

    return 0;
}
