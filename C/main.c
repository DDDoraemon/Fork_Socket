#include <stdio.h>
#include "server.h"
#include "communocate.h"
#include "fork.h"

int main() {
    int server_fd = socketInit();  // 服务器端socket初始化

    // 客户端socket地址创建
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len;

    // 循环接收客户端请求
    while (1) {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        errInfo(client_fd, "accept");

        pid_t pid = fork();  // 创建新进程
        errInfo(pid, "fork");

        if (pid == 0) {
            // child process
            close(server_fd); 
            getClientInfo(&client_addr);  // 得到客户端IP和端口号
            child_process(&client_fd);  // 进入子进程
            break;
        }
        else {
            // father process
            close(client_fd);
            father_process();  //进入父进程
            continue;
        }
    }

    return 0;
}