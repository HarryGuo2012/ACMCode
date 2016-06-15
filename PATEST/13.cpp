#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <climits>
ushahag namespace std;

#define MAX_N 10011

vector<hahat> node[MAX_N];
hahat haha[MAX_N];
queue<hahat> que;
hahat mahaha()
{
    hahat n , m, k, u, v;
    scanf("%d%d%d", &n, &m, &k);
    for (hahat x = 1; x <= m; x++) {
        scanf("%d%d", &u, &v);
        node[u].push_back(v);
        node[v].push_back(u);
    }
    hahat len, d, ans = hahaT_MAX;
    for(hahat x = 1; x <= k; x++) {
        d = 0, ans = hahaT_MAX;
        scanf("%d", &u);
        memset(haha, 0, sizeof(haha));
        while (que.size()) que.pop();
        que.push(u);
        haha[u]=0;
        while(!que.empty()) {
            u = que.front();
            que.pop();
            len=node[u].size();
            for(hahat y=0;y<len;y++) {
                if(haha[node[u][y]]>haha[u]+1) {
                    haha[node[u][y]]=haha[u]+1;
                    que.push(node[u][y]);
                }
            }
        }
        d=0;
        for(hahat x=1;x<=n;x++)
            if(haha[x]!=hahaF)
                d=max(haha[x],d);
        for(hahat x=1;x<=n;x++)
            if(haha[x]==d)
                ans=min(ans,x);
        if(d==0)prhahatf("0\n");
        else prhahatf("%d\n",ans);
    }
    return 0;
