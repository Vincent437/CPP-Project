#include <iostream>
#include <cstdlib>  //exit
#include <unistd.h>  //fork
#include <csignal>
#include <sys/wait.h> //waitpid

//信号处理函数
void sig_usr(int signo)
{
    //printf("收到了SIGUSR1信号，进程id=%d!\n",getpid());    
    int  status;
    switch(signo)
    {
    case SIGUSR1:
        std::cout<<"收到了SIGUSR1信号，进程id="<<getpid()<<"!\n";    
        break;
    case SIGCHLD:
        
        std::cout<<"收到了SIGCHLD信号，进程id"<<getpid()<<"!\n";
        //waitpid获取子进程的终止状态，这样，子进程就不会成为僵尸进程了
        pid_t pid = waitpid(-1,&status,WNOHANG); //第一个参数为-1，表示等待任何子进程
                                                  //第二个参数：保存子进程的状态信息
                                                   //第三个参数：提供额外选项，WNOHANG表示不要阻塞，让waitpid()立即返回
        if(pid == 0) //子进程没结束，会立即返回这个数字，但这里应该不是这个数字
            std::cout<<"An issue occured: SIGCHILD received but child process is not end"<<std::endl;
            return;
        if(pid == -1)      //这表示这个waitpid调用有错误
            return;
        //走到这里，表示成功
        return;
        break;
    }
}

int main(int argc, char *const *argv)
{
    pid_t  pid;

    std::cout<<"进程开始执行!\n";

    struct sigaction sa;
    sa.sa_handler = sig_usr;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGUSR1,&sa,nullptr) < 0)
    {
        std::cout<<"无法捕捉SIGUSR1信号!\n";
        exit(1);
    }

    if(sigaction(SIGCHLD,&sa,nullptr) < 0) 
    {
        std::cout<<"无法捕捉SIGCHLD信号!\n";
        exit(1);
    }

    //---------------------------------
    pid = fork();  //创建一个子进程，子进程返回值为0

    //要判断子进程是否创建成功
    if(pid < 0)
    {
        std::cout<<"子进程创建失败!\n";
        exit(1);
    }

    //现在，父进程和子进程同时开始 运行了 
    for(;;)
    {        
        sleep(1); //休息1秒
        std::cout<<"休息1秒，进程id="<<getpid()<<"!\n";
    }
    std::cout<<"程序结束!\n";
    return 0;
}
