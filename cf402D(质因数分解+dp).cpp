/*
题意:给出一个数列
可以将某一个前缀除去他们的gcd,
有一个函数f(x)，
f(1) = 0 ,
f(x) = f(x/p)+1,
f(x) = f(x/p)-1(p是坏素数)
问
∑i≤n f(a[i])
的最大值
思路：倒着扫描，如果某个gcd的坏素因子个数>Gcd好素因子个数的话，
那么就让1-i都除以这个gcd
然后就直接统计即可
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=5005;
const int maxnum=100005;
int n,m;
int a[maxn],b[maxn];
bool sieve[maxnum];
vector<int> primes;
map<int,bool> Map;
void getprimelist()
{
    memset(sieve,0,sizeof(sieve));
    primes.clear();

    sieve[1]=1;
    for(int i=2;i*i<maxnum;i++)
    {
        if(sieve[i])continue;
        for(int j=i*i;j<maxnum;j+=i)
            sieve[j]=1;
    }
    for(int i=2;i<maxnum;i++)
    {
        if(sieve[i])continue;
        primes.push_back(i);
    }
}
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
//    freopen("input.txt","r",stdin);
    getprimelist();
    while(cin>>n>>m)
    {
        Map.clear();

        for(int i=0;i<n;i++)scanf("%d",&a[i]);
        for(int i=0;i<m;i++)scanf("%d",&b[i]);

        for(int i=0;i<m;i++)Map[b[i]]=true;
        for(int i=n-1;i>=0;i--)
        {
            int x=0;
            for(int j=0;j<=i;j++)
                x=gcd(x,a[j]);

            int Gcd=x;
            int tot=0;
            for(int j=0;j<primes.size()&&primes[j]*primes[j]<=x;j++)
            {
                if(x%primes[j])continue;
                bool flag=Map[primes[j]];
                while(x%primes[j]==0)
                {
                    x/=primes[j];
                    if(flag)tot--;
                    else tot++;
                }
            }
            if(x>1)
            {
                if(Map[x])tot--;
                else tot++;
            }
            if(tot<0)
                for(int j=0;j<=i;j++)a[j]/=Gcd;
        }
        int ans=0;
        for(int i=0;i<n;i++)
        {
            int x=a[i];
            for(int j=0;j<primes.size()&&primes[j]*primes[j]<=x;j++)
            {
                if(x%primes[j])continue;
                bool flag=Map[primes[j]];
                while(x%primes[j]==0)
                {
                    x/=primes[j];
                    if(flag)ans--;
                    else ans++;
                }

            }
            if(x>1)
            {
                if(Map[x])ans--;
                else ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
