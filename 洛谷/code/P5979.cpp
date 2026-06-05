#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+5;
const int MOD = 1e9+7;
const int INF = 1e9;

int n;
int c[MAXN];
int d[MAXN];

int addhead[MAXN];
int addnxt[MAXN];
int addto[MAXN];
int addcnt=1;

int delhead[MAXN];
int delnxt[MAXN];
int delto[MAXN];
int delcnt=1;

int maxtree[MAXN<<2];
int alltree[MAXN<<2];

int maxdp[MAXN];
int alldp[MAXN];

// 查询线段树时的临时答案
int querymax;
int queryall;

void merge_ans(int &maxx,int &all,int valmax,int valall){
    // 这题合法dp一定 >= 0，负数表示无效
    if(valmax<0){
        return;
    }

    if(maxx<valmax){
        maxx=valmax;
        all=valall;
    }
    else if(maxx==valmax){
        all+=valall;
        if(all>=MOD){
            all-=MOD;
        }
    }
}

void addaddedge(int u,int v){
    addnxt[addcnt]=addhead[u];
    addto[addcnt]=v;
    addhead[u]=addcnt++;
}

void deladdedge(int u,int v){
    delnxt[delcnt]=delhead[u];
    delto[delcnt]=v;
    delhead[u]=delcnt++;
}

void push_up(int i){
    maxtree[i]=-INF;
    alltree[i]=0;

    merge_ans(maxtree[i],alltree[i],maxtree[i<<1],alltree[i<<1]);
    merge_ans(maxtree[i],alltree[i],maxtree[i<<1|1],alltree[i<<1|1]);
}

void build(int l,int r,int i){
    maxtree[i]=-INF;
    alltree[i]=0;

    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
}

// 单点修改
// 线段树位置pos表示前缀断点pos
// 上线时放入maxdp[pos], alldp[pos]
// 下线时放入-INF, 0
void update(int pos,int valmax,int valall,int l,int r,int i){
    if(l==r){
        maxtree[i]=valmax;
        alltree[i]=valall;
        return;
    }

    int mid=(l+r)>>1;

    if(pos<=mid){
        update(pos,valmax,valall,l,mid,i<<1);
    }
    else{
        update(pos,valmax,valall,mid+1,r,i<<1|1);
    }

    push_up(i);
}

// 区间查询
// 查询当前在线的断点中，maxdp最大的值和方案数
void query(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return;
    }

    if(jobl<=l&&r<=jobr){
        merge_ans(querymax,queryall,maxtree[i],alltree[i]);
        return;
    }

    int mid=(l+r)>>1;

    if(jobl<=mid){
        query(jobl,jobr,l,mid,i<<1);
    }

    if(jobr>mid){
        query(jobl,jobr,mid+1,r,i<<1|1);
    }
}

void compute_lt(int l,int mid,int r){
    int maxx=1;
    int minn=n;

    for(int i=mid;i>=l;i--){
        // 当前i对应左半段 [i+1, mid]
        // maxx = max(c[i+1..mid])
        // minn = min(d[i+1..mid])
        // 最后一组长度是 j-i
        // 左半段要求 maxx <= j-i <= minn
        // 所以 i+maxx <= j <= i+minn

        int start=i+maxx;
        int over=i+minn;

        int lt=max(start,mid+1);
        int rt=min(over,r);

        if(lt<=rt){
            // 在lt时让i上线
            addaddedge(lt,i);

            // 在rt+1时让i下线
            if(rt+1<=r){
                deladdedge(rt+1,i);
            }
        }

        // 下一轮i-1的左半段会多包含第i个小朋友
        if(i>=1){
            maxx=max(maxx,c[i]);
            minn=min(minn,d[i]);
        }
    }
}

// 让id这个断点上线
void put_online(int id,int l,int mid){
    if(maxdp[id]>=0){
        update(id,maxdp[id],alldp[id],l,mid,1);
    }
    else{
        update(id,-INF,0,l,mid,1);
    }
}

void compute_add(int j,int l,int mid){
    for(int i=addhead[j];i;i=addnxt[i]){
        put_online(addto[i],l,mid);
    }
}

// 让id这个断点下线
void put_offline(int id,int l,int mid){
    update(id,-INF,0,l,mid,1);
}

void compute_del(int j,int l,int mid){
    for(int i=delhead[j];i;i=delnxt[i]){
        put_offline(delto[i],l,mid);
    }
}

void update_dp(int j,int valmax,int valall){
    // valmax是查到的maxdp[i]
    // 转移到j时，需要新增一组，所以+1
    if(valmax<0){
        return;
    }

    int curmax=valmax+1;
    int curall=valall;

    if(maxdp[j]<curmax){
        maxdp[j]=curmax;
        alldp[j]=curall;
    }
    else if(maxdp[j]==curmax){
        alldp[j]+=curall;
        if(alldp[j]>=MOD){
            alldp[j]-=MOD;
        }
    }
}

void query_update(int j,int maxx,int minn,int l,int mid){
    // 当前j对应右半段 [mid+1, j]
    // maxx = max(c[mid+1..j])
    // minn = min(d[mid+1..j])
    // 最后一组长度是 j-i
    // 右半段要求 maxx <= j-i <= minn
    // 所以 j-minn <= i <= j-maxx

    int lt=j-minn;
    int rt=j-maxx;

    lt=max(lt,l);
    rt=min(rt,mid);

    if(lt<=rt){
        querymax=-INF;
        queryall=0;

        query(lt,rt,l,mid,1);

        update_dp(j,querymax,queryall);
    }
}

void compute_rt(int l,int mid,int r){
    int maxx=1;
    int minn=n;

    for(int j=mid+1;j<=r;j++){
        // 处理当前j处需要上线的断点
        compute_add(j,l,mid);

        // 处理当前j处需要下线的断点
        compute_del(j,l,mid);

        // 维护右半段 [mid+1, j] 的最大c和最小d
        maxx=max(maxx,c[j]);
        minn=min(minn,d[j]);

        // 根据右半段条件查询合法断点范围，并更新dp[j]
        query_update(j,maxx,minn,l,mid);
    }
}

void compute(int l,int mid,int r){
    // 清空当前层右半边会用到的事件头
    for(int i=mid+1;i<=r;i++){
        addhead[i]=0;
        delhead[i]=0;
    }

    addcnt=1;
    delcnt=1;

    // 当前版本每层重建当前线段树
    build(l,mid,1);

    // 左半边固定i，计算i在哪些j时上线/下线
    compute_lt(l,mid,r);

    // 右半边扫描j，在线段树中查询合法i
    compute_rt(l,mid,r);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }

    int mid=(l+r)>>1;

    // 先算左半边dp
    cdq(l,mid);

    // 用左半边dp更新右半边dp
    compute(l,mid,r);

    // 再算右半边内部dp
    cdq(mid+1,r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>c[i]>>d[i];
    }

    for(int i=0;i<=n;i++){
        maxdp[i]=-INF;
        alldp[i]=0;
    }

    maxdp[0]=0;
    alldp[0]=1;

    cdq(0,n);

    if(maxdp[n]<0){
        cout<<"NIE"<<endl;
    }
    else{
        cout<<maxdp[n]<<' '<<alldp[n]<<endl;
    }

    return 0;
}