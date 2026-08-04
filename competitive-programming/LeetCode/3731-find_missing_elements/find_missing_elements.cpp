using namespace std;

#include <iostream>
#include <vector>
#include <cmath>

class Solution
{
    public:
        vector<int> findMissingElements(vector<int>& nums)
        {
            int mini = INT_MAX;
            int maxi = INT_MIN;

            for (int num : nums)
            {
                mini = min(num, mini);
                maxi = max(num, maxi);
            }

            vector<bool> bitmap(maxi - mini + 1, false);
            for (int num : nums) bitmap[num - mini] = true;

            vector<int> res;
            for (int i = 0; i <= maxi - mini; i++)
            {
                if (!bitmap[i]) res.push_back(i + mini);
            }

            return res;
        }
};

int main() {

    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) cin >> nums[i];

    Solution sol;
    vector<int> res = sol.findMissingElements(nums);
    
    for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
    cout << endl;

    return 0;
}