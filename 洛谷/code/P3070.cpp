#include<bits/stdc++.h>
 using namespace std;
 int fx[4]={-1,1,0,0};
 int fy[4]={0,0,-1,1};
 int n,m,i,j,k,cnt,l,r,lim,ans,maxn;
 int c[20],f[33000][17];
 int num[55][55],d[20][20];
 int x[5005],y[5005],dis[5005];
 bool used[55][55];
 char s[55][55];
 inline int read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}
 void land_f()//预处理第一步
{
	int a,b,xx,yy,i;
	while(l<=r)
	{
		a=x[l]; b=y[l++];
		for(i=0;i<4;i++)
		{
			xx=a+fx[i]; yy=b+fy[i];
			if(xx<=0||yy<=0||xx>n||yy>m||used[xx][yy]||s[xx][yy]!='X') continue;
			used[xx][yy]=true; num[xx][yy]=cnt;
			x[++r]=xx; y[r]=yy;
		}
	}
}
 void land_c(int now){
 //预处理第二步
	int a,b,c,xx,yy,i;
	while(l<=r){
		a=x[l]; b=y[l]; c=dis[l++];
		for(i=0;i<4;i++){
			xx=a+fx[i]; yy=b+fy[i];
			if(xx<=0||yy<=0||xx>n||yy>m||used[xx][yy]||s[xx][yy]=='.') continue;
			used[xx][yy]=true;
			if(s[xx][yy]=='X')
			{
				if(d[now][num[xx][yy]]<0)
				 d[now][num[xx][yy]]=c;
				x[--l]=xx; y[l]=yy; dis[l]=c;
				continue;
			}
			x[++r]=xx; y[r]=yy; dis[r]=c+1;
		}
	}
}
 int main()
{
	n=read();
	m=read();
	for(i=1;i<=n;i++){
        scanf("%s",s[i]+1);
	}
	for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(s[i][j]=='X'&&(!used[i][j])){
                ++cnt;
                l=r=1;
                x[1]=i;
                y[1]=j;
            }
            used[i][j]=true; num[i][j]=cnt;
            land_f();
        }
    }
	maxn=n*m;
    memset(d,-1,sizeof(d));
	for(k=1;k<=cnt;k++){
		l=maxn+1;
		r=maxn;
		d[k][k]=0;
		for(i=1;i<=n;i++) {
            for(j=1;j<=m;j++){
                used[i][j]=false;
                if(num[i][j]==k){
                    x[++r]=i;
                    y[r]=j;
                    dis[r]=0;
                    used[i][j]=true;
                }
            }
		}
		land_c(k);
	}
	lim=(1<<cnt)-1;
    memset(f,63,sizeof(f));
	for(i=1;i<=cnt;i++) {
        c[i]=1<<i-1;
        f[c[i]][i]=0;
	}
	for(i=1;i<lim;i++){
		for(j=1;j<=cnt;j++){
            if((i&c[j])&&f[i][j]<maxn){
                for(k=1;k<=cnt;k++){
                    if(!(i&c[k])&&d[j][k]>0){
                        //如果d[j][k]=-1,说明岛屿j和岛屿k不连通
                        f[i|c[k]][k]=min(f[i|c[k]][k],f[i][j]+d[j][k]);
                    }
                }
            }
		}
	}
	ans=1e9;
	for(i=1;i<=cnt;i++) ans=min(ans,f[lim][i]);
	printf("%d",ans);
	return 0;
}
