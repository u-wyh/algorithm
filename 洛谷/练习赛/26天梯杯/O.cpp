#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 105;
const int INF = 1e9;

int n;
int val[MAXN][MAXN];
int pre[MAXN][MAXN];
int allans;

int row[MAXN];

int ans;
struct node{
    int all,x1,y1,x2,y2;
};
node cand;

bool better(node &a){
    if(a.all!=cand.all){
        return a.all>cand.all;
    }
    else if(a.x1!=cand.x1){
        return a.x1<cand.x1;
    }
    else if(a.y1!=cand.y1){
        return a.y1<cand.y1;
    }
    else if(a.x2!=cand.x2){
        return a.x2<cand.x2;
    }
    return a.y2<cand.y2;
}

void compute(){
    for(int i=1;i<=n;i++){
        pre[i][0]=0;
        for(int j=1;j<=n;j++){
            pre[i][j]=pre[i][j-1]+val[i][j];
        }
    }
    for(int l=1;l<=n;l++){
        for(int r=l;r<=n;r++){
            for(int i=1;i<=n;i++){
                row[i]=pre[i][r]-pre[i][l-1];
            }

            int st=1;
            int now=0;
            for(int i=1;i<=n;i++){
                if(now<0){
                    now=row[i];
                    st=i;
                }
                else{
                    now+=row[i];
                }
                node tmp={now,l,st,r,i};
                if(better(tmp)){
                    cand=tmp;
                }
            }
        }
    }
}

void calc(){
    int x1=cand.x1;
    int y1=cand.y1;
    int x2=cand.x2;
    int y2=cand.y2;
    int h=y2-y1+1;
    for(int x=x1;x<=x2;x++){
        for(int i=y1-1;i>-1;i--){
            val[i+h][x]=val[i][x];
        }
        for(int i=1;i<=h;i++){
            val[i][x]=-INF;
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>val[i][j];
            if(val[i][j]==0){
                val[i][j]=-INF;
            }
        }
    }

    while(true){
        cand={-INF,0,0,0,0};
        compute();
        if(cand.all<=0){
            break;
        }
        allans+=cand.all;
        cout<<"("<<cand.x1<<", "<<cand.y1<<") "<<"("<<cand.x2<<", "<<cand.y2<<") "<<cand.all<<endl;
        calc();
    }
    cout<<allans;
    return 0;
}