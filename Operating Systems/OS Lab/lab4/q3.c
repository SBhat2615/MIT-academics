//#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
//#include <inttypes.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Insufficient arguments\n");
        return 1;
    }

    char newpath[100] = "file_out.txt";

    struct stat sb1;
    int ret = stat(argv[1], &sb1);
    if (ret)
    {
        perror("stat");
        return 1;
    }
    system("ls -i");
    printf("Number of hard links before:%hu\n", sb1.st_nlink);
    

    ret = link(argv[1], newpath);
    printf("\nNew Hard link created.\n");
    struct stat sb2;
    ret = stat(argv[1], &sb2);
    if (ret)
    {
        perror("stat");
        return 1;
    }
    system("ls -i");
    printf("Number of hard links:%hu\n", sb2.st_nlink);
    printf("\nNEW PATH: %s\n", newpath);
    system("cat file_out.txt");
    

    ret = unlink(argv[1]);
    struct stat sb3;
    ret = stat(newpath, &sb3);
    if (ret)
    {
        perror("stat");
        return 1;
    }
    printf("\nUnlinking new Hard link\n");
    printf("Number of hard links after:%hu\n", sb3.st_nlink);
    system("ls -i");
}