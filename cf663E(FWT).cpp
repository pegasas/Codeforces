/*
【题意】
给出一个n(n≤20)行m(m≤105)列的01矩阵。每次操作可以将某一行取反或者将某一列取反。要求操作后的矩阵中的1的个数最少，求最小个数。
【解题思路】
由于行比较少，我们考虑状压。状压每一列的状态，sta第i位为1，代表第i行为1，否则为0。现在我们有一个F(sta) 代表状态为sta的时候的列的数量。
考虑一下我们操作了哪些行？对于一个状态mask，第i位为一代表我们翻转了第i行，否则代表没翻转。
考虑一个mask对sta的影响，显然是sta ^ mask。不妨设为res。
然后对于一个res,我们不妨预处理一个G(res)代表res这样的一列翻转之后和翻转之前1的个数的最小值。
但是m有10^5直接做是不可能的，我们考虑如何优化？
构造一个函数H(mask)，表示操作为mask的时候1的个数。不难想到
H(mask)=∑F(sta)×G(sta⊕mask),sta=(0,2n−1)
我们改写一下这个等式：
H(mask)=∑∑[sta⊕mask=res]F(sta)×G(res),sta,res=(0,2n−1)
这样难道不就是做一个异或卷积和就行了吗？所以我们用FWT优化即可。
*/
#pragma comment(linker,"/STACK:102400000,102400000")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <cstdio>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <complex>
#include <sstream> //isstringstream
#include <iostream>
#include <algorithm>
using namespace std;
//using namespace __gnu_pbds;
typedef long long LL;
typedef pair<int, LL> pp;
#define REP1(i, a, b) for(int i = a; i < b; i++)
#define REP2(i, a, b) for(int i = a; i <= b; i++)
#define REP3(i, a, b) for(int i = a; i >= b; i--)
#define CLR(a, b)     memset(a, b, sizeof(a))
#define MP(x, y)      make_pair(x,y)
template <class T1, class T2>inline void getmax(T1 &a, T2 b) { if (b>a)a = b; }
template <class T1, class T2>inline void getmin(T1 &a, T2 b) { if (b<a)a = b; }
const int maxn = 20;
const int maxm = 1e5+5;
const int maxs = 10;
const int maxp = 1e3 + 10;
const int INF  = 1e9;
const int UNF  = -1e9;
const int mod  = 1e9 + 7;
const int rev = (mod + 1) >> 1; // FWT
const double PI = acos(-1);
//head

int A[maxm], n , m;
char s[maxm];
int F[1<<maxn], G[1<<maxn];

void FWT(int a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+mod)%mod;
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
}

void UFWT(int a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*rev%mod,a[i+j+d]=(1LL*(x-y)*rev%mod+mod)%mod;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
                //or:a[i+j+d]=y-x;
            }
}

void solve(int a[],int b[],int n)
{
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%mod;
    UFWT(a,n);
}


int main()
{
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        scanf("%s", s);
        for(int j = 0; j < m; j++){
            A[j] = A[j] << 1 | (s[j] - '0');
        }
    }
    for(int i = 0; i < m; i++) F[A[i]] += 1;
    for(int i = 0; i < (1<<n); i++){
        int t = __builtin_popcount(i);
        G[i] = min(t, n - t);
    }
    solve(F, G, 1<<n);
    int ans = n * m;
    for(int i = 0; i < 1 << n; i++){
        ans = min(ans , (int) F[i]);
    }
    cout << ans << endl;
}
