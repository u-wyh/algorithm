#include<bits/stdc++.h>
using namespace std;
const int LIMIT = 17;
const int MAXN = 140000;

int n,m;
int arr[MAXN];
int st[MAXN][LIMIT];
int log_2[MAXN];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

inline void build(int n){
    log_2[0]=-1;
    for(int i=1;i<=n;i++){
        log_2[i]=log_2[i>>1]+1;
        st[i][0]=arr[i];
    }
    for(int p=1;p<=log_2[n];p++){
        for(int i=1;i<=n;i++){
            st[i][p]=max(st[i][p-1],st[(i+(1<<(p-1)))>n?n:(i+(1<<(p-1)))][p-1]);
        }
    }
}

inline int query(int a,int b){
    int p=log_2[b-a+1];
    return max(st[a][p],st[b-(1<<p)+1][p]);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    build(n);
    for(int i=1,a,b;i<=m;i++){
        a=read(),b=read();
        cout<<query(a,b)<<endl;
    }

    return 0;
}
