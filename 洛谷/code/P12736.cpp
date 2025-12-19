#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXH = 22;

int n,m;
int fa[MAXN][MAXH];
int one[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int find(int i,int j){
    return fa[i][j]==i?i:fa[i][j]=find(fa[i][j],j);
}

void un(int x,int y,int k){
    int fx=find(x,k);
    int fy=find(y,k);
    if(fx!=fy){
        fa[fx][k]=fy;
    }
}

int main()
{
    n=read(),m=read();

    one[0]=-1;
    for(int i=1;i<=n;i++){
        one[i]=one[i>>1]+1;
    }

    for(int i=1;i<=n;i++){
        for(int j=0;j<=one[n];j++){
            fa[i][j]=i;
        }
    }

    for(int i=1;i<=m;i++){
        int l1=read();
        int l2=read();
        int len=read();
        int k=one[len];
        un(l1,l2,k);
        un(l1+len-(1<<k),l2+len-(1<<k),k);
    }

    for(int k=one[n];k>=1;k--){
        for(int i=1;i+(1<<k)-1<=n;i++){
            int fa=find(i,k);
            if(fa==i){
                continue;
            }
            un(i,fa,k-1);
            un(i+(1<<(k-1)),fa+(1<<(k-1)),k-1);
        }
    }

    int ans=0;
    for(int i=1;i<=n;i++){
        if(find(i,0)==i){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}