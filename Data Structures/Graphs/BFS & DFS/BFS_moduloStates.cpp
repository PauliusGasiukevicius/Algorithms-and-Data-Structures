#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
int main()
{
    ios::sync_with_stdio(0);
    ll t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        queue<ll>q;
        vector<int>visited(n,0);
        vector<int>P(n,-1);
        vector<int>E(n,0);
        visited[1]=E[1]=1;
        q.push(1);
 
        while(!q.empty())
        {
            ll c = q.front();
            if(c%n==0)
            break;
 
            q.pop();
            if(!visited[(10*c)%n])
            q.push((10*c)%n),visited[(10*c)%n]=1,P[(10*c)%n]=c;
            if(!visited[(10*c+1)%n])
            q.push((10*c+1)%n),visited[(10*c+1)%n]=1,P[(10*c+1)%n]=c,E[(10*c+1)%n]=1;
        }
 
        string ats;
        int c = 0;
 
        while(c!=-1)
        {
            ats+=('0'+E[c]);
            c=P[c];
        }
        reverse(ats.begin(),ats.end());
        cout<<ats<<"\n";
    }
}
