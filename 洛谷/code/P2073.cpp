#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXL = 20;
//这个值的选取是 2的MAXL次方 是  最接近大于MAXN的最小值
const int MAXN = 100001;

int cnt;//用于记录节点编号 和AVL一样
int key[MAXN];//用于记录当前节点对应的键值是多少
int key_count[MAXN];//用于记录当前值出现了多少次
int level[MAXN];//用于记录该节点最多有多少层   初始时随机生成
int next_node[MAXN][MAXL + 1];//用于记录该节点的第i层指向的下一个节点是什么
int len[MAXN][MAXL + 1];//记录该节点的第i层到下一个数字之间有多少个数字  对应第一层的数字个数  左开右闭
int val[MAXN];
int realcnt=0;

void build() {
    cnt = 1;
    key[cnt] = INT_MIN;//第一个节点的编号永远记1
    level[cnt] = MAXL;//它的层数直接设置为最多层
    val[1]=0;
}
//初始化表头  整张表 越往右 值越大

int randomLevel() {
    //随机生成新节点的层数值 并且永远不会更改
    int ans = 1;
    while ((std::rand() / double(RAND_MAX)) < 0.5) {
        ans++;
    }
    return min(ans, MAXL);
}

int find(int i, int h, int num) {
    while (next_node[i][h] != 0 && key[next_node[i][h]] < num) {
        i = next_node[i][h];
    }
    if (h == 1) {
        if (next_node[i][h] != 0 && key[next_node[i][h]] == num) {
            return next_node[i][h];
        } else {
            return 0;
        }
    }
    return find(i, h - 1, num);
}

int addNode(int i, int h, int j) {
    int rightCnt = 0;
    //用于统计i节点到  下一个节点大于等于key[j] 的节点中间距离
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        rightCnt += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        next_node[j][h] = next_node[i][h];
        next_node[i][h] = j;
        len[j][h] = key_count[next_node[j][h]];//直接就是词频  因为这是最底层
        len[i][h] = key_count[next_node[i][h]];//这个地方也可以是1   毕竟这是新建节点  一定是1
        return rightCnt;
    } else {
        int downCnt = addNode(i, h - 1, j);
        if (h > level[j]) {
            len[i][h]++;
        } else {
            next_node[j][h] = next_node[i][h];
            next_node[i][h] = j;
            len[j][h] = len[i][h] + 1 - downCnt - key_count[j];
            len[i][h] = downCnt + key_count[j];
        }
        return rightCnt + downCnt;
    }
}

// 增加num，重复加入算多个词频
void add(int num,int k) {
    if (find(1, MAXL, num) != 0) {
        return ;
    } else {
        realcnt++;
        key[++cnt] = num;
        key_count[cnt] = 1;
        level[cnt] = randomLevel();
        val[cnt]=k;
        addNode(1, MAXL, cnt);
    }
}

// 当前在i号节点的h层，删除空间编号为j的节点
void removeNode(int i, int h, int j) {
    if (h < 1) {
        return;
    }
    while (next_node[i][h] != 0 && key[next_node[i][h]] < key[j]) {
        i = next_node[i][h];
    }
    if (h > level[j]) {
        len[i][h]--;
    } else {
        next_node[i][h] = next_node[j][h];
        len[i][h] += len[j][h] - 1;
    }
    removeNode(i, h - 1, j);
}

// 删除x，如果有多个，只删掉一个
void remove(int num) {
    int j = find(1, MAXL, num);
    cout<<23<<' '<<num<<endl;
//    if(j!=realcnt&&j!=1){
//        cout<<j<<' '<<num<<endl;
//        system("pause");
//    }
    if (j != 0) {
        removeNode(1, MAXL, j);
        realcnt--;
    }
}

// 当前在i号节点的h层，查询排名第x的key是什么
int index(int i, int h, int x) {
    int c = 0;
    while (next_node[i][h] != 0 && c + len[i][h] < x) {
        c += len[i][h];
        i = next_node[i][h];
    }
    if (h == 1) {
        return key[next_node[i][h]];
    } else {
        return index(i, h - 1, x - c);
    }
}

// 查询排名第x的key是什么
int index(int x) {
    return index(1, MAXL, x);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    build();
    int op;
    cin>>op;
    while(op!=-1){
        if(op==1){
            int x,k;
            cin>>k>>x;
            add(x,k);
        }
        else if(op==2&&realcnt>0){
            cout<<2<<' '<<index(1)<<endl;
            remove(index(1));
        }
        else if(op==3&&realcnt>0){
            cout<<3<<' '<<index(realcnt)<<endl;
            remove(index(realcnt));
        }
        //cout<<' '<<realcnt<<endl;
        cin>>op;
    }
    int ans1=0,ans2=0;
    for(int i=next_node[1][1];i!=0;i=next_node[i][1]){
        ans1+=val[i];
        ans2+=key[i];
        cout<<key[i]<<' ';
    }
    cout<<endl;
    printf("%lld %lld",ans1,ans2);
    return 0;
}

