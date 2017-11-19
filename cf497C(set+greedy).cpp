/*
题意：
给定n个任务
下面[l, r]是n个任务需要占用的时间。
m个人
下面是m个人的空闲时间以及这个人至多能做的任务个数（一个人同一时刻只能做一个任务,即人是单线程的）
[l, r] num
问：
若任务不能被全部完成则输出NO
否则输出YES
输出每个任务是谁完成的。
思路：
把人和任务放一起按右端点排序。
若遇到了任务则把任务的左端点放到set里。
若遇到了人，则把set中>=人的左端点的 num个数删掉。
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=200005;
struct node
{
    ll l,r,op,id,num;
    node(ll l=0,ll r=0,ll op=0,ll id=0):l(l),r(r),id(id),op(op){}
};
node p[2*maxn];
bool cmp(node x,node y)
{
    if(x.r!=y.r)return x.r<y.r;
    if(x.op!=y.op)return x.op<y.op;
}
struct Left
{
    ll id,l;
    Left(ll id=0,ll l=0):id(id),l(l){}
    bool operator < (const Left &u) const
    {
        if(l!=u.l)return l<u.l;
        return id<u.id;
    }
};
set<Left> S;
set<Left>::iterator it;
ll n,m;
ll top;
ll Ans[maxn];
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        top=0;
        for(ll i=1;i<=n;i++)
        {
            ll l,r;
            scanf("%I64d%I64d",&l,&r);
            p[top]=node(l,r,0,i);
            top++;
        }
        cin>>m;
        for(ll i=1;i<=m;i++)
        {
            ll l,r,num;
            scanf("%I64d%I64d%I64d",&l,&r,&num);
            p[top]=node(l,r,1,i);
            p[top].num=num;
            top++;
        }
        sort(p,p+top,cmp);
        ll ans=0;
        S.clear();
        for(ll i=0;i<top;i++)
        {
            if(p[i].op)
            {
                while(S.size()&&p[i].num--)
                {
                    it=S.lower_bound(Left(0,p[i].l));
                    if(it==S.end())break;
                    Left x=(*it);
                    Ans[x.id]=p[i].id;
                    S.erase(it);
                    ans++;
                }
            }
            else
                S.insert(Left(p[i].id,p[i].l));
        }
        if(ans==n)
        {
            printf("YES\n");
            for(ll i=1;i<=n;i++)printf("%I64d%c",Ans[i],i==n?'\n':' ');
        }
        else
            printf("NO\n");
    }
    return 0;
}
