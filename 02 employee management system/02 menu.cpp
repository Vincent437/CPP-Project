#include"02 menu.h"

menu::menu(){
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs.is_open()){
        this->emp_num=0;
        this->emp_arr=NULL;
        file_is_empty=true;
        ifs.close();
        return;
    }

    char ch;
    ifs>>ch;
    if (ifs.eof()){
        emp_num=0;
        emp_arr=nullptr;
        file_is_empty=true;
        ifs.close();
        return;
    }

    file_is_empty=false;
    int num = get_emp_num();
    cout<< "there are "<< num<< "employees"<< endl;
    emp_num= num;

    emp_arr= new worker*[emp_num];
    init_emp();
}

void menu:: init_emp(){
    ifstream ifs;
    ifs.open(filename,ios::in);

    int id;
    string name;
    int did;
    int index=0;

    while(ifs>>id &&ifs>>name &&ifs>>did){
        worker *w =nullptr;

        if(did==1){
            w= new employee(id, name, did);
        }
        else if(did==2){
            w= new manager(id, name, did);
        }
        else if(did==3){
            w= new boss(id, name, did);
        }

        emp_arr[index]=w;
        index++;
    }

    ifs.close();
}

int menu:: get_emp_num(){
    ifstream ifs;
    ifs.open(filename,ios::in);

    int id;
    int name;
    int did;

    int num=0;
    while(ifs>>id &&ifs>>name &&ifs>>did){
        num++;
    }

    return num;
}

void menu:: show_menu(){
    cout<< endl;
    cout<< "*************************"<<endl;
    cout<<endl;
    cout<<"welcome to employee management system!"<< endl;
    cout<<"1 add employee information"<< endl;
    cout<<"2 show all employees"<< endl;
    cout<<"3 delete resigned employee"<< endl;
    cout<<"4 modify employee information"<< endl;
    cout<<"5 search for employee information"<< endl;
    cout<<"6 sort the roster"<< endl;
    cout<<"7 delete all information"<< endl;
    cout<<"0 exit system"<< endl;
    cout<< endl;
}

void menu::exit_system(){
    cout<< "thank you for using this system!"<<endl;
    exit(0);
}

bool menu::avoid_repetitive_name(int n){
    for (int i=0;i<emp_num; i++){
        if(emp_arr[i]->id==n){
            cout<< "this id exists, please change another one"<< endl;
            return false;
        }
    }
    return true;
}

void menu::add_emp(){
    cout<<"please enter the number of employees you want to add"<< endl;
    int add_num;
    cin>> add_num;
    if (add_num>0){
        int new_size=this->emp_num+add_num;
        worker ** newspace= new worker* [new_size];

        if (emp_arr != nullptr){
            for (int i=0;i<emp_num;i++){
                newspace[i]=emp_arr[i];
            }
        }

        for (int i=0;i<add_num;i++){
            int id;
            string name;
            int department_id;
            cout<< "please enter the "<< i+1<<"th employee's id"<<endl;
            if(emp_num!=0){
                do{
                    cin>>id;
                }while (!avoid_repetitive_name(id));
            }
            cout<< "please enter the "<< i+1<<"th employee's name"<<endl;
            cin>>name;
            cout<< "please enter the "<< i+1<<"th employee's id"<<endl;
            cout<< "1. staff\n2. manager\n3. leader"<<endl;
            cin>>department_id;

            worker *w=NULL;
            switch (department_id)
            {
            case 1:
                w= new employee(id, name, department_id);
                break;
            case 2:
                w= new manager(id, name, department_id);
                break;
            case 3:
                w= new boss(id, name, department_id);
                break;

            default:
                break;
            }

            newspace[emp_num+i]=w;
        }
        if (emp_arr != nullptr){
            delete[] emp_arr;
        }
        emp_arr=newspace;
        emp_num=new_size;
        save();
        file_is_empty=false;
        cout<< "add "<<add_num<<" employees succeed"<< endl;
    }
    else{
        cout<< "please enter a positive number"<< endl;
    }
}

void menu::show_emp(){
    ifstream ifs;
    ifs.open(filename, ios::in);
    char ch;
    ifs>>ch;
    if (ifs.eof()){
        emp_num=0;
        emp_arr=nullptr;
        file_is_empty=true;
        ifs.close();
    }
    if(file_is_empty){
        cout<< "file is empty or does not exist"<< endl;
    }
    else{
        for (int i=0;i<emp_num;i++){
            emp_arr[i]->show_info();
        }
    }
}

int menu:: is_exist(int n){
    int index= -1;

    for (int i=0; i<emp_num; i++){
        if(emp_arr[i]->id==n){
            index=i;
        }
    }

    return index;
}

