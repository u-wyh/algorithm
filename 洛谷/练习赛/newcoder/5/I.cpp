#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1<<20)+5;

int n;
string str;
int nums[MAXN];
int ans[MAXN];

int compute(int k){
    if(k==0){
        return 0;
    }

    int mid=1<<(k-1);
    int lst=0;

    for(int i=mid;i<(1<<k);i++){
        if(nums[i]==0){
            continue;
        }

        if(lst==0){
            lst=i;
        }
        else{
            int x=lst;
            int y=i;
            int z=x^y;

            ans[x]=y;
            
            nums[x]^=1;
            nums[y]^=1;
            nums[z]^=1;

            lst=0;
        }
    }

    int left=compute(k-1);

    if(lst&&left){
        int x=lst;
        int y=left;
        int z=left^lst;

        ans[x]=y;
        nums[x]^=1;
        nums[y]^=1;
        nums[z]^=1;
        return z;
    }
    else if(lst){
        return lst;
    }
    else{
        return left;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        cin>>n>>str;
        int len=(1<<n)-1;

        for(int i=1;i<=len;i++){
            nums[i]=str[i-1]-'0';
            ans[i]=0;
        }

        compute(n);

        for(int i=1;i<=len;i++){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
    }
    return 0;
}