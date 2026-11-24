#include <cstdio>

long long h[100001];
int arr[100001];

int main() {
    int n, top, i;
    long long maxarea, area;

    while (scanf("%d", &n) == 1 && n != 0) {
        for (i = 0; i < n; i++)
            scanf("%lld", &h[i]);

        h[n] = 0;
        top = -1;
        maxarea = 0;

        for (i = 0; i <= n; i++) {
            while (top >= 0 && h[arr[top]] > h[i]) {
                int idx = arr[top--];
                int width = (top < 0) ? i : i - arr[top] - 1;
                area = h[idx] * width;
                if (area > maxarea) maxarea = area;
            }
            arr[++top] = i;
        }

        printf("%lld\n", maxarea);
    }

    return 0;
}