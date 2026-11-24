#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
T getNum() {
    T res = 0;
    char c;
    while (1) {
        c = getchar_unlocked();
        if (c == ' ' || c == '\n') continue;
        else break;
    }
    res = c - '0';
    while (1) {
        c = getchar_unlocked();
        if (c >= '0' && c <= '9') res = 10 * res + c - '0';
        else break;
    }
    return res;
}

class Jobs {
    int t1, t2;
public:
    Jobs(int a, int b) : t1(a), t2(b) {}
    int rd_t1() { return t1; }
    int rd_t2() { return t2; }
    bool operator<(const Jobs &b) const {
        return (min(t1, b.t2) < min(t2, b.t1));
    }
};

int n, tmp1[303], tmp2[303], packing, res;
vector<Jobs> vc_jobs;

int main() {
    n = getNum<int>();
    for (int i = 0; i < n; i++) tmp1[i] = getNum<int>();
    for (int i = 0; i < n; i++) tmp2[i] = getNum<int>();

    for (int i = 0; i < n; i++) {
        Jobs tmp(tmp1[i], tmp2[i]);
        vc_jobs.push_back(tmp);
    }

    sort(vc_jobs.begin(), vc_jobs.end());

    packing = 0;
    res = 0;

    for (int i = 0; i < n; i++) {
        packing += vc_jobs[i].rd_t1();
        if (res < packing) res = packing;
        res += vc_jobs[i].rd_t2();
    }

    printf("%d\n", res);

    return 0;
}
