/*
���⣺
����n������
����[l, r]��n��������Ҫռ�õ�ʱ�䡣
m����
������m���˵Ŀ���ʱ���Լ�������������������������һ����ͬһʱ��ֻ����һ������,�����ǵ��̵߳ģ�
[l, r] num
�ʣ�
�������ܱ�ȫ����������NO
�������YES
���ÿ��������˭��ɵġ�
˼·��
���˺������һ���Ҷ˵�����
����������������������˵�ŵ�set�
���������ˣ����set��>=�˵���˵�� num����ɾ����
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
