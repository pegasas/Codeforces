/*
题目：
给n个高度，然后q个询问区间[l,r]里面是否存在一段非递减的连续长度大于w
1<=n,q<=1e5
题解：
首先先对高度从高到底排序，然后处理，每一次插入一个新的链到可持久化线段树里，
然后调用历史记录二分高度，看它是哪个高度里正好>=w的最高的高度
输出哪个高度即可
复杂度nlgn^2
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,q;
int sz;
struct panel
{
    int h,id;
}p[maxn];
inline bool cmp(const panel &a,const panel &b)
{
    return a.h>b.h;
}
const int maxnlgn=1000005;
int root[maxn];
struct Node
{
    int lc,rc,lp,rp,L,R,S;
    Node(int lc=0,int rc=0,int lp=0,int rp=0,int L=0,int R=0,int S=0):lc(lc),rc(rc),lp(lp),rp(rp),L(L),R(R),S(S){}
    int length()
    {
        return rp-lp+1;
    }
}nd[maxnlgn<<2];
inline int newNode()
{
    ++sz;
    return sz;
}
inline void pushup(int u) {
    int lcid = nd[u].lc, rcid = nd[u].rc;
    nd[u].L = nd[lcid].L + (nd[lcid].L == nd[lcid].length() ? nd[rcid].L : 0);
    nd[u].R = nd[rcid].R + (nd[rcid].R == nd[rcid].length() ? nd[lcid].R : 0);
    nd[u].S = max(nd[lcid].R + nd[rcid].L, max(nd[lcid].S, nd[rcid].S));
}
void build(int &u,int l,int r)
{
    if(u==0)u=newNode();
    nd[u]=Node(0,0,l,r,0,0,0);
    if(l==r)return;
    int mid=(l+r)>>1;
    build(nd[u].lc,l,mid);
    build(nd[u].rc,mid+1,r);
    pushup(u);
}
int Insert(int u,int x)
{
    int k=newNode();
    nd[k]=nd[u];
    if(nd[k].lp==x&&x==nd[k].rp)
    {
        nd[k].S=nd[k].L=nd[k].R=1;
        return k;
    }
    int mid=(nd[k].lp+nd[k].rp)>>1;
    if(x<=mid)nd[k].lc=Insert(nd[k].lc,x);
    else nd[k].rc=Insert(nd[k].rc,x);
    pushup(k);
    return k;
}
inline Node Merge(Node a,Node b)
{
    Node u;
    u.lp=a.lp;u.rp=b.rp;
    u.L=a.L+(a.L==a.length()?b.L:0);
    u.R=b.R+(b.R==b.length()?a.R:0);
    u.S=max(a.R+b.L,max(a.S,b.S));
    return u;
}
Node query(int u,int l,int r)
{
    if(l<=nd[u].lp&&nd[u].rp<=r)return nd[u];
    int mid=(nd[u].lp+nd[u].rp)>>1;
    if(r<=mid)return query(nd[u].lc,l,r);
    else if(l>mid)return query(nd[u].rc,l,r);
    else
    {
        Node ll=query(nd[u].lc,l,r);
        Node rr=query(nd[u].rc,l,r);
        return Merge(ll,rr);
    }
}
int main()
{
//    freopen("input.txt","r",stdin);
    while(scanf("%d",&n)==1)
    {
        sz=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&p[i].h);
            p[i].id=i;
        }
        sort(p+1,p+1+n,cmp);
        build(root[0],1,n);
        for(int i=1;i<=n;i++)root[i]=Insert(root[i-1],p[i].id);
        scanf("%d",&q);
        while(q--)
        {
            int l,r,w;
            scanf("%d%d%d",&l,&r,&w);
            int L=1,R=n;
            while(L<R)
            {
                int M=L+(R-L)/2;
                if(query(root[M],l,r).S>=w)
                    R=M;
                else
                    L=M+1;
            }
            printf("%d\n",p[L].h);
        }
    }
    return 0;
}
