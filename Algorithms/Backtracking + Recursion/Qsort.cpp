#include <bits/stdc++.h>
using namespace std;
#define ll long long

int pivot(vector<int>&A, int l, int r)
{
    int x = l + rand()%(r-l+1);
    swap(A[x],A[l]);
    int j = l+1;

    for(int i=l+1; i<=r; i++)
        if(A[i] <= A[l])
        swap(A[i],A[j]),j++;

    swap(A[l],A[j-1]);
    return j-1;
}

void Qsort(vector<int>&A, int l, int r)
{
    if(l>=r)return;
    int piv = pivot(A,l,r);
    Qsort(A,l,piv-1);
    Qsort(A,piv+1,r);
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int>A(n);
    for(int&x:A)cin>>x;
    Qsort(A,0,n-1);
    for(int&x:A)cout<<x<<"\n";
}
