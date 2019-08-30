ll A[200005];
ll seg[4*200005][6]; //[val][mul][add]
//so every node is val*mul + add
//addition: add+=x
//setRange: mul*=0, add+=x;
 
void build(int c, int l, int r)
{
    seg[c][1]=1;
    if(l==r)
    {
        seg[c][0]=A[r];
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m);
    build(2*c+1,m+1,r);
    seg[c][0]=seg[2*c][0]+seg[2*c+1][0];
}
 
void Lazy(int c, int l, int r)
{
    seg[c][0] = seg[c][0]*seg[c][1] + seg[c][2]*(r-l+1);
    if(l!=r)
    {
        seg[2*c][1]*=seg[c][1];
        seg[2*c][2]*=seg[c][1];
        seg[2*c][2]+=seg[c][2];
        seg[2*c+1][1]*=seg[c][1];
        seg[2*c+1][2]*=seg[c][1];
        seg[2*c+1][2]+=seg[c][2];
    }
    seg[c][1]=1;
    seg[c][2]=0;
}
 
void mul(int c, int l, int r, int L, int R, int x)
{
    Lazy(c,l,r);
    if(l > r || l > R || r < L)return;
    if(l >= L && r <= R)
    {
        seg[c][1]*=x;
        seg[c][2]*=x;
        Lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    mul(2*c,l,m,L,R,x);
    mul(2*c+1,m+1,r,L,R,x);
    seg[c][0] = seg[2*c][0] + seg[2*c+1][0];
}
 
void add(int c, int l, int r, int L, int R, int x)
{
    Lazy(c,l,r);
    if(l > r || l > R || r < L)return;
    if(l >= L && r <= R)
    {
        seg[c][2]+=x;
        Lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    add(2*c,l,m,L,R,x);
    add(2*c+1,m+1,r,L,R,x);
    seg[c][0] = seg[2*c][0] + seg[2*c+1][0];
}
 
ll Get(int c, int l, int r, int L, int R)
{
    Lazy(c,l,r);
    if(l > r || l > R || r < L)return 0;
    if(l >= L && r <= R) return seg[c][0];
    int m = (l+r)/2;
    ll res = Get(2*c,l,m,L,R) + Get(2*c+1,m+1,r,L,R);
    seg[c][0] = seg[2*c][0] + seg[2*c+1][0];
    return res;
}