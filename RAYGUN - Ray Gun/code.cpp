#include <cstdio>
using namespace std;

class MobiusCalculator {
private:
    int mobius[1000001], mertens[1000001], minprima[1000001], prima[80000];
    int totalprima;

public:
    MobiusCalculator() {
        totalprima = 0;
        mobius[1] = 1;
        for (int i = 2; i <= 1000000; ++i) {
            if (minprima[i] == 0) {
                minprima[i] = i;
                prima[totalprima++] = i;
                mobius[i] = -1;
            }
            for (int j = 0; j < totalprima; ++j) {
                int p = prima[j];
                long long v = 1LL * p * i;
                if (v > 1000000) break;
                minprima[(int)v] = p;
                if (i % p == 0) {
                    mobius[(int)v] = 0;
                    break;
                } else mobius[(int)v] = -mobius[i];
            }
        }
        for (int i = 1; i <= 1000000; ++i)
            mertens[i] = mertens[i - 1] + mobius[i];
    }

    long long solve(long long m, long long n) {
        if (m < n) {
            long long t = m;
            m = n;
            n = t;
        }
        long long s = n, hasil = 0, l = 1;
        while (l <= s) {
            long long a = m / l;
            long long b = n / l;
            long long r1 = m / a;
            long long r2 = n / b;
            long long r = (r1 < r2 ? r1 : r2);
            if (r > s) r = s;
            long long totalmobius = (long long)mertens[(int)r] - (long long)mertens[(int)l - 1];
            hasil += totalmobius * a * b;
            l = r + 1;
        }
        if (m >= 1) hasil++;
        if (n >= 1) hasil++;
        return hasil;
    }
};

int main() {
    MobiusCalculator calc;
    int T;
    scanf("%d", &T);
    for (int TI = 1; TI <= T; ++TI) {
        long long m, n;
        scanf("%lld %lld", &m, &n);
        printf("Case %d: %lld\n", TI, calc.solve(m, n));
    }
    return 0;
}
