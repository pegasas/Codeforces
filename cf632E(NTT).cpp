/*
��Ŀ���˵����n�ּ�ֵ��һ����Ʒ��ÿ�����������޶࣬��ȡ��k����Ʒ��ȡ������Ʒ��ֵ�͵����������
��ĸ�����⣬��ֵΪָ��������Ϊϵ�����������ʽ��k���ݼ��ɡ�
����Ȼ�뵽FFT+������������ʱ�临�ӶȲŹ���
FFTֱ����Ļ������ϵ����󵽴�10001000̫��ը�ˣ�
��ȻҲ������һ�ξ�����0ָ�����¸�ֵ��1��
���������ſ�ͷһ��DFT��βһ��IDFT�������졢�����ɵ㣬������NTT�ˡ���
��NTTģ��ȡ1004535809 WA��20��ȡ998244353 WA��21����
��������ϵ��ȡģ���Ϊ0�ˣ����ݵ��ġ��������Ҿ�����ģ����ȡ��
(��ʵ��ΪNTT DFT֮��IDFT����������Ψһ�ģ�����ֻ��ˮ������)
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define MAXN 1048576

//const ll P=50000000001507329LL; // 190734863287 * 2 ^ 18 + 1
ll P=1004535809; // 479 * 2 ^ 21 + 1
//const ll P=998244353; // 119 * 2 ^ 23 + 1
const int G=3;

ll mul(ll x,ll y)
{
	return (x*y-(ll)(x/(long double)P*y+1e-3)*P+P)%P;
}
ll qpow(ll x,ll k,ll p)
{
	ll ret=1;
	while(k)
    {
		if(k&1)ret=mul(ret,x);
		k>>=1;
		x=mul(x,x);
	}
	return ret;
}

ll wn[25];
void getwn()
{
	for(int i=1;i<=21;i++)
    {
		int t=1<<i;
		wn[i]=qpow(G,(P-1)/t,P);
	}
}
int len;
void NTT(ll y[],int op)
{
	for(int i=1,j=len>>1,k;i<len-1;i++)
    {
		if(i<j)swap(y[i],y[j]);
		k=len>>1;
		while(j>=k)
        {
			j-=k;
			k>>=1;
		}
		if(j<k)j+=k;
	}
	int id=0;
	for(int h=2;h<=len;h<<=1)
	{
		++id;
		for(int i=0;i<len;i+=h)
		{
			ll w=1;
			for(int j=i;j<i+(h>>1);j++)
            {
				ll u=y[j],t=mul(y[j+h/2],w);
				y[j]=u+t;
				if(y[j]>=P)y[j]-=P;
				y[j+h/2]=u-t+P;
				if(y[j+h/2]>=P)y[j+h/2]-=P;
				w=mul(w,wn[id]);
			}
		}
    }
    if(op==-1)
    {
		for(int i=1;i<len/2;i++)swap(y[i],y[len-i]);
		ll inv=qpow(len,P-2,P);
		for(int i=0;i<len;i++)y[i]=mul(y[i],inv);
    }
}


ll A[MAXN],B[MAXN],C[MAXN];
ll cnt[MAXN];
int n,k;
int main()
{
//    freopen("input.txt","r",stdin);
	while(scanf("%d%d",&n,&k)==2)
	{
        int Max=0;
        for(int i=0;i<n;i++)
        {
            int a;
            scanf("%d",&a);
            ++cnt[a];
            Max=max(Max,a);
        }

        for(len=1;len<Max*k;len<<=1);

        getwn();
        P=1004535809;
        memcpy(A,cnt,sizeof(cnt));
        NTT(A,1);
        memcpy(B,A,sizeof(B));
        k--;
        int tmp=k;
        while(k)
        {
            if(k&1)for(int i=0;i<len;i++)B[i]=mul(A[i],B[i]);
            for(int i=0;i<len;i++)A[i]=mul(A[i],A[i]);
            k>>=1;
        }
        NTT(B,-1);

        P=998244353;
        getwn();
        memcpy(A,cnt,sizeof(cnt));
        NTT(A,1);
        memcpy(C,A,sizeof(C));
        k=tmp;
        while(k)
        {
            if(k&1)for(int i=0;i<len;i++)C[i]=mul(A[i],C[i]);
            for(int i=0;i<len;i++)A[i]=mul(A[i],A[i]);
            k>>=1;
        }
        NTT(C,-1);

        for(int i=0;i<len;i++)
            if(B[i]||C[i])printf("%d ",i);
	}
	return 0;
}
