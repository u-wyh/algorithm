#include<bits/stdc++.h>
using namespace std;
#define int long long
long long dx[3]={0, 1, 0}, dy[3]={0, 0, 1};
long long n, m, t;
long long cnt, tot;
long long ans;
struct node{
    long long x, y, dis;
}a[260005];
long long f[505][505];
long long father[260005],size[260005];
long long num[505][505],v[260005];
long long find(long long x)
{
  if(x!=father[x])
    father[x]=find(father[x]);
  return father[x];
}
bool cmp(node x,node y)
{
  return x.dis<y.dis;
}
signed main()
{
    for(int i=1;i<=260004;i++)
      size[i]=1,father[i]=i;
    scanf("%lld%lld%lld",&n,&m,&t);
    tot=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            scanf("%lld",&f[i][j]);
            tot+=1;
            num[i][j]=tot;
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            int flag;
            scanf("%d",&flag);
            if(flag) v[num[i][j]]=1;
            for (int k=1;k<=2;k++)
            {
                int tx=i+dx[k],ty=j+dy[k];
                if (tx<n+1&&ty<m+1) a[++cnt]=(node){num[i][j],num[tx][ty],abs(f[i][j]-f[tx][ty])};
            }
        }
    }//建图
    sort(a+1,a+1+cnt,cmp);//排序
    for(int i=1;i<=cnt;i++)//不断加边
    {
        int x=a[i].x,y=a[i].y;
        int fx=find(x), fy=find(y);
        if(fx==fy)continue;
        if (size[fx]+size[fy]>=t)
        {
            if (size[fx]<t)ans+=a[i].dis*v[fx];
            if (size[fy]<t)ans+=a[i].dis*v[fy];
        }
        if (size[fx]>size[fy]) swap(fx,fy);
        father[fx]=fy;
        size[fy]+=size[fx],v[fy]+=v[fx];
    }
    printf("%lld",ans);//输出答案
    return 0;
}
