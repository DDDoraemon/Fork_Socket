#include "server.h"

int server_fd;
struct sockaddr_in server_addr;

// 返回值错误检测
void errInfo(int ret, char* info) {
    if (ret < 0) {
        perror(info);
        exit(EXIT_FAILURE);
    }
}

int socketInit() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    errInfo(server_fd,"socket");

    server_addr.sin_port = htons(PORT);
    server_addr.sin_family = AF_INET;
    //inet_pton(AF_INET, IP, (struct sockaddr*)&server_addr.sin_addr);    
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // 端口复用
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, (void*)&opt, sizeof(opt));

    int bind_ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    errInfo(bind_ret, "bind");

    int listen_ret = listen(server_fd, MAXLINK);
    errInfo(listen_ret, "listen");

    return server_fd;
}
