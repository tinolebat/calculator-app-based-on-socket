/*
Command line argument:
filename server_ipaddress portnumber

argv[0] filename
argv[1] server_ipaddress
argv[2] port number
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){

    int sockfd, port_number, n;
      

    struct sockaddr_in serv_addr;
    struct hostent *server; //store informations about a host

    char buffer[255];

    if(argc < 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    port_number = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error on opening socker");
    }

    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr, "Error , no such host");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server -> h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port_number);

    // Connection
    if(connect(sockfd, (struct sockaddr *) &serv_addr , sizeof(serv_addr))<0){
        error("connection Failed");
    }

    // calculator
    int num1, num2, answer, choice;
/*provide for numb 1*/
    S : bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if(n<0){
        error("Error on read");   
    }
    printf("Server: %s", buffer);
    scanf("%d", &num1);
    write(sockfd, &num1,sizeof(int));

/*provide for numb 2*/
    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if(n<0){
        error("Error on read");   
    }
    printf("Server: %s", buffer);
    scanf("%d", &num2);
    write(sockfd, &num2,sizeof(int));

/*provide for operator*/
    bzero(buffer, 255);
    n = read(sockfd, buffer, 255);
    if(n<0){
        error("Error on read");   
    }
    printf("Server: %s", buffer);
    scanf("%d", &choice);
    write(sockfd, &choice,sizeof(int));

    if(choice == 5){
        goto Q;
    }

/*Answer*/
    
    read(sockfd,&answer, sizeof(int));
    if(n<0){
        error("Error on read");   
    }
    printf("Server: The answer is %d \n", answer);

    if(choice != 5){
        goto S;
    }


    Q:  printf("You selected 5 to exit\n");
    close(sockfd);
    return 0;
}

/*
while(1){
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));

        n = read(sockfd, buffer, 255);
        if(n<0){
            error("Error on read");
            
        }
        printf("Server: %s", buffer);

        int i = strncmp("Bye", buffer, 3);
        if(i == 0)
        break;

    }
*/