#include <stdio.h>
#include <queue>
#include <unordered_map>
using namespace std;

int main() {
    int totalteam;
    scanf("%d", &totalteam);

    queue<int> a;
    queue<int> b[totalteam];
    unordered_map<int, int> steam;
    
    bool visited[totalteam];

    for (int i = 0; i < totalteam; i++) {
        int student;
        scanf("%d", &student);
        for (int j = 0; j < student; j++) {
            int sid;
            scanf("%d", &sid);
            steam[sid] = i;
        }
        visited[i] = 0;
    }

    char command[10];
    
    while (scanf("%s", command) != EOF) {
        if (command[0] == 'E') {
            int sid;
            scanf("%d", &sid);
            int tid = steam[sid];

            if (visited[tid] == 0) {
                a.push(tid);
                visited[tid] = 1;
            }
            b[tid].push(sid);

        } else if (command[0] == 'D') {
            int tid = a.front();
            printf("%d\n", b[tid].front());
            b[tid].pop();

            if (b[tid].empty()) {
                a.pop();
                visited[tid] = 0;
            }
        }
    }

    return 0;
    
}