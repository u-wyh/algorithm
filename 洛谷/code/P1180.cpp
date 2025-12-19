#include<bits/stdc++.h>
using namespace std;

double dis,maxn,s1,money,ans;
int n;
double s[55],d[55];

void dfs(int now,double oil,double paid){
    if(paid>ans)
        return ;
    if(now==n+1){
        ans=min(ans,paid);
        return ;
    }
    if(oil*s1>=s[now+1]-s[now]){
        if(oil*2>maxn){
            dfs(now+1,oil-(s[now+1]-s[now])/s1,paid);
        }else{
            dfs(now+1,maxn-(s[now+1]-s[now])/s1,paid+(maxn-oil)*d[now]+20);
            dfs(now+1,oil-(s[now+1]-s[now])/s1,paid);
        }
    }else{
        dfs(now+1,maxn-(s[now+1]-s[now])/s1,paid+(maxn-oil)*d[now]+20);
    }
}

int main()
{
    cin>>dis>>maxn>>s1>>money;
    ans=money;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s[i]>>d[i];
        ans+=20+maxn*d[i];
    }
    s[n+1]=dis;
    dfs(1,maxn-s[1]/s1,money);
    printf("%.1lf\n",ans);
    return 0;
}
