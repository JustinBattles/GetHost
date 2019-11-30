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



int main(int argc, char *argv[])
{  

  if (argv[1] == NULL) {
    printf("Usage: ./a.out <host to check>\n"); 
    exit(1);
  }

	struct hostent *he = gethostbyname(argv[1]);

	if (he == NULL) {
	  printf("Host not found: %s\n", argv[1]);
	  exit(1);
	}


  printf("Host: %s\n", he->h_name);
  

 if (he->h_aliases[0] != NULL) { 
   printf("Aliases: \n");
   
   for (int i = 0; he->h_aliases[i] != NULL; i++)
    printf("  %s\n", he->h_aliases[i]);

 }
  


 if (he->h_addrtype == AF_INET)
   printf("Host type: IPv4\n");
 else if (he->h_addrtype == AF_INET6) 
   printf("Host type: IPv6\n");
 

  char buf[INET_ADDRSTRLEN];
  
  printf("Addresses: \n");

   for (int i = 0; he->h_addr_list[i] != NULL; i++) {  
     inet_ntop(he->h_addrtype, he->h_addr_list[i], buf, INET_ADDRSTRLEN);
     printf("  %s\n", buf);
  }

  return 0;
}
