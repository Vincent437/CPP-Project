#include<set>
#include<vector>
#include"Proj1.h"

int c_directory::init(){
    std::cout<<"1. add contact\n"
    "2. show all contacts\n"
    "3. delete contact\n"
    "4. search for contact\n"
    "5. modify contact\n"
    "6. delete all contacts\n"
    "0. exit directory"<<std::endl;

    std::cin>>ans;

    return ans;
}

int* read_conf(){
    std::fstream f;
    f.open("Proj1.conf", std::ios::in);
    f.seekg(0,std::ios::beg);
    std::string line;
    int* conf = new int[2];
    int mark = 0;
    while(getline(f, line)){
        size_t pos= line.find('=');
        conf[mark++]=std::stoi(line.substr(pos+1));
    }
    return conf;
}

c_directory::c_directory(std::string address):fileaddress(address){
    ans=init();
    file.open(fileaddress, std::ios::in | std::ios::out |std::ios::app);
    int* conf = read_conf();
    name_max = conf[0];
    num_max = conf[1];
    delete[] conf;
};

static std::set<char> letters_and_space=[](){
    std::set<char> s;
    for(char c='a';c<='z';c++){s.insert(c);}
    for(char c='A';c<='Z';c++){s.insert(c);}
    s.insert(' ');
    return s;
}();

static std::set<int> numbers=[](){
    std::set<int> n;
    for(char c = '0'; c<='9'; c++){n.insert(c);}
    return n;
}();

bool exam_alphabet(std::string target){
    for(char i :target){
        if(letters_and_space.find(i)==letters_and_space.end()){
            std::cout<<"incorrect name format\n";
            return false;
        }
    }
    return true;
}

bool exam_numbers(std::string target){
    for(char i :target){
        if(numbers.find(i)==numbers.end()){
            std::cout<<"incorrect number format\n";
            return false;
        }
    }
    return true;
}

void max_override(std::string max_key, int max_val){
    std::vector<std::string> lines;
    std::string line;
    std::ifstream infile("Proj1.conf");
    while(getline(infile,line)){
        size_t pos = line.find('=');
        std::string key = line.substr(0,pos);
        std::string val = line.substr(pos+1);

        if(max_key==key){
            line = key+"="+std::to_string(max_val);
        }
        lines.push_back(line);
    }
    infile.close();

    std::ofstream outfile("Proj1.conf",std::ios::trunc);
    for(std::string l :lines){
        outfile<<l<<std::endl;
    }
    outfile.flush();
    outfile.close();
}

void c_directory::add_contact(std::fstream &file){
    std::string name;
    std::string num;
    bool flag = false;
    while(!flag){
        std::cout<<"please enter the name\n";
        std::cin>>name;
        flag = exam_alphabet(name);
    }
    if(name_max<name.size()){
        name_max = name.size();
        max_override("name_max",name_max);
    }
    else{
        name.append(name_max-name.size(),' ');
    }
    flag=false;

    while(!flag){
        std::cout<<"please enter the number\n";
        std::cin>>num;
        flag = exam_alphabet(name);
    }
    if(num_max<num.size()){
        num_max = num.size();
        max_override("num_max",num_max);
    }
    else{
        num.append(num_max-num.size(),' ');
    }

    if(file.is_open()){
        file.clear();
        
        file.seekp(0,std::ios::end);
        file<<name<<" "<<num<<std::endl;
        file.flush();
        std::cout<<"Succeed to add them!\n";
    }
    else{
        std::cout<<"Failed to open file\n";
    }
}