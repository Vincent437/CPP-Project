#include"02 menu.h"
#include"02 employee.h"

void test1(){
    worker *w= new employee(1,"2",3);
    w->show_info();
    
    w= new manager(1,"2",3);
    w->show_info();
    
    w= new boss(1,"2",3);
    w->show_info();
    
    exit(0);
}

int main(){
    menu m;
    int choice=0;
    //test1();
    while(true){
        m.show_menu();
        cout<<"please select your choice"<< endl;
        cin>> choice;
        switch (choice)
        {
        case 1:
            m.add_emp();
            break;
        case 2:
            m.show_emp();
            break;
        case 3:
            m.delete_emp();
            break;
        case 4:
            m.modify_emp();
            break;
        case 5:
            m.find_emp();
            break;
        case 6:
            m.sort_emp();
            break;
        case 7:
            m.clean_file();
            break;
        case 0:
            m.exit_system();
            break;
        
        default:
            break;
        }
    }

    return 0;
}