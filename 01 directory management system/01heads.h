#include<iostream>
using namespace std;
#include<string.h>
#define max 1000

struct contacts{
    string name;
    int sex;
    int age;
    string phone_number;
    string address;
};

struct directory{
    contacts contact_array[max];
    int current_contacts;
};

void showMenu();

void add_contact(directory * D);

void show_directory(directory * D);

int detect_contact(string delete_name, directory * D);

void search_contact( directory * D);

void modify_contact(directory * D);

void clear_all_contacts(directory * D);

void delete_contact(directory * D);