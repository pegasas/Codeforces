#include <cstdio>
int a[81];
bool used[81];
int e[81];
int main()
{
    int n,k,cnt,maxx,maxi,ans=0;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(used[a[i]])
            continue;
        if(cnt<k)
        {
            cnt++;
            used[a[i]]=true;
            ans++;
        }
        else
        {
            for(int j=1;j<=n;j++)
                e[j]=0;
            for(int j=1;j<=n;j++)
                if(used[j])
                    e[j]=100;
            for(int j=1;j<=n;j++)
                if(used[j])
                {
                    for(int k=i+1;k<=n;k++)
                        if(a[k]==j)
                        {
                            e[j]=k;
                            break;
                        }
                }
            maxx=0;
            maxi=-1;
            for(int j=1;j<=n;j++)
                if(e[j]>maxx)
                {
                    maxx=e[j];
                    maxi=j;
                }
            used[maxi]=false;
            used[a[i]]=true;
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
