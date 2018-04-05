#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    priority_queue<int>maxHeap;
    priority_queue<int,vector<int>,greater<int>>minHeap;

    string s;

    while(cin>>s)
    {
        if(s.back()=='#')
        {
            cout<<minHeap.top()<<endl;
            minHeap.pop();
        }
        else
        {
            stringstream ss(s);
            int x;
            ss>>x;
            if(maxHeap.empty() || x <= maxHeap.top())
                maxHeap.push(x);
            else minHeap.push(x);
        }
        if(minHeap.empty() && maxHeap.empty())continue;

            while(maxHeap.size() >= minHeap.size())
                minHeap.push(maxHeap.top()),maxHeap.pop();

            while(minHeap.size() > maxHeap.size()+1)
                maxHeap.push(minHeap.top()),minHeap.pop();
    }
}
