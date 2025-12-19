#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300001;
int head = 0;
int cnt = 0;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
double priority[MAXN];
int limit;
int enter=0;
int change=0;

//没有词频压缩  所以出现次数就是1
void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + 1;
}

void split(int l, int r, int i, int num) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (key[i] <= num) {
            rs[l] = i;
            split(i, r, rs[i], num);
        } else {
            ls[r] = i;
            split(l, i, ls[i], num);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

//没有词频压缩  直接就是新增节点
void add(int num) {
    split(0, 0, head, num);
    key[++cnt] = num;
    size[cnt] = 1;
    priority[cnt] = (double)rand() / RAND_MAX;
    head = merge(merge(rs[0], cnt), ls[0]);
}

//删除节点的时候 是将树按照num分裂  然后将<=num 的按照 num-1 分裂
//将那么 >num-1 的树头结点一定是num  只要将这个节点忽略就是删除节点
void remove(int num) {
    split(0, 0, head, num);
    int lm = rs[0];
    int r = ls[0];
    split(0, 0, lm, num - 1);
    int l = rs[0];
    int m = ls[0];
    head = merge(merge(l, merge(ls[m], rs[m])), r);
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + 1 < x) {
        return index(rs[i], x - size[ls[i]] - 1);
    } else {
        return key[i];
    }
}

int index(int x) {
    return index(head, x);
}

void departure(){
    int num=limit-change-1;
    //cout<<num<<' ';
    split(0,0,head,num);
    int r;
    r=ls[0];
    head=r;
    up(head);

}

void print(int x){
    cout<<key[x]<<' ';
    if(ls[x]){
        print(ls[x]);
    }
    if(rs[x]){
        print(rs[x]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n;
    cin >> n>>limit;
    for(int i=1;i<=n;i++){
        char op;
        int x;
        cin>>op>>x;
        if(op=='I'){
            if(x>=limit){
                add(x-change);
                enter++;
            }
        }
        else if(op=='A'){
            change+=x;
        }
        else if(op=='S'){
            change-=x;
            departure();
        }
        else{
            print(head);
            cout<<change<<' '<<size[head] - x + 1<<' ';
            cout<<endl;
            if(x>size[head]){
                cout<<-1<<endl;
            }
            else{
                //cout<<777<<endl;
                cout << index(size[head] - x + 1) + change << endl;
            }
        }
    }
    cout<<enter-size[head]<<endl;
    return 0;
}
/*
20 0
I 4
F 1

I 6
S 9
F 14

I 6
I 7
A 8
I 3
F 2


I 9
I 6
I 6
S 3
S 5
I 6
F 1


I 3
A 2
F 5

*/

