/*
题意：n个点围成一个圈，
按顺时针编号为0~n-1。
在某个点上会有一个物品C，
初始位置范围是1~n-1。
2个人A、B进行博弈，
A有一个数集s[1]，B有一个数集s[2]
数集内的数x满足1≤x≤n-1。
A、B轮流进行操作，
每轮的操作者可以从自己的数集中选出一个数x，
然后把物品C顺时针向后移动x个点。
先把物品C移动到点1的人获胜。
A、B都采取最优策略使得自己胜利，
若无法胜利就采取最优策略使自己不败（即平局）。
问A、B分别为先手且物品C的位置在点2~n时先手的最优结果。
分析：
设f[pos][who]表示who（用1表示A，2表示B）
先手位于位置pos采取最优策略的结果，胜则为1，败则为2，平局为0。
容易列出状态转移方程（此处略）。
根据状态转移方程我们可以倒着bfs进行转移。
初始化f[0]
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=7005;
int n;
int k[3];
int s[3][maxn];
struct Node
{
    int pos,who,final;
    Node(int pos=0,int who=0,int final=0):pos(pos),who(who),final(final){}
};
queue<Node> Q;
int f[maxn][3],num[maxn][3];
bool vis[maxn][3];
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        cin>>k[1];
        for(int i=1;i<=k[1];i++)scanf("%d",&s[1][i]);
        cin>>k[2];
        for(int i=1;i<=k[2];i++)scanf("%d",&s[2][i]);
        memset(vis,0,sizeof(vis));
        memset(f,0,sizeof(f));
        memset(num,0,sizeof(num));
        Q.push(Node(0,1,2));vis[0][1]=1;
        Q.push(Node(0,2,2));vis[0][2]=1;
        while(!Q.empty())
        {
            Node u=Q.front();Q.pop();
            if(u.final==2)
            {
                int who=3-u.who;
                for(int i=1;i<=k[who];i++)
                {
                    int pos=(u.pos-s[who][i]+n)%n;
                    if(!vis[pos][who])
                    {
                        f[pos][who]=1;
                        vis[pos][who]=1;
                        Q.push(Node(pos,who,1));
                    }
                }
            }
            else
            {
                int who=3-u.who;
                for(int i=1;i<=k[who];i++)
                {
                    int pos=(u.pos-s[who][i]+n)%n;
                    num[pos][who]++;
                    if(!vis[pos][who]&&num[pos][who]==k[who])//？？？
                    {
                        f[pos][who]=2;
                        vis[pos][who]=1;
                        Q.push(Node(pos,who,2));
                    }
                }
            }
        }
        for(int i=1;i<n;i++)
        {
            if(f[i][1]==1)printf("Win");
            else if(f[i][1]==2)printf("Lose");
            else printf("Loop");
            printf("%c",i==n-1?'\n':' ');
        }
        for(int i=1;i<n;i++)
        {
            if(f[i][2]==1)printf("Win");
            else if(f[i][2]==2)printf("Lose");
            else printf("Loop");
            printf("%c",i==n-1?'\n':' ');
        }
    }
    return 0;
}
