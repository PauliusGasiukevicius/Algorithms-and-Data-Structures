/*
Solves a task of finding whether some query number x thats < 1e9 can be obtained by summing some subset of given set (with repetitions allowed)
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int A[5001];
int SP[50001];
vector<pair<int,int>>G[50001];

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    for(int i=0; i<n; i++)cin>>A[i];
    int m = A[0];

    for(int i=0; i<m; i++)
        {
        SP[i]=INT_MAX;
        for(int&e : A)
        G[i].push_back({e,(e+i)%m});
        }

    SP[0]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push({0,0});

    while(!q.empty())
    {
        int w = q.top().first;
        int c = q.top().second;
        q.pop();

        for(auto&p : G[c])
            if(w+p.first < SP[p.second])
        SP[p.second]=w+p.first,q.push({w+p.first,p.second});
    }

    int k,x;
    cin>>k;

    while(k--)
    {
        cin>>x;
        if(x>=SP[x%m])cout<<"TAK\n";
        else cout<<"NIE\n";
    }
}
