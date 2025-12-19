#include<stdio.h>
#include<string.h>

int vis[200005];
int n,m;

int main()
{
    scanf("%d %d",&n,&m);
    int l,r;
    int ans=n;
    for(int i=1;i<=m;i++){
        scanf("%d %d",&l,&r);
        int k=r-l+1;
        for(int i=l;i<=r;i++){
            if(vis[i]==1){
                k--;
            }
            vis[i]=1;
        }
        ans-=k;
        printf("%d\n",ans);
    }
    return 0;
}
