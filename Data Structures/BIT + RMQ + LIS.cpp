#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void add(vector<int>&BIT, int c, int v)
{
    for(c;c<BIT.size(); c+=c&-c)
        BIT[c]=max(BIT[c],v);
}

int get(vector<int>&BIT, int c, int s=0)
{
    for(c;c;c-=c&-c)
        s=max(s,BIT[c]);
    return s;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    while(cin>>n && n>0)
    {
    vector<array<int,2>>A(n);
    vector<int>BIT(n+1);
    vector<int>LIS(n+1);
    vector<int>O(n+1);
    vector<int>MX(n+2);

    for(int i=0; i<n; i++)
        cin>>A[i][0],A[i][1]=i+1,O[i+1]=A[i][0];
    sort(A.begin(),A.end());

    for(int i=0; i<n; i++)
        {
            LIS[A[i][1]] = 1 + get(BIT,A[i][1]);
            add(BIT,A[i][1],LIS[A[i][1]]);
           //cout<<A[i][1]<<" "<<LIS[A[i][1]]<<"\n";
        }

    vector<int>ats;
    int mx = *max_element(LIS.begin(),LIS.end());

    for(int i=n; i>=1; i--)
        if(LIS[i]==mx)
        ats.push_back(O[i]),MX[mx]=max(MX[mx],O[i]);
        else if(O[i] < MX[LIS[i]+1])
        ats.push_back(O[i]),MX[LIS[i]]=max(MX[LIS[i]],O[i]);

    cout<<ats.size()<<"\n";
    sort(ats.begin(),ats.end());
    for(int j=0; j<ats.size(); j++)
        cout<<ats[j]<<(j+1<ats.size() ? " " : "\n");
    }
}
