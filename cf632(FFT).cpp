/*
���⣺n����Ʒÿ����Ʒ�����޸���ÿ����Ʒ��һ���۸�������ѡȡk�������Կ����ܼۡ�
˼·��FFT�����ֻѡ��������Ʒ�Ļ����������뵽FFT������������k��ֻҪ���ƿ��������󼴿ɣ�������ʱ�临�Ӷ�ΪO(W*logW*logK)��
��ʵ�����Խ�һ���Ż���ÿһ��fft�ĳ���ֻ��Ҫ����Ϊ��ǰ�Ŀ������ֵ�����ˣ�Ҳ����˵fft��lengthҲ�Ǳ����ģ����Ը��ӶȽ�Ϊ��O(W*min(log1000,logK))��
Ҫע�������Ϊ�����˿��ܱ����ȣ�����ÿһ����ĳһ��ֵ����1���Ͱ���һλ��������Ϊ1����������ȷ�����ᱬ��
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
//�����ṹ��
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
 * ����FFT��IFFTǰ�ķ�ת�任��
 * λ��i�� ��i�����Ʒ�ת��λ�ã�����
 * len����ȡ2����
 */
void change(complex y[],int len)
{
    int i,j,k;
    for(i=1,j=len/2;i<len-1;i++)
    {
        if(i<j)swap(y[i],y[j]);
        //������ΪС�귴ת��Ԫ�أ�i<j��֤����һ��
        //i��������+1��j��ת���͵�+1,ʼ�ձ���i��j�Ƿ�ת��
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
 * ��FFT
 * len����Ϊ2^k��ʽ��
 * on==1ʱ��DFT��on==-1ʱ��IDFT
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
