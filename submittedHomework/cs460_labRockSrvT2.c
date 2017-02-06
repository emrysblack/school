/***********************************************************************
 * Program:
 *    Lab RockSrvT2, Rock/Paper/Scissors with Sockets - Server Code
 *    Brother Jones, CS 460
 * Author:
 *    Brady Field
 * Summary:
 *    Server side of RPS
 ************************************************************************
 * Changes:
 * - added comments for clarity
 *
 *
 *
 *
 *
 ************************************************************************/

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, newsockfd1;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     /*first player*/
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     printf("Waiting for second client\n");
     /*second player*/
     newsockfd1 = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     printf("Game starting\n");
     /*win, lose, tie, quit selection*/
    const char *game[4][4] = {
        {"t", "l", "w", "q"},
        {"w", "t", "l", "q"},
        {"l", "w", "t", "q"},
        {"q", "q", "q", "q"}
    };
     int p1, p2;
     do
     {
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from player 1");
        printf("Player 1: %s\n",buffer);      
        switch(buffer[0])
        { /*translate into array*/
           case 'r':
              p1 = 0;
              break;
           case 'p':
              p1 = 1;
              break;
           case 's':
              p1 = 2;
              break;
           case 'q':
              p1 = 3;
              break;
           default:
              printf("Unknown code error\n");
              break;
        }
        bzero(buffer,256);
        n = read(newsockfd1,buffer,255);
        if (n < 0) error("ERROR reading from player 2");
        printf("Player 2: %s\n",buffer);
        switch(buffer[0])
        { /*translate into array*/
           case 'r':
              p2 = 0;
              break;
           case 'p':
              p2 = 1;
              break;
           case 's':
              p2 = 2;
              break;
           case 'q':
              p2 = 3;
              break;
           default:
              printf("Unknown code error\n");
              break;
        }
        /*send results back to players*/
        printf("p 1: %s\n", game[p1][p2]);
        n = write(newsockfd,game[p1][p2],2);
        if (n < 0) error("ERROR writing to player 1");
        n = write(newsockfd1,game[p2][p1],2);       
        if (n < 0) error("ERROR writing to player 2");
     } while (game[p1][p2][0] != 'q');
     /*close connections and exit*/
     close(newsockfd);
     close(newsockfd1);
     close(sockfd);
     return 0; 
}
