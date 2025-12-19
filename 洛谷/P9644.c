#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool check(int x,char *s,int n){
    int ans=0;
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            ans++;
            for(int j=i;j<=i+x-1&&j<n;j++){
                s[j]='0';
            }
        }
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int n,k;
        scanf("%d %d",&n,&k);
        char s[n+1];
        scanf("%s",s);
        //printf("%c %c\n",s[0],s[n-1]);
        int l=0,r=n,mid,ans;
        while(l<=r){
            mid=l+((r-l)>>1);
            if(check(mid,s,n)<=k){
                ans=mid;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
