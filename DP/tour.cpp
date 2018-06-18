/*
 You have won a contest sponsored by an airline. The prize is a ticket to travel around Canada, beginning in the most western point served by this airline, then traveling only from west to east until you reach the most eastern point served, and then coming back only from east to west until you reach the starting city. No city may be visited more than once, except for the starting city, which must be visited exactly twice (at the beginning and the end of the trip). You are not allowed to use any other airline or any other means of transportation.

Given a list of cities served by the airline and a list of direct flights between pairs of cities, find an itinerary which visits as many cities as possible and satisfies the above conditions beginning with the first city and visiting the last city on the list and returning to the first city. 
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
PROG: tour
LANG: C++14
*/

int n;
int M[101][101];
int DP[101][101];


int main()
{
    ios::sync_with_stdio(0);
    freopen("tour.in","r",stdin);
    freopen("tour.out","w",stdout);
    int m;
    cin>>n>>m;
    vector<string>A(n);
    map<string,int>mp;
    for(int i=0; i<n; i++)
        cin>>A[i],mp[A[i]]=i;

    for(int i=0; i<m; i++)
    {
        string a,b;
        cin>>a>>b;
        M[mp[a]][mp[b]]=M[mp[b]][mp[a]]=1;
    }

    //let DP[i][j] - maximum distinct cities visited when Person 1 is in city i
    //and Person 2 is in city j
    //Lets also assume person 1 is faster
    DP[0][0]=1;

    for(int i=0; i<n; i++) //where person A is
    for(int j=i; j<n; j++) //where person B is
        if(DP[i][j])
    for(int k=min(n-1,max(i,j)+1); k<n; k++)//where person X will go
       {
           if(M[i][k])
            DP[k][j]=DP[j][k]=max(DP[k][j],DP[i][j]+1);
           if(M[j][k])
            DP[i][k]=DP[k][i]=max(DP[i][k],DP[i][j]+1);
       }


    cout<<max(1,DP[n-1][n-1]-1)<<"\n";
}
