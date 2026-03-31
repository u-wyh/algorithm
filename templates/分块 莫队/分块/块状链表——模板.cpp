// 文本编辑器，块状链表实现，C++版
// 一开始文本为空，光标在文本开头，也就是1位置，请实现如下6种操作
// Move k     : 将光标移动到第k个字符之后，操作保证光标不会到非法位置
// Insert n s : 在光标处插入长度为n的字符串s，光标位置不变
// Delete n   : 删除光标后的n个字符，光标位置不变，操作保证有足够字符
// Get n      : 输出光标后的n个字符，光标位置不变，操作保证有足够字符
// Prev       : 光标前移一个字符，操作保证光标不会到非法位置
// Next       : 光标后移一个字符，操作保证光标不会到非法位置
// Insert操作时，字符串s中ASCII码在[32,126]范围上的字符一定有n个，其他字符请过滤掉
// 测试链接 : https://www.luogu.com.cn/problem/P4008
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3000001;// 整个文章能到达的最大长度
const int BLEN = 3001;// 块内容量，近似等于 2 * 根号n，每块内容大小不会超过容量
const int BNUM = (MAXN / BLEN) << 1;// 块的数量上限

// 写入内容的空间，编号为i的块，内容写入到space[i]
char space[BNUM][BLEN];
// 编号分配池，其实是一个栈，分配编号从栈顶弹出，回收编号从栈顶压入
int pool[BNUM];
// 分配池的栈顶
int top = 0;

// nxt[i]表示编号为i的块，下一块的编号
int nxt[BNUM];
// siz[i]表示编号为i的块，写入了多少长度的内容
int siz[BNUM];

// 插入字符串时，先读入进str，然后写入到块
// 获取字符串时，先从块里取出内容保留在str，然后打印str
char str[MAXN];

// 准备好分配池，从栈顶到栈底，依次是1、2、... BNUM - 1
// 准备好头块的配置
void prepare() {
    for (int i = 1, id = BNUM - 1; i < BNUM; i++, id--) {
        pool[i] = id;
    }
    top = BNUM - 1;
    siz[0] = 0;
    nxt[0] = -1;
}

// 分配编号
int assign() {
    return pool[top--];
}

// 回收编号
void recycle(int id) {
    pool[++top] = id;
}

// 寻找整个文章中的pos位置
// 找到所在块的编号 和 块内位置
// 块编号设置给bi，块内位置设置给pi
int bi, pi;

void find(int pos) {
    int curb = 0;
    while (curb != -1 && pos > siz[curb]) {
        pos -= siz[curb];
        curb = nxt[curb];
    }
    bi = curb;//找到所在块编号
    pi = pos;//确定在所在块内的位置
}

// 链表中让curb块和nextb块，连在一起，然后让nextb块从0位置开始，写入如下的内容
// 从src[pos]开始，拿取长度为len的字符串
//这个nextb一定是空的
void linkAndWrite(int curb, int nextb, char* src, int pos, int len) {
    nxt[nextb] = nxt[curb];
    nxt[curb] = nextb;
    memcpy(space[nextb], src + pos, len);
    siz[nextb] = len;
}

// curb块里，在内容的后面，追加nextb块的内容，然后nextb块从链表中删掉
void merge(int curb, int nextb) {
    memcpy(space[curb] + siz[curb], space[nextb], siz[nextb]);
    siz[curb] += siz[nextb];
    nxt[curb] = nxt[nextb];
    recycle(nextb);
}

// curb块的pos位置往后的内容，写入到新分裂出的块里
void split(int curb, int pos) {
    if (curb == -1 || pos == siz[curb]) return;
    int nextb = assign();
    linkAndWrite(curb, nextb, space[curb], pos, siz[curb] - pos);
    siz[curb] = pos;
}

// 从头到尾遍历所有的块，检查任意相邻块，内容大小的累加和 <= 块内容量，就合并
void maintain() {
    for (int curb = 0, nextb; curb != -1; curb = nxt[curb]) {
        nextb = nxt[curb];
        while (nextb != -1 && siz[curb] + siz[nextb] <= BLEN) {
            merge(curb, nextb);
            nextb = nxt[curb];
        }
    }
}

// 插入的字符串在str中，长度为len，从整个文章的pos位置插入
void insert(int pos, int len) {
    find(pos);
    split(bi, pi);
    int curb = bi, newb, done = 0;
    while (done + BLEN <= len) {
        newb = assign();
        linkAndWrite(curb, newb, str, done, BLEN);
        done += BLEN;
        curb = newb;
    }
    if (len > done) {
        newb = assign();
        linkAndWrite(curb, newb, str, done, len - done);
    }
    maintain();
}

// 从整个文章的pos位置，往后len的长度，这些内容删掉
void erase(int pos, int len) {
    find(pos);
    split(bi, pi);
    int curb = bi;
    int nextb = nxt[curb];
    while (nextb != -1 && len > siz[nextb]) {
        len -= siz[nextb];
        recycle(nextb);
        nextb = nxt[nextb];
    }
    if (nextb != -1) {
        split(nextb, len);
        recycle(nextb);
        nxt[curb] = nxt[nextb];
    } else {
        nxt[curb] = -1;
    }
    maintain();
}

// 从整个文章的pos位置，往后len的长度，这些内容找到，写入进str
void get(int pos, int len) {
    find(pos);
    int curb = bi;
    pos = pi;
    int done = (len < siz[curb] - pos) ? len : (siz[curb] - pos);
    memcpy(str, space[curb] + pos, done);//首先将需要复制的、出现在这一块中的文字先复制进去
    curb = nxt[curb];
    while (curb != -1 && done + siz[curb] <= len) {
        //只要长度不够 那么就将接下来的块也全都复制进去
        memcpy(str + done, space[curb], siz[curb]);
        done += siz[curb];
        curb = nxt[curb];
    }
    if (curb != -1 && done < len) {
        memcpy(str + done, space[curb], len - done);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int pos = 0, len;
    char op[10];
    prepare();
    for (int i = 1; i <= n; i++) {
        cin >> op;
        if (op[0] == 'P') {
            pos--;
        } else if (op[0] == 'N') {
            pos++;
        } else if (op[0] == 'M') {
            cin >> pos;
        } else if (op[0] == 'I') {
            cin >> len;
            for (int j = 0; j < len; ) {
                char ch = cin.get();
                if (32 <= ch && ch <= 126) {
                    str[j++] = ch;
                }
            }
            insert(pos, len);
        } else if (op[0] == 'D') {
            cin >> len;
            erase(pos, len);
        } else {
            cin >> len;
            get(pos, len);
            cout.write(str, len);
            cout.put('\n');
        }
    }
    return 0;
}