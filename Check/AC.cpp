#include <cstdio>

#define MAX_N 10004

int N, Q;

int A[MAX_N];

int main(){
	scanf("%d%d", &N, &Q);
	for(int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	while(Q--){
		int t, x, y;
		scanf("%d%d", &t, &x);
		if(t == 1){
			scanf("%d", &y);
			for(int j = x; j <= N; j++){
				A[j] += y;
				y--;
				if(y < 0) y = 0;
			}
		}
		else
			printf("%d\n", A[x]);
	}
	return 0;
}