#include <cstdio>
#include <algorithm>

#define MAX_N 6

bool table[MAX_N][MAX_N];

int n, m;

int main(){
	table[0][1] = table[1][0] = 1;
	table[0][2] = table[2][0] = 1;
	table[0][3] = table[3][0] = 1;
	table[1][2] = table[2][1] = 1;
	table[1][3] = table[3][1] = 1;
	table[1][4] = table[4][1] = 1;
	table[2][3] = table[3][2] = 1;
	table[2][4] = table[4][2] = 1;
	table[3][4] = table[4][3] = 1;
	table[3][5] = table[5][3] = 1;
	table[4][5] = table[5][4] = 1;
	scanf("%d%d", &n, &m);
	if(n <= 5 && m <= 5){
		if(table[n][m])printf("Yes\n");
		else printf("No\n");
	}
	else{
		if(abs(n - m) == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}