#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150;

int w,h,n;
int cnt;
string s[20];
int id[20][20];

int to[MAXN][5];
int out[MAXN];
int st[3],en[3];
int d[MAXN][MAXN][MAXN];
int sta[MAXN][MAXN][MAXN];

int nums1[MAXN*MAXN*MAXN],cnt1;
int nums2[MAXN*MAXN*MAXN],cnt2;
int lt=1,rt=1,tl=1,tr=1;
int flag;

// 二进制状态压缩
int mm(int a, int b, int c) {
    return (a << 16) | (b << 8) | c;
} 

// 返回 a -> b 的鬼和 x -> y 的鬼路线是否冲突
bool ct(int a, int b, int x, int y) {
    return b == y || (a == y && b == x);
} 

void bfs(int u,int op){
    int a=u>>16;
    int b=(u>>8)&255;
    int c=u&255;

    for(int i=0;i<out[a];i++){
        for(int j=0;j<out[b];j++){
            if(ct(a,to[a][i],b,to[b][j])){
                continue;
            }
            for(int k=0;k<out[c];k++){
                if(ct(a,to[a][i],c,to[c][k])||ct(b,to[b][j],c,to[c][k])){
                    continue;
                }

                if(sta[to[a][i]][to[b][j]][to[c][k]]==0){
                    d[to[a][i]][to[b][j]][to[c][k]]=d[a][b][c]+1;
                    sta[to[a][i]][to[b][j]][to[c][k]]=op;
                    if(op==1){
                        nums1[++cnt1]=mm(to[a][i],to[b][j],to[c][k]);
                    }
                    else{
                        nums2[++cnt2]=mm(to[a][i],to[b][j],to[c][k]);
                    }
                }
                else{
                    if(sta[to[a][i]][to[b][j]][to[c][k]]!=op){
                        flag=d[to[a][i]][to[b][j]][to[c][k]]+d[a][b][c]+1;
                        return ;
                    }
                    else{
                        continue;
                    }
                }

            }
        }
    }
}

void compute(){
    memset(d,-1,sizeof(d));
    memset(sta,0,sizeof(sta));
    cnt1=cnt2=0;
    lt=tl=tr=rt=1;
    flag=0;

    nums1[++cnt1]=mm(st[0],st[1],st[2]);
    nums2[++cnt2]=mm(en[0],en[1],en[2]);
    d[st[0]][st[1]][st[2]]=0;
    sta[st[0]][st[1]][st[2]]=1;
    d[en[0]][en[1]][en[2]]=0;
    sta[en[0]][en[1]][en[2]]=2;
    while(true){
        for(int i=lt;i<=rt;i++){
            bfs(nums1[i],1);
            if(flag){
                return ;
            }
        }
        lt=rt+1;
        rt=cnt1;

        for(int i=tl;i<=tr;i++){
            bfs(nums2[i],2);
            if(flag){
                return ;
            }
        }
        tl=tr+1;
        tr=cnt2;
    }
}

int main()
{
    while(scanf("%d %d %d",&w,&h,&n)==3){
        cnt=0;
        getchar();
        memset(id, 0, sizeof id); // 更安全的初始化方式
        memset(out,0,sizeof(out));
        
        for(int i=1;i<=h;i++){
            getline(cin,s[i]);
            for(int j=0;j<w;j++){
                if(s[i][j]!='#'){
                    id[i][j]=++cnt;
                    to[cnt][out[cnt]++]=cnt;

                    if(s[i-1][j]!='#'){
                        to[cnt][out[cnt]++]=id[i-1][j];
                        to[id[i-1][j]][out[id[i-1][j]]++]=cnt;
                    }

                    if(s[i][j-1]!='#'){
                        to[cnt][out[cnt]++]=id[i][j-1];
                        to[id[i][j-1]][out[id[i][j-1]]++]=cnt;
                    }

                    if(islower(s[i][j])){
                        st[s[i][j]-'a']=cnt;
                    }
                    else if(isupper(s[i][j])){
                        en[s[i][j]-'A']=cnt;
                    }
                }
            }
        }

        if(n<=2){
            out[++cnt]=1;
            to[cnt][0]=cnt;
            st[2]=en[2]=cnt;
        }
        if(n==1){
            out[++cnt]=1;
            to[cnt][0]=cnt;
            st[1]=en[1]=cnt;
        }

        compute();
        cout<<flag<<endl;
    }
    return 0;
}