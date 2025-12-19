#include<bits/stdc++.h>
using namespace std;

int st[3000005];
int n,r=0;
int nums[3000005],R[3000005];

int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        nums[i]=read();
    int cur;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]<=nums[i]){
            cur=st[--r];
            R[cur]=i;
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        R[cur] = 0;
    }

    for(int i=n-2;i>=0;i--){
        if(R[i]!=0&&nums[i]==nums[R[i]])
            R[i]=R[R[i]];
    }
    for(int i=1;i<=n;i++)
        cout<<R[i]<<' ';
    return 0;
}
