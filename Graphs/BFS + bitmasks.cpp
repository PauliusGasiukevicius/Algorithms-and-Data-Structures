#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

unordered_map<int,int>mp;

//we gonna store everything into int
//[0,5] - cube faces booleans
//[6,7] - row
//[8,9] - column
//[10,25] - flea grid

int getbit(int x, int b)
{return (x>>b)&1;}

void setbit(int &x, int b)
{x|=(1<<b);}

void offbit(int &x, int b)
{x&=~(1<<b);}

int getRow(int x)
{return (x>>6)&3;}

int getCol(int x)
{return (x>>8)&3;}

void setRow(int& x, int r)
{
    x &= ~(3<<6);
    x |= (r<<6);
}

void setCol(int& x, int c)
{
    x &= ~(3<<8);
    x |= (c<<8);
}

int getCell (int x, int r, int c)
{
    int shift = 10 + 4*r + c;
    return (x>>shift)&1;
}

int rotN(int& mask)
{
    bitset<32>old(mask);
    bitset<32>nw(mask);
    nw[0]=old[2];
    nw[1]=old[1];
    nw[2]=old[5];
    nw[3]=old[0];
    nw[4]=old[4];
    nw[5]=old[3];
    return mask=nw.to_ullong();
}

int rotS(int& mask)
{
    int x=mask;
    x=rotN(x);
    x=rotN(x);
    x=rotN(x);
    return mask = x;
}

int rotE(int& mask)
{
    bitset<32>old(mask);
    bitset<32>nw(mask);
    nw[0]=old[1];
    nw[1]=old[5];
    nw[2]=old[2];
    nw[3]=old[3];
    nw[4]=old[0];
    nw[5]=old[4];
    return mask=nw.to_ullong();
}

int rotW(int& mask)
{
    int x = mask;
    rotE(x);
    rotE(x);
    rotE(x);
    return mask=x;
}

void printMask(int x)
{
    cout<<"Mask: "<<bitset<32>(x).to_string()<<"\n";
    cout<<"Distance: "<<mp[x]<<"\n";
    cout<<"Cube: "<<bitset<6>(x&63).to_string()<<"\n";
    cout<<"Row: "<<getRow(x)<<" Col: "<<getCol(x)<<"\n";

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        cout<<getCell(x,i,j)<<(j==3?"\n":"");
    cout<<"-------\n";
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin>>t;

    int x = (1<<6)-1;
    queue<int>q;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
    {
        setRow(x,i);
        setCol(x,j);
        mp[x]=0;
        q.push(x);
    }

    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        /*printMask(x);
        int xyz;
        cin>>xyz;*/
        int r = getRow(x);
        int c = getCol(x);
        int old = x;

    if(r>0) //N
    {
        x=old;
        x=rotN(x);
        r--;
        setRow(x,r);

        if(getbit(x,5) && getCell(x,r,c)); //fleas both on cube bot and cell, so just swap
        else if(getbit(x,5))setbit(x,10+4*r+c),offbit(x,5); //flea jumps on cell
        else if(getCell(x,r,c))setbit(x,5),offbit(x,10+4*r+c); //flea jumps on cube
        r++;
        if(!mp.count(x))mp[x]=mp[old]+1,q.push(x);
    }

    if(c<3) //E
    {
        x=old;
        x=rotE(x);
        c++;
        setCol(x,c);

        if(getbit(x,5) && getCell(x,r,c)); //fleas both on cube bot and cell, so just swap
        else if(getbit(x,5))setbit(x,10+4*r+c),offbit(x,5); //flea jumps on cell
        else if(getCell(x,r,c))setbit(x,5),offbit(x,10+4*r+c); //flea jumps on cube
        c--;
        if(!mp.count(x))mp[x]=mp[old]+1,q.push(x);
    }

    if(r<3) //S
    {
        x=old;
        x=rotS(x);
        r++;
        setRow(x,r);
        if(getbit(x,5) && getCell(x,r,c)); //fleas both on cube bot and cell, so just swap
        else if(getbit(x,5))setbit(x,10+4*r+c),offbit(x,5); //flea jumps on cell
        else if(getCell(x,r,c))setbit(x,5),offbit(x,10+4*r+c); //flea jumps on cube
        r--;
        if(!mp.count(x))mp[x]=mp[old]+1,q.push(x);
    }

    if(c>0) //W
    {
        x=old;
        x=rotW(x);
        c--;
        setCol(x,c);
        if(getbit(x,5) && getCell(x,r,c)); //fleas both on cube bot and cell, so just swap
        else if(getbit(x,5))setbit(x,10+4*r+c),offbit(x,5); //flea jumps on cell
        else if(getCell(x,r,c))setbit(x,5),offbit(x,10+4*r+c); //flea jumps on cube
        c++;
        if(!mp.count(x))mp[x]=mp[old]+1,q.push(x);
    }
    }

    while(t--)
    {
        vector<string>A(4);
        for(auto&s:A)cin>>s;
        int x = 0;

        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            if(A[i][j]=='D')setRow(x,i),setCol(x,j);
        else if(A[i][j]=='X')setbit(x, 10 + 4*i + j);

        if(mp.count(x))
            cout<<mp[x]-1<<"\n";
        else
            cout<<"impossible\n";
    }
}
