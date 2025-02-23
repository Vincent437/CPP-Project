#include"Proj1.h"

void c_directory::delete_all_contacts(){
    file.close();
    file.clear();
    file.open(fileaddress,std::ios::in | std::ios::out | std::ios::trunc);
    if(!file.is_open()){std::cout<<"Failed to delete all contacts\n";}
}