#include"01heads.h"

// main function
int main(){
    int select = 0;
    directory book;
    book.current_contacts=0;

    
    while(1){
        showMenu();

        cin>> select;
        
        switch (select)
        {
        case 1:
            add_contact(&book);
            break;
        
        case 2:
            show_directory(&book);
            break;

        case 3:
            delete_contact(&book);
            break;

        case 4:
            search_contact(&book);
            break;

        case 5:
            modify_contact(&book);
            break;
        
        case 6:
            clear_all_contacts(&book);
            break;
        
        case 0:
            cout<< "See you"<<endl;
            return 0;
            break;
        default:
            break;
        }
        cout<< endl;
    }
    

    
    return 0;
}