#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 500050

ll f[N][22],a[N];
int n,Q,nxt[N][22];
ll ans;
int st[N],top;
int buf[111],p;

inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}

inline void Output(ll x){
	p=0;
	while(x)buf[++p]=x%10,x/=10;
	while(p)putchar(buf[p--]+'0');
	putchar('\n');
}

int main()
{
	n=read(),Q=read();
	int MX=log2(n)+1;
	for(int i=1;i<=n;i++){
		a[i]=read();
	}

	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i]){
			nxt[st[top]][0]=i;
			--top;
		}
		st[++top]=i;
	}

	while(top)nxt[st[top--]][0]=n+2;
	nxt[n+1][0]=nxt[n+2][0]=n+2;
	for(register int i=1;i<=n;++i){
		f[i][0]=1LL*a[i]*(nxt[i][0]-i);
	}
	for(register int j=1;j<=MX;++j){
		for(register int i=1;i<=n+2;++i){
			nxt[i][j]=n+2;
		}
		for(register int i=1;i+(1<<j)-1<=n;++i){
			nxt[i][j]=nxt[nxt[i][j-1]][j-1];
			f[i][j]=f[i][j-1]+f[nxt[i][j-1]][j-1];
		}
	}
	while(Q--){
		int u=read(),v=read();
		int l=1+(u^ans)%n,r=(v^(ans+1))%(n-l+1)+l;
		int pos=l;
		ans=0;
		for(register int i=MX;i>=0;--i){
			if(nxt[pos][i]-1>r)continue;
			ans+=f[pos][i];
			pos=nxt[pos][i];
		}
		ans+=a[pos]*(r-pos+1);
		Output(ans);
	}
	return 0;
}
