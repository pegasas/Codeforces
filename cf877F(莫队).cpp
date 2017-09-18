/*
题意：
有n本书，可能是经济书，可能是数学书
然后每本书有一个问题数，
给q个询问，每个询问询问[li,ri]区间里面满足经济书的问题与数学书的问题之差恰为k的子区间个数是多少？
答案：
莫队，sum[r]-sum[l-1]=k
然后每次增加减少区间的时候查询sum[l-1]+k或者是sum[r]-k的个数有多少个
离散化之后可以预处理，边做边维护
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=100005;
ll n,k;
ll unit;
ll t[maxn],a[maxn],sum[maxn];
ll Size;
ll Hash[maxn];
ll q;
ll id[maxn][3];
ll ans[maxn];
ll cnt[maxn];
struct Query
{
    ll l,r,id;
    Query(ll l=0,ll r=0,ll id=0):l(l),r(r),id(id){}
}que[maxn];
bool cmp(const Query &a,const Query &b)
{
    if(a.l/unit==b.l/unit)
    {
        if(a.r==b.r)return a.l<b.l;
        else return a.r<b.r;
    }
    else return a.l/unit<b.l/unit;
}

inline ll idx(ll x)
{
    ll p=lower_bound(Hash+1,Hash+1+Size,x)-Hash;
    if(Hash[p]!=x)return 0;
    return p;
}
inline ll addl(ll l)
{
    ll x=id[l-1][2];
    ll ret=cnt[x];
    cnt[id[l-1][0]]++;
    return ret;
}
inline ll addr(ll r)
{
    ll x=id[r][1];
    ll ret=cnt[x];
    cnt[id[r][0]]++;
    return ret;
}
inline ll deletel(ll l)
{
    cnt[id[l-1][0]]--;
    ll x=id[l-1][2];
    if(!x)return 0;
    return cnt[x];
}
inline ll deleter(ll r)
{
    cnt[id[r][0]]--;
    ll x=id[r][1];
    if(!x)return 0;
    return cnt[x];
}
void solve()
{
    ll now=0;
    ll l=1,r=0;
    cnt[id[0][0]]++;
    for(ll i=1;i<=q;i++)
    {
        while(l>que[i].l)now+=addl(--l);
        while(r<que[i].r)now+=addr(++r);
        while(l<que[i].l)now-=deletel(l++);
        while(r>que[i].r)now-=deleter(r--);
        ans[que[i].id]=now;
    }
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n>>k)
    {
        Size=0;
        memset(cnt,0,sizeof(cnt));

        unit=sqrt(n+0.5);
        for(ll i=1;i<=n;i++)scanf("%I64d",&t[i]);
        for(ll i=1;i<=n;i++)
        {
            scanf("%I64d",&a[i]);
            if(t[i]==1)a[i]*=1;
            else a[i]*=-1;
            sum[i]=sum[i-1]+a[i];
            Hash[++Size]=sum[i];
        }

        Hash[++Size]=0;
        sort(Hash+1,Hash+1+Size);
        Size=unique(Hash+1,Hash+1+Size)-Hash-1;

        scanf("%I64d",&q);
        for(ll i=1;i<=q;i++)
        {
            ll l,r;
            scanf("%I64d%I64d",&l,&r);
            que[i]=Query(l,r,i);
        }
        sort(que+1,que+1+q,cmp);

        for(ll i=0;i<=n;i++)
        {
            id[i][0]=idx(sum[i]);
            id[i][1]=idx(sum[i]-k);
            id[i][2]=idx(sum[i]+k);
        }
        solve();
        for(ll i=1;i<=q;i++)
            printf("%I64d\n",ans[i]);
    }
    return 0;
}
