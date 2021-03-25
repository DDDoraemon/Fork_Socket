#include "communocate.h"

char readBuf[BUFSIZ];
char writeBuf[BUFSIZ];

static char* ip = NULL;  // 仅在communicate.c文件内使用 用于显示客户端的IP和端口号
static int port;


void getClientInfo(struct sockaddr_in* client_addr) {
    ip = inet_ntoa(client_addr->sin_addr);  // 网络字节序转到主机字节序
    port = ntohs(client_addr->sin_port);
}

int reading(int* client_fd) {
    memset(readBuf, 0, BUFSIZ);  // 清空接收区

    int read_ret = read(*client_fd, readBuf, BUFSIZ);
    if (read_ret < 0) {  //接收的字节<0  read函数出错
        perror("read");
        close(*client_fd);
        return -1;
    }
    else if (read_ret == 0) {  // ==0 客户端主动断开链接
        printf("[%s:%d] cancel connection\n", ip, port);
        close(*client_fd);
        return -1;
    }
    else {
        printf("[%s:%d] send %d byte:%s\n", ip, port, read_ret, readBuf);
        return 0;
    }
}

int writing(int* client_fd) {
    memset(writeBuf, 0, BUFSIZ);
    
    fgets(writeBuf, BUFSIZ, stdin);
    int write_ret = write(*client_fd, writeBuf, sizeof(writeBuf));
    if (write_ret < 0) {
        perror("write");
        close(*client_fd);
        return -1;
    }
    else {
        printf("Have write %d byte to [%s:%d]: %s\n", write_ret, ip, port, writeBuf);
        return 0;
    }
}