/* rpg-nowaste.c */
/* Random Password Generator - No Waste Edition */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

uint32_t bitcount(uint32_t num)
{
    uint32_t c;
    for (c = 0; num; ++c) num >>= 1;
    return c;
}

static char *random_device = "/dev/urandom";
uint32_t csprng(uint32_t bits)
{
    static FILE *fp;
    static uint32_t bits_left, buf;
    uint32_t ret, shift;

    if (!fp && !(fp = fopen(random_device, "rb"))) {
        fprintf(stderr, "Could not open %s\n", random_device);
        exit(5);
    }

    if (bits > 8*sizeof(buf)) bits = 8*sizeof(buf);

    ret = 0;

    if (bits_left < bits) {
        shift = 8*sizeof(buf) - bits_left;
        ret = buf >> shift;
        bits -= bits_left;
        ret <<= bits;

        if (fread(&buf, sizeof(buf), 1, fp) != 1) {
            fprintf(stderr, "I/O error while reading from %s\n", random_device);
            exit(5);
        }
        buf = htonl(buf);
        bits_left = 8*sizeof(buf);
    }

    shift = 8*sizeof(buf) - bits;
    ret |= buf >> shift;
    buf <<= bits;
    bits_left -= bits;

    return ret;
}

static char charset[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+_";

#define DEFAULT_LENGTH 12
int main(int argc, char **argv)
{
    uint32_t length;

    switch (argc) {
    case 1:
        length = DEFAULT_LENGTH;
        break;

    case 2:
        length = strtoull(argv[1], NULL, 10);
        break;

    case 3:
        length = strtoull(argv[1], NULL, 10);
        random_device = argv[2];
        break;

    default:
        fprintf(stderr, "Usage:\n\trpg-nowaste [length] [random-file]\n");
        exit(1);
        break;
    }

    while (length--) putchar(charset[csprng(bitcount(strlen(charset) - 1))]);

    putchar('\n');
    return 0;
}
/* end of rpg.c */
