int fastRead_int() {
 register int c = getchar_unlocked();
 int x;
 x = 0;
 int neg = 0;

 for(; ((c<48 || c>57) && c != '-'); c = getchar_unlocked());

 if(c=='-') {
  neg = 1;
  c = getchar_unlocked();
 }

 for(; c>47 && c<58 ; c = getchar_unlocked()) {
  x = (x<<1) + (x<<3) + c - 48;
 }

 if(neg)
  x = -x;
 return x;
}

void fastRead_string(char *str, char delim)
{
 register char c = 0;
 register int i = 0;

 while (c < 33)
  c = getchar_unlocked();

 while (c != delim) {
  str[i] = c;
  c = getchar_unlocked();
  i = i + 1;
 }

 str[i] = '\0';
}

int main()
{

 int n;
 char s[100];

 n = fastRead_int();
 printf("%d\n", n);

 fastRead_string(s, '\n');
 printf("%s\n", s);
 return 0;
}

