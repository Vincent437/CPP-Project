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
using namespace std;
#include"02 competitor.h"

class interface{
    public:
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    map<int, competitor> competitor_map;

    int round;

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
    void exit_system();
    
};