/*
题目大意：给出n和m，表示有n个数，m次修改，然后给出n个数的值a1[i]，通过a1数组可以推断出a2数组，长的为a1的长度减一，接着a3、a4直到an（长度为1），
ai[k] = ai-1[k] & ai-1[k+1].sun为所有数的和。每次修改有p和x两个值，表示将a1数组的第p个位置修改成x，输出修改后的sum。
解题思路：假设一开始计算好了sun，然后每一次修改的时候，x和t[p]，只要考虑二进制的每个位即可，如果（x&(1<<i)) == (t[p]&(1<<i))那么不变；如果（x&(1<<i)) = 1，
(t[p]&(1<<i))=0，那么就要加上s；否则减掉s；s的计算方法：从p往左，连续的l个数t[j]&（1<<i) = 1，往右连续r个数t[j]&(1<<i) = 1，s = （l + r + l*r) * (1<<i)。
因为如果出现有一个t[j]&(1<<i) = 0，那么在它后面有多少个t&(1<<i) = 1也没有用。解决完修改的部分，初始值计算就是个问题了，一开始用o（n^2)的方法超时了，很费解。
初始值计算，对于每个位i，遍历一遍数组，计算各个连续的片t&（1<<i) = 1的个数c，s += （c*（c+1）*（1<<i)).
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
