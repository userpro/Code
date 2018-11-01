#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
using namespace std;

class Solution {
public:
    /* 455 */
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if (g.empty() || s.empty()) return 0;
        auto cmp = [](int i, int j) { return i > j; };
        std::sort(g.begin(), g.end(), cmp);
        std::sort(s.begin(), s.end(), cmp);
        int tot=0;
        auto g_s = g.begin();
        for (auto i : s)
        {
            while (i < *g_s && g_s < g.end()) g_s++;
            if (g_s == g.end()) break;
            tot++;
            g_s++;
        }
        return tot;
    }

    /* 376 */
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int diff = 0, flag = 0;
        auto ans = nums.size();
        for (auto i = 1; i < nums.size(); i++)
        {
            diff = nums[i] - nums[i - 1];
            if (diff == 0) ans--;
            else if (diff > 0) flag == 1 ? ans-- : flag = 1;
            else if (diff < 0) flag == -1 ? ans-- : flag = -1;
        }

        return ans;
    }

    /* 402 */
    string removeKdigits(string num, int k) {
        string res("");
        int n = num.size(), m = n - k;
        for (char c : num)
        {
            while (k && res.size() && res.back() > c)
            {
                res.pop_back();
                k--;
            }
            res.push_back(c);;
        }

        res.resize(m);
        while (!res.empty() && res[0] == '0') res.erase(res.begin());
        return res.empty() ? "0" : res;
    }

    /* 55 */
    bool canJump(vector<int>& nums) {
        int left = 0, right = 0;
        while (left < nums.size() && left <= right)
        {
            right = std::max(right, nums[left]+left);
            left++;
        }
        if (right >= nums.size() - 1) 
            return true;
        return false;
    }

    /* 45 */
    int jump(vector<int>& nums) {
        int max_to = 0;
        int min_step = 0;
        int cur_in = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (cur_in < i)
            {
                min_step++;
                cur_in = max_to;
            }
            max_to = std::max(max_to, nums[i] + i);
        }
        return min_step;
    }

    /* 452 选endpoint排序 */
    int findMinArrowShots(vector<pair<int, int>>& points) {
        auto cmp = [] (pair<int, int>p1, pair<int, int>p2)
            { return p1.second < p2.second; };
        sort(points.begin(), points.end(), cmp);
        
        int i = 0, j = 0, t = 0, cnt = 0;
        for (i = 0; i < points.size(); i++)
        {
            j = i;
            t = points[j].second;
            while (j + 1 < points.size() && points[j + 1].first <= t) j++;
            i = j;
            cnt++;
        }
        return cnt;
    }
};

int main(int argc, char const *argv[])
{
    vector<pair<int, int>> A {{10,16}, {2,8}, {1,6}, {7,12}};
    vector<pair<int, int>> B {{1,2}, {3,4}, {5,7}, {7,8}};
    vector<pair<int, int>> C {{3,9},{7,12},{3,8},{6,8},{9,10},{2,9},{0,9},{3,9},{0,6},{2,8}};
    vector<pair<int, int>> D {{9,12},{1,10},{4,11},{8,12},{3,9},{6,9},{6,7}};
    Solution solve;
    cout << solve.findMinArrowShots(A) << endl;
    cout << solve.findMinArrowShots(D) << endl;
    return 0;
}