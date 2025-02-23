#include"Proj1.h"

void c_directory::delete_contact(){
    std::string name;
    std::string line;
    std::string new_address="tmp.txt";
    std::ofstream outfile(new_address);

    std::cout<<"Who do you want to delete?\n";
    std::cin>>name;

    file.clear();
    
    while(getline(file,line)){
        size_t pos = line.find(' ');
        std::string l_name=line.substr(0,pos);
        if(name!=l_name){
            outfile<<line<<'\n';
        }
    }

    if(std::remove(fileaddress.c_str())==0){
        if(std::rename(new_address.c_str(),fileaddress.c_str())==0){
            std::cout<<"Succeed to delete the contact!\n";
            file.close();
            file.open(fileaddress);
        }
    }
    else{
        std::cout<<"Failed to delete!\n";
    }
}