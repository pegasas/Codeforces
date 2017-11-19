
#include <bits/stdc++.h>
template <class T>
inline bool rd(T &ret) {
    char c; int sgn;
    if(c=getchar(),c==EOF) return 0;
    while(c!='-'&&(c<'0'||c>'9')) c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
    ret*=sgn;
    return 1;
}
template <class T>
inline void pt(T x) {
    if (x <0) {
        putchar('-');
        x = -x;
    }
    if(x>9) pt(x/10);
    putchar(x%10+'0');
}
using namespace std;
typedef long long ll;
#define int ll
const int N = 200050;
int n, m;
struct node{
    int op, l, r, num, id;
}a[N*2];
bool cmp(node x, node y){
    if(x.r != y.r)
        return x.r<y.r;
    if(x.op!=y.op)
        return x.op<y.op;
}
int top, b[N];
void input(){
    top = 0;
    for(int i = 1; i <= n; i++){
        rd(a[top].l); rd(a[top].r);
        a[top].op = 0;
        a[top].id = i;
        top++;
    }
    rd(m);
    for(int i = 1; i <= m; i++){
        rd(a[top].l); rd(a[top].r); rd(a[top].num);
        a[top].op = 1;
        a[top].id = i;
        top++;
    }
    sort(a, a+top, cmp);
}
struct Edge{
    int id, l;
    bool operator<(const Edge&e)const{
        if(e.l!=l)return e.l>l;
        return e.id>id;
    }
    Edge(int a=0,int b=0):id(a),l(b){}
}tmp;
set<Edge>s;
set<Edge>::iterator p;
#undef int
int main(){
#define int ll
    while(cin>>n){
        input();
        int ans = 0;
        s.clear();
        for(int i = 0; i < top; i++){
            if(a[i].op){
                while(s.size() && a[i].num--)
                {
                    p = s.lower_bound(Edge(0, a[i].l));
                    if(p == s.end())break;
                    tmp = *p;
                    b[tmp.id] = a[i].id;
                    s.erase(p);
                    ans++;
                }
            }
            else {
                s.insert(Edge(a[i].id, a[i].l));
            }
        }
        if(ans == n)
        {
            puts("YES");
            for(int i = 1; i <= n; i++){pt(b[i]); putchar(' ');}
        }
        else puts("NO");
    }
    return 0;
}
