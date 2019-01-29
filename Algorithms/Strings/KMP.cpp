#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void KMP_table(vector<int>&KMP, string&a)
{
    for(int i=1,j=0; i<a.size(); i++)
        if(a[i]==a[j])KMP[i]=j+1,j++;
        else
        {
            while(a[i]!=a[j] && j)
                j=KMP[j-1];
            KMP[i]=(a[i]==a[j] ? j+1 : 0);
        }
}

// a is pattern
int first_match(vector<int>&KMP, string&a, string&b)
{
    KMP_table(KMP,a);
int i=0,j=0;
    while(i<b.size())
        if(a[j]==b[i])
        {
            if(j+1==a.size())
            {
                // we can comment this line and add all matches to vector if we need all
                return i-j;
                j=KMP[j];
                i++;
            }else i++,j++;
        }
        else
        {
            if(j)
            j=KMP[j-1];
            else
            i++;
        }
    return -1;
}

//Tries matching reversed_string with string
//Returns matching done at the end
//so the rest of reversed_string should be appended to make string a palindrome
int solve(vector<int>&KMP, string&a, string&b)
{
    KMP_table(KMP,a);
int i=0,j=0;
    while(i<b.size())
        if(a[j]==b[i])
        {
            if(j+1==a.size())
            {
                return j+1;
                j=KMP[j];
                i++;
            }else i++,j++;
        }
        else
        {
            if(j)
            j=KMP[j-1];
            else
            i++;
        }
    return j;
}

int main()
{
    ios::sync_with_stdio(0);
    string s;
    while(cin>>s)
    {
        vector<int>KMP(s.size());
        string r=s;;
        reverse(r.begin(),r.end());
        int j = solve(KMP,r,s);
        while(j<r.size())
            s+=r[j++];

        cout<<s<<"\n";
    }
}
