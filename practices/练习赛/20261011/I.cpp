#include <cstdlib>
#include <iostream>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int fa[MAXN];
int a[MAXM];
int b[MAXM];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main(int argc, char *argv[]) {
    int id = argc > 1 ? atoi(argv[1]) : 0;

    int n,m;
    cin>>n>>m;
    if(id==0){
        for(int i=1;i<=n;i++){
            fa[i]=i;
        }
        int a,b;
        for(int i=1;i<=m;i++){
            cin>>a>>b;
            un(a,b);
        }
        cout<<m<<endl;
        cout<<a<<b<<endl;

        for(int i=1;i<=3;i++){
            cin>>m;
            for(int i=1;i<=m;i++){
                cin>>a>>b;
                un(a,b);
            }
        }
        
        int ans=0;
        for(int i=1;i<=n;i++){
            if(find(i)==i){
                ans++;
            }
        }
        cout<<ans<<endl;
    }
    else{
        cout<<m<<endl;
        int a,b;
        for(int i=1;i<=m;i++){
            cin>>a>>b;
        }
        cout<<a<<b<<endl;

        int ans;
        cin>>ans;
        cout<<ans<<endl;
    }
    return 0;
}