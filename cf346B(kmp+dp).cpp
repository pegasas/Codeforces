/*
题意：
给s1,s2,virus,需要求出LCS(s1,s2)且不包含virus为子串
答案：
dp[i][j][k]表示s1[1..i]与s2[1..j]的LCS并且virus匹配长度为k的最长长度
然后转移即可
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
const int inf=0x3f3f3f3f;
char s1[maxn],s2[maxn],virus[maxn];
int Next[maxn];
int dp[maxn][maxn][maxn],pre[maxn][maxn][maxn];
void getNext(char s[])
{
    int i,j,len;
    len=strlen(s);
    j=Next[0]=-1;
    i=0;
    while(i<len)
    {
        while(j!=-1&&s[i]!=s[j])j=Next[j];
        i++;j++;
        Next[i]=((j!=-1&&s[i]==s[j])?Next[j]:j);
    }
}
int get(int i,int j,int k)
{
    return (i<<16)+(j<<8)+k;
}
void dfs(int id)
{
    int i=(id>>16),j=id>>8&0xff,k=id&0xff;
    if(!i&&!j)return;
    id=pre[i][j][k];
    int ii=(id>>16),jj=id>>8&0xff,kk=id&0xff;
    dfs(id);
    if(dp[i][j][k]-dp[ii][jj][kk]==1)printf("%c",s1[i]);
}
int main()
{
////    freopen("input.txt","r",stdin);
    while(cin>>s1+1>>s2+1>>virus+1)
    {
        int lens1=strlen(s1+1);
        int lens2=strlen(s2+1);
        int lenvirus=strlen(virus+1);

        getNext(virus+1);
        memset(dp,-inf,sizeof(dp));
        for(int i=0;i<=lens1;i++)
            for(int j=0;j<=lens2;j++)dp[i][j][0]=0;

        for(int i=1;i<=lens1;i++)
            for(int j=1;j<=lens2;j++)
                for(int k=0;k<lenvirus;k++)
                {
                    if(dp[i][j][k]<dp[i-1][j][k])
                    {
                        dp[i][j][k]=dp[i-1][j][k];
                        pre[i][j][k]=get(i-1,j,k);
                    }
                    if(dp[i][j][k]<dp[i][j-1][k])
                    {
                        dp[i][j][k]=dp[i][j-1][k];
                        pre[i][j][k]=get(i,j-1,k);
                    }
                    if(s1[i]==s2[j])
                    {
                        int w=k;
                        while(w!=-1&&s1[i]!=virus[1+w])w=Next[w];
                        w++;
                        if(dp[i][j][w]<dp[i-1][j-1][k]+1)
                        {
                            dp[i][j][w]=dp[i-1][j-1][k]+1;
                            pre[i][j][w]=get(i-1,j-1,k);
                        }
                    }
                }
        int ans=0,ansid;
        for(int i=0;i<lenvirus;i++)
            if(dp[lens1][lens2][i]>ans)
            {
                ans=dp[lens1][lens2][i];
                ansid=get(lens1,lens2,i);
            }
        if(!ans)printf("0\n");
        else dfs(ansid);
    }
    return 0;
}
