#pragma comment(linker, "/stack:200000000")
/*Lets have large arrays in stack memmory*/
#pragma GCC optimize("Ofast")
/*
-O (Same as -O1)
-O0 (do no optimization, the default if no optimization level is specified)
-O1 (optimize minimally)
-O2 (optimize more) <--codeforces default?
-O3 (optimize even more)
-Ofast (optimize very aggressively to the point of breaking standard compliance)
*/
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
/*Tries to use target architecture if possible, good for optimizing brute force loops*/

scanf("%hhu",&ch) - scans unsigned char, unsigned char > unsigned short > unsigned int
