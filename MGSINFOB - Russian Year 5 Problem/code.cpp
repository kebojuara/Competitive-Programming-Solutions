#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
	int a,total=100;
	
	unordered_map<int, int> seen;
	
	int n;
    scanf("%d", &n);
    
    if(n == 1){
        scanf("%d", &a);
        printf("1");
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        int c = total - a;
        if (seen.find(c) != seen.end()) {
            printf("%d\n%d", seen[c]+1, i+1);
            return 0;
        }
        seen[a] = i;
    }
}