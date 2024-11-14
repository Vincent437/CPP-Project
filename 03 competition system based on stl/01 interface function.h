#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<deque>
#include<random>
#include<algorithm>
#include<functional>
#include<numeric>
#include<time.h>
using namespace std;
#include"02 competitor.h"

class interface{
    public:
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    map<int, competitor> competitor_map;

    int round;

    bool record_file_is_empty;

    map<int, vector<string> > record;

    interface();

    ~interface();

    void show_manu();
    void init_comp();
    void create_competitor();
    void competition_draw();
    void contest();
    void show_score();
    void start_competition();
    void save_record();
    void load_record();
    void show_record();
    void clear_record();
    void exit_system();
    
};