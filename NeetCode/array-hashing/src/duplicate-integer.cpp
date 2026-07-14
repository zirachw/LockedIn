using namespace std;

#include<vector>
#include<unordered_map>
#include<iostream>

class Solution {
public:
    bool hasDuplicate(vector<int>& nums) {

        unordered_map<int,int> umap;

        for(int i = 0; i < nums.size(); i++) {
            cout << nums[i] << endl;
            if (umap.find(nums[i]) == umap.end()) {
                umap[nums[i]] = 1;
            }
            else {
                return true;
            }
        }
        return false;
    }
};