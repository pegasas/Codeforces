/*
���⣺��һ��n���ڵ����������m���ڵ㱻��죬
��һ�����ߵ�����һ�����ʱ��Ϊ1
�����m������������ʱ��
˼·��
��1��һ���ǴӺ�ɫ�ĵ㿪ʼ�ߣ���Ȼ�Ʊػ����ߵ���ɫ�ĵ㣬�Ͳ������
��2��Ҫ����m���ڵ㣬�ͱ������m���ڵ㹹�ɵ��ǿ�����,�������ڵ���Ϊtot
��3��Ȼ�����ŷ���һ���������������ֱ���ߣ���ֱ���ĳ���Ϊd,
����·�߳���Ϊ2*(tot-1)-d��
tot-1��ʾ�����ı���
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=123456+5;
int n,m;
vector<int> G[maxn];
int A[maxn];
int insubtree[maxn],dis[maxn];
int s;
int d;
int v;
int tot;
bool dfs1(int u,int fa)
{
    bool flag=false;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa)continue;
        dis[v]=dis[u]+1;
        flag|=dfs1(v,u);
    }
    if(A[u])
    {
        flag=true;
        if(dis[u]>d||(dis[u]==d&&u<s))
        {
            s=u;
            d=dis[u];
        }
    }
    if(flag)
    {
        insubtree[u]=true;
        tot++;
    }
    return flag;
}
void dfs2(int u,int fa)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa)continue;
        if(insubtree[v])
        {
            dis[v]=dis[u]+1;
            if(dis[v]>d||(dis[v]==d&&v<s))
            {
                s=v;
                d=dis[v];
            }
            dfs2(v,u);
        }

    }
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n>>m)
    {
        for(int i=1;i<=n;i++)G[i].clear();
        memset(A+1,0,sizeof(A[0])*n);
        memset(insubtree+1,0,sizeof(insubtree[0])*n);


        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i=0;i<m;i++)
        {
            int x;
            scanf("%d",&x);
            A[x]=true;
            s=x;
        }
        tot=0;
        memset(dis+1,-1,sizeof(dis[0])*n);
        d=0;
        dis[s]=0;
        dfs1(s,-1);
        int v1=s;
        memset(dis+1,-1,sizeof(dis[0])*n);
        d=0;
        dis[s]=0;
        dfs2(s,-1);
        int v2=s;
        v=min(v1,v2);
        printf("%d\n%d\n",v,2*(tot-1)-d);
    }
    return 0;
}
