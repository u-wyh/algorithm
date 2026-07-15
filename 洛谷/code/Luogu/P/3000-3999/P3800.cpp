#include<bits/stdc++.h>
using namespace  std;

int n,m,k,t;
int nums[4005][4005];

inline int read(){
	int fl=1,w=0;char ch=getchar();
	while(!isdigit(ch) && ch!='-') ch=getchar();
	if(ch=='-') fl=-1;
	while(isdigit(ch)){w=w*10+ch-'0',ch=getchar();}
	return fl*w;
}

int main()
{
    n=read(),m=read(),k=read(),t=read();
    int x,y,m;
    for(int i=1;i<=k;i++){
        cin>>x>>y>>m;
        nums[x][y]=m;
    }

    return 0;
}
