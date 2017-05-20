/* rpg.c */
/* Random Password Generator */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LENGTH_LOWER  8
#define DEFAULT_LENGTH_UPPER 16

#define ASCII_READABLE_LOWER 0x21
#define ASCII_READABLE_UPPER 0x7e

size_t lrand(size_t rand, size_t lower, size_t upper)
{
    return rand % (upper - lower + 1) + lower;
}

size_t csprng()
{
    static FILE *fp;
    size_t number;

    if (!fp && !(fp = fopen("/dev/urandom", "rb"))) {
        fprintf(stderr, "Could not open /dev/urandom.\n");
        exit(5);
    }

    if (fread(&number, sizeof(number), 1, fp) != 1) {
        fprintf(stderr, "I/O error while reading from /dev/urandom.\n");
        exit(5);
    }

    return number;
}

int main(int argc, char **argv)
{
    size_t length;

    length = argc == 2 ? strtoull(argv[1], NULL, 10) :
                    lrand(csprng(), DEFAULT_LENGTH_LOWER, DEFAULT_LENGTH_UPPER);

    while (length--)
        putchar(lrand(csprng(), ASCII_READABLE_LOWER, ASCII_READABLE_UPPER));

    putchar('\n');

    return 0;
}
/* end of rpg.c */
