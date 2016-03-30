#include <cstring>
#include <cstdio>
#include <string>

#define MAX_N (1 << 23) + 5

int n;

char p[MAX_N], s[MAX_N];

std::string pattern, text;

void Add(){
	for(int i = 0; i < n; i++){
		if(p[i] == 'a')
			p[i + n] = 'b';
		else
			p[i + n] = 'a';
	}
}

int next[MAX_N];

int KMP(){
	int n = pattern.size();
	for(int i = 1; i < n; i++){
		int j = i;
		while(j > 0){
			j = next[j];
			if(pattern[j] == pattern[i]){
				next[i + 1] = j + 1;
				break;
			}
		}
	}
	int m = text.size();
	for(int i = 0, j = 0; i < m; i++){
		if(j < n && text[i] == pattern[j]) j++;
		else{
			while(j > 0){
				j = next[j];
				if(text[i] == pattern[j]){
					j++;
					break;
				}
			}
		}
		if(j == n)
			return i - n + 1;
	}
	return -2;
}

int main(){
	n = 1;
	p[0] = 'a';
	while(true){
		Add();
		n <<= 1;
		if((n << 1) > MAX_N) break;
	}
	scanf("%s", s);
	pattern = s, text = p;
	int ans = KMP() + 1;
	printf("%d\n", ans);
	return 0;
}