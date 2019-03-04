#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define HIDWORD(_qw)    ((uint32_t)(((_qw) >> 32) & 0xffffffff))
//#define SAR(x, y)    ( (x) / pow(2, (y)) )
#define SAR(x, y)    ( (x) >> (y) )

// https://stackoverflow.com/a/2463888
/*int64_t SAR(int64_t x, int64_t n) {
    if (x < 0 && n > 0)
        return x >> n | ~(~0U >> n);
    else
        return x >> n;
}*/

int64_t operation(int64_t rcx) {
	return (rcx - ((SAR(HIDWORD(rcx * 0xea0ea0eb) + rcx, 0x6)) - (SAR(rcx, 0x1f))) * 0x46);// + 0x30
}
/*
uint8_t enc_char(char pt_current, char ct_previous) {
    uint64_t rcx = (ct_previous & 0xff) * (pt_current + 0xc) + 0x11;
    return rcx / 70  + 0x30 ;//(rcx - ((SAR(HIDWORD(rcx * 0xea0ea0eb) + rcx, 0x6)) - (SAR(rcx, 0x1f))) * 0x46) + 0x30;
}



int main()
{
    int x = enc_char('C', 0x48);
    printf("Hello World %c (%x)\n", x, x);

    return 0;
}
*/

int main()
{
    int x = operation(1000);
    printf("operation %c (%x)\n", x, x);

    return 0;
}