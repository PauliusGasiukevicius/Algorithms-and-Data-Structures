/*
This this was university exercise and it`s buggy & slow, so for contests I should better use
https://gist.github.com/ar-pa/957297fb3f88996ead11
/*

#include <bits/stdc++.h>
using namespace std;

#define N 30
//maximum number of digits

class BigInteger
{
    private:

        vector<int>D; // digits in reverse, i.e. 123 = {[3][2][1]}
        bool neg;

    public:

        BigInteger(){D.reserve(N);D.push_back(0);neg=false;}

        BigInteger(string s)
        {
            neg = false;
            if(s[0]=='-')neg = true;
            if(s[0]=='-' || s[0]=='+')s.erase(s.begin());
            reverse(s.begin(),s.end());
            D.reserve(N);

            for(int i=0; i<s.size(); i++)
                D.push_back(s[i]-'0');
        }

        BigInteger(int n)
        {
            neg = false;
            if(n < 0)neg = true,n=-n;
            D.reserve(N);

            while(n > 0)
                D.push_back(n%10),n/=10;

            while(D.size() > 1 && D.back()==0)
                D.pop_back();
        }

        BigInteger(vector<int>&D,bool neg)
        {
            this->D = D;
            this->neg = neg;
        }

        BigInteger(BigInteger& b)
        {
            this->neg = b.neg;
            this->D = b.D;
        }

        string toString()//NOT USED
        {
            string s;
            if(neg)
                s.push_back('-');
            for(int i=D.size()-1; i>=0; i--)
                s+=('0' + D[i]);
            return s;
        }

        friend ostream& operator<<(ostream& os, BigInteger& b)
        {
            if(b.neg)os<<"-";
            for(int i=b.D.size()-1; i>=0; i--)
                os<<b.D[i];
            return os;
        }

        friend istream& operator>>(istream& is, BigInteger& b)
        {
            string s;
            is>>s;
            BigInteger temp(s);
            b = temp;

            return is;
        }

        BigInteger& operator=(BigInteger& b)
        {
            this->D = b.D;
            this->neg = b.neg;
            return *this;
        }

        bool operator==(BigInteger& b)
        {
            return (this->D == b.D && this->neg == b.neg);
        }

        bool operator<(BigInteger& b)
        {
            if(this->neg && !b.neg)return true;
            if(!this->neg && b.neg)return false;

            if(this->D.size() < b.D.size())return true;
            if(this->D.size() > b.D.size())return false;

            for(int i=b.D.size()-1; i>=0; i--)
                if(this->D[i] < b.D[i])return true;
                else if(this->D[i] > b.D[i])return false;

            return false;
        }

        bool operator<=(BigInteger& b)
        {
            if(this->neg && !b.neg)return true;
            if(!this->neg && b.neg)return false;

            if(this->D.size() < b.D.size())return true;
            if(this->D.size() > b.D.size())return false;

            for(int i=b.D.size()-1; i>=0; i--)
                if(this->D[i] < b.D[i])return true;
                else if(this->D[i] > b.D[i])return false;

            return true;
        }

        bool operator>(BigInteger& b)
        {
            return !(*this <= b);
        }

        bool operator>=(BigInteger& b)
        {
            return !(*this < b);
        }

        BigInteger& operator+(BigInteger& b)
        {
            if(this->neg && !b.neg)
                return b-(-(*this));
            if(!this->neg && b.neg)
                return (*this)-(-b);

            vector<int>A = this->D;
            vector<int>B = b.D;
            vector<int>D;
            D.reserve(N);

            while(A.size() < B.size())A.push_back(0);
            while(B.size() < A.size())B.push_back(0);

            bool neg = this->neg;

            int carry = 0;
            for(int i=0; i<A.size(); i++)
            {
                D.push_back(A[i] + B[i] + carry);
                carry = 0;
                if(D.back() > 9)
                    carry = 1, D.back()-=10;
            }

            if(carry > 0)
                D.push_back(carry);

            while(D.size() > 1 && D.back()==0)
                D.pop_back();

            return *(new BigInteger(D,neg));
        }

        BigInteger& operator-()
        {
            //this->neg = !this->neg;
            return *(new BigInteger(this->D,!this->neg));
        }

        BigInteger& operator-(BigInteger& b)
        {
            if(this->neg && !b.neg)
                return (*this) + (-b);
            if(!this->neg && b.neg)
                return (*this) + b;
            if(this->neg && b.neg)
                return (-b)-(-(*this));

            //now problem is reduced to a - b, where`s both a and b are positive
            if((*this) < b)
            {
                BigInteger temp = (b-(*this));
                return -temp;
            }

            vector<int>A = this->D;
            vector<int>B = b.D;
            vector<int>D;
            D.reserve(N);

            while(B.size() < A.size())B.push_back(0);

            int borrow = 0;
            for(int i=0; i<A.size(); i++)
            {
                D.push_back(A[i] - B[i] - borrow);
                borrow = 0;
                if(D.back() < 0)
                    borrow = 1, D.back()+=10;
            }

                while(D.size() > 1 && D.back()==0)
                    D.pop_back();

            return *(new BigInteger(D,false));
        }

        BigInteger& operator+=(BigInteger& b)
        {
            *this = (*this)+b;
            return (*this);
        }

        BigInteger& operator-=(BigInteger& b)
        {
            *this = (*this)-b;
            return (*this);
        }

        BigInteger& operator*=(BigInteger& b)
        {
            *this = (*this)*b;
            return (*this);
        }

        BigInteger& operator/=(BigInteger& b)
        {
            *this = (*this)/b;
            return (*this);
        }

        BigInteger& operator%=(BigInteger& b)
        {
            *this = (*this)%b;
            return (*this);
        }

        BigInteger& operator*(BigInteger& b)
        {
            bool neg = this->neg ^ b.neg;
            BigInteger ats;

            const vector<int>&B = b.D;
            const vector<int>&A = this->D;
            vector<int>R,C;
            R.reserve(2*N);
            C.reserve(2*N);

            for(int j=0; j<B.size(); j++)
            {
                C = R;
                R.push_back(0);

                int carry = 0;

                for(int i=0; i<A.size(); i++)
                {
                    C.push_back(A[i]*B[j] + carry);
                    carry = 0;

                    if(C.back() > 9)
                        carry = C.back()/10, C.back()%=10;
                }

                if(carry > 0)
                    C.push_back(carry);

                BigInteger temp(C,false);
                ats+=temp;
            }

            while(ats.D.size() > 1 && ats.D.back()==0)
                ats.D.pop_back();

            return *(new BigInteger(ats.D,neg));
        }

        BigInteger& operator/(BigInteger& b)
        {
            bool neg = this->neg ^ b.neg;
            BigInteger r,ten(10);

            const vector<int>&A = this->D;
            vector<int>D;
            D.reserve(N);

            int i = A.size()-1;

            while(r < b && i >=0)
            {
                BigInteger digit(A[i]);
                r = r*ten + digit;
                i--;
            }

            D.push_back(0);
            while(r >= b)
                {
                    D.back()++;
                    r-=b;
                }

            for(i; i>=0; i--)
            {
                BigInteger digit(A[i]);
                r = r*ten + digit;
                D.push_back(0);

                while(r >= b)
                {
                    D.back()++;
                    r-=b;
                }
            }

            reverse(D.begin(),D.end());

            while(D.size() > 1 && D.back()==0)
                D.pop_back();

            return *(new BigInteger(D,neg));
        }

        BigInteger& operator%(BigInteger& b)
        {
            bool neg = this->neg ^ b.neg;
            BigInteger r,ten(10);

            vector<int>A = this->D;
            vector<int>D;

            int i = A.size()-1;

            while(r < b && i >=0)
            {
                BigInteger digit(A[i]);
                r = r*ten + digit;
                i--;
            }

            D.push_back(0);
            while(r >= b)
                {
                    D.back()++;
                    r-=b;
                }

            for(i; i>=0; i--)
            {
                BigInteger digit(A[i]);
                r = r*ten + digit;

                D.push_back(0);

                while(r >= b)
                {
                    D.back()++;
                    r-=b;
                }
            }

            reverse(D.begin(),D.end());

            while(D.size() > 1 && D.back()==0)
                D.pop_back();

            return *(new BigInteger(r.D,neg));
        }

        BigInteger&  root()
        {
            BigInteger L(0), R = *this, two(2), one(1),M,x;

            while(L < R)
            {
                M = L + (R-L+one)/two;
                x = (M*M);

                if(x <= (*this))
                    L=M;
                else
                    R=M-one;
            }

            return *(new BigInteger(R));
        }

        int lastDigit()
        {
            return D[0];
        }
};

int main()
{
  BigInteger x("111111111"), y;
  cin>>y;
  cout<<x+y<<"\n";
  cout<<x-y<<"\n";
  cout<<x*y<<"\n";
  cout<<x/y<<"\n";
  cout<<x%y<<"\n";
  cout<<y.root()<<"\n";
}
