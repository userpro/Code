#include <cstdio>
#include <iostream>
#include <deque>
#include <vector>

class MyStack {
private:
    std::deque<int> que;

public:
    /** Initialize your data structure here. */
    MyStack() {
        que.clear();
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        que.push_back(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int a = que.back();
        que.pop_back();
        return a;
    }
    
    /** Get the top element. */
    int top() {
        return que.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return que.empty();
    }
};

class MyQueue {
private:
    std::deque<int> que;

public:
    /** Initialize your data structure here. */
    MyQueue() {
        que.clear();
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        que.push_back(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int a = que.front();
        que.pop_front();
        return a;
    }
    
    /** Get the front element. */
    int peek() {
        return que.front();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return que.empty();
    }
};

class MinStack {
private:
    std::deque<std::pair<int, int> > que;

public:
    /** initialize your data structure here. */
    MinStack() {
        que.clear();
    }
    
    void push(int x) {
        if (!que.empty())
        {
            int a = std::min(x, que.back().second);
            que.push_back(std::make_pair(x, a));
        }
        else
            que.push_back(std::make_pair(x, x));
    }
    
    void pop() {
        que.pop_back();
    }
    
    int top() {
        return que.back().first;
    }
    
    int getMin() {
        return que.back().second;
    }
};

/* 215 */
class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        auto cmp = [] (int i, int j) { return i > j; };
        std::sort(nums.begin(), nums.end(), cmp);
        return nums[k-1];
    }
};

class MedianFinder {
private:
    std::vector<int> v;

public:
    /** initialize your data structure here. */
    MedianFinder() {
        v.clear();
    }
    
    void addNum(int num) {
        auto i = std::upper_bound(v.begin(), v.end(), num);
        if (i != v.end())
            v.insert(i, num);
        else
            v.push_back(num);
    }
    
    double findMedian() {
        if (v.size() % 2)
            return v[v.size()/2];
        else
            return (v[v.size()/2] + v[v.size()/2-1]) * 1.0 / 2;
    }
};

int main(int argc, char const *argv[])
{
    MedianFinder obj;
    obj.addNum(1);
    obj.addNum(2);
    obj.addNum(1);
    double param_1 = obj.findMedian();
    obj.addNum(3);
    double param_2 = obj.findMedian();
    printf("%f %f\n", param_1, param_2);
    return 0;
}