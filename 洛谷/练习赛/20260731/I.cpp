#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n;
char s[MAXN];
int nums[MAXN];
int ans[MAXN];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        scanf("%s",s+1);
        for(int i=1;i<(1<<n);i++){
            nums[i]=s[i]-'0';
        }

        if(n==1){
            cout<<1<<endl;
            continue;
        }
        
        for(int i=(1<<n)-1;i>=2;i--){
            if(nums[i]==1){
                if(i%2==1){
                    ans[i]=1;
                    nums[1]^=1;
                    nums[i-1]^=1;
                }
                else{

                }
                nums[i]=0;
            }
            else{
                
            }
        }
    }
    return 0;
}