#include <stdio.h>
#include <stdint.h>

uint32_t    htonf(float f)
{
    uint32_t    p;
    uint32_t    sign = 0;

    if (f < 0) {
        sign++;
        f = -f;
    }

    p = ((((uint32_t)f) & 0x7fff) << 16) | (sign << 31);
    p |= (uint32_t)(((f - (int)f) * 65536.0f)) & 0xffff;

    return p;
}

float       ntohf(uint32_t p)
{
    float   f;

    f = ((p >> 16) & 0x7fff);
    f += (p & 0xffff) / 65536.0f;

    if (((p >> 31) & 0x1) == 0x1)
        f = -f;
    return f;
}

int     main()
{
    float       f = 3.1415926, f2;
    uint32_t    netf;

    netf = htonf(f);
    f2 = ntohf(netf);

    printf("Original: %f\n", f);
    printf("Network: 0x%08X\n", netf);
    printf("Unpacked: %f\n", f2);
    return (0);
}