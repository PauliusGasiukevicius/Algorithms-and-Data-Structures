#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int t;
    //freopen("o.txt","w",stdout);
    cin>>t;
    cin.ignore();
    cin.ignore();
    string s,name,party,club;
    while(t--)
    {
        vector<vector<int>>M(3002,vector<int>(3002,0));
        vector<int>G[3002];
        int ppl_c = 1, party_c = 1001, club_c = 2001, en = 3001;
        map<string,int>mppl,mparty,mclub;
        vector<string>A(3002);

        while(getline(cin,s) && s!="")
        {
            stringstream ss(s);
            ss>>name>>party;

            if(!mppl.count(name))mppl[name]=ppl_c,A[ppl_c++]=name;
            if(!mparty.count(party))mparty[party]=party_c,A[party_c++]=party;

                G[0].push_back(mparty[party]);
                G[mparty[party]].push_back(0);
                M[0][mparty[party]]=2;

                G[mparty[party]].push_back(mppl[name]);
                G[mppl[name]].push_back(mparty[party]);
                M[mparty[party]][mppl[name]]=1;

            while(ss>>club)
            {
                if(!mclub.count(club))
                mclub[club]=club_c,A[club_c++]=club;

                G[mppl[name]].push_back(mclub[club]);
                G[mclub[club]].push_back(mppl[name]);
                G[en].push_back(mclub[club]);
                G[mclub[club]].push_back(en);
                M[mppl[name]][mclub[club]]=1;
                M[mclub[club]][en]=1;
            }
        }

        for(int i=0; i<3002; i++)
            for(int j=0; j<3002; j++)
            if(M[i][j]==2)M[i][j]=(club_c-2001+1)/2-1;

        int maxFlow=0;

        while(1)
        {
            queue<int>q;
            vector<int>P(3002,-1);
            vector<int>visited(3002,0);
            visited[0]=1;
            q.push(0);

            while(!q.empty() && q.front()!=en)
            {
                int c = q.front();
                q.pop();

                for(auto&u : G[c])
                    if(M[c][u] > 0 && !visited[u])
                    q.push(u),P[u]=c,visited[u]=1;
            }

            if(q.empty())break;
            vector<int>path;
            int c = en;
            int flow = +oo;
            while(c!=-1)
            {
                path.push_back(c);
                c=P[c];
            }
            reverse(path.begin(),path.end());

            for(int i=1; i<path.size(); i++)
                flow=min(flow,M[path[i-1]][path[i]]);

            for(int i=1; i<path.size(); i++)
                M[path[i-1]][path[i]]-=flow,M[path[i]][path[i-1]]+=flow;
            maxFlow+=flow;
        }

        if(maxFlow==club_c-2001)
        {
            for(int i=1; i<ppl_c; i++)
            for(int k=2001; k<club_c; k++)
            if(M[k][i]>0)
            cout<<A[i]<<" "<<A[k]<<"\n";
        }else cout<<"Impossible.\n";
            if(t)cout<<"\n";
    }
}
