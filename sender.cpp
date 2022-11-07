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

#define BUFLEN 4096

int sleeps;
float timeouts;

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

std::string intToString(int INT) {
  std::string STRING = "0000000000000000";
  if (INT >= 4096) {
    STRING[3] = '1';
    INT -= 4096;
  }
  if (INT >= 2048) {
    STRING[4] = '1';
    INT -= 2048;
  }
  if (INT >= 1024) {
    STRING[5] = '1';
    INT -= 1024;
  }
  if (INT >= 512) {
    STRING[6] = '1';
    INT -= 512;
  }
  if (INT >= 256) {
    STRING[7] = '1';
    INT -= 256;
  }
  if (INT >= 128) {
    STRING[8] = '1';
    INT -= 128;
  }
  if (INT >= 64) {
    STRING[9] = '1';
    INT -= 64;
  }
  if (INT >= 32) {
    STRING[10] = '1';
    INT -= 32;
  }
  if (INT >= 16) {
    STRING[11] = '1';
    INT -= 16;
  }
  if (INT >= 8) {
    STRING[12] = '1';
    INT -= 8;
  }
  if (INT >= 4) {
    STRING[13] = '1';
    INT -= 4;
  }
  if (INT >= 2) {
    STRING[14] = '1';
    INT -= 2;
  }
  if (INT == 1) {
    STRING[15] = '1';
    INT -= 1;
  }
  if (INT > 0) {
    return "ERROR";
  } else {
    return STRING;
  }
}

