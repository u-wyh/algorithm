#include<bits/stdc++.h>
using namespace std;

int n,m,A,h,t;
int arr[5000005];
int q1[5000005],q2[5000005],b[5000005],c[5000005],s2[5000005],s1[5000005];
int sum=0,maxn;

inline int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
    n=rd(),m=rd(),A=rd();
    for(int i=1;i<=n;i++){
        arr[i]=rd();
    }
    h=t=0;
    for(int i=1;i<=n;i++){
        while(h<t&&i-q1[h]>=m){
            h++;
        }
        while(h<t&&arr[q1[t-1]]<arr[i]){
            t--;
        }
        q1[t++]=i;
        if(i>=m){
            sum+=arr[q1[h]];
            b[i-m+1]=arr[q1[h]];
        }
    }
    m--;
    h=t=0;
    for(int i=1;i<=n;i++){
        while(h<t&&i-q2[h]>=m){
            h++;
        }
        while(h<t&&arr[q2[t-1]]<arr[i]){
            t--;
        }
        q2[t++]=i;
        if(i>=m){
            c[i-m+1]=arr[q2[h]];
        }
    }
    for(int i=1;i<=n-m+1;i++)
        c[i]=max(c[i],A);
	for(int i=1;i<=n;i++)
        s2[i]=s2[i-1]+c[i];
	m++;
	for(int i=1;i<=n;i++)
        s1[i]=s1[i-1]+b[i];
	for(int i=0;i<=n;i++){
		int ret=c[i+1];
		ret-=s1[i];
        ret+=s1[max(0,i-m+1)];
		ret+=(s2[i]-s2[max(0,i-m+1)]);
		maxn=max(maxn,ret);
	}
	cout<<sum+maxn<<endl;
    return 0;
}
