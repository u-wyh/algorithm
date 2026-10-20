// https://www.luogu.com.cn/problem/P6562
#include<bits/stdc++.h>
using namespace std;
using uint = uint32_t;
const int MAXN = (1<<16)+5;
const int MAXB = 1505;

int n,q,N;
uint val[MAXN];
uint pre[MAXN];
uint tag[MAXN];
int cnt[MAXN];
uint pw[20];

struct Update{
    int a,b;
    uint k;
};
Update update[MAXB+5];
int cntu;

void build(){
    for(int s=0;s<N;s++){
        pre[s]=val[s];
    }
    for(int j=0;j<n;j++){
        int bit=(1<<j);
        for(int s=0;s<N;s++){
            if(s&bit){
                pre[s]+=pre[s^bit];
            }
        }
    }
}

void prepare(){
    for(int i=1;i<N;i++){
        cnt[i]=cnt[i>>1]+(i&1);
    }
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2u;
    }
    build();
}

void rebuild(){
    if(cntu==0){
        return ;
    }

    for(int i=0;i<N;i++){
        tag[i]=0;
    }
    bool flag=false;
    for(int i=1;i<=cntu;i++){
        int a=update[i].a;
        int b=update[i].b;
        uint k=update[i].k;

        int freemask=a^b;
        if(cnt[freemask]<=cnt[a]){
            for(int s=freemask;;s=(s-1)&freemask){
                val[a|s]+=k;
                if(s==0){
                    break;
                }
            }
        }
        else{
            flag=true;
            for(int s=a;;s=(s-1)&a){
                if(cnt[s]&1){
                    tag[b^s]-=k;
                }
                else{
                    tag[b^s]+=k;
                }

                if(s==0){
                    break;
                }
            }
        }
    }

    if(flag){
        for(int j=0;j<n;j++){
            int bit=1<<j;
            for(int s=0;s<N;s++){
                if(!(s&bit)){
                    tag[s]+=tag[s|bit];
                }
            }
        }
        for(int s=0;s<N;s++){
            val[s]+=tag[s];
        }
    }
    cntu=0;
    build();
}

uint query(int a,int b){
    if((a&b)!=a){
        return 0;
    }

    int freemask=a^b;
    uint ans=0;

    if(cnt[freemask]<=cnt[a]){
        for(int s=freemask;;s=(s-1)&freemask){
            ans+=val[a|s];
            if(s==0){
                break;
            }
        }
    }
    else{
        for(int s=a;;s=(s-1)&a){

            if(cnt[s]&1){
                ans-=pre[b^s];
            }
            else{
                ans+=pre[b^s];
            }

            if(s==0){
                break;
            }
        }
    }
    return ans;
}

void compute(){
    for(int i=0;i<q;i++){
        if(i&&(i%MAXB==0)){
            rebuild();
        }

        int op,a,b;
        cin>>op>>a>>b;
        if(op==1){
            uint k;
            cin>>k;
            if((a&b)==a){
                update[++cntu]={a,b,k};
            }
        }
        else{
            uint ans=query(a,b);

            if((a&b)==a){
                for(int j=1;j<=cntu;j++){
                    int L=a|update[j].a;
                    int R=b&update[j].b;

                    if((L&R)!=L){
                        continue;
                    }
                    else{
                        int t=cnt[L^R];
                        ans+=update[j].k*pw[t];
                    }
                }
            }

            cout<<ans<<endl;
        }
    }
}

int main()
{
    cin>>n>>q;
    N=1<<n;

    for(int i=0;i<N;i++){
        cin>>val[i];
    }

    prepare();

    compute();

    return 0;
}