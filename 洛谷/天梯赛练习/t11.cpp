#include<bits/stdc++.h>
using namespace std;

int n;
int arr[5];
int sum,squ;
int nums[25];
int cnt[1000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int k=0;
    if(n==3){
        cnt[0]=0;
        for(int i=1;i<=64;i++){
            cnt[i]=cnt[i-(i&-i)]+1;
        }
        nums[++k]=arr[0]*100+arr[1]*10+arr[2];
        nums[++k]=arr[0]*100+arr[1]+arr[2]*10;
        nums[++k]=arr[0]*10+arr[1]*100+arr[2];
        nums[++k]=arr[0]*10+arr[1]+arr[2]*100;
        nums[++k]=arr[0]+arr[1]*10+arr[2]*100;
        nums[++k]=arr[0]+arr[1]*100+arr[2]*10;
        for(int i=1;i<=k;i++){
            sum+=nums[i];
            squ+=nums[i]*nums[i];
        }
        
        for(int i=1;i<64;i++){
            if(cnt[i]==3){
                int tmp1=0,tmp2=0;
                for(int j=0;j<6;j++){
                    if(i&(1<<j)){
                        tmp1+=nums[j+1];
                        tmp2+=nums[j+1]*nums[j+1];
                    }
                }
                if(tmp1==sum/2&&tmp2==squ/2){
                    for(int j=0;j<6;j++){
                        if(i&(1<<j)){
                            cout<<nums[j+1]<<endl;
                        }
                    }
                    return 0;
                }
                
            }
        }
    }
    return 0;
}