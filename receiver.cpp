#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <math.h>
#include "CTP.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <sys/time.h>
#include <stdio.h>

using namespace std;

#define BUFLEN 2048

int sleeps;

void wait(){
  sleep(1);
  sleeps++;
}

int stringToInt(std::string STRING) {
    int INT = 0;
    int minus = STRING.length() - 1;
    for (unsigned int i = 0; i < STRING.length(); i++) {
        switch(STRING[i]) {
            case '1':
            INT += pow(10, (minus - i));
            break;
            case '2':
            INT += 2 * pow(10, (minus - i));
            break;
            case '3':
            INT += 3 * pow(10, (minus - i));
            break;
            case '4':
            INT += 4 * pow(10, (minus - i));
            break;
            case '5':
            INT += 5 * pow(10, (minus - i));
            break;
            case '6':
            INT += 6 * pow(10, (minus - i));
            break;
            case '7':
            INT += 7 * pow(10, (minus - i));
            break;
            case '8':
            INT += 8 * pow(10, (minus - i));
            break;
            case '9':
            INT += 9 * pow(10, (minus - i));
            break;
            default: break;
        }
    }
    return INT;
}

int main(int argc, char **argv)
{
    clock_t beginTransfer = clock();
    sleeps = 0;
    std::vector<std::string> lines; //file converted to a vector of strings
    std::string portInput(argv[2]);
    int port = stringToInt( portInput );

    char Ack[3] = {"10"};
    char Nack[3] = {"11"};
    char Cls[3] = {"00"};
    char IPAdr[10] = {"127.0.0.1"};
    char* host(IPAdr);

    std::string fileName(argv[1]);
    std::ofstream source;
    std::string message = "";

	struct sockaddr_in myaddr, remaddr;	// addresses
  socklen_t addrlen = sizeof(myaddr);
	int fd, recvlen;	// our sockets
	char buf[BUFLEN];

  std::string crc, header;
  bool run = true; // determines whether to continue running loop
  bool recv = true; // determines if receiving or Sending
                    // true = receiving - false = sending (ack / nack)
  bool secondRun = false;
  bool breakRun = false;

  while(run) {
    if (recv) { // receiving packets
      int pckgs = 0;
      // create socket
    	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    		perror("cannot create socket");
    		return 0;
    	}
    	printf("created Receiving socket: descriptor = %d\n", fd);

      memset((char *)&myaddr, 0, sizeof(myaddr));
      myaddr.sin_family = AF_INET;
      myaddr.sin_addr.s_addr = htonl(INADDR_ANY); // sender address *used to use htonl
      myaddr.sin_port = htons(port);

    	// bind to an arbitrary address
      if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
      		perror("bind failed");
      		return 0;
      	}
      printf("bind complete. Port number = %d\n", ntohs(myaddr.sin_port));
      while (recv) {
        printf("waiting on port %d for packet \n", port);

           recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&myaddr, &addrlen);
      		 printf("received %d bytes\n", recvlen);
      		 if (recvlen > 0) {
      			   buf[recvlen] = 0;
      			   printf("received message: \"%s\"\n", buf);
               char CR[13] = {"closeRequest"};
               if (buf != CR) {
                 for (long unsigned int i = 0; i < strlen(buf); i++) {
                   message += buf[i];
                 }
               }
               if (message == "closeRequest") {
                 breakRun = true;
                 break;
               } else {
               lines.push_back(message);
               if (!breakRun) {
                 source.open(fileName.c_str());
                 source << "FULL RECEIVED PACKET INFORMATION \n";
                 unsigned int i = 0;
                 for (i; i < lines.size(); i++) {
                   switch(i) {
                     case 0:
                      source << "Header: ";
                      source << lines[i] << "\n";
                      header = lines[i];
                     break;
                     case 1:
                      source << "TimeStamp: ";
                      source << lines[i] << "\n";
                     break;
                     case 2:
                      source << "CRC1: ";
                      source << lines[i] << "\n";
                      crc = lines[i];
                     break;
                     case 3:
                      source << "Payload: ";
                      source << lines[i] << "\n";
                     break;
                     default: break;
                  }
                 pckgs = i;
               }
               source.close();
             }
            }
               message = "";
          }
          if (breakRun) {
            recv = false;
          }
          if (pckgs == 3) {
            lines.clear();
            pckgs = 0;
            recv = false;
          }
      }
      close(fd);

    } else { // sending acks
      wait();
      ///////////////
      /// remaddr ///
      if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    		perror("cannot create socket");
    		return 0;
    	}
      printf("created Sending socket: descriptor = %d \n", fd);

      memset((char *) &remaddr, 0, sizeof(remaddr));
      remaddr.sin_family = AF_INET;
      remaddr.sin_port = htons(port);
      if (inet_aton(host, &remaddr.sin_addr)==0) {
            remaddr.sin_addr.s_addr = inet_addr(host); // address
            remaddr.sin_port = htons(port); //port
      }
      if (inet_aton(host, &remaddr.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        return 0;
      }
      if (breakRun){
        printf("Sending Close Acknowledgement %s to %s port %d\n \n", "CloseAck", host, port);
        if (sendto(fd, Cls, 2, 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
            perror("sendto");
        }
        run = false;
        break;
      } else if (secondRun){
        CTP packet;
        packet.setCRC1(header);

        if (crc == packet.getCRC1()) {
          std::cout << "CRC's MATCH: VALID PACKET \n";
          printf("Sending packet %s to %s port %d\n \n", "Ack", host, port);
          if (sendto(fd, Ack, 2, 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
              perror("sendto");
          }
        } else if (crc != packet.getCRC1()) {
          std::cout << "'ERROR' CRC's DON'T MATCH: INVALID PACKET \n";
          printf("Sending packet %s to %s port %d\n \n", "Nack", host, port);
          if (sendto(fd, Nack, 2, 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
              perror("sendto");
          }
        }
      } else {
        std::cout << "No Packet received, no ack sent \n \n";
      }
      crc = "", header = "";
      if (!breakRun) {
        recv = true;
      }
      secondRun = true;
      close(fd);
      wait();
    }
  }
  clock_t endTransfer = clock();
	return 0;
}
