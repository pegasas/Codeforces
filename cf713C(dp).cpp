/*
题意：给n个数的一个list,在一次操作内可以使得n个数中任一个数加1减1，问使得这个序列严格递增的最小操作数
答案：
（1）严格递增=>严格非递减
令a[i]'=a[i]-i,
因为严格递增满足a[i]>a[i-1] 而i>i-1 所以 a[i]-(i)>=a[i-1]-(i-1)
（2）严格非递减的数一定是原来n个数中的
因为不是n个数中，也一定会是n个数介于两个数中间的
如果那样 调整到一边 总会有更好的收益（或者存在收益相同的对应方案）
dp[i][j]表示前i个数构成递增序列，其中第i个数取原来n个数里面第j个
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