void menu:: delete_emp(){
    if(file_is_empty){
        cout<< "file is empty or does not exist"<< endl;
    }
    else{
        cout<< "please enter the id of the person you want to delete"<< endl;
        int n;
        cin>>n;

        int index= is_exist(n);

        if (index==-1){
            cout<<"no such person"<<endl;
        }
        else{
            for(int i=index;i<emp_num-1;i++){
                emp_arr[i]=emp_arr[i+1];
            }
            emp_num--;
            save();
        }
    }
}

void menu:: modify_emp(){
    if(file_is_empty){
        cout<< "file is empty or does not exist"<< endl;
    }
    else{
        cout<< "please enter the id of the person you want to modify"<< endl;
        int n;
        cin>> n;

        int re= is_exist(n);
        if (re!=-1){
            delete emp_arr[re];
            int new_id;
            string new_name;
            int new_did;

            cout<< "please enter a new id for "<< emp_arr[re]->name<<endl;
            cin>> new_id;
            cout<< "please enter a new name"<<endl;
            cin>> new_name;
            cout<< "please enter a new position"<<endl;
            cout<< "1. staff\n2. manager\n3. leader"<<endl;
            cin>> new_did;

            worker *w=nullptr;
            switch (new_did)
            {
            case 1:
                w= new employee(new_id, new_name, new_did);
                break;
            case 2:
                w= new manager(new_id, new_name, new_did);
                break;
            case 3:
                w= new boss(new_id, new_name, new_did);
                break;
            default:
                break;
            }
            emp_arr[re]= w;
            cout<< "success"<< endl;
            save();
        }
        else{
            cout<< "no such perosn"<< endl;
        }
    }
}

void menu::find_emp(){
    if (file_is_empty){
        cout<<"no file"<< endl;
        return;
    }
    else{
        cout<<"please enter how you want to search"<< endl;
        cout<<"1. by id\n2. by name"<<endl;
        int select;
        cin>>select;
        if (select==1){
            int id;
            cout<<"please enter their id"<< endl;
            cin>>id;

            int ret=is_exist(id);
            if (ret!=-1){
                emp_arr[ret]->show_info();
            }
            else{
                cout<<"no such person"<<endl;
            }
            
        }
        else if(select==2){
            string name;
            cout<<"please enter their name"<< endl;
            cin>>name;
            int flag=0;

            for(int i=0; i<emp_num; i++){
                if(emp_arr[i]->name==name){
                    emp_arr[i]->show_info();
                    flag=1;
                }
            }

            if(flag==false){
                cout<<"no such person"<<endl;
            }
        }
        else{
            cout<< "wrong input"<< endl;
        }
    }
}

void menu:: sort_emp(){
    if(file_is_empty){
        cout<< "no file"<< endl;
    }
    else{
        cout<<"how to sort it?\n1. ascending\n2. descending"<<endl;
        int sort;
        cin>>sort;

        for (int i=0; i<emp_num-1; i++){
            int m=i;
            for(int j=i+1; j<emp_num; j++){
                if(sort==1){
                    if(emp_arr[i]->id>emp_arr[j]->id){
                        m=j;
                    }
                }
                else{
                    if(emp_arr[i]->id<emp_arr[j]->id){
                        m=j;
                    }
                }
            }
            if(i!=m){
                worker * temp=emp_arr[i];
                emp_arr[i]=emp_arr[m];
                emp_arr[m]=temp;
            }
            
        }
        save();
        cout<<"success"<<endl;
    }
}

void menu:: clean_file(){
    cout<< "please confirm your choice\n1. comfirm\n2. cancel"<< endl;
    int select;
    cin>>select;

    if(select==1){
        ofstream ofs(filename, ios::trunc);
        ofs.close();
        if(emp_arr!=nullptr){
            for(int i=0; i<emp_num; i++){
                delete emp_arr[i];
                emp_arr[i]=nullptr;
            }
            delete[] emp_arr;
            emp_arr=nullptr;
            emp_num=0;
            file_is_empty=true;
        }
        cout<< "success"<< endl;
    }

    else{
        return;
    }
}

void menu:: save(){
    ofstream ofs;
    ofs.open(filename,ios::out);
    
    for (int i=0; i<emp_num; i++){
        ofs<< emp_arr[i]->id<<" "
        << emp_arr[i]->name<<" "
        << emp_arr[i]->department_id<<endl;
    }

    ofs.close();
}

menu:: ~menu(){
    if(emp_arr != NULL){

        for(int i=0; i<emp_num; i++){
            delete emp_arr[i];
            emp_arr[i]=nullptr;
        }
        delete[] emp_arr;
        emp_arr=nullptr;
    }
}