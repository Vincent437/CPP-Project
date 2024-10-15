#include"02 menu.h"
#include"02 employee.h"

employee:: employee(int id, string name, int department_id){
    this->id=id;
    this->name=name;
    this->department_id=department_id;
}

void employee:: show_info(){
    cout<<"staff ID: "<<this->id
    <<"\tstaff name: "<<this->name
    <<"\tstaff department: "<< this->get_department()
    <<endl;
}

string employee:: get_department(){
    return string("employee");
}

manager:: manager(int id, string name, int department_id){
    this->id=id;
    this->name=name;
    this->department_id=department_id;
}

void manager:: show_info(){
    cout<<"staff ID: "<<this->id
    <<"\tstaff name: "<<this->name
    <<"\tstaff department: "<< this->get_department()
    <<endl;
}

string manager:: get_department(){
    return string("manager");
}

boss:: boss(int id, string name, int department_id){
    this->id=id;
    this->name=name;
    this->department_id=department_id;
}

void boss:: show_info(){
    cout<<"staff ID: "<<this->id
    <<"\tstaff name: "<<this->name
    <<"\tstaff department: "<< this->get_department()
    <<endl;
}

string boss:: get_department(){
    return string("leader");
}