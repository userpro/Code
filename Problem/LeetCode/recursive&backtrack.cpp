#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <set>
#include <numeric>
#include <iostream>
using namespace std;

class Solution
{
public:
    /* 78 */
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> cur;
        for (int i = 0; i < (1<<nums.size()); i++)
        {
            for (int j = 0; j < nums.size(); j++)
                if (i & (1<<j))
                    cur.push_back(nums[j]);
            ret.push_back(cur);
            cur.clear();
        }
        return ret;
    }

    /* 90 */
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> path;
        sort(nums.begin(), nums.end());
        subsetsWithDup_helper(nums, 0, path, ret);
        return ret;
    }

    void subsetsWithDup_helper(vector<int> &s, int begin, vector<int> &path, vector<vector<int>> &ret)
    {
        ret.push_back(path);
        for (int i = begin; i < s.size(); i++)
        {
            if (i != begin && s[i] == s[i - 1]) continue;
            path.push_back(s[i]);
            subsetsWithDup_helper(s, i + 1, path, ret);
            path.pop_back();
        }
    }

    /* 40 */
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ret;
        vector<int> path;
        sort(candidates.begin(), candidates.end());
        combinationSum2_helper(candidates, 0, 0, target, path, ret);
        return ret;
    }

    void combinationSum2_helper(vector<int> &s, int begin, int sum, int target, vector<int> &path, vector<vector<int>> &ret)
    {
        if (sum == target)
        {
            ret.push_back(path);
            return;
        }
        if (sum > target)
            return;
        for (int i = begin; i < s.size(); i++)
        {
            if (i != begin && s[i] == s[i - 1]) continue;
            path.push_back(s[i]);
            sum += s[i];
            combinationSum2_helper(s, i + 1, sum, target, path, ret);
            path.pop_back();
            sum -= s[i];
        }
    }

    /* 22 */
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        string path;
        generateParenthesis_helper(n, n, path, ret);
        return ret;
    }

    void generateParenthesis_helper(int lhs, int rhs, string &path, vector<string> &ret)
    {
        if (lhs == 0 && rhs == 0)
        {
            ret.push_back(path);
            return;
        }

        if (lhs > 0)
        {
            path += '(';
            generateParenthesis_helper(lhs-1, rhs, path, ret);
            path.pop_back();
        }
        if (rhs > 0 && lhs < rhs)
        {
            path += ')';
            generateParenthesis_helper(lhs, rhs-1, path, ret);
            path.pop_back();
        }
    }

    /* 51 */
    vector<vector<string>> solveNQueens(int n) {
        int **cnt =  new int*[n];
        for (int i = 0; i < n; i++) 
        {
            cnt[i] = new int[n];
            memset(cnt[i], 0, sizeof(int) * n);
        }
        vector<vector<string>> ret;
        vector<string> path;
        solveNQueens_helper(n, 0, path, ret, cnt);
        delete [ ] cnt;
        return ret;
    }

    void solveNQueens_helper(int n, int row, vector<string> &path, vector<vector<string>> &ret, int **cnt)
    {
        if (row >= n)
        {
            ret.push_back(path);
            return;
        }

        for (int j = 0; j < n; j++)
        {
            if (cnt[row][j] == 0)
            {
                /* 米字标记 */
                cnt[row][j]++;
                int c1, c2;
                c1 = c2 = j;
                for (int i = row + 1; i < n; i++)
                {
                    if (--c1 >= 0) cnt[i][c1]++;
                    if (++c2 < n) cnt[i][c2]++;
                    cnt[i][j]++;
                }
                /* 生成该行棋盘 */
                string s;
                for (int i = 0; i < n; i++) 
                    s += '.';
                s[j] = 'Q';
                path.push_back(s);
                solveNQueens_helper(n, row + 1, path, ret, cnt);
                path.pop_back();

                /* 复原上一轮棋盘 */
                cnt[row][j]--;
                c1 = c2 = j;
                for (int i = row + 1; i < n; i++)
                {
                    if (--c1 >= 0) 
                    {
                        if (cnt[i][c1] - 1 <= 0) cnt[i][c1] = 0;
                        else cnt[i][c1]--;
                    }
                    if (++c2 < n)  
                    {
                        if (cnt[i][c2] - 1 <= 0) cnt[i][c2] = 0;
                        else cnt[i][c2]--;
                    }
                    if (cnt[i][j] - 1 <= 0) cnt[i][j] = 0;
                    else cnt[i][j]--;
                }
            }
        }
    }

    /* 473 TLE */
    // bool makesquare(vector<int>& nums) {
    //     if (nums.empty()) return false;
    //     vector<int> sums(4, 0);
    //     return makesquare_helper(sums, nums, 0);
    // }

    // bool makesquare_helper(vector<int> &sums, vector<int> &nums, int idx)
    // {
    //     if (idx == nums.size())
    //         return sums[0] == sums[1] && sums[1] == sums[2] && sums[2] == sums[3];

    //     for (int i = 0; i < 4; i++)
    //     {
    //         sums[i] += nums[idx];
    //         if (makesquare_helper(sums, nums, idx + 1)) return true;
    //         sums[i] -= nums[idx];
    //     }
    //     return false;
    // }

    /* 473 AC */
    bool makesquare(vector<int>& nums) {
        int n = nums.size();

        long sum = accumulate(nums.begin(), nums.end(), 0l);
        if (sum % 4)
            return false;
        long sideLen = sum / 4;
        // need to solve the problem of partitioning nums into four equal subsets each having
        // sum equal to sideLen
        vector<int> usedMasks;
        // validHalfSubsets[i] == true iff the subset represented by bitmask i
        // has sum == 2*sideLen, AND the subset represented by i can be further partitioned into
        // two equal subsets. See below for how it is used.
        vector<bool> validHalfSubsets(1<<n, false);

        // E.g., if n = 5, (1 << 5 - 1) = 11111 represents the whole set
        int all = (1 << n) - 1;
        // go through all possible subsets each represented by a bitmask
        for (int mask = 0; mask <= all; mask++) {
            long subsetSum = 0;
            // calculate the sum of this subset
            for (int i = 0; i < 32; i++) {
                if ((mask >> i) & 1)
                    subsetSum += nums[i];
            }
            // if this subset has what we want
            if (subsetSum == sideLen) {
                for (int usedMask : usedMasks) {
                    // if this mask and usedMask are mutually exclusive
                    if ((usedMask & mask) == 0) {
                        // then they form a valid half subset whose sum is 2 * sideLen,
                        // that can be further partitioned into two equal subsets (usedMask and mask)
                        int validHalf = usedMask | mask;
                        validHalfSubsets[validHalf] = true;
                        // if in the past we concluded that the other half is also a valid
                        // half subset, DONE!
                        if (validHalfSubsets[all ^ validHalf])
                            return true;
                    }
                }
                usedMasks.push_back(mask);
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums {12,12,12,12,12,12,12,12,12,12,12,12,12};
    Solution solve;
    auto ret = solve.makesquare(nums);
    cout << ret << endl;
    return 0;
}