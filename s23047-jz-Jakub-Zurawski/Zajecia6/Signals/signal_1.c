#define _POSIX_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void chatchSigint(int signum){
    installHandler();
    printf("Handler triggered. s = %d\n", signum);
}
void installHandler(void){
    struct sigaction setUp_Action;
    sigset_t blockMask;
    sigemptyset(&blockMask);

    setUp_Action.sa_handler = &chatchSigint;
    setUp_Action.sa_mask = blockMask;
    setUp_Action.sa_flags = 0;

    sigaction(SIGINT, &setUp_Action, NULL);
}
int main(){
    char x = '1';
    installHandler();
    while(x != 0){
        fflush(stdout);
        printf("Input 0 to end!: ");
        x = getchar();
    }
    return 0;
}