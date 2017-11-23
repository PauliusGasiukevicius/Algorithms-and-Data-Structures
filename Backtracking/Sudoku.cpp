/*
* Assumes standart Sudoku (9x9 board with 3x3 larger cells)
*/

#include <bits/stdc++.h>
using namespace std;

void print(vector<string>&a)
{
for(int i=0; i<9; i++)
    for(int j=0; j<9; j++)
        cout<<a[i][j]<<(j==8?"\n":" ");
}

bool canPlace(int r, int c, char ch, vector<string>&a)
{
    for(int i=0; i<9; i++)
        if(a[r][i]==ch || a[i][c]==ch)
        return false;

    int R = 0;
    if(r > 2)R=3;
    if(r > 5)R=6;
    int C = 0;
    if(c > 2)C=3;
    if(c > 5)C=6;

    for(int i=R; i<R+3; i++)
        for(int j=C; j<C+3; j++)
        if(a[i][j]==ch)
        return false;
    return true;
}

void solve(int r, int c,vector<string>&a, vector<string>&sol)
{
    if(r==9)
    {
        sol=a;
        return;
    }
    if(!sol.empty())return;

    if(a[r][c]!='0')
    {
        c++;
        if(c==9)c=0,r++;
        solve(r,c,a,sol);
        return;
    }

    for(int i='1'; i<='9'; i++)
    if(canPlace(r,c,i,a))
    {
        a[r][c]=i;
        solve((c==8?r+1:r),(c==8?0:c+1),a,sol);
        a[r][c]='0';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);

    string s;
    int x,ats = 0;

    while(cin>>s>>x)
    {
        vector<string>a(9,"");
        for(int i=0; i<9; i++)
            cin>>a[i];
        vector<string>solution;
        solve(0,0,a,solution);
        s=string(solution[0].begin(),solution[0].begin()+3);
        stringstream ss(s);
        ss>>x;
        ats+=x;
        print(solution);
    }

    cout<<ats;

    return 0;
}
