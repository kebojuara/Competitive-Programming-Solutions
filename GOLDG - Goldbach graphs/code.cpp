#include <cstdio>
#include <cstring>
using namespace std;

class goldbach {
private:
    bool prima[1001];
    int faktorprima[1001];
    bool visited[1001];
    int distance[1001];
    int queue[1001];

    void tabelprima() {
        int i;
        for (i = 0; i <= 1000; i++) {
            prima[i] = true;
            faktorprima[i] = i;
        }
        prima[0] = false;
        prima[1] = false;
        for (i = 2; i * i <= 1000; i++) {
            if (prima[i]) {
                int j;
                for (j = i * i; j <= 1000; j += i) {
                    if (prima[j]) prima[j] = false;
                    if (faktorprima[j] == j) faktorprima[j] = i;
                }
            }
        }
    }

    bool bfs(int n, int start) {
        memset(visited, 0, sizeof(visited));
        int head = 0;
        int tail = 0;
        visited[start] = true;
        distance[start] = 0;
        queue[tail++] = start;

        while (head < tail) {
            int p = queue[head++];
            int q = n - p;
            int val = q;

            while (val > 1) {
                int faktor = faktorprima[val];
                while (val % faktor == 0) val /= faktor;

                if (faktor < n && prima[faktor]) {
                    if (!visited[faktor]) {
                        visited[faktor] = true;
                        distance[faktor] = distance[p] + 1;

                        int qq = n - faktor;
                        if (qq > 1 && qq <= 1000 && prima[qq]) {
                            printf("Solution found at distance %d.\n", distance[faktor]);
                            return true;
                        }

                        queue[tail++] = faktor;
                    }
                }
            }
        }
        return false;
    }

public:
    goldbach() {
        tabelprima();
    }

    void proses() {
        int n, start;
        while (true) {
            if (scanf("%d", &n) != 1) return;
            if (n == 0) break;
            if (scanf("%d", &start) != 1) return;

            if (start <= 1 || start >= n || !prima[start]) {
                printf("%d is not a node!\n", start);
                continue;
            }

            int q0 = n - start;
            if (q0 > 1 && q0 <= 1000 && prima[q0]) {
                printf("Solution found at distance 0.\n");
                continue;
            }

            bool found = bfs(n, start);
            if (!found) {
                printf("Solution not reachable.\n");
            }
        }
    }
};

int main() {
    goldbach g;
    g.proses();
    return 0;
}