#include <bits/stdc++.h>
using namespace std;

bool check(vector<vector<int>>&M, int r, int c)
{
    for(int k=1; r+k<M.size() && c+k<M.size(); k++)
        if(M[r+k][c+k])return false;
    for(int k=1; r-k<M.size() && c+k<M.size(); k++)
        if(M[r-k][c+k])return false;
    for(int k=1; r+k<M.size() && c-k<M.size(); k++)
        if(M[r+k][c-k])return false;
    for(int k=1; r-k<M.size() && c-k<M.size(); k++)
        if(M[r-k][c-k])return false;
    return true;
}

void solve(vector<vector<int>>&M, int r, vector<vector<int>>&ats, bool C[])
{
    if(!ats.empty())return;
    if(r==M.size())
    {
        ats=M;
        return;
    }

    for(int c=0; c<M.size(); c++)
        if(check(M,r,c) && !C[c])
    {
        M[r][c]=C[c]=1;
        solve(M,r+1,ats,C);
        M[r][c]=C[c]=0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
   int n;
   cin>>n;
   vector<vector<int>>M(n,vector<int>(n)),ats;
   bool C[1001]={};
   solve(M,0,ats,C);

   if(ats.empty())
    cout<<"Not possible\n";
   else
   {
       for(auto&v:ats)
        for(int i=0; i<v.size(); i++)
        cout<<v[i]<<(i+1==v.size()?"\n":" ");
   }
}
