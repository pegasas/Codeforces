/*
��Ŀ���⣺����n��m����ʾ��n������m���޸ģ�Ȼ�����n������ֵa1[i]��ͨ��a1��������ƶϳ�a2���飬����Ϊa1�ĳ��ȼ�һ������a3��a4ֱ��an������Ϊ1����
ai[k] = ai-1[k] & ai-1[k+1].sunΪ�������ĺ͡�ÿ���޸���p��x����ֵ����ʾ��a1����ĵ�p��λ���޸ĳ�x������޸ĺ��sum��
����˼·������һ��ʼ�������sun��Ȼ��ÿһ���޸ĵ�ʱ��x��t[p]��ֻҪ���Ƕ����Ƶ�ÿ��λ���ɣ������x&(1<<i)) == (t[p]&(1<<i))��ô���䣻�����x&(1<<i)) = 1��
(t[p]&(1<<i))=0����ô��Ҫ����s���������s��s�ļ��㷽������p����������l����t[j]&��1<<i) = 1����������r����t[j]&(1<<i) = 1��s = ��l + r + l*r) * (1<<i)��
��Ϊ���������һ��t[j]&(1<<i) = 0����ô���������ж��ٸ�t&(1<<i) = 1Ҳû���á�������޸ĵĲ��֣���ʼֵ������Ǹ������ˣ�һ��ʼ��o��n^2)�ķ�����ʱ�ˣ��ܷѽ⡣
��ʼֵ���㣬����ÿ��λi������һ�����飬�������������Ƭt&��1<<i) = 1�ĸ���c��s += ��c*��c+1��*��1<<i)).
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100005;
int n,m;
int a[maxn];
ll sum;
void find(int k,ll &l,ll &r,int p)
{
    l=r=0;
    for(int i=p-1;i>=1;i--)
    {
        if((a[i]&k)==0)break;
        l++;
    }
    for(int i=p+1;i<=n;i++)
    {
        if((a[i]&k)==0)break;
        r++;
    }
}
void solve(int p,int nowv,int prev)
{
    for(int i=0;(1<<i)<=100000;i++)
    {
        if((nowv&(1<<i))==(prev&(1<<i)))continue;
        ll l,r;
        find((1<<i),l,r,p);
        ll add=(l*r+l+r+1)*(1LL<<i);
        if(nowv&(1<<i))
            sum+=add;
        else
            sum-=add;
    }
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n>>m)
    {
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        sum=0;
        for(int i=0;(1<<i)<=100000;i++)
        {
            int cntbit=0;
            for(int j=1;j<=n;j++)
                if(a[j]&(1<<i))cntbit++;
                else
                {
                    sum+=cntbit*(cntbit+1)*(1<<i)/2;
                    cntbit=0;
                }
            sum+=(ll)cntbit*(cntbit+1)*(1<<i)/2;
        }
        for(int i=0;i<m;i++)
        {
            int p,v;
            scanf("%d%d",&p,&v);
            solve(p,v,a[p]);
            a[p]=v;
            printf("%I64d\n",sum);
        }
    }
    return 0;
}
