/*
���⣺
ԭ����һ��������൥�ʣ��м��ÿո�����������ѵ���ȫ��ת����Сд��
Ȼ��ת���ٰ��м�����еĿո�ȫ��ȥ����
�͵õ���һ��ȫ��Сд��ĸ��ɵĴ���
���ڸ����������Ĵ�t
���������ֵ�w[i](1<=i<=m)
Ҫ���ҳ�һ������������ԭ��
��֤�н⡣
˼·��
�Ȱ�ÿһ��w[i]����trie���У�Ȼ����dfs��t,���Ӷ�ԼĪΪ
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
