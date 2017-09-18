/*
题意：需要在地图上连续走DIMA四个字母
答案：dfs,走过的就记下来下次不要再走，然后如果是走到已经vis过的表明走到了一个环
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
const int inf=0x3f3f3f3f;
int n,m;
char M[maxn][maxn];
char Next[200];
int dis[maxn][maxn];
bool vis[maxn][maxn];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int dfs(int x,int y)
{
    if(dis[x][y]!=-1)return dis[x][y];
    int step=0;
    char c=M[x][y];
    for(int i=0;i<4;i++)
    {
        int xx=x+dx[i],yy=y+dy[i];
        if(xx<0||xx>=n||yy<0||yy>=m||Next[c]!=M[xx][yy])continue;
        if(vis[xx][yy])step=inf;
        else
        {
            vis[xx][yy]=1;
            int tmp=dfs(xx,yy);
            step=max(tmp,step);
            vis[xx][yy]=0;
        }
    }
    dis[x][y]=step+1;
    return dis[x][y];
}
int main()
{
    while(cin>>n>>m)
    {
        for(int i=0;i<n;i++)scanf("%s",M[i]);
        Next['D']='I';
        Next['I']='M';
        Next['M']='A';
        Next['A']='D';
        memset(dis,-1,sizeof(dis));
        int ans=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(M[i][j]=='D'&&dis[i][j]==-1)
                {
                    vis[i][j]=1;
                    int t=dfs(i,j);
                    ans=max(ans,t/4);
                    vis[i][j]=0;
                }
        if(ans==0) cout<<"Poor Dima!"<<endl;
        else if(ans>=inf/4)cout<<"Poor Inna!"<<endl;
        else cout<<ans<<endl;
    }
    return 0;
}
