#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>

#define eps 1e-10

using namespace std;

void print(const vector<int> &vec) {
    for (auto &l : vec)
        cout << l << ' ';
    cout << '\n';
}

double CalculateLength(const vector<int> &v, const vector<pair<double, double>>& dots) {
    int n = v.size();
    double ans = 0;

    for (int i = 0; i < n; i++) {
        ans += sqrt((dots[v[i]].first - dots[v[(i + 1) % n]].first) * (dots[v[i]].first - dots[v[(i + 1) % n]].first) +
                    (dots[v[i]].second - dots[v[(i + 1) % n]].second) *
                    (dots[v[i]].second - dots[v[(i + 1) % n]].second));

    }
    //cout << ans << '\n';
    return ans;
}

double pathL(pair<double, double> a, pair<double, double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

double generatePerm(vector<int> &perm, const vector<pair<double, double>>& dots, double currentLength) {
    int n = perm.size();
    int i = rand() % n;
    int j = rand() % n;
    while (i == j)
        j = rand() % n;
    if (j < i)
        swap(i, j);

    int l = (n + i - 1) % n;
    int k = (j + 1) % n;

    if (j == l && i == k)
        return currentLength;
    //cout << i << ' ' << j << '\n';


    double deltaL = -pathL(dots[perm[l]], dots[perm[i]]) - pathL(dots[perm[j]], dots[perm[k]]) +
                    pathL(dots[perm[j]], dots[perm[l]]) + pathL(dots[perm[i]], dots[perm[k]]);

    reverse(perm.begin() + i, perm.begin() + j + 1);

    return currentLength + deltaL;

}

double getProbability(double dE, double t) {
    return 1 / (1 + exp(dE / t));
}

bool makeTransit(double p) {
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution d(p);
    int x = d(gen);
    return x == 1;
}

double DecreaseTemperature(int initialTemperature, int i) {
    return initialTemperature / log(2 + i);
}

int main() {

    double initialTemperature = 200;
    double endTemperature = 0;

    cout.setf(ios::fixed);
    cout.precision(5);
    srand(10);

    fstream file("../data/tsp_51_1.txt");

    int n;
    double x, y;
    file >> n;
    cout << n << '\n';

    vector<int> perm(n);
    vector<pair<double, double>> dots(n);

    int i = 0;
    for (auto &l : perm)
        l = i++;

    for (i = 0; i < n; i++) {
        file >> x >> y;
        dots[i] = make_pair(x, y);
        //cout  << dots[i].first << ' ' << dots[i].second << '\n';
    }

    shuffle(perm.begin(), perm.end(), default_random_engine(1)); // создаю началбную перестановку

    double currentLength = CalculateLength(perm, dots);
    double L = currentLength;
    double min = L;
    cout << currentLength << '\n';

    double T = initialTemperature; // Температура

    for (i = 0; i < 2000000; i++) {

        vector<int> newperm = perm;
        double newLength = generatePerm(newperm, dots, currentLength); // generatePerm(newperm, dost);
        //double nnLength = CalculateLength(newperm, dots);
        //print(newperm);
        //cout << newLength << ' ' << nnLength << '\n';

        if (newLength < currentLength) {
            currentLength = newLength;
            perm = newperm;
        } else {
            double p = getProbability(newLength - currentLength, T);
            if (makeTransit(p)) {
                currentLength = newLength;
                perm = newperm;
            }
        }

        T = DecreaseTemperature(initialTemperature, i);

        if (i % 10000 == 0) {
            cout << currentLength / L << '\n';
        }

        if (currentLength < min)
            min = currentLength;

        if (abs(T - endTemperature) <= eps)
            break;
    }

    cout << "genetic algorithm result: " << currentLength << endl;
    cout << "minimum on the path: " << min << endl;

    file.close();
    return 0;
}