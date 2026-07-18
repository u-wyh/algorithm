// 不同名字数量，C++版
// 一共有n个节点，编号1~n，给定每个节点的名字和父亲节点编号
// 名字是string类型，如果父亲节点编号为0，说明当前节点是某棵树的头节点
// 注意，n个节点组成的是森林结构，可能有若干棵树
// 一共有m条查询，每条查询 x k，含义如下
// 以x为头的子树上，到x距离为k的所有节点中，打印不同名字的数量
// 1 <= n、m <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/CF246E
// 测试链接 : https://codeforces.com/problemset/problem/246/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的大思路是借助set去重
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;

unordered_map<string, int> nameId;
bool root[MAXN];//判断这个节点是不是头结点
int id[MAXN];//这个节点的文本名字转换回来的数字编号

// 链式前向星建图连边
int headg[MAXN];
int nextg[MAXN];
int tog[MAXN];
int cntg;

// 问题列表
int headq[MAXN];
int nextq[MAXN];
int ansiq[MAXN];
int kq[MAXN];
int cntq;

// 树链剖分
int fa[MAXN];
int siz[MAXN];
int dep[MAXN];
int son[MAXN];

// 树上启发式合并
vector<unordered_set<int>> depSet;//表示在层数为i的不同名字的个数 set自动去重了
int ans[MAXN];

//输入一个名字 返回名字的编号
//如果之前已经存在这个名字 那么直接返回编号即可
//如果不存在 那么新加入进去  并返回编号
int getNameId(const string &name) {
    if (nameId.find(name) != nameId.end()) {
        return nameId[name];
    }
    int newId = nameId.size() + 1;
    nameId[name] = newId;
    return newId;
}

//在deep层 加入一个id
void addId(int deep, int id) {
    depSet[deep].insert(id);
}

//在deep层 删除一个id
void removeId(int deep, int id) {
    depSet[deep].erase(id);
}

//统计deep层的去重后的答案
int sizeOfDeep(int deep) {
    if (deep > n) {
        return 0;
    }
    return (int)depSet[deep].size();
}

void addEdge(int u, int v) {
    nextg[++cntg] = headg[u];
    tog[cntg] = v;
    headg[u] = cntg;
}

void addQuestion(int u, int ansi, int k) {
    nextq[++cntq] = headq[u];
    ansiq[cntq] = ansi;
    kq[cntq] = k;
    headq[u] = cntq;
}

//树链剖分  统计sz  dep son等信息
void dfs1(int u, int f) {
    fa[u] = f;
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        dfs1(tog[e], u);
    }
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        siz[u] += siz[v];
        if (son[u] == 0 || siz[son[u]] < siz[v]) {
            son[u] = v;
        }
    }
}

void effect(int u) {
    addId(dep[u], id[u]);
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        effect(tog[e]);
    }
}

void cancle(int u) {
    removeId(dep[u], id[u]);
    for (int e = headg[u]; e > 0; e = nextg[e]) {
        cancle(tog[e]);
    }
}

void dfs2(int u, int keep) {
    //先去轻儿子
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            dfs2(v, 0);
        }
    }
    //再去重儿子
    if (son[u] != 0) {
        dfs2(son[u], 1);
    }
    //计算这个节点的贡献
    addId(dep[u], id[u]);
    //回收轻儿子
    for (int e = headg[u], v; e > 0; e = nextg[e]) {
        v = tog[e];
        if (v != son[u]) {
            effect(v);
        }
    }
    for (int i = headq[u]; i > 0; i = nextq[i]) {
    	ans[ansiq[i]] = sizeOfDeep(dep[u] + kq[i]);//统计这个深度的节点个数
    }
    if (keep == 0) {
        cancle(u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    string name;
    int father;
    for (int i = 1; i <= n; i++) {
        cin >> name >> father;
        id[i] = getNameId(name);
        if (father == 0) {
        	root[i] = true;//表示是头结点
        } else {
            addEdge(father, i);//否则连边
        }
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            //从每棵树的头结点开始树链剖分
            dfs1(i, 0);
        }
    }
    depSet.resize(n + 1);
    cin >> m;
    for (int i = 1, node, k; i <= m; i++) {
        cin >> node >> k;
        addQuestion(node, i, k);//问题建图
    }
    for (int i = 1; i <= n; i++) {
        if (root[i]) {
            //计算答案
            dfs2(i, 0);
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}