#include<bits/stdc++.h>
using namespace std;

int n,k,tail,head,ans[1000005];
unsigned long long stk[1000005];

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) {
        scanf("%llu",stk+i);
        if(head-tail&&ans[tail+1]+k<=i)
            tail++;
        while(head-tail&&stk[ans[head]]<=stk[i])
            head--;
        ans[++head]=i;
        if(i>=k) printf("%d\n",head-tail);
    }
    return 0;
}