int main(int argc, char **argv)
{
    timeouts = 0.0;
    sleeps = 0;
    // setting up packet to send
    CTP packet;
    //int seqNumber = 1;
    packet.setType("01"); // sets type to data
    packet.setTR("1"); // sets TR
    packet.setWindow("00001"); //window set to be 0
    packet.setSeqNum("00000001"); // first sequence number

    //command line args
    std::string fileName(argv[1]);
    std::ifstream source;
    source.open(fileName.c_str());
    char payload[4096]; //file converted to a char array
    std::string line;
    long unsigned int i = 0;
    while (std::getline(source, line))
    {
        for (i; i < line.length(); i++) {
            payload[i] = line[i];
        }
        payload[i] = '\n';
        i++;
    }

    // setting length
    std::string lgth = intToString(i);
    packet.setLength(lgth);
    packet.setCRC1();
    char* pyld = payload;
    packet.setPayload(pyld);

    //Setting TIMESTAMP
    time_t rawtime;
    struct tm * timeinfo;
    char tme[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(tme,sizeof(tme),"%d/%m/%Y %H:%M:%S",timeinfo);
    std::string str(tme);
    packet.setTimeStamp(str);

    char buf[BUFLEN];
    char* host(argv[2]);
    std::string portInput(argv[3]);
    int port = stringToInt( portInput );
    //int port = 2222;

    struct sockaddr_in myaddr, remaddr;
    socklen_t addrlen = sizeof(myaddr);
  	int fd, recvlen;

    char CLOSE[13] = {"closeRequest"};

    bool run = true; // controls if there is still data to be transfered
    bool send = true; // true = sending | false = receiving (Ack/Nack)
    bool secondRun = false; // Wrong CRC
    bool thirdRun = false; // Wrong CRC
    bool fourthRun = false; // sends normal
    bool ack = false;

    clock_t beginTransfer = clock();
    while (run) {
      if (send) {
        // delays to give time to receiver to bind to port
        wait();
        ///////////////////////////////////
        /// remaddr (address to send to)///
        ///////////////////////////////////

        if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
          perror("cannot create socket");
          return 0;
        }
        printf("created Sending socket: descriptor = %d\n", fd);

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

        printf("Bind successful on port number: %d\n", ntohs(remaddr.sin_port));
        if (!ack) {
          if (secondRun || thirdRun) {
            char INFO1[32], INFO6[19], INFO7[32];
            /// SETTING HEADER ///
            std::string info = packet.getType();
            info += packet.getTR();
            info += packet.getWindow();
            info += packet.getSeqNum();
            if (fourthRun) {
              info += packet.getLength();
            } else {
              info = packet.getLength();
            }
            for (int j = 0; j < 32; j++) {
              INFO1[j] = info[j];
            }
            // Sending TimeStamp //
            info = packet.getTimeStamp();
            for (int j = 0; j < 19; j++) {
              INFO6[j] = info[j];
            }
            // Sending CRC1 //
            info = packet.getCRC1();
            for (int j = 0; j < 32; j++) {
              INFO7[j] = info[j];
            }
            // Sending Payload //
            info = packet.getPayload();
            unsigned int L = info.length();
            char INFO8[L];
            for (unsigned int j = 0; j < L; j++) {
              INFO8[j] = info[j];
            }
            printf("Sending packet %s to %s port %d\n", "Header", host, port);
            if (sendto(fd, INFO1, 32, 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
              perror("sendto");
            }
            printf("Sending packet %s to %s port %d\n", "TimeStamp", host, port);
            if (sendto(fd, INFO6, 19, 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
              perror("sendto");
            }
            printf("Sending packet %s to %s port %d\n", "CRC1", host, port);
            if (sendto(fd, INFO7, 32, 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
              perror("sendto");
            }
            printf("Sending packet %s to %s port %d\n \n", "Payload", host, port);
            if (sendto(fd, INFO8, strlen(INFO8), 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
              perror("sendto");
            }
          } else {
            printf("Sending packet %s to %s port %d\n", "Header", host, port);
            printf("Sending packet %s to %s port %d\n", "TimeStamp", host, port);
            printf("Sending packet %s to %s port %d\n", "CRC1", host, port);
            printf("Sending packet %s to %s port %d\n \n", "Payload", host, port);
          }
        } else {
          printf("Sending Close Request %s to %s port %d\n \n", "CloseReq", host, port);
          if (sendto(fd, CLOSE, strlen(CLOSE), 0, (struct sockaddr *)&remaddr, sizeof(remaddr))==-1) {
            perror("sendto");
          }
        }
        send = false;
        wait();
      } else {
        if (secondRun) {
          if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      		    perror("Failed to create socket");
      		      return 0;
      	  }
      	   printf("Created Receiving socket: %d \n", fd);

           memset((char *)&myaddr, 0, sizeof(myaddr));
           myaddr.sin_family = AF_INET;
           myaddr.sin_addr.s_addr = htonl(INADDR_ANY); // sender address *used to use htonl
           myaddr.sin_port = htons(port);

           if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0 && secondRun) {
        		   perror("bind failed");
          } else {
               printf("bind complete. Port number = %d\n", ntohs(myaddr.sin_port));
          }

          while (!send) {

             printf("waiting on port %d for Ack / Nack \n", port);
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 5000;
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(fd, &readfds);
            int ret = select(fd + 1, &readfds, NULL, NULL, &tv);

            if (ret > 0) {
                recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&myaddr, &addrlen);
                std::string message;
                if (recvlen > 0) {
                    buf[recvlen] = 0;
                    printf("received message: \"%s\"\n", buf);
                    for (long unsigned int i = 0; i < strlen(buf); i++) {
                        message += buf[i];
                      }
                      if (message == "10") {
                        std::cout << "Packet transfer successful \n \n";
                        send = true;
                        ack = true;
                      } else if (message == "11"){
                        std::cout << "Packet corrupted, resending \n \n";
                        send = true;
                      } else if (message == "00"){
                        std::cout << "Close Ack Received, beginning close \n \n";
                        send = true;
                        run = false;
                      }
                }
            } else {
                std::cout << "Timed out waiting for ack \n \n";
                send = true;
                timeouts += 1.0;
            }
        }
        close(fd);
      } else {
        std::cout << "Timed out waiting for ack \n \n";
        timeouts += 1.0;
        send = true;
      }
        if (thirdRun) {
          fourthRun = true;
        }
        if (secondRun) {
          thirdRun = true;
        }
        secondRun = true;
        send = true;
      }
    }
    clock_t endTransfer = clock();
    printf("Time elapsed before execution: %f seconds \n", ((float)beginTransfer) / CLOCKS_PER_SEC);
    printf("Time elapsed after execution: %f seconds \n", ((float)endTransfer) / CLOCKS_PER_SEC);
	  return 0;
}
