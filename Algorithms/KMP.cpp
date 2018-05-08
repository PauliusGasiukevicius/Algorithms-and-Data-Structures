    #include <bits/stdc++.h>
    using namespace std;
    #define ll long long
    #define ld long double
    #define oo 666666666
     
    int main()
    {
        ios::sync_with_stdio(0);
        int n;
        while(cin>>n)
        {
            vector<int>KMP(n);
            string a,b;
            cin>>a>>b;
     
            for(int i=1,j=0; i<a.size(); i++)
                if(a[i]==a[j])KMP[i]=j+1,j++;
                else
                {
                    while(a[i]!=a[j] && j)
                        j=KMP[j-1];
                    KMP[i]=(a[i]==a[j] ? j+1 : 0);
                }
     
           /* for(int i=0; i<a.size(); i++)
                cout<<KMP[i]<<(i+1==a.size()?"\n":" ");*/
     
            int i=0,j=0;
            while(i<b.size())
            {
                //cout<<i<<" "<<j<<endl;
                if(a[j]==b[i])
                {
                    if(j+1==a.size())
                    {
                        cout<<i-j<<endl;
                        j=KMP[j];
                        i++;
                    }else i++,j++;
                }
                else
                {
                    if(j)
                    j=KMP[j-1];
                    else
                    i++;
                }
            }
            cout<<"\n";
        }
    }
     
