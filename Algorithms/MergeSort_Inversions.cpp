#include <bits/stdc++.h>
using namespace std;

long long Merge(vector<int>&A, int l, int m, int r) //Merges [l,m] with [m+1,r]
{
    vector<int>left(A.begin()+l,A.begin()+m+1);
    vector<int>right(A.begin()+m+1,A.begin()+r+1);
    int p1=0, p2=0;
    long long inv = 0;

    while(p1 < left.size() && p2 < right.size())
        if(left[p1] <= right[p2])
        A[l++]=left[p1++];
        else
        A[l++]=right[p2++], inv+=left.size()-p1;

    while(p1<left.size())
        A[l++]=left[p1++];

    while(p2<right.size())
        A[l++]=right[p2++];

    return inv;
}

long long MergeSort(vector<int>&A, int l, int r) //Also returns inversions
{
    if(l>=r)return 0;
    long long inv = 0;
    int m = l + (r-l)/2;
    inv+= MergeSort(A,l,m);
    inv+= MergeSort(A,m+1,r);
    inv+= Merge(A,l,m,r);
    return inv;
}
int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int>A(n);
    for(int&x : A)cin>>x;
    cout<<"Inversions of array A : "<<MergeSort(A,0,n-1)<<"\n";
}
