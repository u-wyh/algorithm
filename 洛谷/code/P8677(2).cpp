// Ì°ÐÄ O(nlogn)
#include<bits/stdc++.h>
#define N 100010
using namespace std;

int n,B[N],S[N],t[N],len,ans,mx;

int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;++i)scanf("%d",&B[i]),mx=max(mx,B[i]);
  for(int i=1;i<=n;++i)
    scanf("%d",&S[i]),ans+=S[i],t[i]=B[i]-S[i];
  for(int i=2,a,b;i<=n;++i){
    scanf("%d%d",&a,&b);
    len+=b*2;
  }
  sort(t+1,t+n+1);
  ans+=max(t[1],0);
  ans=max(ans,mx);
  printf("%d %d\n",len,ans);
}
