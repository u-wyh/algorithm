#include<iostream>
using namespace std;
#define int long long
const int MAXN = 1005;
const int MAXM = 12;

int n,m;
int arr[MAXN][MAXM];
int f[MAXN][MAXM][1<<12];

int get(int s, int j) {
	return (s >> j) & 1;
}

int set(int s, int j, int v) {
	return v == 0 ? (s & (~(1 << j))) : (s | (1 << j));
}

int compute(int i,int j,int s){
    if(i==n){
        return 0;
    }
    if(j==m){
        return compute(i+1,0,s);
    }
    if(f[i][j][s]!=-1){
        return f[i][j][s];
    }
    int ans=0;
    if(get(s,j)==1){
        if(arr[i][j]==1)
            ans=compute(i,j+1,s);
        else
            ans=compute(i,j+1,set(s,j,0));
    }
    else{
        if(arr[i][j]==0){
            ans=compute(i,j+1,s);
        }
        else{
            ans=compute(i,j+1,set(s,j,1))+1;
            int k=j;
            while(k<m&&arr[i][k]){
                ans=min(ans,compute(i,k+1,s)+1);
            }
        }
    }
    f[i][j][s]=ans;
    return ans;
}

signed main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char c;
            cin>>c;
            arr[i][j]= c=='#';
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<(1<<m);k++){
                f[i][j][k]=-1;
            }
        }
    }
    cout<<compute(0,0,0);
    return 0;
}
/*
3 3
#.#
.#.
#.#

3 3
###
###
###
*/
