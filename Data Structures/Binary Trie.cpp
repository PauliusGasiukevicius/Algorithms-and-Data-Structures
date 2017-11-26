/*
* This is a solution to http://codeforces.com/problemset/problem/706/D
*/

#include <bits/stdc++.h>
using namespace std;


int T[6400000][2];   // Trie to store multiset
int cnt[6400000]; // Trie to store node cnt

int main()
{
    ios::sync_with_stdio(0);
    int q,x,nxt = 2;
    char type;
    cin>>q;

    while(q--)
    {
        cin>>type>>x;
        if(type=='+') //Inserts into Trie
        {
            int c = 1;
            bitset<32>bits(x);

            for(int i=31; i>=0; i--)
                if(T[c][bits[i]] == 0)
            {
                c = T[c][bits[i]] = nxt++;
                cnt[c]++;
            }
            else
            {
                c = T[c][bits[i]];
                cnt[c]++;
            }
        }
        else if(type=='-')  //Delete`s from Trie
        {
            int c = 1;
            bitset<32>bits(x);

            for(int i=31; i>=0; i--)
            {
                int last = c;
                c = T[c][bits[i]];
                if(--cnt[c]==0)
                    T[last][bits[i]] = 0;
            }
        }
        else  //Finds such element y that`s in trie, that x^y -> max, also assumes that 0 is always in Trie
        {
            bitset<32>bits(x);
            int c = 1;
            int y = 0;
            bool none = false;

            for(int i=31; i>=0; i--)
             if(T[c][!bits[i]] != 0)
            {
                c = T[c][!bits[i]];
                y|=((!bits[i])<<i);
            }
            else
            {
                if(T[c][bits[i]] == 0)
                {
                    none = true;
                    break;
                }
                c = T[c][bits[i]];
                y|=((bits[i])<<i);
            }

            int ats = x;
            if(!none)ats = max(ats, x^y);
            cout<<ats<<"\n";
        }
    }
}
