/*
���⣺
��һ��ѡ���У�
n����ѡ�ˣ�
ÿ����ѡ��ҪͶ��a[i]���˵�ѡ����Ҫ����b[i]��Ǯ������Ͷ�㣬
�����ǵ�0���ˣ�����Ҫѡ����ˣ�a[i]=b[i]=0��
��������Ҫ����������Ӯ��ѡ��
˼·��
ö�ٵ�ǰ��Ͷ�Լ���Ϊ����Ϊi(1<=i<=n)����
Ȼ��ÿ�δ�i-1��i,
�����и����ɣ�ÿ�ζ��������˵Ķ�������push�����ģ�
Ȼ��ӻ���С��ʹ������Ͷ�Լ�������cnt>i��
Ȼ��ͳ�ƴ𰸼���
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
