/*
 * LPC checksum calculation and placement program.
 * Adapted from the fix-checksum tool by Alessandro Rubini
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
    int i, fd;
    void *mapaddr;
    uint32_t sum=0, *data;

	/* usage: lpcsum BINARY */
    if (argc != 2) {
		fprintf(stderr, "%s: pass the filename of the binary\n", argv[0]);
		exit(1);
    }

	/* Open the binary file so we can mmap it later */
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
		fprintf(stderr, "%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		exit(1);
    }
	/* Map the binary file into memory using mmap (we need READ and WRITE) */
    mapaddr = mmap(0, 0x20, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapaddr == (typeof(mapaddr))-1) {
		fprintf(stderr, "%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		exit(1);
    }
	/* Sum up the first 7 entries of the table (32 bits each) */
    data = mapaddr;
    for (i = 0; i < 7; i++)
		sum += data[i];
	/* Place the negative of the sum in the 8th table entry */
    data[i] = -sum;
	printf("Checksum: %08x\n", sum);
	return 0;
}
