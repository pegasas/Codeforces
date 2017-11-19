/*
题意：
在一次选举中，
n个候选人，
每个候选人要投第a[i]号人当选，需要花费b[i]的钱让他改投你，
（你是第0号人，对于要选你的人，a[i]=b[i]=0）
求最少需要花多少让你赢得选举
思路：

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
using namespace std;

#define LL long long
#define ULL unsigned long long
#define mod 1000000007
#define eps 1e-8
#define MP make_pair
#define REP(i,a,b) for (int i = a; i <= b; ++i)

vector<int> a[100005], p, q;
priority_queue<int> k;

int main()
{
    int n, x, b, ans = 0;
    cin >> n;
    REP(i,1,n) {
        scanf( "%d%d", &x, &b );
        if (x) a[x].push_back(b);
        ans += b;
    }
    REP(i,1,100000) if (a[i].size()) {
        sort(a[i].begin(), a[i].end());
        p.push_back(i);
    }
    int cnt = n, sum = ans;
    REP(i,1,n) {
        q.clear();
        if (p.size() == 0) break;
        for (int j = 0; j < p.size(); ++j) {
            sum -= a[p[j]].back(); --cnt;
            k.push(-a[p[j]].back());
            a[p[j]].pop_back();
            if (a[p[j]].size()) q.push_back(p[j]);
        }
        while (cnt <= i && k.size()) {
            sum += -k.top();
            ++cnt;
            k.pop();
        }
        if (cnt > i) ans = min(ans, sum);
        p.clear();
        for (int j = 0; j < q.size(); ++j) p.push_back(q[j]);
    }
    cout << ans << endl;
    return 0;
}
