vector<int> kasai(vector<int>&sa, string&s){ //returns array lcp of size ||s|| - 1, such that lcp[i] is longest common prefix of suffixes sa[i] and sa[i+1]
    int n = sa.size();
    vector<int>lcp(n),pos(n);
    for(int i=0; i<n; i++)pos[sa[i]] = i;

    int k = 0;
    for(int i=0; i < n - 1; i++){
        int j = sa[pos[i] - 1];

        while(k+j < n && s[j+k] == s[i+k])k++;
        lcp[pos[i]] = k;
        k = (k==0 ? 0 : k-1);
    }
    lcp.erase(lcp.begin());
    return lcp;
}

vector<int> suffix_array(string &s) //O(n log n)
{
    s+='$';
    int n = s.size();
    vector<int>R(n),cnt(n);

    vector<array<int,3>>S(n),tmp(n);
    for(int i=0; i<s.size(); i++)S[i]={s[i],s[i],i};

    sort(S.begin(),S.end());
    for(int i=1; i<n; i++)
        R[S[i][2]] = R[S[i-1][2]] + (S[i-1][0] == S[i][0] && S[i-1][1] == S[i][1] ? 0 : 1);

    for(int k=1; k <= n; k*=2)
    {
        for(int i=0; i<n; i++)
            S[i] = {R[i], R[(i+k >= n ? i+k-n : i+k)], i};

        for(int j=1; j>=0; j--) //sort by
        {
            fill(cnt.begin(),cnt.end(),0);
            for(int i=0; i<n; i++)cnt[S[i][j]]++;
            for(int i=1; i<n; i++)cnt[i]+=cnt[i-1];
            for(int i=n-1; i>=0; i--)tmp[--cnt[S[i][j]]]=S[i];
            swap(tmp, S);
        }

        R[S[0][2]]=0;

        for(int i=1; i<n; i++)
            R[S[i][2]] = R[S[i-1][2]] + (S[i-1][0] == S[i][0] && S[i-1][1] == S[i][1] ? 0 : 1);
    }

    vector<int>sa(n);
    for(int i=0; i<n; i++)
        sa[i] = S[i][2];
    return sa;
}

vector<int> suffix_array(string &s) //O(n log^2 n)
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
