#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<int> buildSA(string s)
{
    s+="$"; //it uses modulo tricks for easier implementation so this addition is necessary
    int n = s.size();
    vector<int>r(n),sa(n);//rank and suffix array

    for(int i=0; i<n; i++)
       r[i]=s[i],sa[i]=i;

    for(int k=0; k<n; k=(k>0 ? 2*k : 1))
    {
        stable_sort(sa.begin(),sa.end(),[&](int i, int j)
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

int main()
{
    ios::sync_with_stdio(0);
    string s;
    cin>>s;

   auto sa = buildSA(s);
    for(int&x:sa)
        cout<<x<<"\n";
}
