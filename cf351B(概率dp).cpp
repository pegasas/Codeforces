/*
���⣺��һ��1~n������p[i]��Jeff���ֿ��Խ���������������Ԫ�أ���Furik����0.5�ļ��ʰ���������p[i] < p[i+1]��p[i]��p[i+1]������
��0.5�ļ��ʰ���������p[i] > p[i+1]��p[i]��p[i+1]�������ʽ��������б�������������С��������
��⣺
Jeffһ�β�����Ȼ����һ������ԣ���Furikһ�β���0.5���ʼ���һ������ԣ�0.5��������һ������ԣ�
��dp[i]Ϊ�����������Ϊiʱ�����б�������������С������������ô��dp[0]=0��dp[1]=1��dp[i]=0.5*dp[i-2]+0.5*dp[i]+2��
��dp[i]=dp[i-2]+4����dp�������ż����������Ȳ����У�dp[i]=2*i��iΪż������dp[i]=2*i-1��iΪ�������������ֱ��n^2��������
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
