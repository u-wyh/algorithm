#include<bits/stdc++.h>
using namespace std;
const int N=1000010;

inline int read(){
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch >'9'){
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

int X[N],Y[N],n,m,mx1,mx2;
int main()
{
	n=read();
	while(n--){
		int a=N,b=0,c=N,d=0;
		for(int i=1;i<=3;i++){
			int x=read(),y=read();
			a=min(a,x),b=max(b,x),c=min(c,y),d=max(d,y);
			mx1=max(mx1,x),mx2=max(mx2,y);
		}
		X[a+1]++,X[b]--,Y[c+1]++,Y[d]--;
	}
	for(int i=0;i<=mx1+1;i++)X[i]+=X[i-1];
	for(int i=0;i<=mx2+1;i++)Y[i]+=Y[i-1];
	m=read();
	while(m--){
		char s;
		cin>>s;
		int x=read();
		if(s=='x')printf("%d\n",X[x]);
		if(s=='y')printf("%d\n",Y[x]);
	}
	return 0;
}
