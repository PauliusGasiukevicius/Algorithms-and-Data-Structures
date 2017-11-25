//Generates shortest prime factors for every number <= n, n is SPF.size()
void genSPF(vector<int>&SPF)
{
    int n = SPF.size();
    for(int i=2; i<n; i++)SPF[i]=i;

    for(int i=2; i*i<n; i++)
        if(SPF[i]==i)
        for(int j=2*i; j<n; j+=i)
        if(SPF[j]==j)SPF[j]=i;
}

/*
* After generation any number < n can be factored in O(log n) time
* i.e. to factor x:
while(x!=1)
{
f = SPF[x];
while(x%f==0)factors.add(f), x/=f;
}
*/
