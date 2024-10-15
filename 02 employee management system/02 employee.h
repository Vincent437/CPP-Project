#pragma once
#include"02 menu.h"

class worker{
    public:
    int id;
    string name;
    int department_id;

    virtual void show_info()=0;
    virtual string get_department()=0;
    virtual ~worker(){}
};

class employee: public worker{
    public:
    employee(int id, string name, int department_id);
    void show_info();
    string get_department();
};

class manager: public worker{
    public:
    manager(int id, string name, int department_id);
    void show_info();
    string get_department();
};

class boss: public worker{
    public:
    boss(int id, string name, int department_id);
    void show_info();
    string get_department();
};