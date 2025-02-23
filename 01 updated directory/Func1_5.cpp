#include"Proj1.h"

void c_directory::modify_contact(){
    std::string name;
    std::string line;
    std::string num;
    std::string new_address="tmp.txt";
    std::ofstream outfile(new_address);

    std::cout<<"Who do you want to modify?\n";
    std::cin>>name;

    file.clear();
    
    while(getline(file,line)){
        size_t pos = line.find(' ');
        std::string l_name=line.substr(0,pos);
        if(name!=l_name){
            outfile<<line<<'\n';
        }
        else{
            std::cout<<name<<" found! Please enter the new number\n";
            std::cin>>num;
            outfile<<name<<' '<<num<<std::endl;
        }
    }

    if(std::remove(fileaddress.c_str())==0){
        if(std::rename(new_address.c_str(),fileaddress.c_str())==0){
            std::cout<<"Succeed to modify the contact!\n";
            file.close();
            file.open(fileaddress);
        }
    }
    else{
        std::cout<<"Failed to modify!\n";
    }
}