#define ll long long

ll powm(ll a, ll n, ll mod) //fast, non-recursive
{
    if(a==0)return 0;
    if(n==0 || a==1)return 1 % mod;
    ll pw = 1;
    while( n > 0)
    {
        if(n&1)pw = pw*a %mod, n--;
        a=a*a % mod;
        n/=2;
    }
    return pw;
}

//a^b MOD M
ll pow(ll a, ll b, ll& M)
{
    if(b==0)return 1;
    if(b==1)return a%M;

    if(b&1)return (a*pow(a,b-1,M))%M;
    return pow((a*a)%M,b/2,M)%M;
}

//a^b
ll pow(ll a, ll b)
{
    if(b==0)return 1;
    if(b==1)return a;

    if(b&1)return (a*pow(a,b-1));
    return pow(a*a,b/2);
}
