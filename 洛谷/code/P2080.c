#include<stdio.h>
#include<math.h>

int n,m;
int a[35],b[35],ans=10000000;

int min(int a,int b){
    return a<b?a:b;
}

void dfs(int x,int A,int B){
    if(x>n){
        if((A+B)>=m)
            ans=min(ans,abs(A-B));
        return ;
    }
    dfs(x+1,A,B);
    dfs(x+1,A+a[x],B+b[x]);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    dfs(1,0,0);
    if(ans==10000000)
        printf("-1\n");
    else
        printf("%d\n",ans);
    return 0;
}
