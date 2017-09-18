/*
题意：
原本有一个串有许多单词，中间用空格隔开，后来把单词全部转换成小写，
然后翻转，再把中间的所有的空格全部去掉，
就得到了一个全是小写字母组成的串。
现在告诉你这样的串t
并告诉你字典w[i](1<=i<=m)
要你找出一种满足条件的原串
保证有解。
思路：
先把每一个w[i]插入trie树中，然后倒着dfs串t,复杂度约莫为
O(sigma(w[i])=1000000*26)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxt=10005;
const int maxm=100005;
const int maxw=1005;
const int maxn=1000005;
int n;
char t[maxt];
int m;
char w[maxm][maxw];
int Next[maxn][26],word[maxn],End[maxn];
int L,root;
int cnt;
int mark[maxt];
int newnode()
{
    memset(Next[L],-1,sizeof(Next[L][0])*26);
    word[L]=0;
    End[L]=-1;
    L++;
    return L-1;
}
void init()
{
    L=0;
    root=newnode();
}
void Insert(char s[],int id)
{
    int u=root;
    int len=strlen(s);
    for(int i=0;i<len;i++)
    {
        int v=tolower(s[i])-'a';
        if(Next[u][v]==-1)
            Next[u][v]=newnode();
        u=Next[u][v];
        word[u]++;
    }
    End[u]=id;
}
bool dfs(int pos)
{
    if(pos==-1)return true;
    if(mark[pos]!=-1)return mark[pos];
    int u=root;
    for(int i=pos;i>=0;i--)
    {
        int v=t[i]-'a';
        if(Next[u][v]==-1)break;
        u=Next[u][v];
        int id=End[u];
        if(id!=-1&&dfs(i-1))
        {
            if(cnt)printf(" ");
            printf("%s",w[id]);
            cnt++;
            return mark[pos]=true;
        }
    }
    return mark[pos]=false;
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        scanf("%s",t);
        cin>>m;
        init();
        for(int i=0;i<m;i++)
        {
            scanf("%s",w[i]);
            Insert(w[i],i);
        }
        memset(mark,-1,sizeof(mark));
        cnt=0;
        dfs(n-1);
        printf("\n");
    }
    return 0;
}
