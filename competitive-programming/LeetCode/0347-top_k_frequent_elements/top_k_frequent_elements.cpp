using namespace std;

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution 
{
    public:
        vector<int> topKFrequent(vector<int>& nums, int k)
        {
            unordered_map<int, int> freq;

            for (int num : nums) freq[num]++;

            vector<vector<int>> groups(nums.size() + 1);

            for (auto& [key, count] : freq) groups[count].push_back(key);

            vector<int> res;

            for (int i = groups.size() - 1; i > 0; i--)
            {
                for (int num : groups[i])
                {
                    res.push_back(num);

                    if (res.size() == k) return res;
                }
            }

            return res;
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

    int k;
    cin >> k;

    Solution sol;
    vector<int> res = sol.topKFrequent(nums, k);

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}