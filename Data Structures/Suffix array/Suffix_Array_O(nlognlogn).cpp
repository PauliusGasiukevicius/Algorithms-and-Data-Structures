#include <bits/stdc++.h>
using namespace std;

void buildSufixArray(string&s, vector<int>&SA)
{
    int n = SA.size();
    vector<vector<int>>suffixes(s.size(),vector<int>(3));// all vectors inside are [rank][next_rank][index]
    vector<int>indexes(n);// we need to keep track which suffix is in which position in array later

    for(int i=0; i<n; i++)
        suffixes[i][2]=i,suffixes[i][0]=s[i],indexes[i]=i;

    for(int i=0; i<n; i++)
        suffixes[i][1]=(i+1<n ? suffixes[i+1][0] : -1);

    sort(suffixes.begin(),suffixes.end());

    for(int sz=2; sz<n; sz*=2)
    {
        int prevRank = suffixes[0][0];
        suffixes[0][0]=0;
        for(int i=1; i<n; i++)
        {
            int oldRank = suffixes[i][0];

            if(oldRank==prevRank && suffixes[i][1] == suffixes[i-1][1])suffixes[i][0] = suffixes[i-1][0];
            else suffixes[i][0] = suffixes[i-1][0] + 1;

            prevRank = oldRank;
        }

        for(int i=0; i<n; i++)
            indexes[suffixes[i][2]] = i;

        for(int i=0; i<n; i++)
            suffixes[i][1] = (suffixes[i][2]+sz < n ? suffixes[indexes[suffixes[i][2]+sz]][0] : -1);

        sort(suffixes.begin(),suffixes.end());
    }

    for(int i=0; i<n; i++)
        SA[i]=suffixes[i][2];
}

int main()
{
    ios::sync_with_stdio(0);
    string test = "banana";
    vector<int>SA(test.size());
    buildSufixArray(test,SA);

    for(auto x : SA)
        cout<<x<<"\n";
}
