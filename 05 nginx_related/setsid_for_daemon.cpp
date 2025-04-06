#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <csignal>

int main(int argc, char *const *argv)
{    
    pid_t pid;
    std::cout << "program begin"<< std::endl;

    pid = fork();
    if(pid < 0)
    {
        std::cout<<"fork进程出错!\n";
    }
    else if(pid == 0)
    {
        std::cout<<"child process\n";
        
       // 创建新的session
       setsid();
        for(;;) 
        {
            sleep(1);
            std::cout<<"子进程休息1秒!\n";
        }
        return 0;
    }
    else
    {
        //父进程
        for(;;)
        {
            sleep(1);
            std::cout<<"父进程休息1秒!\n";
        }
        return 0;
    }
    std::cout<<"程序退出!\n";
    return 0;
}