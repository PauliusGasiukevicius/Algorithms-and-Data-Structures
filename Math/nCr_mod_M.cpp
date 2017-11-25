//a^b MOD M
ll pow(ll a, ll b, ll& M)
{
    if(b==0)return 1;
    if(b==1)return a%M;

    if(b&1)return (a*pow(a,b-1,M))%M;
    return pow((a*a)%M,b/2,M)%M;
}

void genFactorialsModM(vector<ll>&F, ll& M)
{
    F[0]=1;
    for(int i=1; i<F.size(); i++)
        F[i] = (F[i-1]*i)%M;
}

void genInverseFactorialsModM(vector<ll>&F,vector<ll>&InvF, ll&M)
{
    for(int i=0; i<InvF.size(); i++)
        InvF[i] = pow(F[i],M-2,M);
}

ll C(int n, int r, vector<ll>&F, vector<ll>&InvF, ll& M)
{
    return ((F[n] * InvF[n-r] )%M * InvF[r])%M;
}
