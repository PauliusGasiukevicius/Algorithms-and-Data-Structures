#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int>A(n);
    for(int&x:A)cin>>x;

    vector<int>res(n,-1);
    vector<int>temp(n,0);

    int k = 0;

    for(int i=1; i<n; i++)
        if(A[i] > A[temp[k]])
        temp[++k]=i,res[i]=temp[k-1];
        else
        {
            int l = 0, r = k;
            while(l<r)
            {
                int mid = l + (r-l)/2;
                if(A[temp[mid]] < A[i])
                    l=mid+1;
                else
                    r=mid;
            }
            temp[r]=i;
            if(r!=0)
            res[i]=temp[r-1];
        }

    cout<<k+1<<"\n";

    
    //LIS printing
    k=temp[k];
    vector<int>ats;

    while(k!=-1)
        ats.push_back(A[k]),k=res[k];

    for(int i=ats.size()-1; i>=0; i--)
        cout<<ats[i]<<"\n";
    


 return 0;
}

/*
If only lis is needed there`s a better way
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> d(n+1, 1000000000);
	for (int i = 0; i < n; i++) {
		*lower_bound(d.begin(), d.end(), a[i]) = a[i];
	}
	for (int i = 0; i <= n; i++) {
		if (d[i] == 1000000000) {
			cout << i << endl;
			return 0;
		}
	}
}
*/
