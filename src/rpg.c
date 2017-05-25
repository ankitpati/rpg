/* rpg.c */
/* Random Password Generator */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t lrand(size_t rand, size_t lower, size_t upper)
{
    return lower > upper ? rand % (lower - upper + 1) + upper :
                           rand % (upper - lower + 1) + lower ;
}

unsigned char csprng()
{
#ifdef _WIN32

    static int seeded;

    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    return rand();

#else

#define RANDOM_DEVICE "/dev/urandom"
    static FILE *fp;
    unsigned char number;

    if (!fp && !(fp = fopen(RANDOM_DEVICE, "rb"))) {
        fprintf(stderr, "Could not open " RANDOM_DEVICE "\n");
        exit(5);
    }

    if (fread(&number, sizeof(number), 1, fp) != 1) {
        fprintf(stderr, "I/O error while reading from " RANDOM_DEVICE "\n");
        exit(5);
    }

    return number;

#endif
}

#define PRINTABLE_MIN      0x21
#define PRINTABLE_MAX      0x7e
#define DEFAULT_MIN_LENGTH    8
#define DEFAULT_MAX_LENGTH   16
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

    while (howmany--) {
        length = lrand(csprng(), min, max);
        while (length--) putchar(lrand(csprng(), PRINTABLE_MIN, PRINTABLE_MAX));
        putchar('\n');
    }

    return 0;
}
/* end of rpg.c */
