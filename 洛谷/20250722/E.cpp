#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;
const int MAXM = 1e6+5;

int cnt;
int prime[MAXN];//欧拉筛中用于收集质数的数组
int num[MAXN];//记录每个数字的最小质因子
int t[MAXN];

int n;
int nums[MAXM];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int euler(int n){
    for(int i=2;i<=n;i++){
        if(num[i]==0){
            prime[++cnt]=i;
            num[i]=i;
        }

        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            num[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break; 
            }
        }
    }
    return cnt;
}

int main()
{
    euler(5000000);
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        sort(nums+1,nums+n+1);

        if(n==1){
            cout<<"YES"<<endl;
            continue;
        }
        if(n==2){
            if(nums[1]==nums[2]){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
            continue;
        }

        int one=1;
        while(nums[one]==1){
            one++;
        }
        one--;

        for(int i=1;i<=n;i++){
            int val=nums[i];
            while(val!=1){
                t[num[val]]++;
                val/=num[val];
            }
        }

        for(int i=1;i<=n;i++){
            int val=nums[i];
            if(val==1){
                continue;
            }
            bool flag=true;
            int p=num[val];
            while(val>1){
                int ti=0;
                p=num[val];
                while(val%p==0){
                    ti++;
                    val/=p;
                }
                if(ti*2>t[p]){
                    flag=false;
                    break;
                }
            }
            if(flag){
                one++;
                break;
            }
        }

        if(n%2==1){
            cout<<"YES"<<endl;
        }
        else{
            if(one){
                bool flag=true;
                for(int i=1;i<=n;i++){
                    int val=nums[i];
                    while(val!=1){
                        if(t[num[val]]%2){
                            flag=false;
                            break;
                        }
                        val/=num[val];
                    }
                }
                if(flag){
                    cout<<"YES"<<endl;
                }
                else{
                    cout<<"NO"<<endl;
                }
            }
            else{
                cout<<"NO"<<endl;
            }
        }

        for(int i=1;i<=n;i++){
            int val=nums[i];
            while(val!=1){
                t[num[val]]=0;
                val/=num[val];
            }
        }
    }
    return 0;
}