#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int L[8001],R[8001];
//pre: root, left, right
//in: left, root, right

//Builds a Binary tree based on preorder and inorder traversals
int solve(vector<int>&pre, vector<int>&in, int l, int r, int l2, int r2)
{
    if(l >= r)return pre[l];
    int root = pre[l];

    for(int i=l2; i<=r2; i++)
        if(in[i]==root)
    {
        if(i>l2)//if left subtree exists
            L[root] = solve(pre,in,l+1,l+i-l2,l2,i-1);

        if(i<r2)//if right subtree exists
            R[root] = solve(pre,in,l+i-l2+1,r,i+1,r2);
    }

    return root;
}

void postOrder(vector<int>&traversal, int c)
{
    if(L[c])postOrder(traversal,L[c]);
    if(R[c])postOrder(traversal,R[c]);
    traversal.push_back(c);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    vector<int>pre(n),post(n),in(n);
    for(int&x:pre)cin>>x;
    for(int&x:post)cin>>x;
    for(int&x:in)cin>>x;
    vector<int>t;
    postOrder(t,solve(pre,in,0,n-1,0,n-1));

    cout<<(t==post ? "yes\n" : "no\n");
}
