int josephus(int n, int k) //standart problem when we always remove every k-th person, complexity O(n)
{
    int ats = 0;
    for(int i=1; i<=n; i++)
        ats=(ats+k)%i;
    return ats+1;
}

int josephus2(int n) //Special case when k=2 can be solved with math formula, complexity O(log n)
{return 2*(n-pow(2,floor(log2(n))))+1;}

ll josephus3(ll n, int k)//Another special case when n is large and k is small, complexity O(k log n)
{
    if (n == 1)return 0;
    if (k == 1)return n-1;
    if (k > n)return (josephus3(n-1, k) + k) % n;
    ll cnt = n / k;
    ll res = josephus3(n - cnt, k);
    res -= n % k;
    res+=(res<0 ? n : res/(k-1));
    return res;
}

int josephusW(int n, vector<int>&K)//modified original problem, now we will remove K[0]-thperson first, then K[1]-th...
{
    int ats = 0;
    for(int i=1; i<=n; i++)
        ats = (ats + K[n-i])%i;
    return ats+1;
}
