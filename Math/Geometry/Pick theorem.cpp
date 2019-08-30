ld cross(ld x1, ld y1, ld x2, ld y2){return x1*y2-x2*y1;}

ld polygonArea(vector<pair<ll,ll>>&A)
{
    ld ats = 0.0;
    for(int i=2; i<A.size(); i++)
        ats+=cross(A[i].first-A[0].first,A[i].second-A[0].second,A[i-1].first-A[0].first,A[i-1].second-A[0].second);
    return fabs(ats/2);
}

ll boundary(vector<pair<ll,ll>>&A)
{
    ll ats = A.size();
    for(int i=0; i<A.size(); i++)
    {
        ll dx = (A[i].first - A[(i+1)%A.size()].first);
        ll dy = (A[i].second - A[(i+1)%A.size()].second);
        ats+=abs(__gcd(dx,dy)) - 1;
    }
    return ats;
}

ll Pick(vector<pair<ll,ll>>&A)
{
    //S - area, B - boundary  integer points, I - points inside
    //Theorem: S = B/2 + I - 1
    //I = S+1-B/2;
    ll S = polygonArea(A);
    ll B = boundary(A);
    ll I = S+1-B/2;
    return I + B;
}
