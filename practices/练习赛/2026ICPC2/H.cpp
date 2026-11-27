#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXH = 15;

int n,k;
int diff[MAXN][MAXH];
bool endpoint[MAXN];

int arr[MAXN];
int ans[MAXN];

int ask(int m,int v){
    cout<<"? "<<m<<" "<<v<<endl;
    int x;
    cin>>x;
    return x;
}

int getnxt(int cur,int pre){
    int nxt=0;
    for(int j=0;j<k;j++){
        int d=diff[cur][j];
        int b=(cur>>j)&1;
        int nb=0;

        if(endpoint[cur]){
            if(d==1){
                nb=b;
            }
            else{
                nb=b^1;
            }
        }
        else{
            int t;
            if(d==0){
                t=1;
            }
            else if(d==1){
                if(b==0){
                    t=2;
                }
                else{
                    t=0;
                }
            }
            else{
                if(b==0){
                    t=0;
                }
                else{
                    t=2;
                }
            }

            nb=t-((pre>>j)&1);
        }

        if(nb){
            nxt|=(1<<j);
        }
    }
    return nxt;
}

int walk(int st,int *arr){
    int len=0;
    int pre=-1;
    int cur=st;
    while(true){
        arr[++len]=cur;
        if(cur==0){
            break;
        }
        int nxt=getnxt(cur,pre);
        pre=cur;
        cur=nxt;
    }
    return len;
}

void solve(){
    cin>>n;
    if(n==1){
        cout<<"! 0"<<endl;
        return ;
    }

    k=0;
    while((1<<k)<n){
        k++;
    }

    for(int j=0;j<k;j++){
        int m=(1<<j);
        int base=ask(m,-1);
        for(int v=1;v<n;v++){
            int x=ask(m,v);
            diff[v][j]=(x-base+3)%3;
        }
    }

    int e1=-1,e2=-1;
    for(int v=1;v<n;v++){
        endpoint[v]=true;
        for(int j=0;j<k;j++){
            if(diff[v][j]==0){
                endpoint[v]=false;
                break;
            }
        }
        if(endpoint[v]){
            if(e1==-1){
                e1=v;
            }
            else{
                e2=v;
            }
        }
    }

    int len=0;
    if(e2==-1){
        len=walk(e1,ans);
    }
    else{
        int len1=walk(e1,arr);
        for(int i=1;i<=len1;i++){
            ans[++len]=arr[i];
        }
        int len2=walk(e2,arr);
        for(int i=len2-1;i>=1;i--){
            ans[++len]=arr[i];
        }
    }

    if(ans[1]>ans[len]){
        reverse(ans+1,ans+len+1);
    }
    cout<<"!";
    for(int i=1;i<=len;i++){
        cout<<" "<<ans[i];
    }
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}