#include<bits/stdc++.h>
using namespace std;

long n,m,s,t,ans=0;
long long nums[200005],d[200005];

long long read(){
	long long a=0,k=1;char c=getchar();
	while (!isdigit(c)){if (c=='-')k=-1;c=getchar();}
	while (isdigit(c)){a=a*10+c-'0';c=getchar();}
	return a*k;
}

int main()
{
    n=read(),m=read(),s=read(),t=read();
    for(int i=0;i<=n;i++){
        nums[i]=read();
    }
    for(int i=1;i<=n;i++){
        d[i]=nums[i-1]-nums[i];
        if(d[i]<0)
            ans+=d[i]*s;
        else
            ans+=d[i]*t;
        //printf("%3d",d[i]);
    }
    //printf("\n");
    //cout<<ans<<endl;
    while(m--){
        //for(int i=1;i<=n;i++){
            //printf("%3d",d[i]);
        //}
        //printf("\n");
        long long a,b,c;
        a=read(),b=read(),c=read();
        if(d[a]<=0&&(d[a]-c)<=0)
            ans-=c*s;
        else if(d[a]>=0&&(d[a]-c)>=0)
            ans-=t*c;
        else if(d[a]>=0&&(d[a]-c)<=0)
            ans+=(d[a]-c)*s-d[a]*t;
        else
            ans+=(d[a]-c)*t-d[a]*s;
        d[a]-=c;
        if(b==n){
            cout<<ans<<endl;
            continue;
        }
        if(d[b+1]<=0&&(d[b+1]+c)<=0)
            ans+=c*s;
        else if(d[b+1]>=0&&(d[b+1]+c)>=0)
            ans+=t*s;
        else if(d[b+1]>=0&&(d[b+1]+c)<=0)
            ans+=(d[b+1]+c)*s-d[b+1]*t;
        else
            ans+=(d[b+1]+c)*t-d[b+1]*s;
        d[b+1]+=c;
        cout<<ans<<endl;
    }
    //for(int i=1;i<=n;i++){
        //printf("%3d",d[i]);
    //}
    //printf("\n");
    return 0;
}
