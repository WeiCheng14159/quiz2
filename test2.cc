#include <stdint.h>
#include <stdio.h>

using namespace std;

uint8_t hexchar2val(uint8_t in)
{
    const uint8_t letter = in & 0x40;
    const uint8_t shift = (letter >> 3) | (letter >> 6);
    return (in + shift) & 0xf;
}

int main()
{
    char in = '0';
    char res = hexchar2val(in);
    printf("%c\n", res);

    return 0;
}
