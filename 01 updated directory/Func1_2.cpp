#include"Proj1.h"

void c_directory::show_contacts(){
    file.clear();
    file.seekg(0,std::ios::beg);
    if (file.peek() == std::ifstream::traits_type::eof()) {
    std::cout << "The directory is empty!" << std::endl;
    }

    std::string lines;
    while(getline(file,lines)){
        std::cout<<lines<<std::endl;
    }
}