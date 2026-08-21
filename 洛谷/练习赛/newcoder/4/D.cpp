#include<bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int T,n;

int p[MAXN];
bool used[MAXN];

// best[dep][i]：当前搜索层dep最终得到的最优答案
int best[MAXN][MAXN];

// 把完整排列p旋转，使1位于开头
// 结果写入best[n]
void getMinRotation(){
    int pos=0;

    for(int i=0;i<n;i++){
        if(p[i]==1){
            pos=i;
            break;
        }
    }

    for(int i=0;i<n;i++){
        best[n][i]=p[(pos+i)%n];
    }
}

// 比较a和b的字典序
// a<b返回-1
// a=b返回0
// a>b返回1
int compareArray(int a[],int b[]){
    for(int i=0;i<n;i++){
        if(a[i]<b[i]){
            return -1;
        }

        if(a[i]>b[i]){
            return 1;
        }
    }

    return 0;
}

// 把src复制到dst
void copyArray(int dst[],int src[]){
    for(int i=0;i<n;i++){
        dst[i]=src[i];
    }
}

// 已经填写了p[0...dep-1]
void dfs(int dep){
    if(dep==n){
        getMinRotation();
        return;
    }

    bool first=true;

    for(int x=1;x<=n;x++){
        if(used[x]){
            continue;
        }

        used[x]=true;
        p[dep]=x;

        dfs(dep+1);

        used[x]=false;

        if(first){
            copyArray(best[dep],best[dep+1]);
            first=false;
        }
        else{
            int cmp=compareArray(best[dep+1],best[dep]);

            if(dep%2==0){
                // Alice回合：希望答案字典序尽可能小
                if(cmp<0){
                    copyArray(best[dep],best[dep+1]);
                }
            }
            else{
                // Bob回合：希望答案字典序尽可能大
                if(cmp>0){
                    copyArray(best[dep],best[dep+1]);
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>T;

    while(T--){
        cin>>n;

        for(int i=1;i<=n;i++){
            used[i]=false;
        }

        dfs(0);

        for(int i=0;i<n;i++){
            cout<<best[0][i];

            if(i+1<n){
                cout<<" ";
            }
        }

        cout<<"\n";
    }

    return 0;
}