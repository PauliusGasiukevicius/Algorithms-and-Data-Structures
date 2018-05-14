#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void print(vector<vector<ll>>&A)
{
    cout<<A.size()<<" "<<A[0].size()<<endl;
    for(int i=0; i<A.size(); i++)
        for(int j=0; j<A[i].size(); j++)
        cout<<A[i][j]<<(j+1==A[i].size()?"\n":" ");
}

vector<vector<ll>> mul(vector<vector<ll>>A, vector<vector<ll>>B, ll M)
{
    vector<vector<ll>>C(A.size(),vector<ll>(A.size()));
    for(int i=0; i<A.size(); i++)
    for(int j=0; j<A.size(); j++)
    for(int k=0; k<A.size(); k++)
        C[i][j] = (C[i][j] + A[i][k]*B[k][j])%M;

    return C;
}

vector<vector<ll>> powMatrix(vector<vector<ll>>A, ll d, ll M)
{
    if(d==1)return A;
    if(d&1)return mul(A,powMatrix(A,d-1,M),M);
    return powMatrix(mul(A,A,M),d/2,M);
}

int main()
{
    /*
R-numbers are numbers which have the property that they do not have the digit '0 '
and sum of every two adjacent digits of the number is prime.
123 is a R-number because 1+2 =3 and 2+3 =5 and 3 , 5 are primes.
How many R-numbers can be formed with atmost length N?
i.e R-numbers of length 1 + R-numbers of length 2 + R-numbers of length 3+....... R-numbers of length N
Length of a number = Number of digits in the number
Only four single digit numbers are R-numbers which are nothing but single digit primes 2,3,5,7
*/
    ios::sync_with_stdio(0);
    int t,n;
    vector<vector<ll>>A(10,vector<ll>(10));
    vector<int>on[10];
    on[0]={0,1,2,3,4,5,6,7,8,9};
    on[1]={1,2,4,6};
    on[2]={1,3,5,9};
    on[3]={2,4,8};
    on[4]={1,3,7,9};
    on[5]={2,6,8};
    on[6]={1,5,7};
    on[7]={4,6};
    on[8]={3,5,9};
    on[9]={2,4,8};

    for(int i=0; i<10; i++)
        for(auto&j:on[i])
        A[i][j]=1;

    ll M = 1e9+7;
    vector<ll>R = {4,4,4,3,4,3,3,2,3,3};

    cin>>t;
    while(t--)
    {
        cin>>n;
        if(n==1)
        {cout<<"4\n";continue;}
        auto B = powMatrix(A,n-1,M);

        ll ats = 0;
        for(int i=0; i<B.size(); i++)
            ats=(ats+R[i]*B[0][i])%M;

        cout<<ats<<"\n";
    }
}
