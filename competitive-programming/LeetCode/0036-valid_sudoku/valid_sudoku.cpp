using namespace std;

#include <iostream>
#include <vector>

class Solution 
{
    public:
        bool isValidSudoku(vector<vector<char>>& board)
        {
            vector<vector<bool>> rows(9, vector<bool>(9, false));
            vector<vector<bool>> cols(9, vector<bool>(9, false));
            vector<vector<bool>> square(9, vector<bool>(9, false));

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (board[i][j] != '.')
                    {
                        int v = board[i][j] - '1';

                        if (rows[i][v]) return false;
                        else rows[i][v] = true;

                        if (cols[i][v]) return false;
                        else cols[i][v] = true;

                        int idx = i / 3 * 3 + j / 3;
                        
                        if (square[idx][v]) return false;
                        else square[idx][v] = true;
                    }
                }
            }

            return true;
        }
};
