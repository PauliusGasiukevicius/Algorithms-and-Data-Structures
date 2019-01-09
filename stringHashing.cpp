#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll A = 13, B = 1e9+7; //hashing base - A, and modulo M.
//in case of collisions: increase base to some larger number ~1e7 or something
//if collisions still happen use multiple hashes with different modulos and bases

ll h[1000001]; //stores hashed string prefix in form: a^x * s[i] + a^(x-1) + s[i+1] + ... + a * s[len-1] + s[len]
ll pf[1000001];//stores base powers in form: a^0, a^1, a^2, ... , a^len

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    pf[0]=1;

    for(int i=1; i<=s.size(); i++)
    {
        h[i]=(h[i-1]*A + s[i-1])%B;
        pf[i]=pf[i-1]*A %B;
    }

    for(int len = s.size()-2; len>=1; len--)
    {
        ll h1 = h[len];
        ll h2 = h[s.size()] - h[s.size()-len]*pf[len] % B;
        if(h2<0)h2+=B;

        if(h1==h2)
        {
            for(int i=len+1; i<s.size(); i++)
            {
                ll h2 = h[i] - h[i-len]*pf[len] % B;
                if(h2<0)h2+=B;

                if(h1==h2)
                    return cout<<s.substr(0,len),0;
            }
        }
    }

    cout<<"Just a legend\n";
}
