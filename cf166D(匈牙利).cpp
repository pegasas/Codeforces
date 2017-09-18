/*
题意：
给n个鞋子，每双鞋子有价钱和大小
给m个顾客，每个乘客有可以支付的价钱以及脚的大小
每个顾客可以穿跟自己脚一样大或者大一码的鞋
问最多有多少个乘客可以穿到鞋？
答案：
二分图，一排鞋子，一排乘客，
然后穿鞋就是连一条边（如果存在的话）
然后跑一边匈牙利算法即可
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100005;
int n,m;
struct Node
{
    int c,s,id;
    Node(int c=0,int s=0):c(c),s(s){}
}S[maxn],C[maxn];
map<int,int> Map;
vector<int> G[maxn];
int match[maxn];
bool cmp(const Node &a,const Node &b)
{
    return a.c>b.c;
}
void AddEdge(int u,int v)
{
    G[u].push_back(v);
}
bool dfs(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(match[v]!=u)
        {
            if(match[v]==-1||dfs(match[v]))
            {
                match[v]=u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        Map.clear();
        for(int i=1;i<=n;i++)
            G[i].clear();
        memset(match+1,-1,sizeof(match[0])*m);

        for(int i=1;i<=n;i++)
        {
            int c,s;
            scanf("%d%d",&c,&s);
            S[i]=Node(c,s);
            S[i].id=i;
        }
        sort(S+1,S+1+n,cmp);
        cin>>m;
        for(int i=1;i<=m;i++)
        {
            int c,s;
            scanf("%d%d",&c,&s);
            C[i]=Node(c,s);
        }
        for(int i=1;i<=n;i++)
            Map[S[i].s]=i;

        for(int i=1;i<=m;i++)
        {
            if(Map[C[i].s+1]&&C[i].c>=S[Map[C[i].s+1]].c)
                AddEdge(Map[C[i].s+1],i);
            if(Map[C[i].s]&&C[i].c>=S[Map[C[i].s]].c)
                AddEdge(Map[C[i].s],i);
        }
        ll ans=0;
        int ret=0;
        for(int i=1;i<=n;i++)
            if(dfs(i))
            {
                ans+=S[i].c*1LL;
                ret++;
            }
        cout<<ans<<"\n"<<ret<<"\n";
        for(int i=1;i<=m;i++)
            if(match[i]!=-1)
                printf("%d %d\n",i,S[match[i]].id);
    }
    return 0;
}
