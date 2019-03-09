int Manacher(string&s)
{
    int n = s.size();
    vector<int> d1(n), d2(n);
    //d1 - largest odd length palindrome with index i as center
    //d2 - largest even length palindrome with indexes i and i-1 as center
    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k])k++;
        d1[i] = k--;

        if (i + k > r)
        {
            l = i - k;
            r = i + k;
        }
    }

    for (int i = 0, l = 0, r = -1; i < n; i++)
    {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k])k++;
        d2[i] = k--;

        if (i + k > r)
        {
            l = i - k - 1;
            r = i + k ;
        }
    }

    return accumulate(d1.begin(),d1.end(),0) + accumulate(d2.begin(),d2.end(),0);
}
