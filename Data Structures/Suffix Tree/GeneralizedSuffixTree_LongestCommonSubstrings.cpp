#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

template<typename T>
struct suffix_tree{
    //notes:
    //suffix tree has at most 2*N nodes
    //longest-common-prefix of 2 suffixes is just root-node path length to their LCA
    //to 'finish' building suffix_tree you need to append some separator, so called dollar ('$')
    //dollar must be smaller than all other letters in alphabet
	const static int inf = 1e9;
	vector<T> s; //our string/int array
	vector<map<T, int>> next; //next nodes to go to, stored in map for easy lex order (array would be faster)
	vector<int> spos, len, link; //spos - start_pos, len - length of current substring, link - suffix link
	int node, pos, last;

	ll distinct;
	int node2, pos2, leaves;
	vector<int> parent;

	suffix_tree() { make_node(0), node = pos = distinct = node2 = pos2 = leaves = 0; }

	int make_node(int p, int f = 0, int l = inf)
	{
		spos.push_back(p);
		parent.push_back(f);
		len.push_back(l);
		link.push_back(0);
		next.emplace_back();
		return spos.size()-1;
	}

	void push(T c)
	{
		distinct += leaves;

		for (s.push_back(c), pos++, ++pos2, last = 0; pos > 0; )// update maximal suffix
		{
			int n = s.size();
			while (pos > len[next[node][s[n - pos]]])
				node = next[node][s[n - pos]], pos -= len[node];

			T edge = s[n - pos];
			int &v = next[node][edge];
			T t = s[spos[v] + pos - 1];

			if (v == 0)
			{
				v = make_node(n - pos, node);
				distinct += get_len(v);  						// add
				++leaves;										// leaf
				link[last] = node;
				last = 0;
			}
			else if (t == c)
			{
				link[last] = node;
				return;
			}
			else
			{
				int u = make_node(spos[v], node, pos - 1);
				next[u][c] = make_node(n - 1, u);
				distinct += get_len(next[u][c]);				// add
				++leaves;										// leaf
				next[u][t] = v;
				spos[v] += pos - 1;
				len[v] -= (len[v] != inf) * (pos - 1);
				parent[v] = u;									// parent
				v = last = link[last] = u;
			}
			if (node == 0)
				pos--;
			else
				node = link[node];
		}
	}

	void pop()
	{
		int n = s.size(), v = -1;

		if (pos != 0)
		{
			while (pos > len[next[node][s[n - pos]]])
				node = next[node][s[n - pos]], pos -= len[node];

			T edge = s[n - pos];
			v = next[node][edge];
		}

		while (pos2 > len[next[node2][s[n - pos2]]])
			node2 = next[node2][s[n - pos2]], pos2 -= len[node2];

		T edge2 = s[n - pos2];
		int v2 = next[node2][edge2];

		if (v == v2)
		{
			distinct -= pos2 - pos;
			spos[v2] += pos2 - pos;

			if (node == 0)
				pos--;
			else
				node = link[node];
		}
		else
		{
			distinct -= get_len(v2);
			next[node2].erase(edge2);
			--leaves;

			if (node2 != 0 && next[node2].size() == 1)
			{
				if (v != -1 && node == node2)
				{
					pos += get_len(node);
					node = parent[node];
				}
				int ch = next[node2].begin()->S;
				spos[ch] -= get_len(node2);
				len[ch] += (len[ch] != inf) * get_len(node2);
				next[parent[ch] = parent[node2]][s[spos[node2]]] = ch;
				next[node2].clear();
			}
		}

		if (node2 == 0)
			pos2--;
		else
			node2 = link[node2];
	}

	int get_len(int p) { return p == 0 ? 0 : min(len[p], (int)s.size()-spos[p]); }
};

int n;
vector<int>res;
int bestLen;

bitset<128> dfs(suffix_tree<int>&st, vector<int>&word_id, int c, int len)
{
    bitset<128>b(0);
    len+=st.get_len(c);

    for(auto&u : st.next[c])
        b|=dfs(st,word_id,u.second,len);

    if(b.count()*2 > n)
    {
        if(len > bestLen)bestLen = len, res.clear();
        if(len == bestLen)res.push_back(st.spos[c]-len+st.get_len(c));
    }

    if(st.next[c].empty())
    {
        int start = st.spos[c]-len+st.get_len(c);
        int id = word_id[start];
        b[id]=1;
    }

    return b;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int cs = 0;
    while(cin>>n && n)
    {
        if(cs++)cout<<"\n";

        if(n==1)
        {
            string s;
            cin>>s;
            cout<<s<<"\n";
            continue;
        }

        res.clear();
        bestLen = 0;

        suffix_tree<int>st;
        vector<int>word_id;
        for(int i=1; i<=n; i++)
        {
            string s;
            cin>>s;
            for(auto&ch:s)st.push(ch),word_id.push_back(i-1);

            st.push(-i); //terminal symbols all unique, for some node, we only consider first symbol we can find
            word_id.push_back(i-1);
        }

        dfs(st,word_id,0,0);

        if(bestLen)
        {
            for(auto&start:res)
                {
                    string s;
                    for(int j=0; j<bestLen; j++)
                    s+=(char)(st.s[start+j]);
                    cout<<s<<"\n";
                }
        }
        else cout<<"?\n";
    }
}
