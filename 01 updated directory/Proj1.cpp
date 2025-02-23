#include"Proj1.h"

int main(int argc, char** argv){

    c_directory dir("dir.txt");

    while(dir.ans){
        switch (dir.ans)
        {
        case 1:
            dir.add_contact(dir.file);
            break;
        
        case 2:
            dir.show_contacts();
            break;
        
        case 3:
            dir.delete_contact();
            break;
        
        case 4:
            dir.search_contact();
            break;
        
        case 5:
            dir.modify_contact();
            break;

        case 6:
            dir.delete_all_contacts();
            break;
        
        default:
            break;
        }
        dir.init();
    }

    std::cout<<"See you next time! Have a good day."<<std::endl;

    return 0;
}