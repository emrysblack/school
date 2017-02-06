/* Bare nslookup utility (w/ minimal error checking) */
#include <stdio.h>          /* stderr, stdout */
#include <netdb.h>          /* hostent struct, gethostbyname() */
#include <arpa/inet.h>      /* inet_ntoa() to format IP address */
#include <netinet/in.h>     /* in_addr structure */
#include <unistd.h>

int main()
{
   struct hostent *host;     /* host information */
   struct in_addr h_addr;    /* internet address */
   char hostName[256];
  
   gethostname(hostName, 256);
   if ((host = gethostbyname(hostName)) == NULL) {
      fprintf(stderr, "(mini) nslookup failed on '%s'\n", hostName);
      return 1;
   }
   h_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);
   fprintf(stdout, "%s\n", inet_ntoa(h_addr));
   return 0;
}
           
