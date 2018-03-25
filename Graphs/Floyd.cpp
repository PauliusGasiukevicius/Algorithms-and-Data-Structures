//Basic floyd for APSP 
for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                G[i][j]=min(G[i][j],G[i][k]+G[k][j]);

//Counting paths fom all pairs of nodes
        for(int k=0; k<=n; k++)
            for(int i=0; i<=n; i++)
                for(int j=0; j<=n; j++)
                M[i][j]+=M[i][k]*M[k][j];

//removing cycles
        for(int k=0; k<=n; k++)
            if(M[k][k])
                for(int i=0; i<=n; i++)
                    for(int j=0; j<=n; j++)
                        if(M[i][k] && M[k][j])
                        M[i][j]=-1;
