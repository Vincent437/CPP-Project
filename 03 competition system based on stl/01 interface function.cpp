#include"01 interface function.h"

interface::interface(){

    this->init_comp();

};

interface::~interface(){

};

void interface:: show_manu(){
    cout<<endl;
    cout<<"this is a competition"<< endl;
    cout<<"*********************"<< endl;
    cout<<"1. start competition"<< endl;
    cout<<"2. review previous winners"<< endl;
    cout<<"3. empty previous records"<< endl;
    cout<<"0. exit system"<< endl;
    cout<<"*********************"<< endl;
};

void interface:: init_comp(){
    srand(static_cast<unsigned int>(time(0)));
    this->v1.clear();
    this->v2.clear();
    this->v3.clear();
    this->competitor_map.clear();

    this->create_competitor();
    this->round=1;
    record.clear();
}

void interface:: create_competitor(){
    string nameseed = "ABCDEFGHIJKL";

    for (int i =0; i< nameseed.size(); i++){
        string name = "competitor ";
        name+= nameseed[i];

        competitor com;
        com.name=name;

        for (int j=0 ; j<2 ; j++){
            com.score[j]=0;
        }

        this->v1.push_back(i);
        this->competitor_map.insert(make_pair(i,com));
    }
}

void printer(int val){
    cout<< val+1<<" ";
}

void interface:: competition_draw(){
    cout<< "round "<< this->round<< " drawing"<< endl;
    cout<< "---------------------"<<endl;
    cout<< "competitor order"<< endl;
    random_device rd;

    if(this->round==1){
        shuffle(v1.begin(), v1.end(),rd);
        for_each(v1.begin(),v1.end(),printer);
        cout<< endl;
    }
    else{
        shuffle(v2.begin(), v2.end(),rd);
        for_each(v2.begin(),v2.end(),printer);
        cout<< endl;
    }

    cout<< "---------------------"<<endl;
}

void interface:: contest(){
    cout<< "-----No. "<< round<< " round starts-----"<< endl;
    cout<< endl;

    multimap<double, int, greater<double> > group_score;
    int group_num=0; 

    vector<int> competitor_group;
    if(round==1){
        competitor_group=v1;
    }
    else{
        competitor_group=v2;
    }

    
    for(vector<int>::iterator it = competitor_group.begin(); it!=competitor_group.end(); it++){
        group_num++;
        deque<double>d;
        
        for(int i =0;i<10; i++){
            double score = (rand()%401+600)/10.f;
            d.push_back(score);
        }
        sort(d.begin(),d.end(),greater<double>());

        d.pop_front();
        d.pop_back();

        double sum = accumulate(d.begin(),d.end(),0.0f);
        double avg = sum / (double)d.size();

        competitor_map[*it].score[round-1]=avg;

        cout<< "the average score of "<< competitor_map[*it].name<< " is "<< avg;
        cout<< endl;

        group_score.insert(make_pair(avg, *it));

        if(group_num %6 ==0){
            cout<< endl;
            cout<< "number "<< group_num/6 << " group contest ranking"<< endl;
            for(multimap<double, int, greater<double> >::iterator it= group_score.begin(); it!=group_score.end(); it++){
                cout<< "number: "<< it->second<< " name: "<< competitor_map[it->second].name<< " score: "<< competitor_map[it->second].score[round-1]<< endl;
            }
            cout<< endl;

            int count = 0;
            for(multimap<double, int, greater<double> >::iterator it= group_score.begin(); it!=group_score.end()&& count<3; it++, count++){
                if(round==1){
                    v2.push_back((*it).second);
                }
                else{
                    v3.push_back((*it).second);
                }
            }

            group_score.clear();
        }
    }
    cout<< "-----No. "<< round<< " round ends-----"<< endl;
    cout<< endl;
}

void interface:: show_score(){
    cout<<"number "<< round << " round winners: "<< endl;
    vector<int> v;
    if(round==1){
        v=v2;
    }
    else{
        v=v3;
    }

    for(vector<int>::iterator it= v.begin(); it!=v.end(); it++){
        cout<< "competitor id: "<< *it<< " name: "<< competitor_map[*it].name<< " score: "<< competitor_map[*it].score[round-1]<< endl;
    }
    cout<< endl;

    if(round==1){cout<< "the second round begins"<<endl; cout<< endl;}
}

void interface:: save_record(){
    ofstream ofs;
    ofs.open("competition.csv", ios::out | ios::app);

    for(vector<int>::iterator it = v3.begin(); it!= v3.end(); it++){
        ofs<< *it<<","<< competitor_map[*it].name<<","<< competitor_map[*it].score[1]<< ",";
    }
    ofs<< endl;

    ofs.close();
    cout<< "record saving complete"<< endl;
    cout<< "the whole competition is over"<< endl;
}

void interface:: start_competition(){
    competition_draw();
    contest();
    show_score();

    round++;
    competition_draw();
    contest();
    show_score();

    save_record();
    init_comp();
}

void interface:: load_record(){
    ifstream ifs("competition.csv", ios::in);
    if(!ifs.is_open()){
        record_file_is_empty=true;
        cout<< "record does not exist"<< endl;
        ifs.close();
        return;
    }

    char ch;
    ifs>> ch;
    if(ifs.eof()){
        cout<< "record is empty"<< endl;
        record_file_is_empty =true;
        ifs.close();
        return;
    }

    record_file_is_empty=false;
    ifs.putback(ch);
    string data;
    int index=1;
    while(getline(ifs, data)){
        int pos =-1;
        int start_pos =0;

        vector<string> v;

        while(true){
            pos = data.find(',',start_pos);
            if (pos == -1){
                break;
            }

            string line=data.substr(start_pos,pos-start_pos);
            v.push_back(line);

            start_pos = pos+1;
        }

        record.insert(make_pair(index, v));
        index++;

    }
    ifs.close();

}

void interface:: show_record(){
    load_record();

    for(map<int, vector<string> >:: iterator it= record.begin(); it!=record.end(); it++){
        cout<< "No. "<< it->first<< " competition's first place is "<< it->second[1]<< " with a score of "<< it->second[2]<< endl;
        cout<< "The second and third place are "<< it->second[4]<< " and "<< it->second[7]<< endl;
    }
}

void interface:: clear_record(){
    cout<<"Are you sure you want to clear the past record?"<< endl;
    cout<<"1. Yes"<< endl;
    cout<<"2. No"<< endl;

    int input;
    cin>> input;

    if(input==1){
        ofstream ofs("competition.csv",ios::trunc);
        ofs.close();
        init_comp();
        cout<< "complete!"<< endl;   
    }
    else{
        cout<< "Invalid input"<< endl;
    }
}

void interface:: exit_system(){
    cout<< endl;
    cout<< "thank you for using"<< endl;
    cout<< endl;
}