#define ll long long

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
