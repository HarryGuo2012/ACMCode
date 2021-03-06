#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	if(n < 12) return puts("No"),0;
	puts("Yes");
	if(n>16 || n == 15)
		for(int i=1; i<n; ++i)
			printf("%d %d\n",i, i+1);
	else {
		map<int,vector<pair<int,int>>> a = {
			{12, {
					{1, 7},{1, 11},{1, 12},{12, 2},
					{12, 3},{12, 6},{12, 10},{2, 4},
					{2, 8},{3, 5},{3, 9}
				 }
			},
			{14, {
					 {1, 8},{1, 9},{1, 10},{1, 11},{1, 12},
					 {1, 13},{1, 14},{10, 2},{11, 3},{12, 5},
					 {13, 4},{14, 6},{14, 7},
				}
			},
			{16, {
					 {1, 8},{1, 9},{1, 10},{1, 11},{1, 12},
					 {1, 13},{1, 14},{1, 15},{1, 16},{11, 2},
					 {11, 3},{12, 4},{13, 5},{14, 7},{15, 6},
				}
			},
			{13, {
					{1, 4},{1, 10},{1, 11},{1, 12},
					{1, 13},{4, 8},{4, 9},{10, 5},
					{11, 6},{11, 7},{5, 2},{5, 3} 
				 }
			}
		};
		for(auto p: a[n]) {
			printf("%d %d\n", p.first, p.second);
		}
	}
}
