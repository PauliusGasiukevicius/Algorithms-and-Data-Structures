typedef vector<int> bigint;
const int base = 1000*1000*1000;

bigint Bigint(string s)
{
    bigint a;
    for (int i=s.length(); i>0; i-=9)
    if (i < 9)
        a.push_back (atoi (s.substr (0, i).c_str()));
    else
        a.push_back (atoi (s.substr (i-9, 9).c_str()));
    return a;
}

bigint Add(bigint a, bigint& b) //Assumes sign(a) == sign(b)
{
    int carry = 0;
    for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i)
    {
        if (i == a.size())a.push_back (0);
        a[i] += carry + (i < b.size() ? b[i] : 0);
        carry = a[i] >= base;
        if (carry)  a[i] -= base;
    }
    return a;
}

bigint Sub(bigint a, bigint& b) //Assumes a >= b
{
    int carry = 0;
    for (size_t i=0; i<b.size() || carry; ++i)
    {
        a[i] -= carry + (i < b.size() ? b[i] : 0);
        carry = a[i] < 0;
        if (carry)  a[i] += base;
    }
    while (a.size() > 1 && a.back() == 0)a.pop_back();
    return a;
}

bigint Mul(bigint a, int b) //Assumes b < base
{
    int carry = 0;
    for (size_t i=0; i<a.size() || carry; ++i)
    {
        if (i == a.size())
            a.push_back (0);
        long long cur = carry + a[i] * 1ll * b;
        a[i] = int (cur % base);
        carry = int (cur / base);
    }
    while (a.size() > 1 && a.back() == 0)a.pop_back();
    return a;
}

bigint Mul(bigint a, bigint b)
{
    bigint c (a.size()+b.size());
    for (size_t i=0; i<a.size(); ++i)
    for (int j=0, carry=0; j<(int)b.size() || carry; ++j)
    {
        long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
        c[i+j] = int (cur % base);
        carry = int (cur / base);
    }
    while (c.size() > 1 && c.back() == 0)c.pop_back();
    return c;
}

bigint Div(bigint a, int b)//Assumes b < base
{
    int carry = 0;
    for (int i=(int)a.size()-1; i>=0; --i)
    {
        long long cur = a[i] + carry * 1ll * base;
        a[i] = int (cur / b);
        carry = int (cur % b);
    }
    while (a.size() > 1 && a.back() == 0)a.pop_back();
    return a;
}
string toString(bigint a)
{
    string res = (a.empty() ? "0" : to_string(a.back()));
    for (int i=a.size()-2; i>=0; --i)
    {
        string cur = to_string(a[i]);
        res+=string(9-cur.size(),'0')+cur;
    }
    return res;
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cout<<toString(Mul(Bigint("11111111111111111111"),Bigint("11111111111111111111")));
}
