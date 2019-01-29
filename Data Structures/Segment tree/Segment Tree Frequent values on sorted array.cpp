#include <bits/stdc++.h>
using namespace std;
 
struct node
{
    pair<int,int>l,r,b; // left, right, best    pair<val,frequency>
};
 
void build(vector<node>&tree, int a[], int left, int right, int pos)
{
    if(left==right)
    {
        tree[pos].l = make_pair(a[left],1);
        tree[pos].r = make_pair(a[left],1);
        tree[pos].b = make_pair(a[left],1);
        return;
    }
 
    int mid = left + (right - left)/2;
 
    build(tree,a,left,mid,2*pos+1);
    build(tree,a,mid+1,right,2*pos+2);
 
        tree[pos].b = tree[2*pos+1].b;
        tree[pos].l = tree[2*pos+1].l;
        tree[pos].r = tree[2*pos+2].r;
 
        if(tree[2*pos+1].l.first == tree[2*pos+2].l.first)
            tree[pos].l.second = tree[2*pos+2].l.second + tree[2*pos+1].l.second;
 
        if(tree[2*pos+2].r.first == tree[2*pos+1].r.first)
            tree[pos].r.second = tree[2*pos+2].r.second + tree[2*pos+1].r.second;
 
        if(tree[2*pos+2].b.second > tree[pos].b.second)
            tree[pos].b = tree[2*pos+2].b;
 
        if(tree[pos].r.second > tree[pos].b.second)
            tree[pos].b = tree[pos].r;
 
        if(tree[pos].l.second > tree[pos].b.second)
            tree[pos].b = tree[pos].l;
 
        if(tree[2*pos+1].r.first == tree[2*pos+2].l.first && tree[2*pos+1].r.second + tree[2*pos+2].l.second > tree[pos].b.second)
            tree[pos].b.first = tree[2*pos+1].b.first, tree[pos].b.second = tree[pos*2+1].r.second + tree[pos*2+2].l.second;
}
 
node query(vector<node>&tree,int pos, int left, int right, int L, int R)
{
    node emp;
    emp.b = emp.r = emp.l = make_pair(0,0);
    if(left > right)return emp;
    if(left > R || right < L)return emp;
 
    if(left>=L && right <=R)
        return tree[pos];
 
    int mid = left + (right - left)/2;
    node l = query(tree,2*pos+1,left,mid,L,R);
    node r = query(tree,2*pos+2,mid+1,right,L,R);
 
    node ats;
    ats.b = l.b;
    ats.l = l.l;
    ats.r = r.r;
 
    if(l.l.first == r.l.first)
        ats.l.second = l.l.second + r.l.second;
 
    if(l.r.first == r.r.first)
        ats.r.second = l.r.second + r.r.second;
 
    if(r.b.second > ats.b.second)
        ats.b = r.b;
 
    if(ats.r.second > ats.b.second)
        ats.b=ats.r;
 
    if(ats.l.second > ats.b.second)
        ats.b=ats.l;
 
    if(l.r.first == r.l.first && l.r.second + r.l.second > ats.b.second)
        ats.b.first = l.r.first, ats.b.second = l.r.second + r.l.second;
 
        return ats;
}
 
int main()
{
ios::sync_with_stdio(false);
 
int n,q;
 
while(cin>>n)
{
    if(n==0)break;
    cin>>q;
    vector<node>tree(4*n,node());
    int a[n];
    for(int i=0; i<n; i++)
        cin>>a[i];
    build(tree,a,0,n-1,0);
 
    for(int i=0; i<q; i++)
    {
        int a,b;
        cin>>a>>b;
        cout<<query(tree,0,0,n-1,a-1,b-1).b.second<<"\n";
    }
}
 
return 0;
   }
