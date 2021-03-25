#ifndef __FORK_H_
#define __FORK_H_

#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "communocate.h"

int child_process(int* client_fd);
void father_process();

#endif