vector<vector<ll>> mul(vector<vector<ll>>A, vector<vector<ll>>B){
    vector<vector<ll>>C(A.size(),vector<ll>(A.size())); //i,k,j order is more cache friendly
    for(int i=0; i<A.size(); i++)
    for(int k=0; k<A.size(); k++)
    for(int j=0; j<A.size(); j++)
        C[i][j] = (C[i][j] + A[i][k]*B[k][j])%MOD; //this works ~x2 faster with defined mod instead of passing mod on every call

    return C;
}

vector<vector<ll>> powMatrix(vector<vector<ll>>A, ll d){
    if(d==1)return A;
    if(d&1)return mul(A,powMatrix(A,d-1));
    return powMatrix(mul(A,A),d/2);
}
