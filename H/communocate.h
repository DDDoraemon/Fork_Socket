#ifndef __COMMUNICATE_H_
#define __COMMUNICATE_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h> // read();
#include "server.h"

void getClientInfo(struct sockaddr_in* client_addr);
int reading(int* client_fd);
int writing(int* client_fd);


#endif