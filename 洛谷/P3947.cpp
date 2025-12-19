#include<bits/stdc++.h>
using namespace std;

int n,mn,T;
char name[25][50];
int t[25],m[25];
int dp[(1<<22)];
string s[(1<<22)];
int stime[(1<<22)];

int main()
{
	scanf("%d %d %d",&n,&mn,&T);
	int ts=0;
	for(int i=1;i<=n;i++){
		scanf("%s %d %d",name+i,t+i,m+i);
		ts+=t[i];
	}
	if(ts>T)
        printf("No Answer"),exit(0);
	int temp0=(1<<n);
	for(int S=1;S<temp0;S++){
		for(int i=1;i<=n;i++){
			if(S&(1<<(i-1))){
				int last=S^(1<<(i-1));
				if(!stime[S])
                    stime[S]=stime[last]+t[i];
				int sum=stime[last];
				int temp=dp[last]+max(0,m[i]-(sum+t[i]));
				if(temp>dp[S]){
					dp[S]=temp;
					s[S]=s[last]+(char)i;
				}
				else if(temp==dp[S]){
					s[S]=min(s[S],s[last]+(char)i);
				}
			}
		}
		//print(S);cout<<" "<<dp[S]<<" ";prints(S);cout<<endl;
	}
	int temp=(1<<n)-1;
	int ans=dp[temp];
	if(ans<mn)
        printf("No Answer"),exit(0);
	printf("%d\n",ans);
	int temp2=s[temp].length();
	for(int i=0;i<temp2;i++){
		printf("%s\n",name[s[temp][i]]);
	}
	return 0;
}
