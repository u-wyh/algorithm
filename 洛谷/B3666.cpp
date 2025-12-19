#include<bits/stdc++.h>
using namespace std;

int n;
unsigned long long nums[1000005];
int eor=0,r=0;
int q[1000005];

inline int read(){
	int fl=1,w=0;char ch=getchar();
	while(!isdigit(ch) && ch!='-') ch=getchar();
	if(ch=='-') fl=-1;
	while(isdigit(ch)){w=w*10+ch-'0',ch=getchar();}
	return fl*w;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        nums[i]=read();
    for(int i=1;i<=n;i++){
        while(r>0&&nums[i]>=nums[q[r-1]]){
            int cur=q[r-1];
            r--;
            eor^=cur;
        }
        eor^=i;
        q[r++]=i;
        cout<<eor<<endl;
    }
    return 0;
}
