#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
There are M gentle men and W ladies in this party except us.
You have C candies in your hand and you distribute them randomly among all these guests ( M men and W ladies),
 of course if possible. Now you collect all the candies from all the gentlemen and this number of
candies is CC.  If you can evenly distribute these (CC) candies equally between two groups
(These two groups are two arbitrary groups) I will dance with you."
Now tell me what is the probability of her dancing with you.
*/

ld Choose(int k, int n)
{
    ld ats = 1.0;
    for(int i=0; i<k; i++)
        ats*=1.0*(n-i)/(k-i);
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int M,F,C;
    while(cin>>M>>F>>C && (M+F))
    {
        ld pM = 1.0*M/(M+F);
        ld pF = 1.0 - pM;
        ld ats = 0;

        for(int c=0; c<=C; c+=2)
            ats+=Choose(c,C)*pow(pM,c)*pow(pF,C-c);
        cout<<setprecision(7)<<fixed<<ats<<"\n";
    }
}
