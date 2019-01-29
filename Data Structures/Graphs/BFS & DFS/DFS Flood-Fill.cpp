void flood(vector<vector<char>>&a, int r, int c)
{
if(r<0 || c<0 || r>=a.size() || c>=a[0].size() || a[r][c]=='*')return;
a[r][c]='*';
flood(a,r-1,c-1);
flood(a,r-1,c);
flood(a,r,c-1);
flood(a,r-1,c+1);
flood(a,r+1,c-1);
flood(a,r+1,c+1);
flood(a,r+1,c);
flood(a,r,c+1);
}

int flood(vector<string>&a, int r, int c, char cur)
{
if(r<0 || c<0 || r>=a.size() || c>=a[0].size() || a[r][c]!=cur)return 0;
a[r][c]='.';
return 1 + flood(a,r-1,c,cur) + flood(a,r,c-1,cur) + flood(a,r+1,c,cur) +
flood(a,r,c+1,cur);
}
