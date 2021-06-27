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

void sendFile(FILE *fp, int sockfd){
    char data[256] = {0};
    while(fgets(data, 256, fp)!=NULL){
        if(send(sockfd, data, sizeof(data), 0)== -1){
            perror("[-] Error in sendung data");
            exit(1);
        }
        bzero(data, 256);
    }
}
int main(int argc, char *argv[]){
    char *ip = "127.0.0.1";
    int port = 8080;
    int sockfd, newsockfd, portNO, n;    
    char buffer[256];
    socklen_t addr_size;
    struct sockaddr_in server_addr, client_addr;
    FILE *fp;
    char *fileName = "paczka1.txt";

    printf("[STARTING] Server has been started\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("[ERROR] Socket opening error!!");
        exit(1);
    }  
    printf("[SUCCESS] Socket runned\n");

    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    n = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(n < 0){
        perror("[ERROR] Bind error!!!");
        exit(1);
    }
    printf("[SUCCESS] Bind OK\n");
    n = listen(sockfd, 5);
    if(n == 0){
        printf("[INFO] Listening...\n");
    }else{
        perror("[-]Error in Binding");
         exit(1);
    }    
    addr_size = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);
    printf("Connection accepted :)");
    n = read(newsockfd, buffer, 255);
    if(n < 0){
        perror("[ERROR] Error reading from socket");
        exit(1);
    }
    printf("Here is the message: %s\n", fp);
    n = read(newsockfd, "I got your message", 18);
    if(n < 0){
        perror("[ERROR] Error writing to socket");
    }
    if(argc == 2){
        fileName = argv[1];
        fp = fopen(fileName, "r");
    }else {
        fp = stdin;
    }
    if(fp == NULL){
        fprintf(stderr, "[ERROR] Error while opening the file\n");
        return 1;
    }
    sendFile(fp,sockfd);
    printf("[SUCCESS] Transfer file complete\n");
    printf("[CLOSING] Closing the connection\n");
    fclose(sockfd);
    return 0;
}