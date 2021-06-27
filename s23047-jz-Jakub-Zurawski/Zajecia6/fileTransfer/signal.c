#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void signalHandler(int);

int main(){
    int x=1;
    while(x!=0){
        signal(SIGINT,&signalHandler);
        printf("podaj 0 zero zeby wyjsc \t");
        scanf("%d",&x);
    }
    return 0;
}
 void signalHandler(int s){
    printf("błąd nie wyjdziesz %d\n",s);
 }