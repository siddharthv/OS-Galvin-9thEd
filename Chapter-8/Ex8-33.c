/* Ex8-33: Identify page number and offset given 32 bit VA and 4K page size
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        perror("insufficient args, usage: ./a.out <addr> \n");
        exit(-1);
    }

    const size_t PAGE_SZ = getpagesize();
    unsigned va = atoi(argv[1]);
    unsigned pn = va / PAGE_SZ;
    unsigned po = va % PAGE_SZ;

    printf("\n The address %d contains: \n", va);
    printf(" Page Number: %d \n", pn);
    printf(" Offset: %d \n", po);

    return 0;
}
