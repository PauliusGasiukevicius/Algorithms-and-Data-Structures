#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

//Finds such x and y, that A*x + B*y = GCD(A,B) in O(log(max(A,B)))
//^ that equation above is called diophantine equation
//we can get infinitely many solution to them
//let g=gcd(a,b) and we want to find solutions to A*x + B*y = C
//then we can find some x and y using Extended Euclid
//and then x0 = x*C/g,  y0 = y*C/g
//and all that holds: xi = x0 + k*b/g,     yi = y0 - a/g
//Can be used to find modulo inverses:
//Inverse of A modulo M is solution to A*C + M*D = GCD(A,M). (GCD must be 1!!!)
vector<ll> ExtendedEuclid(ll A, ll B)
{
    vector<vector<ll>>M = {{1,0,A},{0,1,B}};
    if(M[0][2] < M[1][2])swap(M[0],M[1]);

    while(M[1][2]!=0)
    {
        ll mul = M[0][2]/M[1][2];
        for(int j=0; j<3; j++)
            M[0][j]-=M[1][j]*mul;

        swap(M[0],M[1]);
    }
    return M[0];
}

int main()
{
    /*
    Example problem:
    You have n marbles. Theres 2 types of boxes, one costs c1 and holds n1 marbles, other costs
    c2 ands holds n2. Find if it`s possible to buy some boxes, fill them fully while minimizing cost
    */
    ios::sync_with_stdio(0);
    ll n,n1,n2,c1,c2;

    while(cin>>n && n && cin>>c1>>n1>>c2>>n2)
    {
        ll gcd = __gcd(n1,n2);
        if(n%gcd!=0)
            cout<<"failed\n";
        else
        {
            auto sol = ExtendedEuclid(n1,n2);
            ll x = sol[0], y = sol[1];
            ll x0 = x*(n/gcd);
            ll y0 = y*(n/gcd);
            x=x0,y=y0;

            if(x < 0)
            {
            ll k = -ceil(1.0*x0/(n2/gcd));
            while(x0 + k*n2/gcd < 0)k++;
            x=x0+k*n2/gcd;
            y=y0-k*n1/gcd;
            }
            else
            {
                ll k = ceil(1.0*x0/(n2/gcd));
                while(x0 - k*n2/gcd < 0)k--;
                x=x0-k*n2/gcd;
                y=y0+k*n1/gcd;
            }
            //^Finds min positive answer with lowest x

            ll cost1 = x*c1 + y*c2;
            ll x2,y2;
            if(y > 0)
            {
                ll k = ceil(1.0*y/(n1/gcd));
                while(y-k*n1/gcd < 0)k--;
                x2 = x + k*n2/gcd;
                y2 = y - k*n1/gcd;
            }
            else
            {
                ll k = -ceil(1.0*y/(n1/gcd));
                while(y + k*n1/gcd < 0)k++;
                x2 = x - k*n2/gcd;
                y2 = y + k*n1/gcd;
            }

            ll cost2 = x2*c1 + y2*c2;
            //^ find answer with lowest y

            if(min(x,y) < 0 && min(x2,y2) < 0)
            {
                cout<<"failed\n";
                continue;
            }

            if(cost2 <= cost1)
                swap(x,x2),swap(y,y2);

           // cout<<x0<<" "<<y0<<" "<<x<<" "<<y<<" "<<x2<<" "<<y2<<"\n";
            cout<<x<<" "<<y<<"\n";
        }
    }
}
