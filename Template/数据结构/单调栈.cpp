// 一个元素向左遍历的第一个比它小的数的位置就是将它插入单调栈时栈顶元素的值，若栈为空，则说明不存在这么一个数。然后将此元素的下标存入栈，就能类似迭代般地求解后面的元素
Stack<int> S;
for(int i=1 ;i<=n ;i++){
    while(S.size() && a[S.top()] >= a[i]) S.pop();

    if(S.empty())     L[i] = 0;
    else              L[i] = S.top();

    S.push(i);
}