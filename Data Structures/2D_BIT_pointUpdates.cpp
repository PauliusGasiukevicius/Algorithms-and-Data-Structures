#include <bits/stdc++.h>
using namespace std;
#define ll long long

int BIT[1025][1025];
int A[1025][1025];
int N = 1024;

int query(int x, int y)
{
    int ats = 0;
    for(x; x>0; x-=(x&-x))
        for(int y1=y; y1>0; y1-=(y1&-y1))
        ats+=BIT[x][y1];
    return ats;
}

void update(int x, int y, int v)
{
    for(x; x<=N; x+=(x&-x))
        for(int y1=y; y1<=N; y1+=(y1&-y1))
        BIT[x][y1]+=v;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,x,y,x1,y1,v;
    string s;
    cin>>t;

    while(t--)
    {
        cin>>n;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=n; j++)
            BIT[i][j]=A[i][j]=0;

        while(cin>>s && s!="END")
        {
            if(s=="SET")
            cin>>x>>y>>v,update(x+1,y+1,-A[x][y]),A[x][y]=v,update(x+1,y+1,v);
            else
            {
            cin>>x>>y>>x1>>y1;
            cout<<query(x1+1,y1+1)-query(x,y1+1)-query(x1+1,y)+query(x,y)<<"\n";
            }
        }
        cout<<"\n";
    }
}
