#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2
multiset<int>G[100001];
int in[100001];
int out[100001];
vector<string> euler;
bitset<100001>v(0),e(0);

string getString(int x)
{
    char a = x/256;
    char b = x%256;
    string s;
    s+=a;
    s+=b;
    return s;
}

int getKey(string s)
{
    return s[0]*256+s[1];
}

void dfs(int c)
{
    while(!G[c].empty())
    {
        int u = *G[c].begin();
        G[c].erase(G[c].find(u));
        dfs(u);
    }
    euler.push_back(getString(c));
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
   int n;
   string s;
   cin>>n;

   while(n--)
   {
       cin>>s;
       int u = getKey(s.substr(0,2));
       int v = getKey(s.substr(1,2));
       G[u].insert(v);
       in[v]++;
       out[u]++;
       e[u]=e[v]=1;
   }

   vector<int>st,en;
   for(int i=0; i<256*256; i++)
    if(in[i]!=out[i])
   {
       if(abs(in[i]-out[i]) > 1)return cout<<"NO",0;
       if(in[i] > out[i])en.push_back(i);
       else st.push_back(i);
   }

   if(st.size() > 1 || en.size() > 1 || (st.size() + en.size())%2!=0)
    return cout<<"NO\n",0;

    int ch = getKey(s.substr(0,2));
    if(st.size()==1)ch=st[0];

    queue<int>q;
    q.push(ch);
    v[ch]=1;
    while(!q.empty())
    {
        int c = q.front();
        q.pop();
        for(auto u : G[c])
            if(!v[u])v[u]=1,q.push(u);
    }

    if(v.count()!=e.count())
        return cout<<"NO\n",0;

    cout<<"YES\n";
    dfs(ch);
    reverse(euler.begin(),euler.end());
    string ats;
    for(int i=0; i<euler.size(); i++)
    {
        if(!ats.empty())ats.pop_back();
        ats+=euler[i];
    }
    cout<<ats<<"\n";
}
