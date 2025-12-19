#include<bits/stdc++.h>
using namespace std;
#define MAXN 200010

int n,m,x,y,mid;
int l[MAXN],r[MAXN];
int w[MAXN],v[MAXN];
long long sw[MAXN],sv[MAXN];
long long W,S,sum;

int main()
{
    cin>>n>>m>>S;
    W=S;//与标准的差值
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];
        y=max(y,w[i]);//初始化最高标准  即产品最大是多少
    }
    x=1,y+=1;//x,y是质量判断标准的变化范围
    //y+=1是考虑如果S=0的话那么就是所有的都不选是最好的   即所有的产品都不合格
    for(int i=1;i<=m;i++)
        cin>>l[i]>>r[i];
    while(x<y){
        memset(sw,0,sizeof(sw));
        memset(sv,0,sizeof(sv));
        mid=(x+y)>>1;
        sum=0;//sum表示在现行标准下指标是多少
        for(int i=1;i<=n;i++){
            if(w[i]>=mid){
                sw[i]=sw[i-1]+1;
                sv[i]=sv[i-1]+v[i];
            }else{
                sw[i]=sw[i-1];
                sv[i]=sv[i-1];
            }
        }
        for(int i=1;i<=m;i++){
            sum+=(sw[r[i]]-sw[l[i]-1])*(sv[r[i]]-sv[l[i]-1]);
        }
        if(sum==S){
            W=0;
            break;
        }
        W=min(W,abs(sum-S));
        if(sum<=S){
            y=mid;
        }else{
            x=mid+1;
        }
    }
    cout<<W;
    return 0;
}
