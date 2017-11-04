/*
���⣺n����Χ��һ��Ȧ��
��˳ʱ����Ϊ0~n-1��
��ĳ�����ϻ���һ����ƷC��
��ʼλ�÷�Χ��1~n-1��
2����A��B���в��ģ�
A��һ������s[1]��B��һ������s[2]
�����ڵ���x����1��x��n-1��
A��B�������в�����
ÿ�ֵĲ����߿��Դ��Լ���������ѡ��һ����x��
Ȼ�����ƷC˳ʱ������ƶ�x���㡣
�Ȱ���ƷC�ƶ�����1���˻�ʤ��
A��B����ȡ���Ų���ʹ���Լ�ʤ����
���޷�ʤ���Ͳ�ȡ���Ų���ʹ�Լ����ܣ���ƽ�֣���
��A��B�ֱ�Ϊ��������ƷC��λ���ڵ�2~nʱ���ֵ����Ž����
������
��f[pos][who]��ʾwho����1��ʾA��2��ʾB��
����λ��λ��pos��ȡ���Ų��ԵĽ����ʤ��Ϊ1������Ϊ2��ƽ��Ϊ0��
�����г�״̬ת�Ʒ��̣��˴��ԣ���
����״̬ת�Ʒ������ǿ��Ե���bfs����ת�ơ�
��ʼ��f[0]
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
                    if(!vis[pos][who]&&num[pos][who]==k[who])//������
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
