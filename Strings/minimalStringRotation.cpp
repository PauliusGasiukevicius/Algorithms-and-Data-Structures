int minLexCyc(string& x) //returns index of minimal string rotation, works in O(n)
{
    int i = 0, j = 1, k = 1, p = 1, a, b, l = x.size();
    while(j+k <= (l<<1))
    {
        if ((a=x[(i+k-1)%l])>(b=x[(j+k-1)%l]))
        {
            i=j++;
            k=p=1;
        } else if (a<b)
        {
            j+=k;
            k=1;
            p=j-i;
        } else if (a==b && k!=p)
        {
            k++;
        } else
        {
            j+=p;
            k=1;
        }
    }
    return i;
}