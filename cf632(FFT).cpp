/*
题意：n种物品每种物品有无限个，每个物品有一个价格，现在问选取k个的所以可能总价。
思路：FFT。如果只选择两件商品的话，很容易想到FFT，对于其他的k，只要类似快速幂来求即可，这样做时间复杂度为O(W*logW*logK)。
其实还可以进一步优化，每一步fft的长度只需要设置为当前的可能最大值就行了，也就是说fft的length也是倍增的，所以复杂度降为了O(W*min(log1000,logK))。
要注意的是因为都变了可能爆精度，所以每一步当某一个值大于1，就把这一位重新设置为1，这样可以确保不会爆。
*/
#include<bits/stdc++.h>
#define eps 1e-6
#define LL long long
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
//#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;

const int MAXN = 2010;
//const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
int n, k, a[MAXN], len;
//复数结构体
struct complex
{
    double r,i;
    complex(double r = 0.0,double i = 0.0)
    {
        this.r=r;this.i=i;
    }
    complex operator + (const complex &b)
    {
        return complex(r+b.r,i+b.i);
    }
    complex operator - (const complex &b)
    {
        return complex(r-b.r,i-b.i);
    }
    complex operator * (const complex &b)
    {
        return complex(r*b.r-i*b.i,r*b.i+i*b.r);
    }
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须取2的幂
 */
void change(complex y[],int len)
{
    int i,j,k;
    for(i=1,j=len/2;i<len-1;i++)
    {
        if(i<j)swap(y[i],y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k=len/2;
        while(j>=k)
        {
            j-=k;
            k/=2;
        }
        if(j<k)j+=k;
    }
}
/*
 * 做FFT
 * len必须为2^k形式，
 * on==1时是DFT，on==-1时是IDFT
 */
void fft(complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0;j < len;j+=h)
        {
            complex w(1,0);
            for(int k = j;k < j+h/2;k++)
            {
                complex u = y[k];
                complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}

complex x1[MAXN*MAXN], x2[MAXN*MAXN], x3[MAXN*MAXN];

void solve(int m) {
	if (m == 1)
		return;
	solve(m/2);
	while (len <= 1000*m)
		len <<= 1;
	fft(x1, len, 1);
	fft(x2, len, 1);
	for (int i = 0; i < len; i++) {
        x1[i] = x1[i] * x2[i];
	}
	fft(x1, len, -1);
	for (int i = 0; i < len; i++)
		if (x1[i].r > 0.5) x1[i] = x2[i] = complex(1, 0);
		else  x1[i] = x2[i] = complex(0, 0);

	if (m&1) {
		fft(x1, len, 1);
		fft(x3, len, 1);
		for (int i = 0; i < len; i++) {
			x1[i] = x1[i] * x3[i];
		}
		fft(x1, len, -1);
		fft(x3, len, -1);
		for (int i = 0; i < len; i++)
			if (x1[i].r > 0.5)
				x1[i] = x2[i] = complex(1, 0);
			else
				x1[i] = x2[i] = complex(0, 0);
		for (int i = 0; i < len; i++)
			if (x3[i].r > 0.5)
				x3[i] = complex(1, 0);
			else
				x3[i] = complex(0, 0);
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &k);
	len = 1024;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		x1[a[i]] = x2[a[i]] = x3[a[i]] = complex(1, 0);
	}
	solve(k);
	for (int i = 0; i <= 1000*k; i++) {
		if (x1[i].r >= 0.5)
			printf("%d ", i);
	}
	return 0;
}
