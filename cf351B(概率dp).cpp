/*
题意：给一个1~n的排列p[i]，Jeff先手可以交换任意两个相邻元素，而Furik会有0.5的几率把任意满足p[i] < p[i+1]的p[i]和p[i+1]交换，
有0.5的几率把任意满足p[i] > p[i+1]的p[i]和p[i+1]交换，问将整个序列变成升序所需的最小期望步数
题解：
Jeff一次操作必然减少一个逆序对，而Furik一次操作0.5几率减少一个逆序对，0.5几率增加一个逆序对，
设dp[i]为序列逆序对数为i时将序列变成升序所需的最小期望步数，那么有dp[0]=0，dp[1]=1，dp[i]=0.5*dp[i-2]+0.5*dp[i]+2，
即dp[i]=dp[i-2]+4，故dp数组分奇偶后就是两个等差数列，dp[i]=2*i（i为偶数），dp[i]=2*i-1（i为奇数），逆序对直接n^2暴力即可
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=3005;
int n;
int a[maxn];
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        int ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<i;j++)
                if(a[j]>a[i])ans++;
        if(ans&1)ans=2*ans-1;
        else ans*=2;
        printf("%d\n",ans);
    }
    return 0;
}
