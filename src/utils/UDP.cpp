#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdint>

#define PORT 20777
#define BUFSIZE 4096
#define MAXPACKETS 65535

// Driver code
int main(int argc, char **argv) {
  struct sockaddr_in myaddr;           /* our address */
  struct sockaddr_in remaddr;          /* remote address */
  socklen_t addrlen = sizeof(remaddr); /* length of addresses */
  std::uint32_t recvlen;               /* # bytes received */
  std::uint32_t fd;                    /* our socket */
  unsigned char buf[BUFSIZE];          /* receive buffer */

  /* create a UDP socket */
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("cannot create socket\n");
    return 0;
  }

  /* bind the socket to any valid IP address and a specific port */
  memset((char *)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(PORT);

  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
    perror("bind failed\n");
    return 0;
  }

  /* now loop, receiving data and printing what we received */
  printf("%s %d\n", "waiting on port", PORT);
  for (std::uint16_t i = 0; i < MAXPACKETS; i++) {
    recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
    printf("%s %d %s\n", "received", recvlen, "bytes");
    if (recvlen > 0) {
      buf[recvlen] = 0;
      printf("(%d) %s ", recvlen, "received message:");
      for (std::uint16_t j = 0; j < recvlen; j++) {
        printf("%x ", buf[j]);
      }
      printf("\n");
    }
  }
  /* never exits */
}

// g++ src/utils/UDP.cpp
// ./a.out
