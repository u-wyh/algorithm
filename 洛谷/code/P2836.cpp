#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;

double len,l,s,sum;
int n;
double x[MAXN],y[MAXN];
double ans=2e18;

void dfs(int to,double oil,double sum){
    //到达哪个城市 还有多少油  到现在花了多少钱
    if(sum>ans){
        return ;
    }
    if(to==n+1){
        ans=min(ans,sum);
        return ;
    }
    if(s*oil>(x[to+1]-x[to])){
        //表示油足够
        if(oil>l/2){
            dfs(to+1,oil-(x[to+1]-x[to])/s,sum);
        }
        else{
            dfs(to+1,oil-(x[to+1]-x[to])/s,sum);
            dfs(to+1,l-(x[to+1]-x[to])/s,sum+2+(l-oil)*y[to]);
        }
    }
    else{
        dfs(to+1,l-(x[to+1]-x[to])/s,sum+2+(l-oil)*y[to]);
    }
}

int main()
{
    cin>>len>>l>>s>>sum>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        y[i]/=100;
    }
    x[n+1]=len;
    dfs(1,l-x[1]/s,sum);
    cout<<fixed<<setprecision(2)<<ans<<endl;
    return 0;
}
