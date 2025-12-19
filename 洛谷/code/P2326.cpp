#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int arr[MAXN],tmp[MAXN];

int main()
{
    int T,cnt=0;
    cin>>T;
    while(T--){
        cnt++;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
        for(int k=20;k>=0;k--){
            int top=0;
            for(int i=1;i<=n;i++){
                if(arr[i]&(1<<k)){
                    tmp[++top]=arr[i];
                }
            }
            if(top>1){
                n=top;
                for(int i=1;i<=top;i++){
                    arr[i]=tmp[i];
                }
            }
        }
        printf("Case #%d: %d\n", cnt, arr[1]&arr[2]);
    }
    return 0;
}
