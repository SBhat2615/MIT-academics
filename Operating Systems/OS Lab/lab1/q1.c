#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int file, i = 0, j = 0;
    char s[100], c;
    if(argc != 3)         // argument count
    {
        printf("Insufficient Arguments\n");
        exit(1);
    }
    if((file = open(argv[2], O_RDONLY)) == -1)        // argument vector, argv[2] - 3rd arg(filename)
    {
        printf("File not found\n");
        exit(1);
    }
    while((read(file, &c, 1)) > 0)
    {
        if(c != '\n')
        {
            s[i] = c;
            i++;
        }
        else
        {
            j++;
            s[i] = '\0';
            i = 0;
            if(strstr(s, argv[1]) != NULL)          // man strstr (Examples)
                printf("Line:%d '%s' \n", j, s);
        }
    }
    exit(0);
}