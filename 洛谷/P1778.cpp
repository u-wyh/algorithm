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

// 二进制状态压缩
int mm(int a, int b, int c) {
    return (a << 16) | (b << 8) | c;
} 

// 返回 a -> b 的鬼和 x -> y 的鬼路线是否冲突
bool ct(int a, int b, int x, int y) {
    return b == y || (a == y && b == x);
} 

int bfs(){
    memset(d,-1,sizeof(d));
    queue<int>q;
    q.push(mm(st[0],st[1],st[2]));
    d[st[0]][st[1]][st[2]]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        int a=u>>16;
        int b=(u>>8)&255;
        int c=u&255;

        if(a==en[0]&&b==en[1]&&c==en[2]){
            return d[a][b][c];
        }

        for(int i=0;i<out[a];i++){
            for(int j=0;j<out[b];j++){
                if(ct(a,to[a][i],b,to[b][j])){
                    continue;
                }
                for(int k=0;k<out[c];k++){
                    if(ct(a,to[a][i],c,to[c][k])||ct(b,to[b][j],c,to[c][k])||d[to[a][i]][to[b][j]][to[c][k]]!=-1){
                        continue;
                    }
                    d[to[a][i]][to[b][j]][to[c][k]]=d[a][b][c]+1;
                    q.push(mm(to[a][i],to[b][j],to[c][k]));
                }
            }
        }
    }
}

int main()
{
    while(scanf("%d %d %d",&w,&h,&n)){
        getchar();
        cnt=0;
        memset(id, 0, sizeof id); // 更安全的初始化方式
        
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

        cout<<bfs()<<endl;
        
        for(int i=1;i<=cnt;i++){
            out[i]=0;
        }

    }
    return 0;
}