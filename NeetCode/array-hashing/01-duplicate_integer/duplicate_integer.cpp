using namespace std;

#include<vector>
#include<unordered_set>
#include<iostream>

class Solution 
{
    public:
        bool hasDuplicate(vector<int>& nums) 
        {
            unordered_set<int> seen;

            for (int num : nums) 
            {
                if (seen.count(num))
                {
                    return true;
                }

                seen.insert(num);
            }

            return false;
        }
};

int main ()
{
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    Solution sol;
    cout << boolalpha << sol.hasDuplicate(nums) << endl;

    return 0;
}