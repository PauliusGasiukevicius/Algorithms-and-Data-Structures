#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    string a,b;
    int cs=0;
    while(getline(cin,a))
    {
        getline(cin,b);
        if(cs++)cout<<"\n";
        a="*"+a;
        b="*"+b;
        vector<vector<int>>DP(a.size(),vector<int>(b.size(),oo));
        vector<vector<int>>fromX(a.size(),vector<int>(b.size(),-1));
        vector<vector<int>>fromY(a.size(),vector<int>(b.size(),-1));
        for(int i=0; i<a.size(); i++)
            DP[i][0]=i,fromX[i][0]=i-1,fromY[i][0]=0;
        for(int j=0; j<b.size(); j++)
            DP[0][j]=j,fromX[0][j]=0,fromY[0][j]=j-1;

        fromX[0][0]=fromY[0][0]=-1;

        //gets DP matrix, and fromXY matrices filled (for solution, and its restoration)
        for(int i=1; i<a.size(); i++)
        for(int j=1; j<b.size(); j++)
            if(a[i]==b[j])//match
            DP[i][j]=DP[i-1][j-1],fromX[i][j]=i-1,fromY[i][j]=j-1;
            else if(DP[i-1][j-1]==min({DP[i-1][j],DP[i][j-1],DP[i-1][j-1]}))
                DP[i][j]=1+DP[i-1][j-1],fromX[i][j]=i-1,fromY[i][j]=j-1;
            else if(DP[i-1][j]==min({DP[i-1][j],DP[i][j-1],DP[i-1][j-1]}))
                DP[i][j]=1+DP[i-1][j],fromX[i][j]=i-1,fromY[i][j]=j;
            else if(DP[i][j-1]==min({DP[i-1][j],DP[i][j-1],DP[i-1][j-1]}))
                DP[i][j]=1+DP[i][j-1],fromX[i][j]=i,fromY[i][j]=j-1;

        int n = a.size()-1, m = b.size()-1;
        vector<pair<int,int>>path;
        while(min(n,m)>-1)
        {
            path.push_back({n,m});
            int nwm = fromY[n][m];
            n=fromX[n][m];
            m=nwm;
        }

        reverse(path.begin(),path.end());

        vector<string>ats;
        cout<<DP[a.size()-1][b.size()-1]<<"\n";
        int del = 0;
        int step = 1;
        for(int i=1; i<path.size(); i++)
        {
            int r1 = path[i-1].first;
            int c1 = path[i-1].second;
            int r2 = path[i].first;
            int c2 = path[i].second;

            if(DP[r1][c1]==DP[r2][c2]); // free move
            else
            {
                if(r1==r2)//horizontal move {insert}
                    cout<<step++<<" Insert "<<c2<<","<<b[c2]<<"\n",del--;
                else if(c1==c2)//vertical move {delete}
                    cout<<step++<<" Delete "<<r2-del<<"\n",del++;
                else //diagonal {replace}
                    cout<<step++<<" Replace "<<r2-del<<","<<b[c2]<<"\n";
            }
        }
    }
}
