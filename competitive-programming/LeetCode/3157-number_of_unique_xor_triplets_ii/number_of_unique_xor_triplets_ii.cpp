using namespace std;

#include <vector>

int uniqueXorTriplets(vector<int>& nums)
{
    const int max_xor = 2048;

    vector<bool> pair_xor(max_xor, false);
    vector<bool> triplet_xor(max_xor, false);

    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i; j < nums.size(); j++)
        {
            pair_xor[nums[i] ^ nums[j]] = true;
        }
    }

    for (int res = 0; res < max_xor; res++)
    {
        if (pair_xor[res])
        {
            for (int value : nums)
            {
                triplet_xor[res ^ value] = true;
            }
        }
    }

    int count = 0;

    for (bool res : triplet_xor)
    {
        if (res) count++;
    }

    return count;
};