#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ordered_set S;
    int q,x;
    char ch;
    cin>>q;

    while(q--)
    {
        cin>>ch>>x;
        if(ch=='I')S.insert(x);
        else if(ch=='D')S.erase(x);
        else if(ch=='C')cout<<S.order_of_key(x)<<"\n";
        else if(S.size() < x)cout<<"invalid\n";
        else cout<<*S.find_by_order(x-1)<<"\n"; //find_by_order, gets kth minimum element, counting from 0
    }
}
