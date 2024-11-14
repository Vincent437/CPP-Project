#include<iostream>
using namespace std;
#include"01 interface function.h"

int main(){

    interface interface_manager;
    int choice;

    while(true){
        interface_manager.show_manu();
        cout<< "please enter your choice and press enter key"<< endl;
        cin>> choice;

        switch (choice)
        {
        case 1:
            interface_manager.start_competition();
            break;
        
        case 2:
            interface_manager.show_record();
            break;
        case 3:
            interface_manager.clear_record();
            break;
        case 0:
            interface_manager.exit_system();
            return 0;

        default:
            break;
        }
    }
    



    return 0;
}