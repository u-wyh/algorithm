#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
int nums[MAXN];

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

int main()
{
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        int kind=-1;
        int minn=INT_MAX,maxx=INT_MIN;
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(nums[i]<minn){
                minn=nums[i];
                kind++;
                cnt=1;
            }
            else if(minn==nums[i]){
                cnt++;
            }

            if(nums[i]>maxx){
                maxx=nums[i];
                kind++;
            }
            // maxx=max(maxx,nums[i]);

            // cout<<i;
            if(kind<=2){
                if(minn!=nums[i]&&maxx!=nums[i]){
                    kind++;
                }

                if(kind==2){
                    if(cnt==1){
                        cout<<(2*maxx)<<' ';
                    }
                    else{
                        cout<<(minn+maxx)<<' ';
                    }
                }
                else if(kind==1){
                    cout<<(2*minn)<<' ';
                }
                else{
                    cout<<(minn+maxx)<<' ';
                }
            }
            else{
                cout<<(minn+maxx)<<' ';
            }
        }
        cout<<endl;
    }
    return 0;
}
/*
3
6
1 1 4 5 1 4
5
1 2 3 4 5
5
1 2 2 1 2
*/