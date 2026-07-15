#include<bits/stdc++.h>
using namespace std;

int t,n,x,y,opt,fa[200010],a[100005],b[100005];

void build(int n){
    for(int i=0;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    fa[find(x)] = find(y);
}

int main()
{
    cin>>t;
    while(t--){
        cin>>n;
        build(2*n);
        for(int i=1;i<=n;i++){
            cin>>x>>y>>opt;
            if(opt==1){
                un(x,y);
            }else{
                int fx=fa[x];
                int fy=fa[y];
                if(fx==fy){
                    cout<<"NO"<<endl;
                    goto next;
                }else{
                    un(x+n,y);
                    un(y+n,x);
                }
            }
        }
        cout<<"YES"<<endl;
        next:
            continue;
    }
    return 0;
}
