/*
����
��һ��ͼ��ݣ��տ�ʼû�飬��������k���飬��n�죬
ÿһ�����һ��������һ���飬����黹�����ͼ������У�
�Ϳ���ֱ�ӽ赽������ͼ��ݵ��˻Ṻ����һ���飬�κ�һ����۸���1��
�������ͼ��ݴ����Ѵ������һ��蹺�������������һЩ�飬�ٹ���
��ͼ��ݵ���������Ҫ������Ǯ����
˼·
̰�ģ�����ÿһ��Ҫ����飬�������ͼ������У��Ͳ��ù��ˣ�
���û�У���������������������С��k����ֱ�ӹ�����һ���飬
���������������е�������һ�γ���������飬Ȼ���ٹ�����һ���飬
ÿһ�춼������󹺽����ܴ������Ǵ�
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
