#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct stat buf;
    char *out;
    char *str = argv[1];
    lstat(str, &buf);
    out = str;
    printf("\n%s\n", out);
    if (!S_ISLNK(buf.st_mode)){
    	printf("not a symlink\n");
	return 1;
    }
    while (S_ISLNK(buf.st_mode)){
	//puts("1");
	//puts("It's a soft link.");
    	//printf("The inode number is %lu.\n", buf.st_ino);
	//printf("attempting to read the link %s, putting result into buffer that currently contains %s, with size %d\n", str, out, 64);
	int value = readlink(out, out, 64);
	out[value] = '\0';
	//printf("going around again, out is %s", out);
	int r = lstat(out, &buf);
	if (r != 0){
	    puts("error baby :(\n");
	    return 1;
            }
	//printf("\n\n\nbuf inode is %ld\n\n\n", buf.st_ino);
	//printf("\nbuf mode is %u\n\n\n", buf.st_mode);
	printf("%s\n", out);
	}
    printf("\nfinal destination is: %s\n\n", out);
    return 0;
}