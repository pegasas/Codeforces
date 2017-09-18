#include <bits/stdc++.h>
using namespace std;
const int maxn = 123456 + 5;
vector<int> G[maxn];
int n, m;
int cnt;
bool On[maxn];
int A[maxn];
int tar, d;
int dis[maxn];
bool vis[maxn];
bool dfs1(int s)
{
    vis[s] = true;
    bool flag = false;
    for(int i = 0; i < G[s].size(); i++) {
        int u = G[s][i];
        if(!vis[u]) {
            dis[u] = dis[s] + 1;
            flag |= dfs1(u);
        }
    }

    if(A[s]) {
        flag = true;
        if(dis[s] > d || (dis[s] == d && s < tar)) {
            d = dis[s];
            tar = s;
        }
    }
    if(flag) {
        On[s] = true;
        cnt++;
    }
    return flag;
}

void dfs2(int s)
{
    vis[s] = true;
    for(int i = 0; i < G[s].size(); i++) {
        int u = G[s][i];
        if(!vis[u] && On[u]) {
            dis[u] = dis[s] + 1;
            if(dis[u] > d || (dis[u] == d && u < tar)) {
                d = dis[u];
                tar = u;
            }
            dfs2(u);
        }
    }
}
int main()
{
    freopen("input.txt","r",stdin);
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for(int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        A[x] = true;
        tar = x;
    }
    fill(dis, dis + n + 1, -1);
    fill(vis, vis + n + 1, false);
    d = 0;
    dis[tar] = 0;
    dfs1(tar);
    int k1 = tar;
    fill(dis, dis + n + 1, -1);
    fill(vis, vis + n + 1, false);
    d = 0;
    dis[tar] = 0;
    dfs2(tar);
    int ans = min(k1, tar);
    printf("%d\n%d", ans, 2*(cnt-1) - d);
    return 0;
}
