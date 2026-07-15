#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int temp[MAXN];
int arr[MAXN];
int n,k;
int cnt[MAXN];
map<int,int>m;
int tot=1;
int ans=0;
int kind=0;

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

void build(){
    sort(temp+1,temp+n+1);
    m[temp[1]]=tot;
    for(int i=2;i<=n;i++){
        if(temp[i]!=temp[i-1]){
            m[temp[i]]=++tot;
            temp[tot]=temp[i];
        }
    }
}

int main()
{
    n=read(),k=read();
    k++;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        temp[i]=arr[i];
    }
    build();
    for(int i=1;i<=n;i++){
        arr[i]=m[arr[i]];
        //cout<<arr[i]<<' ';
    }
    cnt[arr[1]]++;
    kind=1;
    ans=1;
    int l=1;
    for(int r=2;r<=n;r++){
        if(cnt[arr[r]]==0){
            kind++;
        }
        cnt[arr[r]]++;
        ans=max(ans,cnt[arr[r]]);
        while(kind>k){
            if(cnt[arr[l]]==1){
                kind--;
            }
            cnt[arr[l++]]--;
        }
    }
    cout<<ans<<endl;
    return 0;
}
