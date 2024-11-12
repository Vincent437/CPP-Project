#include<iostream>
using namespace std;
#include<vector>

#include<algorithm>
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        vector<int>:: iterator it = find(nums.begin(), nums.end(), target);
        if(it!=nums.end()){
            int flag=0;
            for(vector<int>::iterator it2= nums.begin(); it2!=it; it2++){
                flag++;
            }
            return flag;
        }
        else{
            int flag = 0;
            for(vector<int>::iterator it2= nums.begin(); it2!=nums.end(); it2++){
                if(target< *it2){
                    return flag;
                }
                else{
                    flag++;
                }
            }
        }
    }
};

int main(){
    vector<int> nums = {1,3,5,6};
    int target = 5;
    Solution s;
    cout<< s.searchInsert(nums,target)<< endl;
    return 0;
}

