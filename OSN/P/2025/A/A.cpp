using namespace std;

#include <iostream>
#include <unordered_map>

class Solution {
public:
    int stringCantik(string s) {

        unordered_map<char, int> umap;

        int idx = 0;
        int res = -1;
        
        while (idx < s.length())
        {
            char c = s[idx];

            if (c == 'O' || c == 'S' || c == 'N')
            {
                umap[c]++;
            }
            if (umap['O'] && umap['S'] && umap['N'] && c == 'P')
            {
                res = max(res + 1, umap['O'] + umap['S'] + umap['N'] + 1);
            }
            idx++;
        }

    return res;

    }
};

int main ()
{
    string s;
    cin >> s;

    Solution sol;
    cout << sol.stringCantik(s) << endl;

    return 0;
};