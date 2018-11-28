#include <bits/stdc++.h>
using namespace std;

const int N = 3000000;

double average_distance(const vector<int> &permutation) {
    double distance_sum = 0;

    for (int i = 0; i < N; i++)
        distance_sum += abs(permutation[i] - i);

    return distance_sum / N;
}

int main() 
{
      ios::sync_with_stdio(0);cin.tie(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //theres also mt19937_64 for 64 bit random integers
    int random_integer = uniform_int_distribution<int>(2, 10)(rnd); //generates random ints in range [2,10]
    vector<int> permutation(N);

    for (int i = 0; i < N; i++)
        permutation[i] = i;

    shuffle(permutation.begin(), permutation.end(), rng);
    cout << average_distance(permutation) << '\n';

    for (int i = 0; i < N; i++)
        permutation[i] = i;

    for (int i = 1; i < N; i++)
        swap(permutation[i], permutation[uniform_int_distribution<int>(0, i)(rng)]);

    cout << average_distance(permutation) << '\n';
}
