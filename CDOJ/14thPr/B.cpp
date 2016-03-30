#include <cstdio>
#include <cstring>

#define MAX_N 10010

int T;
int x, y;

int coin[20] = {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
int pos = 0;
bool b[20];

int haha(int a, int i){
	if(a == 1 || a == 3)
		b[i] = 1;
	if(a == 2 || a == 4 || a == 6 || a == 7 || a == 8 || a == 9)
		b[i + 1] = 1;
	if(a == 5 || a == 7 || a == 9)
		b[i + 2] = 1;
}

bool check(int t){
	memset(b, 0, sizeof(b));
	haha(t % 10, 0);
	haha(t / 10 % 10, 3);
	haha(t / 100 % 10, 6);
	haha(t / 1000 % 10, 9);
	if(t >= 10000)
		b[12] = 1;
	return b[pos];
}

int main(){
	scanf("%d", &T);
	while(T--){
		pos = 0;
		double X, Y;
		scanf("%lf%lf", &X, &Y);
		int ans;
		x = X * 100, y = Y * 100;
		while(coin[pos] != y) pos++;
		for(int i = x; i >= 0; i--){
			if(check(i)){
				ans = x - i;
				break;
			}
		}
		printf("%.2f\n", ans / 100.0);
	}
	return 0;
}