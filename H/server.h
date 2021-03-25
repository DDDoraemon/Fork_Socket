#ifndef __SERVER_H_
#define __SERVER_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 9600
#define IP "192.168.24.128"
#define MAXLINK 128

void errInfo(int ret, char* info);
int socketInit();

#endif