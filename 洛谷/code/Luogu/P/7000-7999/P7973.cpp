#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int a[MAXN],b[MAXN];
int fa[MAXN],val[MAXN];
int n;
vector<int>zero;
vector<int>one;

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    //cout<<x<<' '<<y<<endl;
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        val[fy]+=val[fx];
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        fa[i]=i,val[i]=b[i];
    }
    for(int i=0;i<=29;i++){
        //cout<<i<<' '<<(1<<i)<<endl;
        for(int j=1;j<=n;j++){
            if((a[j]&(1<<i))&&(a[j]<(1<<(i+1)))){
                one.push_back(j);
            }
            if((a[j]>=(1<<(i+1)))&&((a[j]&(1<<i))==0)){
                zero.push_back(j);
            }
        }
        //cout<<i<<' '<<one.size()<<' '<<zero.size()<<endl;
        if(one.size()>0&&zero.size()>0){
            for(int j=0;j<one.size()-1;j++){
                un(one[j],one[j+1]);
            }
            for(int j=0;j<zero.size()-1;j++){
                un(zero[j],zero[j+1]);
            }
            un(one[0],zero[0]);
        }
        one.clear();
        zero.clear();
    }
    for(int i=1;i<=n;i++){
        int f=find(i);
        cout<<val[f]<<endl;
    }
    return 0;
}
