#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int A[200001];
int f[1000001];//frequency
ll ats = 0;

void Remove(int idx)//Remove element at index idx from current range [L,R]
{
    int x = A[idx];
    ats-=1LL*f[x]*f[x]*x;
    f[x]--;
    ats+=1LL*f[x]*f[x]*x;
}

void Add(int idx)//Add element at index idx to current range [L,R]
{
    int x = A[idx];
    ats-=1LL*f[x]*f[x]*x;
    f[x]++;
    ats+=1LL*f[x]*f[x]*x;
}

ll GetAnswer()//Get answer for current range [L,R]
{
    return ats;
};

const int block_size = 666; //its around sqrt(n) but usually varies

struct Query {
    int l, r, idx;
    bool operator<(Query other) const{
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

//Complexity for Mo is something like O(Q log Q + (N+Q)*sqrt(N)*O(add + remove)
vector<ll> Mo(vector<Query> queries) {
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end());

    int L = 0;
    int R = -1;

    for (Query q : queries) {
        while (L > q.l)Add(--L);
        while (R < q.r)Add(++R);
        while (L < q.l)Remove(L++);
        while (R > q.r)Remove(R--);
        answers[q.idx] = GetAnswer();
    }
    return answers;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n>>q;
    vector<Query>Q(q);

    for(int i=1; i<=n; i++)
        cin>>A[i];

    for(int i=0; i<q; i++)
    {
        cin>>Q[i].l>>Q[i].r;
        Q[i].idx=i;
    }

    for(auto& x : Mo(Q))
        cout<<x<<"\n";
}
