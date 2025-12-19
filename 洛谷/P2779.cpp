#include<bits/stdc++.h>
using namespace std;
const int p=1e9+9;
char str[500006];
int dp[500006]={1},n;
int main() {
    cin>>str+1;
    n=strlen(str+1);
    for(int i=1;i<=n;i++) {
    	if(str[i]!='W') {
    		int l=i,r=i+1;
    		for(int j=i;l>=1&&r<=n;j++) {
    			if(str[l]=='W'||str[r]=='B') break;
    			dp[r]=(dp[r]+dp[l-1])%p;
    			l--,r++;
			}
		}
	}
	cout<<dp[n];
    return 0;
}
