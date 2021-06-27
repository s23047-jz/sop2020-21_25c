#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include <arpa/inet.h>

void writeFile(int sockfd){
    int n; 
    FILE *fp;
    char *filename = "paczka2.txt";
    char buffer[256];
    fp = fopen(filename, "w");
    if(fp==NULL){
        perror("[-]Error in creating file.");
        exit(1);
    }
    while(1){
        n = recv(sockfd, buffer, 256, 0);
        if(n<=0){
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, 256);
    }
    return;    
}
int main(int argc, char *argv[]){
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("[ERROR] Socket error!!\n");
        exit(1);
    }  
    printf("[OK] Socket good\n");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(e == -1){
        perror("[ERROR] Connecting error!!!\n");
        exit(1);
    }
    printf("[SUCCESS] Connected to the server.\n");
    writeFile(e);
    return 0;
}