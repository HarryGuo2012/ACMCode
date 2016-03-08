#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
#define MAX_N 100005
#define MAX_L 1003
using namespace std;

string s;

typedef long long ll;
ll sum[MAX_N],po[MAX_N];
const ll P=137,mod=1000000009;

void init(){
    for(int i=s.length()-1;i>=0;i--)
        sum[i]=(sum[i+1]*P%mod+s[i])%mod;
}

bool dp[MAX_N];
int pre[MAX_N];

string word[MAX_N];

typedef pair<ll,int> pa;

vector<pa> w[MAX_L];
int ans[MAX_N];
ll n,m;
ll Get(string st){
    ll res=0;
    reverse(st.begin(),st.end());
    for(int i=0;i<st.size();i++){
        char c=st[i];
        if(c>='A'&&c<='Z')c=c-'A'+'a';
        res=(res+c*po[i]%mod)%mod;
    }
    return res;
}

int check(int i,int j){
    ll tmp=((sum[i]-sum[i+j]*po[j])%mod+mod)%mod;
    int t=lower_bound(w[j].begin(),w[j].end(),make_pair(tmp,0))-w[j].begin();
    if(t<w[j].size()&&w[j][t].first==tmp)return w[j][t].second;
    return 0;
}

void output(int i,int j){
    cout<<(char)(s[j-1]-'a'+'A');
    for(int k=j-2;k>=i;k--)
        cout<<s[k];
    cout<<" ";
}

int main(){
    cin.sync_with_stdio(false);
    po[0]=1;
    for(int i=1;i<MAX_N;i++)
        po[i]=po[i-1]*P%mod;
    cin>>n>>s>>m;
    init();
    for(int i=1;i<=m;i++){
        cin>>word[i];
        w[word[i].length()].push_back(make_pair(Get(word[i]),i));
    }
    for(int i=0;i<MAX_L;i++)
        sort(w[i].begin(),w[i].end());
    dp[n]=1;
    for(int i=n-1;i>=0;i--){
        for(int j=1;j<MAX_L;j++){
            if(j+i>n)break;
            if(dp[j+i]){
                int t=check(i,j);
                if(t==0)continue;
                ans[i]=t;
                dp[i]=1,pre[i]=i+j;
            }
        }
    }
    int now=0;
    while(now!=n){
        cout<<word[ans[now]]<<" ";
        now=pre[now];
    }
    cout<<endl;
    return 0;   
}