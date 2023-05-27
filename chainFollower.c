#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

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
	int value = readlink(out, out, 64);
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
