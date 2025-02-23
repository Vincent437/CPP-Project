#include"Proj1.h"

void c_directory::search_contact(){
    std::string name;

    std::cout<<"Please enter the name: \n";
    std::cin>>name;

    std::ifstream infile(fileaddress);
    std::string line;

    while(getline(infile,line)){
        if(line.find(name)!=std::string::npos){
            std::cout<<line<<'\n';
            return;
        }
    }
    
    std::cout<<name<<" is not saved in this directory!\n";
}