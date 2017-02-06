/***********************************************************************
 * Program:
 *    Lab RockClient, Rock/Paper/Scissors with Sockets - Client Code
 *    Brother Jones, CS 460
 * Author:
 *    Brady Field
 * Summary:
 *    Client side of RPS
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    int ch;
    do
    {
       printf("(r)ock, (p)aper, (s)cissors, (q)uit: ");
       bzero(buffer,256);
       
       fgets(buffer,2,stdin);
       switch(buffer[0])
       {
          case 'r':
              printf("Rock\n");
              break;
          case 'p':
              printf("Paper\n");
              break;
          case 's':
              printf("Scissors\n");
              break;
          case 'q':
              break;
          default:
              printf("ERROR: unknown command\n");
              break;
       }
       n = write(sockfd,buffer,strlen(buffer));
       // clear input buffer
       while ((ch = getchar()) != '\n' && ch != EOF);
       if (n < 0) 
          error("ERROR writing to socket");
       bzero(buffer,256);
       n = read(sockfd,buffer,255);
       if (n < 0) 
          error("ERROR reading from socket");
       switch(buffer[0])
       {
          case 'w':
             printf("You win\n");
             break;
          case 'l':
             printf("You lose\n",buffer);
             break;
          case 't':
             printf("tie\n",buffer);
             break;
          case 'q':
             printf("Player ended game\nThanks for playing\n",buffer);
             break;
          default:
             printf("ERROR: I don't know what happened\n",buffer);
             break;
       }
       
       
    } while (buffer[0] != 'q');
    close(sockfd);
    return 0;
}
