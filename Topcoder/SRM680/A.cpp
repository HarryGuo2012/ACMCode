#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class BearPair{
public:
	int bigDistance(string s){
		int ans=-1;
		for(int i=0;i<s.length();i++)
			for(int j=0;j<s.length();j++)
				if(s[i]!=s[j])ans=max(ans,abs(i-j));
		return ans;
	}
};

int main(){
	return 0;
}