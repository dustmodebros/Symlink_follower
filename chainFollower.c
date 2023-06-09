#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2){
        printf("Usage %s is ./chainFollower [symbolic link path]\n", argv[0]);
	return(2);
	}
    struct stat buf;
    char *out = argv[1];
    lstat(out, &buf);
    printf("\n%s\n", out);
    if (!S_ISLNK(buf.st_mode)){
    	printf("not a symlink\n");
	return 1;
    }
    while (S_ISLNK(buf.st_mode)){
	long value = readlink(out, out, 64);
	out[value] = '\0';
	int r = lstat(out, &buf);
	if (r != 0){
	    puts("error baby :(\n");
	    return 1;
            }
	printf("%s\n", out);
	}
    printf("\nfinal destination is: %s\n\n", out);
    return 0;
}
