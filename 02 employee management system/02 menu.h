#pragma once
#include<iostream>
#include<fstream>
using namespace std;
#include<string>
#include<fstream>
#include"02 employee.h"
#define filename "emplist.txt"

class worker;

class menu{
    public:
    menu();

    void show_menu();

    void exit_system();

    int emp_num;

    worker ** emp_arr;

    bool avoid_repetitive_name(int n);

    void add_emp();

    bool file_is_empty;

    int get_emp_num();

    void init_emp();

    void show_emp();

    int is_exist(int);

    void delete_emp();

    void modify_emp();

    void find_emp();

    void sort_emp();

    void clean_file();

    void save();

    ~menu();
};



