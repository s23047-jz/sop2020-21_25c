#define _POSIX_SOURCE
#include<signal.h>

void termination_handler(int signum){
    struct tempFile *fp;
    for(fp = tempFile_list; p; p = p->next){
        unlink(p->name);
    }
}
int main(void){
    struct sigaction new_action, old_action;

    new_action.sa_handler = termination_handler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;

    sigaction(SIGINT, NULL, &old_action);
    if(old_action.sa_handler != SIG_IGN){
        sigaction(SIGINT, &new_action, NULL)
    }
    sigaction(SIGHUP, NULL, &old_action);
    if(old_action.sa_handler != SIG_IGN){
        sigaction(SIGHUP, &new_action, NULL)
    }
    sigaction(SIGTERM, NULL, *old_action);
    if(old_action.sa_handler != SIG_IGN){
        sigaction(SIGTERM, &new_action, NULL)
    }
}