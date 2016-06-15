bool dfs(bool *vis, int cou, int k, int sum, int x) {
    //deep++;
    if (cou == n)
        return true;
    int same = -1;
    for (int i = x; i < n; i++) {
        if (vis[i] || same == stick[i] || compelet[i])
            continue;
        vis[i] = true;
        if (stick[i] + k < sum) {
            if (dfs(vis, cou + 1, stick[i] + k, sum, i)) {
                compelet[i] = 1;
                return true;
            }
            else
                same = stick[i];
        }
        else if (stick[i] + k == sum) {
            if (dfs(vis, cou + 1, 0, sum, 0))
                return true;
            else {
                same = stick[i];
                vis[i] = false;
                return false;
            }
        }
        vis[i] = false;
        if (k == 0)break;
    }
    return false;
}