#include "fork.h"


// 回调函数 回收结束的子进程
void reclaimChildProcess(int signum) {
    while (waitpid(-1, NULL, WNOHANG) > 0);  // 当没有可回收的子进程时 返回0  非阻塞回收
    return;
}

int child_process(int* client_fd) {
    pid_t ppid;
    ppid = fork();
    errInfo(ppid, "child fork");
    while (1) {
        if (ppid == 0) {
            if (writing(client_fd) == -1) return -1;
        }
        else {
            if (reading(client_fd) == -1) return -1;  // 读客户端消息
        }
    }
}

// 父进程创建信号集 捕捉到的信号都按该信号集的设定来处理收到的信号
// sa_handler设定回调函数
// sa_flags设定当系统调用被打断时 会重新执行系统调用
void father_process() {
    struct sigaction act;
    act.sa_handler = reclaimChildProcess;
    act.sa_flags = SA_RESTART;
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD, &act, NULL);  // 捕捉子进程变化信号 主要是子进程结束信号
}