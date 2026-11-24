#include <cstdio>
#include <algorithm>
using namespace std;

int R, C, N, F, V;
char names[20][15];
int status[20];
pair<int,int> friends[200];
pair<int,int> rivals[200];
int grid[5][5];
int best = -1;
bool found = false;

bool isValid() {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == -1) continue;
            int s1 = grid[r][c];
            
            if (r > 0 && grid[r-1][c] != -1) {
                int s2 = grid[r-1][c];
                if (status[s1] == 1 && status[s2] == 1) return false;
                for (int i = 0; i < V; i++) {
                    if ((rivals[i].first == s1 && rivals[i].second == s2) ||
                        (rivals[i].first == s2 && rivals[i].second == s1)) return false;
                }
            }
            
            if (c > 0 && grid[r][c-1] != -1) {
                int s2 = grid[r][c-1];
                if (status[s1] == 1 && status[s2] == 1) return false;
                for (int i = 0; i < V; i++) {
                    if ((rivals[i].first == s1 && rivals[i].second == s2) ||
                        (rivals[i].first == s2 && rivals[i].second == s1)) return false;
                }
            }
        }
    }
    return true;
}

int countFriends() {
    int count = 0;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == -1) continue;
            int s1 = grid[r][c];
            
            if (r > 0 && grid[r-1][c] != -1) {
                int s2 = grid[r-1][c];
                for (int i = 0; i < F; i++) {
                    if ((friends[i].first == s1 && friends[i].second == s2) ||
                        (friends[i].first == s2 && friends[i].second == s1)) {
                        count++;
                    }
                }
            }
            
            if (c > 0 && grid[r][c-1] != -1) {
                int s2 = grid[r][c-1];
                for (int i = 0; i < F; i++) {
                    if ((friends[i].first == s1 && friends[i].second == s2) ||
                        (friends[i].first == s2 && friends[i].second == s1)) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

void solve(int pos, int used[]) {
    if (pos == R * C) {
        if (isValid()) {
            found = true;
            int cnt = countFriends();
            best = max(best, cnt);
        }
        return;
    }
    
    int r = pos / C;
    int c = pos % C;
    
    grid[r][c] = -1;
    solve(pos + 1, used);
    
    for (int i = 0; i < N; i++) {
        if (used[i]) continue;
        used[i] = 1;
        grid[r][c] = i;
        solve(pos + 1, used);
        used[i] = 0;
    }
    
    grid[r][c] = -1;
}

int getStudentId(char* name) {
    for (int i = 0; i < N; i++) {
        int match = 1;
        for (int j = 0; names[i][j] || name[j]; j++) {
            if (names[i][j] != name[j]) {
                match = 0;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

int main() {
    scanf("%d %d", &R, &C);
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        char statusStr[15];
        scanf("%s %s", names[i], statusStr);
        status[i] = (statusStr[0] == 'D') ? 1 : 0;
    }
    
    scanf("%d", &F);
    for (int i = 0; i < F; i++) {
        char name1[15], name2[15];
        scanf("%s %s", name1, name2);
        friends[i] = make_pair(getStudentId(name1), getStudentId(name2));
    }
    
    scanf("%d", &V);
    for (int i = 0; i < V; i++) {
        char name1[15], name2[15];
        scanf("%s %s", name1, name2);
        rivals[i] = make_pair(getStudentId(name1), getStudentId(name2));
    }
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            grid[i][j] = -1;
        }
    }
    
    int used[20] = {0};
    solve(0, used);
    
    if (!found) {
        printf("Impossible\n");
    } else {
        printf("%d\n", best);
    }
    
    return 0;
}