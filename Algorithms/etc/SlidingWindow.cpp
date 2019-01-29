#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int n,k,ats=0;
    cin>>n;
    vector<int>A(n);
    for(int&x:A)cin>>x;
    cin>>k;

    deque<int>q;

    for(int i=0; i<n; i++)
    {
        while(!q.empty() && A[q.front()] < A[i])q.pop_front();
        q.push_front(i);
        while(!q.empty() && i-q.back() >= k)q.pop_back();
        if(i+1>=k)
            cout<<max(A[q.front()],A[q.back()])<<" ";
    }
}
