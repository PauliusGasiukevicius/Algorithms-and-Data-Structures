#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long
#define oo 666666666666666

/*
Heron's Formula:
Let s = (a+b+c)/2. The area of the triangle, A, is sqrt(s(s-a)(s-b)(s-c)).

Circumradius:
The radius of the circumscribed (outside) circle is (a*b*c)/(4*A).

Inradius:
The radius of the inscribed (inside) circle is A / s.
*/

int main()
{
    ios::sync_with_stdio(0);
    ld a,b,c;
    while(cin>>a>>b>>c)
    {
        ld s = (a+b+c)/2;
        ld A = sqrt(s*(s-a)*(s-b)*(s-c));
        ld r2 = a*b*c/4.0/A;
        ld r1 = A/s;
        ld pi = atan(1)*4;

        ld sunf = r2*r2*pi - A;
        ld viol = A - r1*r1*pi;
        ld rose = r1*r1*pi;

        cout<<setprecision(4)<<fixed<<sunf<<" "<<viol<<" "<<rose<<"\n";
    }
}
