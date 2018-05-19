#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<int> buildSA(string s)
{//it uses modulo tricks for easier implementation so this addition to string end is necessary
    s+=((char)1); //BTW it should be < than all alphabet characters
    int n = s.size();
    vector<int>r(n),sa(n);//rank and suffix array

    for(int i=0; i<n; i++)
       r[i]=s[i],sa[i]=i;

    for(int k=0; k<n; k=(k>0 ? 2*k : 1))
    {
        sort(sa.begin(),sa.end(),[&](int i, int j)
             {
                 return (r[i]!=r[j] ? r[i] < r[j] : r[(i+k)%n] < r[(j+k)%n]);
             });
        vector<int>nr(n);//new rank

        for(int i=1,rnk=0; i<n; i++)
        {
            if(r[sa[i]]!=r[sa[i-1]])rnk++;
            else if(r[(sa[i] + k)%n] != r[(sa[i-1] + k)%n])rnk++;
            nr[sa[i]]=rnk;
        }
        r=nr;
    }
    sa.erase(sa.begin()); //'$' was not part of original string so we can erase it
    return sa;
}

vector<int> kasai(string s, vector<int> sa)
{
    int n=s.size(),k=0;
    vector<int> lcp(n);
    vector<int> r(n);

    for(int i=0; i<n; i++) r[sa[i]]=i;

    for(int i=0; i<n; i++, k?k--:0)
    {
        if(r[i]==n-1) {k=0; continue;}
        int j=sa[r[i]+1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[r[i]]=k;
    }
    return lcp;
}

vector<int> suffix_array(string s)
{
    s+=(char)1;
    int n = s.size(), N = n + 256;
    vector<int> sa(n), ra(n);
    for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for(int k = 0; k < n; k ? k *= 2 : k++)
    {
        vector<int> nsa(sa), nra(n), cnt(N);
        for(int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n;
        for(int i = 0; i < n; i++) cnt[ra[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

        int r = 0;
        for(int i = 1; i < n; i++)
        {
            if(ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if(ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        ra = nra;
    }
    sa.erase(sa.begin());
    return sa;
}

int main()
{
    ios::sync_with_stdio(0);
    string s;
    cin>>s;
    auto sa = suffix_array(s);
}
