#include<bits/stdc++.h>
using namespace std;
const int MAXN = (1<<20)+5;

int n,N;
int a[MAXN];
int ans[MAXN];

int solve(int k)
{
    if(k==0){
        return 0;
    }

    int mid=1<<(k-1);
    int last=0;

    // 右半部分的1两两消除
    for(int i=mid;i<(mid<<1);i++){
        if(a[i]==0){
            continue;
        }

        if(last==0){
            last=i;
        }
        else{
            int x=last;
            int y=i;
            int z=x^y;

            ans[x]=y;

            a[x]^=1;
            a[y]^=1;
            a[z]^=1;

            last=0;
        }
    }

    int left=solve(k-1);

    // 左右各剩一个1时合并
    if(last&&left){
        int y=last^left;

        ans[last]=y;

        a[last]^=1;
        a[y]^=1;
        a[left]^=1;

        return y;
    }

    if(last){
        return last;
    }

    return left;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--){
        string s;

        cin>>n;
        cin>>s;

        N=(1<<n)-1;

        for(int i=1;i<=N;i++){
            a[i]=s[i-1]-'0';
            ans[i]=0;
        }

        solve(n);

        for(int i=1;i<=N;i++){
            cout<<ans[i];
            if(i==N){
                cout<<'\n';
            }
            else{
                cout<<' ';
            }
        }
    }

    return 0;
}