#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX_N 303

int T;
int N, M;

int G[MAX_N][MAX_N];
int h[MAX_N][MAX_N], f[MAX_N][MAX_N];

int main(){
	scanf("%d", &T);
	while(T--){
		memset(h, 0, sizeof(h));
		memset(f, 0, sizeof(f));
		int ans = 1;
		scanf("%d%d", &N, &M);
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= M; j++)
				scanf("%d", &G[i][j]);
		for(int x = 1; x <= N; x++)
			for(int y = 1; y <= M; y++){
				for(int l = 1; l + x <= N && x - l >= 1 && G[l + x][y] == G[x - l][y]; l++)
					h[x][y] = l;
				for(int l = 1; l + y <= M && y - l >= 1 && G[x][l + y] == G[x][y - l]; l++)
					f[x][y] = l;
			}
		for(int x = 1; x <= N; x++)
			for(int y = 1; y <= M; y++){
				int l;
				for(l = 0; l <= std::min(h[x][y], f[x][y]); l++)
					if(f[l + x][y] < l || f[x - l][y] < l || h[x][y - l] < l || h[x][y + l] < l)
						break;
				ans = std::max(ans, 2 * (l - 1) + 1);
			}
		memset(h, 0, sizeof(h));
		memset(f, 0, sizeof(f));
		for(int x = 1; x <= N; x++)
			for(int y = 1; y <= M; y++){
				for(int l = 1; l + x <= N && x - (l - 1) >= 1 && G[l + x][y] == G[x - l + 1][y]; l++)
					h[x][y] = l;
				for(int l = 1; l + y <= M && y - (l - 1) >= 1 && G[x][y + l] == G[x][y - l + 1]; l++)
					f[x][y] = l;
			}
			
		for(int x = 1; x <= N; x++)
			for(int y = 1; y <= M; y++){
				int l;
				for(l = 1; l <= std::min(h[x][y], f[x][y]); l++)
					if(f[l + x][y] < l || f[x - l + 1][y] < l || h[x][y - l + 1] < l || h[x][y + l] < l)
						break;
					ans = std::max(ans, 2 * (l - 1));
			}
		printf("%d\n", ans);
	}
	return 0;
}