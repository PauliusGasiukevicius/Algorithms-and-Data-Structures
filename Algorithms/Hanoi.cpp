#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void printState(vector<int>A,vector<int>B,vector<int>C)
{
    if(B[0]=='A')swap(A,B);
    if(C[0]=='A')swap(A,C);
    if(B[0]=='C')swap(B,C);

    cout<<"A=>"<<(A.size()<=1?"":"  ");
    for(int i=1; i<A.size(); i++)cout<<" "<<A[i];
    cout<<"\n";

    cout<<"B=>"<<(B.size()<=1?"":"  ");
    for(int i=1; i<B.size(); i++)cout<<" "<<B[i];
    cout<<"\n";

    cout<<"C=>"<<(C.size()<=1?"":"  ");
    for(int i=1; i<C.size(); i++)cout<<" "<<C[i];
    cout<<"\n\n";
}

void solve(vector<int>&A,vector<int>&B,vector<int>&C, int& m, int n)
{//A - from, C - to, B - spare
    if(m<1)return;
    if(n==1)
    {
        C.push_back(A.back());
        A.pop_back();
        printState(A,B,C);
        m--;
        return;
    }

    solve(A,C,B,m,n-1);
    if(m<1)return;
    C.push_back(A.back());
    A.pop_back();
    m--;
    printState(A,B,C);
    if(m<1)return;
    solve(B,A,C,m,n-1);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,cs=1;
    while(cin>>n>>m && n)
    {
        cout<<"Problem #"<<cs++<<"\n\n";
        vector<int>A(1,'A'),B(1,'B'),C(1,'C');
        for(int i=n; i>=1; i--)
            A.push_back(i);

        printState(A,B,C);
        solve(A,B,C,m,n);
    }
}
