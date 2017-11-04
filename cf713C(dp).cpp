/*
���⣺��n������һ��list,��һ�β����ڿ���ʹ��n��������һ������1��1����ʹ����������ϸ��������С������
�𰸣�
��1���ϸ����=>�ϸ�ǵݼ�
��a[i]'=a[i]-i,
��Ϊ�ϸ��������a[i]>a[i-1] ��i>i-1 ���� a[i]-(i)>=a[i-1]-(i-1)
��2���ϸ�ǵݼ�����һ����ԭ��n�����е�
��Ϊ����n�����У�Ҳһ������n���������������м��
������� ������һ�� �ܻ��и��õ����棨���ߴ���������ͬ�Ķ�Ӧ������
dp[i][j]��ʾǰi�������ɵ������У����е�i����ȡԭ��n���������j��
dp[i][j]=min(dp[i-1][k]+abs(a[i]-b[k]))(1<=k<=j)
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
int n;
int a[maxn],b[maxn],dp[maxn][maxn];
int main()
{
    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        for(int i=1;i<=n;i++){scanf("%d",&a[i]);a[i]-=i;b[i]=a[i];}
        sort(b+1,b+1+n);
        for(int i=1;i<=n;i++)
        {
            int Min=dp[i-1][1];
            for(int j=1;j<=n;j++)
            {
                Min=min(Min,dp[i-1][j]);
                dp[i][j]=Min+abs(a[i]-b[j]);
            }
        }
        int ans=dp[n][1];
        for(int i=2;i<=n;i++)ans=min(ans,dp[n][i]);
        printf("%d\n",ans);
    }
    return 0;
}
