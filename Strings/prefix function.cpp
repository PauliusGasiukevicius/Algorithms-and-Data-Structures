/*Builds array P[], P[i] - is the longest proper prefix of the substring s[0…i]
  which is also a suffix of this substring.
  A proper prefix of a string is a prefix that is not equal to the string itself.
  By definition, P[0]=0.*/
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

//returns vector of indexes, if some index i is in array it means that b[i:i+a.size()]==a
vector<int> get_matches(string&a, string&b){
    vector<int> P=prefix_function(a);
    int i=0,j=0;
    vector<int>ats;

    while(i<b.size())
        if(a[j]==b[i])
        {
            if(j+1==a.size())
            {
                ats.push_back(i-j);
                j=P[j];
                i++;
            }else i++,j++;
        }
        else
        {
            if(j)j=P[j-1];
            else i++;
        }
    return ats;
}
