#include<bits/stdc++.h>
using namespace std;
const int BASE = 499;
const int MAXN = 30005;
const int MAXM = 205;

long long p[MAXM];
long long h[MAXN][MAXM];
int n,m,l,op;
char s[MAXM];
long long cnt[MAXN];

int main()
{
    cin>>n>>l>>op;
    p[0]=1;
    for(int i=1;i<=l;i++){
        p[i]=p[i-1]*BASE;
    }
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=l;j++){
			h[i][j]=h[i][j-1]*BASE+s[j];
        }
    }
    int ans=0;
    for(int k=1;k<=l;k++){
		for(int i=1;i<=n;i++){
			cnt[i]=h[i][l]-h[i][k]*p[l-k]+h[i][k-1]*p[l-k];
		}
		sort(cnt+1,cnt+1+n);
		int t=1;
		for(int i=1;i<=n;i++){
			if(cnt[i]==cnt[i-1]){
				ans+=t;
				++t;
			}
			else{
				t=1;
			}
		}
	}
	cout<<ans<<endl;
    return 0;
}
