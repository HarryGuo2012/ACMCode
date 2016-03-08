#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#define MAX_N 500
using namespace std;

typedef long long ll;

ll F[MAX_N],G[MAX_N];

ll N;

ll dp[MAX_N];
ll a[MAX_N];

double X1(int t){
    return a[t];
}

double Y1(int t){
    return G[t-1]-G[t]+F[t];
}

double Slope1(int u,int v) {
    return (Y1(u) - Y1(v)) / (X1(u) - X1(v));
}

double Y2(int t){
    return F[t-1];
}

double X2(int t){
    return t;
}

double Slope2(int u,int v){
    return (Y2(u)-Y2(v))/(X2(u)-X2(v));
}

int que[MAX_N];
int T;
int main() {
    cin.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>a[i];
    for(int i=1;i<=N;i++)
        F[i]=F[i-1]+a[i];
    for(int i=1;i<=N;i++)
        G[i]=G[i-1]+a[i]*i;
    long long ans=G[N];
    int front = 0, rear = 0;
    que[rear++] = 1;

    for (int i = 2; i <= N; i++) {
        while (rear - front > 1 && Slope1(que[front], que[front + 1]) >= i)front++;
        int j = que[front];
        ans=max(ans,G[j-1]+G[N]-G[i]+G[i]-G[j]-F[i]+F[j]+a[j]*i);
        //cout<<i<<" "<<j<<" "<<ans<<endl;
        while (rear - front > 1 && Slope1(que[rear - 1], que[rear - 2]) <= Slope1(que[rear - 1], i))rear--;
        que[rear++] = i;
    }
    front = 0, rear = 0;
    que[rear++] = 1;

    for (int i = 2; i <= N; i++) {
        while (rear - front > 1 && Slope2(que[front], que[front + 1]) >= G[i])front++;
        int j = que[front];
        ans=max(ans,G[N]-G[i]+G[i-1]+F[i-1]-F[j-1]+a[i]*j);
        while (rear - front > 1 && Slope2(que[rear - 1], que[rear - 2]) <= Slope2(que[rear - 1], i))rear--;
        que[rear++] = i;
    }
    cout<<ans<<endl;
    //cin>>N;
    return 0;
}