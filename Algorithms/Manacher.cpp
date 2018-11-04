#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    int n = s.size();

    vector<int> d1(n);//saves length of longest odd palindrome with center at i
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
        {
            k++;
        }
        d1[i] = k--;
        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }

    vector<int> d2(n);//saves length of longest even palindrome with center at i
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])
        {
            k++;
        }
        d2[i] = k--;
        if (i + k > r)
        {
            l = i - k - 1;
            r = i + k ;
        }
    }

    int mx1 = *max_element(d1.begin(),d1.end());
    string ats1,ats2;
    for(int i=0; i<n; i++)
        if(d1[i]==mx1)
        {
            ats1=s.substr(i-mx1+1,mx1*2-1);
            break;
        }

    int mx2 = *max_element(d2.begin(),d2.end());
    for(int i=0; i<n; i++)
        if(d2[i]==mx2)
        {
            ats2=s.substr(i-mx2,mx2*2);
            break;
        }

    if(ats1.size() >= ats2.size())cout<<ats1;
    else cout<<ats2;

    //ats1 - longest odd palindrome, ats2-even
}
