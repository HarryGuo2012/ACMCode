#include <cstdio>
#include <cstring>

int T;
char c[4];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%s", c);
		double sum = 0;
		for(int i = 0; i < 3; i++)
			sum += c[i];
		printf("%.2f\n", sum / 3);
	}
	return 0;
}