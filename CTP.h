#ifndef CTP_H
#define CTP_H

#include <iostream> // for testing purposes
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <bitset>

class CTP {
    public:

        CTP();
        ~CTP(){}

        void setType(std::string);
        std::string getType();

        void setTR(std::string);
        std::string getTR();

        void setWindow(std::string);
        std::string getWindow();

        void setSeqNum(std::string);
        std::string getSeqNum();

        void setLength(std::string);
        std::string getLength();

        void setTimeStamp(std::string);
        std::string getTimeStamp();

        void setCRC1();
        void setCRC1(std::string msg);
        std::string getCRC1();

        void setPayload(char*);
        std::string getPayload();

        unsigned char* getBufferPointer();

    private:

        unsigned char buffer[4192];
        unsigned char* bufferPtr;

};

CTP::CTP() {
  for (int i = 0; i < 4192; i++) {
    buffer[i] = '-';
  }
}
///////////////////////
// TYPE FUNCTIONS //
///////////////////////
void CTP::setType(std::string str) {
    for (long unsigned int i = 0; i < str.length(); i++) {
        buffer[i] = str[i];
    }
}

std::string CTP::getType() {
    std::string Type;
    for (int i = 0; i < 2; i++) {
        Type += buffer[i];
    }
    return Type;
}

///////////////////////
// TR FUNCTIONS //
///////////////////////
void CTP::setTR(std::string str) {
    int index = 0;
    for (long unsigned int i = 2; i < (str.length() + 2); i++) {
        buffer[i] = str[index];
        index++;
    }
}

std::string CTP::getTR() {
    std::string TR;
    TR += buffer[2];
    return TR;
}

///////////////////////
// WINDOW FUNCTIONS //
///////////////////////
void CTP::setWindow(std::string str) {
    int index = 0;
    for (long unsigned int i = 3; i < (str.length() + 3); i++) {
        buffer[i] = str[index];
        index++;
    }
}

std::string CTP::getWindow() {
    std::string Window;
    for (long unsigned int i = 3; i < 8; i++) {
        if (buffer[i] != '-') {
          Window += buffer[i];
        }
    }
    return Window;
}

///////////////////////
// SEQNUM FUNCTIONS //
///////////////////////
void CTP::setSeqNum(std::string str) {
    int index = 0;
    for (long unsigned int i = 8; i < (str.length() + 8); i++) {
        buffer[i] = str[index];
        index++;
    }
}
std::string CTP::getSeqNum() {
    std::string SeqNum;
    for (int i = 8; i < 16; i++) {
      if (buffer[i] != '-') {
        SeqNum += buffer[i];
      }
    }
    return SeqNum;
}

///////////////////////
// LENGTH FUNCTIONS //
///////////////////////
void CTP::setLength(std::string str) {
    int index = 0;
    for (long unsigned int i = 16; i < (str.length() + 16); i++) {
        buffer[i] = str[index];
        index++;
    }
}
std::string CTP::getLength() {
    std::string Length;
    for (int i = 16; i < 32; i++) {
      if (buffer[i] != '-') {
        Length += buffer[i];
      }
    }
    return Length;
}

///////////////////////
// TIMESTAMP FUNCTIONS //
///////////////////////
void CTP::setTimeStamp(std::string str) {
    int index = 0;
    for (long unsigned int i = 32; i < (str.length() + 32); i++) {
        buffer[i] = str[index];
        index++;
    }
}
std::string CTP::getTimeStamp() {
    std::string TimeStamp;
    for (int i = 32; i < 64; i++) {
      if (buffer[i] != '-') {
        TimeStamp += buffer[i];
      }
    }
    return TimeStamp;
}

///////////////////////
// CRC1 FUNCTIONS //
///////////////////////
void CTP::setCRC1() {
    std::string msg = "", crc = "10000010011000001000111011011011", encoded = "";
    msg += getType();
    msg += getTR();
    msg += getWindow();
    msg += getSeqNum();
    msg += getLength();
    int m=msg.length(),n=crc.length();
    encoded += msg;
    for(int i = 1; i <= n-1; i++){
        encoded+='0';
    }
    for(int i=0; i <=encoded.length()-n; ){
        for(int j=0;j<n;j++)
            encoded[i+j]= encoded[i+j]==crc[j]? '0':'1';
        for( ; i<encoded.length() && encoded[i]!='1'; i++);
    }
    std::string str = encoded.substr(encoded.length()-n);

    int index = 0;
    for (long unsigned int i = 64; i < (str.length() + 64); i++) {
        buffer[i] = str[index];
        index++;
    }
}
void CTP::setCRC1(std::string msg) {
    std::string crc = "10000010011000001000111011011011", encoded = "";
    int m=msg.length(),n=crc.length();
    encoded += msg;
    for(int i = 1; i <= n-1; i++){
        encoded+='0';
    }
    for(int i=0; i <=encoded.length()-n; ){
        for(int j=0;j<n;j++)
            encoded[i+j]= encoded[i+j]==crc[j]? '0':'1';
        for( ; i<encoded.length() && encoded[i]!='1'; i++);
    }
    std::string str = encoded.substr(encoded.length()-n);

    int index = 0;
    for (long unsigned int i = 64; i < (str.length() + 64); i++) {
        buffer[i] = str[index];
        index++;
    }
}
std::string CTP::getCRC1() {
    std::string CRC1;
    for (int i = 64; i < 96; i++) {
      if (buffer[i] != '-') {
        CRC1 += buffer[i];
      }
    }
    return CRC1;
}

///////////////////////
// PAYLOAD FUNCTIONS //
///////////////////////
void CTP::setPayload(char* str) {
    unsigned int index = 0;
    for (long unsigned int i = 96; i < 4192; i++) {
          buffer[i] = str[index];
          index++;
    }
}
std::string CTP::getPayload() {
    std::string Payload;
    for (long unsigned int i = 96; i < 512; i++) {
        if (buffer[i] != '0') {
        Payload += buffer[i];
        }
    }
    return Payload;
}

unsigned char* CTP::getBufferPointer() {
    bufferPtr = buffer;
    return bufferPtr;
}

#endif
