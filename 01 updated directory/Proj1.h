#pragma once

#include<iostream>
#include<string>
#include<fstream>



class c_directory{
    public:
    int ans;
    std::string fileaddress;
    int name_max;
    int num_max;

    std::fstream file;
    std::fstream conf;

    int init();
    void add_contact(std::fstream &file);
    void show_contacts();
    void delete_contact();
    void search_contact();
    void modify_contact();
    void delete_all_contacts();
    void exit_dir();

    c_directory(std::string address);
    ~c_directory(){file.close();}
};