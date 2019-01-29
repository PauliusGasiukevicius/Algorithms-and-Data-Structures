    //SPOJ AGGRCOW
    #include <bits/stdc++.h>
    using namespace std;
     
    int main()
    {
        ios_base::sync_with_stdio(false);
        int t,n,c,a[100001];
        cin>>t;
     
        while(t--)
        {
            cin>>n>>c;
            for(int i=0; i<n; i++)
                cin>>a[i];
            sort(a,a+n);
     
            int l = 0, r = 1e9;
     
            while(l < r)
            {
                int m = l + (r-l+1)/2;
                // try keeping distance of m between cows
                int left = c-1;
                int last = a[0];
     
                for(int i=1; i<n; i++)
                    if(a[i] - last >= m)
                    last = a[i],left--;
     
                if(left <=0)
                    l = m;
                else
                    r = m-1;
            }
                cout<<r<<"\n";
        }
    }
     
