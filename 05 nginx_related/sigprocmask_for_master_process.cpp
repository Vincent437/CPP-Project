#include <iostream>
#include <cstdlib> 
#include <unistd.h>
#include <csignal>

//信号处理函数
void sig_quit(int signum)
{   
    std::cout<<"收到了SIGQUIT信号!\n";

    struct sigaction sa;
    sa.sa_handler = SIG_DFL;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGQUIT, &sa, nullptr)==-1)
    {
        std::cout<<"无法为SIGQUIT信号设置缺省处理!\n";
        exit(1);
    }
}

int main(int argc, char *const *argv)
{
    sigset_t newmask,oldmask; //定义信号集：新的信号集，原有的信号集
    struct sigaction sa;
    sa.sa_handler = sig_quit;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGQUIT, &sa, nullptr) == -1)  //注册信号对应的信号处理函数
    {        
        std::cout<<"无法捕捉SIGUSR1信号!\n";
        exit(1);   //退出程序，参数是错误代码，0表示正常退出，非0表示错误
    }

    sigemptyset(&newmask); //newmask信号集中所有信号都清0（表示这些信号都没有来）
    sigaddset(&newmask,SIGQUIT); //设置newmask信号集中的SIGQUIT信号位为1

    //设置该进程所对应的信号集
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)  //第一个参数用了SIG_BLOCK表明设置 进程 新的信号屏蔽字 为 “当前信号屏蔽字 和 第二个参数指向的信号集的并集
    {                                                 //一个 ”进程“ 的当前信号屏蔽字，刚开始全部都是0的；所以相当于把当前 "进程"的信号屏蔽字设置成 newmask（屏蔽了SIGQUIT)；
                                                      //第三个参数不为空，则进程老的(调用本sigprocmask()之前的)信号集会保存到第三个参数里，用于后续，这样后续可以恢复老的信号集给进程
        std::cout<<"sigprocmask(SIG_BLOCK)失败!\n";
        exit(1);
    }
    
    if(sigismember(&newmask,SIGQUIT))  //测试一个指定的信号位是否被置位，这里测试的是newmask
    {
        std::cout<<"SIGQUIT信号被屏蔽了!\n";
    }
    else
    {
        std::cout<<"SIGQUIT信号没有被屏蔽!!!!!!\n";
    }
    if(sigismember(&newmask,SIGHUP))  //测试另外一个指定的信号位是否被置位,测试的是newmask
    {
        std::cout<<"SIGHUP信号被屏蔽了!\n";
    }
    else
    {
        std::cout<<"SIGHUP信号没有被屏蔽!!!!!!\n";
    }

    std::cout<<"屏蔽10秒，此时无法接收SIGQUIT信号!\n";
    sleep(10);   //这个期间无法收到SIGQUIT信号的
    std::cout<<"10秒结束!\n";

    //现在我要取消对SIGQUIT信号的屏蔽(阻塞)--把信号集还原回去
    if(sigprocmask(SIG_SETMASK,&oldmask, nullptr) < 0) //第一个参数用了SIGSETMASK表明设置 进程  新的信号屏蔽字为 第二个参数 指向的信号集，第三个参数没用
    {
        std::cout<<"sigprocmask(SIG_SETMASK)失败!\n";
        exit(1);
    }

    std::cout<<"sigprocmask(SIG_SETMASK)成功!\n";
    
    if(sigismember(&oldmask,SIGQUIT))  //测试一个指定的信号位是否被置位,这里测试的是oldmask
    {
        std::cout<<"SIGQUIT信号被屏蔽了!\n";
    }
    else
    {
        std::cout<<"SIGQUIT信号没有被屏蔽，可以发送SIGQUIT信号了，程序将持续10秒钟，请在此期间测试SIGQUIT\n";
        int mysl = sleep(10);
        if(mysl > 0)
        {
            std::cout<<"sleep还没睡够，剩余"<<mysl<<"秒\n";
        }
    }
    std::cout<<"测试结束!\n";
    return 0;
}
