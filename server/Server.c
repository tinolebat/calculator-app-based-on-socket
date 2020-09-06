#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr, "port number not provided. program terminated\n");
        exit(1);
    }

    int sockfd, newsockfd, port_number, n;
    char buffer[255];

    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error opening socker");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // Clear any data it refers to.

    port_number= atoi(argv[1]); //argv[1] contains the port number from cli input

    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr  = INADDR_ANY;
    serv_addr.sin_port = htons(port_number);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Binding failed");
    }

    listen(sockfd, 5); // 5: max limit of clients that can connect to the server

    client_len = sizeof(client_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len);
    if(newsockfd < 0){
        error("Error on Accpet");
    }
    
    // create a calculator
    int num1, num2, answer, choice;

/*Ask for numb 1*/
    S : n = write(newsockfd, "Enter number 1:", strlen("Enter number 1:"));
    if(n<0){
        error("when writing socket");
    }
    read(newsockfd, &num1, sizeof(int));
    printf("Client - number 1 is: %d\n", num1);

/*Ask for numb 2*/
    n = write(newsockfd, "Enter number 2:", strlen("Enter number 2:"));
    if(n<0){
        error("when writing socket for num2");
    }
    read(newsockfd, &num2, sizeof(int));
    printf("Client - number 2 is: %d\n", num2);

/*Ask for operation*/
    n = write(newsockfd, "Enter choice : \n1.Addition\n2.Subsctraction\n3.Multiplication\n4.Division\n5.Exit\n",strlen("Enter choice : \n1.Addition\n2.Subsctraction\n3.Multiplication\n4.Division\n5.Exit\n"));
    if(n<0){
        error("when writing choice");
    }
    read(newsockfd, &choice, sizeof(int));
    printf("Client - operator is: %d\n", choice);

    switch(choice){
        case 1:
            answer = num1 + num2;
            break;
        case 2:
            answer = num1 - num2;
            break;
        case 3:
            answer = num1 * num2;
            break;
        case 4:
            answer = num1 /  num2;
            break;
        case 5:
            goto Q;
            break;
    }

    write(newsockfd, &answer, sizeof(int));
    if(choice !=5){
        goto S;
    }


Q:  close(newsockfd);
    close(sockfd);
    return 0;
}

/*
while(1){
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255); // we store our data from the new socket descriptor to the buffer
        if(n<0){
            error("Error on reading");
        }
        printf("Client : %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if(n<0){
            error("Error on writing");
        }

        int i = strncmp("Bye", buffer, 3);
        if(i == 0)
        break;
    }

*/