/*
题意
有一个图书馆，刚开始没书，最多可容纳k本书，有n天，
每一天会有一个人来借一本书，当天归还，如果图书馆里有，
就可以直接借到，否则图书馆的人会购进这一本书，任何一本书价格都是1，
如果现在图书馆存书已达上限且还需购买，则必须先舍弃一些书，再购买，
问图书馆的人最少需要花多少钱购书
思路
贪心，对于每一天要借的书，如果现在图书馆里有，就不用管了，
如果没有，考虑现有书的数量，如果小于k，就直接购进这一本书，
否则，先舍弃掉已有的书中下一次出现最晚的书，然后再购进这一本书，
每一天都处理完后购进的总次数就是答案
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=80+5;
int n,k;
int a[maxn],buy[maxn];
int Next[maxn];
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n>>k)
    {
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        memset(buy+1,0,sizeof(buy[0])*n);
        int cnt=0;
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            if(buy[a[i]])continue;
            if(cnt<k)
            {
                cnt++;
                ans++;
                buy[a[i]]=true;
            }
            else
            {
                memset(Next+1,0,sizeof(Next[0])*n);
                for(int j=1;j<=n;j++)
                    if(buy[j])Next[j]=100;
                for(int j=1;j<=n;j++)
                    if(buy[j])
                    {
                        for(int k=i+1;k<=n;k++)
                            if(a[k]==j)
                            {
                                Next[j]=k;
                                break;
                            }
                    }
                int Maxpos=0;
                int Maxj=-1;
                for(int j=1;j<=n;j++)
                    if(Next[j]>Maxpos)
                    {
                        Maxpos=Next[j];
                        Maxj=j;
                    }
                buy[Maxj]=false;
                buy[a[i]]=true;
                ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
