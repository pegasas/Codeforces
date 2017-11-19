/*
题意：
在一次选举中，
n个候选人，
每个候选人要投第a[i]号人当选，需要花费b[i]的钱让他改投你，
（你是第0号人，对于要选你的人，a[i]=b[i]=0）
求最少需要花多少让你赢得选举
思路：
枚举当前不投自己的为至少为i(1<=i<=n)个，
然后每次从i-1到i,
这里有个技巧，每次都从排序了的队列里面push出最大的，
然后加回最小的使其满足投自己的人数cnt>i的
然后统计答案即可
*/
#include<bits/stdc++.h>
using namespace std;
const int maxa=100005;
int n;
vector<int> a[maxa],p,q;
priority_queue<int> pq;
int main()
{
//    freopen("input.txt","r",stdin);
    while(cin>>n)
    {
        for(int i=1;i<=100000;i++)a[i].clear();
        p.clear();
        q.clear();
        int ans=0;
        while(!pq.empty())pq.pop();

        for(int i=1;i<=n;i++)
        {
            int x,b;
            scanf("%d%d",&x,&b);
            if(x)a[x].push_back(b);
            ans+=b;
        }
        for(int i=1;i<=100000;i++)
            if(a[i].size())
            {
                sort(a[i].begin(),a[i].end());
                p.push_back(i);
            }
        int cnt=n,sum=ans;
        for(int i=1;i<=n;i++)
        {
            q.clear();
            if(p.size()==0)break;
            for(int j=0;j<p.size();j++)
            {
                sum-=a[p[j]].back();
                pq.push(-a[p[j]].back());
                --cnt;
                a[p[j]].pop_back();
                if(a[p[j]].size())q.push_back(p[j]);
            }
            while(cnt<=i&&pq.size())
            {
                sum+=-pq.top();
                ++cnt;
                pq.pop();
            }
            if(cnt>i)ans=min(ans,sum);
            p.clear();
            for(int j=0;j<q.size();j++)p.push_back(q[j]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
