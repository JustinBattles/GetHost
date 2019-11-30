#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>

/* Includes go here */

/*
 * List who you worked with here:
 *
 */

/* host.c: (3pts)
 *   A program to print the IP address of a host specified on the command
 *   line.  If no argument is provided, print a usage message and exit.
 * Example input/output:
 * > ./host www.indstate.edu
 * Host: www-prod-cms-lb.indstate.edu
 * Aliases:
 *   www.indstate.edu
 * Host type: IPv4
 * Addresses:
 *   139.102.15.65
 */

int main(int argc, char *argv[])
{
  /* man 3 gethostbyname for information on the hostent structure: */

  if (argv[1] == NULL) {
    printf("Usage: ./a.out <host to check>\n"); 
    exit(1);
  }
  /**
   * Use the gethostbyname(3) function to look-up the host provided on the
   * first command line argument (argv[1]), assign the result to host.  If
   * host is NULL, print "Host not found: " followed by name of the host and
   * exit with a value of 1:
   */

	struct hostent *he = gethostbyname(argv[1]);

	if (he == NULL) {
	  printf("Host not found: %s\n", argv[1]);
	  exit(1);
	}


  /* Print the name of the host: */
  printf("Host: %s\n", he->h_name);
  

  /**
   * If h_aliases[0] is not null, then print a list of aliases, otherwise don't:
   * (there may be more than one, ex: cs.indstate.edu while logged into CS)
   */
 if (he->h_aliases[0] != NULL) { 
   printf("Aliases: \n");
   
   for (int i = 0; he->h_aliases[i] != NULL; i++)
    printf("  %s\n", he->h_aliases[i]);

 }
  
  /* Print the host type (IPv4 or IPv6). */


 if (he->h_addrtype == AF_INET)
   printf("Host type: IPv4\n");
 else if (he->h_addrtype == AF_INET6) 
   printf("Host type: IPv6\n");
 

  /**
   * Print the addresses, there may be more than one: (ex: amazon.com)
   * Use the inet_ntop(3) function to write the IP-address into a buffer, then
   * print the string found in the buffer.
   */

  char buf[INET_ADDRSTRLEN];
  
  printf("Addresses: \n");

   for (int i = 0; he->h_addr_list[i] != NULL; i++) {  
     inet_ntop(he->h_addrtype, he->h_addr_list[i], buf, INET_ADDRSTRLEN);
     printf("  %s\n", buf);
  }

  return 0;
}
