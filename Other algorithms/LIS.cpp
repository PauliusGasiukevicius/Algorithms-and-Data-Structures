vector<int> getLIS(vector<int>A)
{
    int n = A.size();
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

    k=temp[k];
    vector<int>ats;

    while(k!=-1)ats.push_back(A[k]),k=res[k];
    return ats;
}

int getLIS_Size(vector<int>&A)//If only LIS lenght is needed there`s a better way
{
    int n = A.size();
        vector<int> d(n+1, 1000000000);
	for (int i = 0; i < n; i++) 
		*lower_bound(d.begin(), d.end(), a[i]) = a[i];
	for (int i = 0; i <= n; i++) 
		if (d[i] == 1000000000) return i;
    return 0;
}

