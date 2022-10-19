#include "msgQueue.h"

int main(int argc, char const *argv[])
{
    int running = 1;
    struct my_msg_st some_data;
    int msgid;
    int num;
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error%d\n", errno);
        exit(EXIT_FAILURE);
    }
    printf("Enter -1 to quit\n");
    while (running)
    {
        printf("Enter a Number: \n");
        scanf("%d", &num);
        some_data.my_msg_type = 1;
        some_data.msg = num;
        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (num == -1)
            running = 0;
    }
    exit(EXIT_SUCCESS);
}