#include <cstdio>

int main() {
    int b;
    scanf("%d", &b);
    
    for (int r = 1; r <= b; r++) {
        int s;
        scanf("%d", &s);
        
        int bestsum = 0, besti = 1, bestj = 1;
        int currentsum = 0, currentstart = 1;
        
        for (int i = 0; i < s - 1; i++) {
            int n;
            scanf("%d", &n);
            currentsum += n;
            int currentj = i + 2;
            int currentlen = currentj - currentstart;
            int bestlen = bestj - besti;
            
            if (currentsum > bestsum || (currentsum == bestsum && currentlen > bestlen)) {
                bestsum = currentsum;
                besti = currentstart;
                bestj = currentj;
            }
            
            if (currentsum < 0) {
                currentsum = 0;
                currentstart = i + 2;
            }
        }
        
        if (bestsum <= 0) {
            printf("Route %d has no nice parts\n", r);
        } else {
            printf("The nicest part of route %d is between stops %d and %d\n", r, besti, bestj);
        }
    }
    
    return 0;
}