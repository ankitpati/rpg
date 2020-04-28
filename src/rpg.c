/* rpg.c */
/* Random Password Generator */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t bitcount(size_t num)
{
    size_t c;
    for (c = 0; num; ++c) num >>= 1;
    return c;
}

size_t lrand(size_t rand, size_t lower, size_t upper)
{
    return rand % (upper - lower + 1) + lower;
}

#define RANDOM_DEVICE "/dev/urandom"
size_t csprng(size_t bits)
{
#ifdef _WIN32

    static int seeded;

    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    return rand();

#else

    static FILE *fp;
    static size_t bits_left, buf;
    size_t ret, shift;

    if (!fp && !(fp = fopen(RANDOM_DEVICE, "rb"))) {
        fprintf(stderr, "Could not open " RANDOM_DEVICE "\n");
        exit(5);
    }

    if (bits > 8*sizeof(buf)) bits = 8*sizeof(buf);

    ret = 0;

    if (bits_left < bits) {
        ret = buf;
        bits -= bits_left;
        ret <<= bits;

        if (fread(&buf, sizeof(buf), 1, fp) != 1) {
            fprintf(stderr, "I/O error while reading from " RANDOM_DEVICE "\n");
            exit(5);
        }
        bits_left = 8*sizeof(buf);
    }

    shift = 8*sizeof(buf) - bits;
    ret |= buf << shift >> shift;
    buf >>= bits;
    bits_left -= bits;

    return ret;

#endif
}

#define PRINTABLE_MIN      0x21
#define PRINTABLE_MAX      0x7e
#define DEFAULT_MIN_LENGTH    8
#define DEFAULT_MAX_LENGTH   16
#define SWAP(a, b) do (a) ^= (b), (b) ^= (a), (a) ^= (b); while (0)
int main(int argc, char **argv)
{
    size_t min, max, howmany, length;

    howmany = 1;

    switch (argc) {
    case 1:
        min = DEFAULT_MIN_LENGTH;
        max = DEFAULT_MAX_LENGTH;
        break;

    case 2:
        min = max = strtoull(argv[1], NULL, 10);
        break;

    case 3:
        min = strtoull(argv[1], NULL, 10);
        max = strtoull(argv[2], NULL, 10);
        break;

    case 4:
        min = strtoull(argv[1], NULL, 10);
        max = strtoull(argv[2], NULL, 10);
        howmany = strtoull(argv[3], NULL, 10);
        break;

    default:
        fprintf(stderr, "Usage:\n\trpg [min-length] max-length [how-many]\n");
        exit(1);
        break;
    }

    if (min > max) SWAP(min, max);

    while (howmany--) {
        length = lrand(csprng(bitcount(max - min)), min, max);
        while (length--)
            putchar(
                lrand(
                    csprng(bitcount(PRINTABLE_MAX - PRINTABLE_MIN)),
                    PRINTABLE_MIN, PRINTABLE_MAX
                )
            );

        putchar('\n');
    }

    return 0;
}
/* end of rpg.c */
