#pragma GCC optimize("Ofast")

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
    //if using dp on suffix-tree using DAG: to-parent edges and suffix links, note that
    //link of root should be ignored (it`s not 0 for some reason) + suffix links for leafs should be added after finishing building the tree
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

const int N = 100001; //max string size + 1 for dollar
int suffixNodeId[2*N+1]; //for suffix that starts at i stores its corresponding node id in suffix tree

void dfs0(suffix_tree<char>&st, int c = 0, int len = 0){
    len+=st.get_len(c);
    for(auto&u:st.next[c])
        dfs0(st,u.second,len);

    if(st.next[c].empty()) //leaf
    {
        int start = st.spos[c] - len + st.get_len(c);
        suffixNodeId[start] = c;
    }
}

void addSuffixLinksForLeafs(suffix_tree<char>&st)
{
    dfs0(st);
    //from some leaf(suffix) starting at i we can go to next one starting at i+1, so we add link
    for(int i=0; i+1<st.s.size(); i++)
        st.link[suffixNodeId[i]] = suffixNodeId[i+1];
}


const int lgN = 19;
int in[2*N+1],out[2*N+1];
int up[2*N+1][lgN+1];
int nodeForSuffixId[2*N+1];
int lenOfPath[2*N+1];

bool isAncestor(int u, int v)
{
    return in[u]<=in[v] && out[u]>=out[v];
}

int LCA(int u, int v)
{
    if(isAncestor(u,v))return u;
    if(isAncestor(v,u))return v;

    for(int i=lgN; i>=0; i--)
        if(!isAncestor(up[u][i],v))
        u = up[u][i];

    return up[u][0];
}

void dfs(suffix_tree<char>&st, vector<int>&sa, int c = 0, ll len = 0, int p = 0)
{
    static int tm = 0;
    in[c]=++tm;

    up[c][0]=p;

    for(int i=1; i<=lgN; i++)
        up[c][i] = up[up[c][i-1]][i-1];

    len+=st.get_len(c);
    lenOfPath[c] = len - (st.next[c].empty()); //do not count dollar

    if(st.next[c].empty())
    {
        int suffixId = st.spos[c]-len+st.get_len(c);
        nodeForSuffixId[suffixId] = c;
        if(lenOfPath[c]!=0)//not dollar only node
            sa.push_back(suffixId);
    }

    for(auto&u:st.next[c])
        dfs(st,sa,u.second,len,c);

    out[c]=tm;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    suffix_tree<char>st;
    string s;
    cin>>s;
    for(auto&ch:s)st.push(ch);
    vector<int>sa;

    st.push(0);
    dfs(st,sa);

    for(int i=1; i<sa.size(); i++)
        cout<<lenOfPath[LCA(nodeForSuffixId[sa[i-1]],nodeForSuffixId[sa[i]])]<<" ";
}
