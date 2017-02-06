/***********************************************************************
 * Program:
 *    Lab RPSPclient, RPSP Rock/Paper/Scissors Protocol - Client Code
 *    Brother Jones, CS 460
 * Author:
 *    Brady Field
 * Summary:
 *    Client side of RPS
 ************************************************************************
 * Changes:
 * - added error handling
 * - added comments to parts of running client
 * - changed to match class protocol
 *
 *
 *
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
    /*connect to server*/
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    int ch;
    printf("Waiting for Player\n");
    n = read(sockfd,buffer,255);
    printf("Game Starting\n");
    do
    {
       printf("(r)ock, (p)aper, (s)cissors, (q)uit: ");
       bzero(buffer,256);
       /* get player move */
       fgets(buffer,2,stdin);
       switch(buffer[0])
       {
          case 'r':
             printf("Rock\n");
             buffer[0] = 2;
             buffer[1] = '\0';
             break;
          case 'p':
             printf("Paper\n");
             buffer[0] = 3;
             buffer[1] = '\0';
             break;
          case 's':
             printf("Scissors\n");
             buffer[0] = 4;
             buffer[1] = '\0';
             break;
          case 'q':
             printf("We must retreat my Lord!\nThanks for Playing\n");
             buffer[0] = 5;
             buffer[1] = '\0';
             break;
          default:
             printf("ERROR: unknown command\nPlease try again\n");
             /* clear input buffer */
             while ((ch = getchar()) != '\n' && ch != EOF);
             continue; /* handles invalid input */
       }
       n = write(sockfd,buffer,strlen(buffer));
       /* clear input buffer */
       while ((ch = getchar()) != '\n' && ch != EOF);
       if (n < 0) 
          error("ERROR writing to socket");
       if (buffer[0] != 5)
       {
          bzero(buffer,256);
          n = read(sockfd,buffer,255);
          if (n < 0) 
             error("ERROR reading from socket");
       
          /* display results */
          switch(buffer[0])
          {
             case 6:
                printf("Thy might crushes thine opponent\n");
                break;
             case 7:
                printf("All Hail King of the Losers!\n");
                break;
             case 8:
                printf("What a disapointing tie\n");
                break;
             case 5:
                printf("Thine opponent has turned tail and run\nThanks for playing\n");
                break;
             default:
                printf("SERVER ERROR: I don't know what happened\n");
                printf("%d", buffer[0]);
                buffer[0] = 5;
                break;
          }
       }
       
    } while (buffer[0] != 5);
    /* close and exit */
    close(sockfd);
    return 0;
}
