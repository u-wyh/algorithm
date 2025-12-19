#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 22;

int n,q,p;
int Next[MAXN];
char s[MAXN];

vector<int>vec[MAXN];

int z[MAXN];
int tree[MAXN<<2];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXH];

void zarray(){
    z[1]=n;
    for(int i=2,c=2,r=2,len;i<=n;i++){
        len=r>i?min(r-i,z[i-c+1]):0;
        while (i + len <= n && s[i + len] == s[len+1]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=z[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
}

int query(int jobl,int jobr,int jobv,int l,int r,int i){
    if((tree[i]<jobv)||(jobl>jobr)){
        return 0;
    }
    if(l==r){
        return l;
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid&&jobr>=mid){
            int ans=query(jobl,jobr,jobv,l,mid,i<<1);
            if(ans==0){
                return query(jobl,jobr,jobv,mid+1,r,i<<1|1);
            }
            else{
                return ans;
            }
        }
        else if(jobl<=mid){
            return query(jobl,jobr,jobv,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
    }
}

void calcnext(){
    Next[1]=0;
    for(int i=2,j=0;i<=n;i++){
        // 当不匹配时，通过next数组回溯
        while(j>0&&s[i]!=s[j+1]){
            j=Next[j];
        }
        // 如果当前字符匹配，j增加
        if(s[i]==s[j+1]){
            j++;
        }
        // 设置当前位置的next值
        Next[i]=j;
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u,int fa){
    // cout<<u<<' '<<fa<<endl;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        //如果相同说明就是祖先关系
        //那么还要向上跳一下  因为要求的是border
        //实际上也可以求stjump[u][0],stjump[v][0]的lca  这样不用跳  直接就是lca
        return st[a][0];
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int find(int x, int k) {
    // 从x开始向上跳，找到最大的u使得vec[u]中至少有k次不重叠出现且第k次出现不超过x
    int u = x;
    
    // 从高位向低位尝试跳
    for(int i = p; i >= 0; i--) {
        if(st[u][i] == 0) continue;
            
        int candidate = st[u][i];
        // cout<<666<<' '<<vec[candidate].size()<<' '<<k<<endl;
        // 检查候选border长度candidate是否满足条件
        if(((int)vec[candidate].size() < k) ||(((int)vec[candidate].size() >= k)&& (vec[candidate][k-1] > x))) {
            // 如果满足条件，就跳过去
            // cout<<888<<endl;
            u = candidate;
        }
        // cout<<candidate<<' '<<u<<' '<<vec[candidate][k-1]<<endl;
    }

    // if((int)vec[u].size() >= k&& (vec[u][k-1] <= x)){
    //     return u;
    // }

    if((int)vec[Next[u]].size() < k ||(((int)vec[Next[u]].size() >= k)&& (vec[Next[u]][k-1] > x))) {
        u = Next[u];
    }
    return Next[u];
}

int main()
{
    scanf("%d",&n);
    p=log2(n+1)+1;
    scanf("%s",s+1);

    zarray();
    // for(int i=1;i<=n;i++){
    //     cout<<i<<":   "<<z[i]<<endl;
    // }
    // cout<<endl;
    build(1,n,1);

    calcnext();
    for(int i=1;i<=n;i++){
        addedge(Next[i],i);
    }
    dfs(0,0);

    for(int i=1;i<=n;i++){
        int lst=i+1;
        vec[i].push_back(i);
        for(int k=2;k<=n/i;k++){
            int pos=query(lst,n,i,1,n,1)+i-1;
            if(pos==i-1){
                break;
            }
            else{
                vec[i].push_back(pos);
                lst=pos+1;
            }
        }

        // cout<<i<<":  "<<vec[i].size()<<"  ";
        // for(int k=0;k<(int)vec[i].size();k++){
        //     cout<<vec[i][k]<<' ';
        // }
        // cout<<endl;
    }
    scanf("%d",&q);
    while(q--){
        int x,k;
        scanf("%d %d",&x,&k);
        /*
        这里需要补充一个二分判断它的第几层祖先可以满足要求  即vec[y].size()>=k&&vec[y][k-1]<=x
        那么答案就是dep[y]-1
        */
        if(k==1){
            printf("1\n");
            continue;
        }
        int u = find(x, k);
        // int delta=1;
        // if(!u||(vec[u].size()>=k&&vec[u][k-1]<=x)){
        //     delta=0;
        // }
        // if(k==1){
        //     u=x;
        // }
        
        // 答案就是满足条件的border长度u的深度（即border链的长度）
        // 因为所有比u短的border也都满足条件
        // cout<<' '<<u<<' ';
        printf("%d\n", dep[u]-1);
    }
    return 0;
}
/*
20
baabbabaaaaabbbbbbba
10
11 8
20 15
10 3
15 10
4 4
1 1
9 3
16 15
11 10
8 3

20
baabbabaaaaabbbbbbba
1  
15 10
*/