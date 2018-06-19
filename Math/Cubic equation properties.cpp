#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    /*
    Problem given x^3 + A*X^2 + B*X + C = 0 find (x1^2 + x2^2 + x3^2)^0.5

    roots: a b c
    (x-a)*(x-b)*(x-c) = 0
    ((x^2 - b*x - a*x + a*b) * (x-c) = 0
    x^3 - (a+b)*x^2 + a*b*x - c*x^2 + b*c*x + a*c*x - a*b*c = 0
    x^3 - (a+b+c)*x^2 + (a*b + b*c + a*c)*x - a*b*c = 0

     we need to find (a^2 + b^2 + c^2)^0.5
     (a+b+c)*(a+b+c) = a*a + b*a + c*a + b*b + a*b + b*c + c*c + c*a + c*b
     (a+b+c)*(a+b+c) = a*a + b*b + c*c + 2*a*b + 2*b*c + 2*a*c
     we are given (a+b+c) == A
     (a*b + b*c + a*c) == B
     hence the solution is A*A - 2*B
    */

    int t;
    cin>>t;
    while(t--)
    {
        ld A,B,C;
        cin>>A>>B>>C;
        cout<<setprecision(0)<<fixed<<A*A-2*B<<"\n";
    }
}
