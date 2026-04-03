#include<bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
const int MAXB = 505;
const int MAXM = MAXB*3;

int n,q,b;
int army[MAXN];
int bel[MAXN];

int op[MAXN];
int ql[MAXN];
int qr[MAXN];
int qx[MAXN];
int qy[MAXN];

int blen,bnum;
int bl[MAXB];
int br[MAXB];

int cnt;
int fa[MAXN];
int f[MAXM];
int sz[MAXM];
int col[MAXM];
long long tag[MAXM];

long long ans[MAXN];

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
}

void compute(int l,int r){
    for(int i=l;i<=r;i++){
        tag[i-l+1]=army[i];
        col[i-l+1]=bel[i];
        f[i-l+1]=0;
        sz[i-l+1]=1;
    }

    long long sum=0;
    int len=r-l+1;
    // for(int i=len+1;i<=cnt;i++){
    //     f[i]=0;
    //     tag[i]=0;
    // }
    cnt=len;
    // 初始化建树
    for(int i=1;i<=len;i++){
        sum+=tag[i];
        if(fa[col[i]]==0){
            ++cnt;
            tag[cnt]=0;
            f[cnt]=0;
            f[i]=cnt;
            sz[cnt]=1;
            col[cnt]=col[i];
            fa[col[i]]=cnt;
        }
        else{
            int u=fa[col[i]];
            f[i]=u;
            sz[u]++;
        }
    }

    // 执行操作
    for(int i=1;i<=q;i++){
        // 命令范围
        int lt=ql[i],rt=qr[i];

        // 不涉及到这个块
        if(lt>r||rt<l){
            continue;
        }

        if(lt<=l&&r<=rt){
            if(op[i]==1){
                if(qx[i]==qy[i]||!fa[qx[i]]){
                    continue;
                }
                else if(fa[qy[i]]==0){
                    col[fa[qx[i]]]=qy[i];
                    fa[qy[i]]=fa[qx[i]];
                    fa[qx[i]]=0;
                }
                else{
                    ++cnt;
                    tag[cnt]=0;
                    f[cnt]=0;
                    col[cnt]=qy[i];
                    f[fa[qx[i]]]=cnt;
                    f[fa[qy[i]]]=cnt;
                    sz[cnt]=sz[fa[qx[i]]]+sz[fa[qy[i]]];
                    fa[qy[i]]=cnt;
                    fa[qx[i]]=0;
                }
            }
            else if(op[i]==2){
                int u=fa[qx[i]];
                if(u){
                    sum+=1ll*sz[u]*qy[i];
                    tag[u]+=qy[i];
                }
            }
            else{
                ans[i]+=sum;
            }
        }
        else{
            for(int u=cnt;u>=1;u--){
                if(f[u]){
                    tag[u]+=tag[f[u]];
                    col[u]=col[f[u]];
                }
            }
            for(int u=len+1;u<=cnt;u++){
                tag[u]=0;
                f[u]=0;
            }
            cnt=len;
            for(int u=1;u<=len;u++){
                f[u]=0;
                fa[col[u]]=0;
            }

            lt=max(l,lt)-l+1,rt=min(r,rt)-l+1;

            if(op[i]==1){
                for(int j=lt;j<=rt;j++){
                    if(col[j]==qx[i]){
                        col[j]=qy[i];
                    }
                }
            }
            else if(op[i]==2){
                for(int j=lt;j<=rt;j++){
                    if(col[j]==qx[i]){
                        sum+=qy[i];
                        tag[j]+=qy[i];
                    }
                }
            }
            else{
                for(int j=lt;j<=rt;j++){
                    ans[i]+=tag[j];
                }
            }

            for(int u=1;u<=len;u++){
                if(fa[col[u]]==0){
                    ++cnt;
                    tag[cnt]=0;
                    f[cnt]=0;
                    f[u]=cnt;
                    sz[cnt]=1;
                    col[cnt]=col[u];
                    fa[col[u]]=cnt;
                }
                else{
                    int k=fa[col[u]];
                    f[u]=k;
                    sz[k]++;
                }
            }
        }
    }

    for(int i=1;i<=b;i++){
        fa[i]=0;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q>>b;
    for(int i=1;i<=n;i++){
        cin>>army[i];
    }
    for(int i=1;i<=n;i++){
        cin>>bel[i];
    }

    for(int i=1;i<=q;i++){
        cin>>op[i]>>ql[i]>>qr[i];
        if(op[i]!=3){
            cin>>qx[i]>>qy[i];
        }
    }

    prepare();
    for(int i=1;i<=bnum;i++){
        compute(bl[i],br[i]);
    }

    for(int i=1;i<=q;i++){
        if(op[i]==3){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}