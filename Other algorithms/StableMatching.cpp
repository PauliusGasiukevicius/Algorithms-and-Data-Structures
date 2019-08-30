vector<array<int,2>> StableMatching(vector<queue<int>>&M, vector<vector<int>>&F){
//Here`s F[f][m] - priority female f has for male m
//And M[m] - stores queue, which women this man should propose to next
int n = M.size()-1;
vector<int>P(n+1,-1); //partner for female f
queue<int>q;
for(int i=1; i<=n; i++)
    q.push(i);

while(!q.empty())
{
    int m = q.front();
    q.pop();

    int f = M[m].front();
    M[m].pop();
    if(P[f]==-1)P[f]=m;
    else if(F[f][P[f]] > F[f][m])
        swap(P[f],m),q.push(m);
    else q.push(m);
}

vector<array<int,2>>ats;
for(int i=1; i<=n; i++)
ats.push_back({P[i],i});
return ats;
}
