vector<int> suffix_array(string &s)
{
    s+='$';
    int n = s.size();
    vector<int>R(n);
    for(int i=0; i<s.size(); i++)R[i]=s[i];

    vector<array<int,3>>S(n);

    for(int k=1; k <= n; k*=2)
    {
        for(int i=0; i<n; i++)
            S[i] = {R[i], R[(i+k)%n], i};

        sort(S.begin(),S.end());
        R[S[0][2]]=0;

        for(int i=1; i<n; i++)
            R[S[i][2]] = R[S[i-1][2]] + (S[i-1][0] == S[i][0] && S[i-1][1] == S[i][1] ? 0 : 1);
    }

    vector<int>sa(n);
    for(int i=0; i<n; i++)
        sa[i] = S[i][2];
    return sa;
}
