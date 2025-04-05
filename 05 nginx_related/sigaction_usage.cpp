#include<iostream>
#include<unistd.h>
#include <csignal>

using namespace std;

void sighandler(int sig, siginfo_t* info, void* context){
    cout<< "received signal"<<endl;
    if (sig == SIGTERM){
        cout<<"from proc: "<<info->si_pid<<endl;
    }
}
//void*: usually ucontext_t * helps get CPU info

int main(){
    struct sigaction sa;
    sa.sa_sigaction = sighandler;
    sigemptyset(&sa.sa_mask); //do not block signals while processing the received signal (use sigaddset(&sa.sa_mask,SIGUSR2) to update)
    sa.sa_flags = SA_SIGINFO; // if 0, sighandler should be sighandler(int sig)

    sigaction(SIGTERM, &sa, nullptr);
    
    std::cout << "Waiting for SIGTERM " << getpid() << "\n";
    while (true) {
        pause();
    }

    return 0;
}