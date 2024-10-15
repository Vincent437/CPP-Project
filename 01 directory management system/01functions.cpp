#include"01heads.h"
#include<iostream>
using namespace std;
#include<string.h>

// show menu
void showMenu(){
    cout<<"1. add contact"<<endl;
    cout<<"2. show all contacts"<<endl;
    cout<<"3. delete contact"<<endl;
    cout<<"4. search for contact"<<endl;
    cout<<"5. modify contact"<<endl;
    cout<<"6. delete all contacts"<<endl;
    cout<<"0. exit directory"<<endl;
}

void add_contact(directory * D){
    if (D->current_contacts >=max){
        cout<< "directory full"<< endl;
        return;
    }
    else{
        cout<< "please tpye in their name"<< endl;
        cin>> D->contact_array[D->current_contacts].name;
        cout<< "please tpye in their sex (0 stands for female, 1 stands for male)"<< endl;
        int temp_sex;
        while(1){
            cin>> temp_sex;
            if (temp_sex==0 || temp_sex ==1){
                D->contact_array[D->current_contacts].sex = temp_sex;
                break;
            }
            else{
                cout<< "0 stands for femail, 1 stands for male"<< endl;
            }
        }
        cout<< "please tpye in their age"<< endl;
        cin>> D->contact_array[D->current_contacts].age;
        cout<< "please tpye in their number"<< endl;
        cin>> D->contact_array[D->current_contacts].phone_number;
        cout<< "please tpye in their address"<< endl;
        cin>> D->contact_array[D->current_contacts].address;
        D->current_contacts+=1;
        cout<< "complete!"<< endl;
    }
    
}

void show_directory(directory * D){
    if (D->current_contacts==0){
        cout<< "no contact" << endl;
    }
    else{
        for (int i=0;i< D->current_contacts; i++){
            cout<< D->contact_array[i].name<< "\t";
            cout<< D->contact_array[i].age<< "\t";
            cout<< (D->contact_array[i].sex==1? "male" :"female") << "\t";
            cout<< D->contact_array[i].phone_number<< "\t";
            cout<< D->contact_array[i].address<< endl;
        }
    }
}

int detect_contact(string delete_name, directory * D){
    for (int i=0; i< D->current_contacts; i++){
        if (D->contact_array[i].name == delete_name){
            return i;
        }
    }
    return -1;
}

void search_contact( directory * D){
    cout<< "who do you want to search?"<<endl;
    string search_name;
    cin>> search_name;
    int place = detect_contact(search_name, D);
    if (place==-1){
        cout<< "no such person"<< endl;
    }
    else{
        cout<< D->contact_array[place].name<< "\t";
        cout<< D->contact_array[place].sex<< "\t";
        cout<< D->contact_array[place].age<< "\t";
        cout<< D->contact_array[place].phone_number<< "\t";
        cout<< D->contact_array[place].address<< endl;
        
    }
}

void modify_contact(directory * D){
    cout<< "enter the name of the contact you want to modify"<< endl;
    string name;
    cin>> name;
    int place = detect_contact(name, D);
    if (place==-1){
        cout<< "no such person"<< endl;
    }
    else{

        cout<< "type the number of category you want to modify\t"<< endl <<"1. name\t2. sex\t3. age\t4. number\t5. address\t6. two or more parts" <<endl;
        int choice;
        cin>> choice;
        while(1){
            switch (choice)
            {
            case 1:
                cout<< "enter the new one"<< endl;
                cin>>D->contact_array[place].name;
                return;
            case 2:
                cout<< "enter the new one"<< endl;
                cin>>D->contact_array[place].sex;
                return;
            case 3:
                cout<< "enter the new one"<< endl;
                cin>>D->contact_array[place].age;
                return;
            case 4:
                cout<< "enter the new one"<< endl;
                cin>>D->contact_array[place].phone_number;
                return;
            case 5:
                cout<< "enter the new one"<< endl;
                cin>>D->contact_array[place].address;
                return;
            case 6:
                cout<< "please tpye in their name"<< endl;
                cin>> D->contact_array[place].name;
                cout<< "please tpye in their sex (0 stands for female, 1 stands for male)"<< endl;
                int temp_sex;
                while(1){
                    cin>> temp_sex;
                    if (temp_sex==0 || temp_sex ==1){
                        D->contact_array[place].sex = temp_sex;
                        break;
                    }
                    else{
                        cout<< "0 stands for femail, 1 stands for male"<< endl;
                    }
                }
                cout<< "please tpye in their age"<< endl;
                cin>> D->contact_array[place].age;
                cout<< "please tpye in their number"<< endl;
                cin>> D->contact_array[place].phone_number;
                cout<< "please tpye in their address"<< endl;
                cin>> D->contact_array[place].address;
                cout<< "complete!"<< endl;
                return;
            default:
                break;
            }
        }
    }
}

void delete_contact(directory * D){
    cout<< "who do you want to delete?" << endl;
    string delete_name;
    cin>> delete_name;
    int delete_place = detect_contact(delete_name,D);
    if (delete_place==-1){
        cout<< "there's no such person" << endl;
    }
    else{
        for(int i=delete_place; i<D->current_contacts; i++){
            D->contact_array[i] = D->contact_array[i+1];
        }
        D->current_contacts-=1;
        cout<< "we deleted them"<< endl;
    }
}

void clear_all_contacts(directory * D){
    D->current_contacts=0;
    cout<< "clear complete"<< endl;
}