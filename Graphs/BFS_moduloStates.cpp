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
        queue<string>Q;
        vector<string>SP(n);
        bitset<32001>visited(0);
        visited[1]=1;
        q.push(1);
        SP[1]="1";
        Q.push("1");

        while(!q.empty())
        {
            ll c = q.front();
            string s = Q.front();
            //cout<<c<<" "<<s<<" "<<SP[c]<<"\n";
            if(c%n==0)
            break;
            q.pop();
            Q.pop();
            if(!visited[(10*c)%n])
            q.push((10*c)%n),Q.push(s+"0"),SP[(10*c)%n]=s+"0",visited[(10*c)%n]=1;
            if(!visited[(10*c+1)%n])
            q.push((10*c+1)%n),Q.push(s+"1"),SP[(10*c+1)%n]=s+"1",visited[(10*c+1)%n]=1;
        }

        cout<<SP[0]<<"\n";
    }
}
