#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300001;

int cnt = 0;
int head = 0;
int key[MAXN];
int key_count[MAXN];
int ls[MAXN];
int rs[MAXN];
int size[MAXN];
double priority[MAXN];

void up(int i) {
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
}

int leftRotate(int i) {
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
    up(i);
    up(r);
    return r;
}

int rightRotate(int i) {
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

int add(int i, int num) {
    if (i == 0) {
        key[++cnt] = num;
        key_count[cnt] = size[cnt] = 1;
        priority[cnt] = static_cast<double>(rand()) / RAND_MAX;
        return cnt;
    }
    if (key[i] == num) {
        key_count[i]++;
    } else if (key[i] > num) {
        ls[i] = add(ls[i], num);
    } else {
        rs[i] = add(rs[i], num);
    }
    up(i);
    if (ls[i] != 0 && priority[ls[i]] > priority[i]) {
        return rightRotate(i);
    }
    if (rs[i] != 0 && priority[rs[i]] > priority[i]) {
        return leftRotate(i);
    }
    return i;
}

void add(int num) {
    head = add(head, num);
}

int small(int i, int num) {
    if (i == 0) {
        return 0;
    }
    if (key[i] >= num) {
        return small(ls[i], num);
    } else {
        return size[ls[i]] + key_count[i] + small(rs[i], num);
    }
}

int getRank(int num) {
    return small(head, num) + 1;
}

int index(int i, int x) {
    if (size[ls[i]] >= x) {
        return index(ls[i], x);
    } else if (size[ls[i]] + key_count[i] < x) {
        return index(rs[i], x - size[ls[i]] - key_count[i]);
    }
    return key[i];
}

int index(int x) {
    return index(head, x);
}

int pre(int i, int num) {
    if (i == 0) {
        return INT_MIN;
    }
    if (key[i] >= num) {
        return pre(ls[i], num);
    } else {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num) {
    return pre(head, num);
}

int post(int i, int num) {
    if (i == 0) {
        return INT_MAX;
    }
    if (key[i] <= num) {
        return post(rs[i], num);
    } else {
        return min(key[i], post(ls[i], num));
    }
}

int post(int num) {
    return post(head, num);
}

int remove(int i, int num) {
    if (key[i] < num) {
        rs[i] = remove(rs[i], num);
    } else if (key[i] > num) {
        ls[i] = remove(ls[i], num);
    } else {
        if (key_count[i] > 1) {
            key_count[i]--;
        } else {
            if (ls[i] == 0 && rs[i] == 0) {
                return 0;
            } else if (ls[i] != 0 && rs[i] == 0) {
                i = ls[i];
            } else if (ls[i] == 0 && rs[i] != 0) {
                i = rs[i];
            } else {
                if (priority[ls[i]] >= priority[rs[i]]) {
                    i = rightRotate(i);
                    rs[i] = remove(rs[i], num);
                } else {
                    i = leftRotate(i);
                    ls[i] = remove(ls[i], num);
                }
            }
        }
    }
    up(i);
    return i;
}

void remove(int num) {
    if (getRank(num) != getRank(num + 1)) {
        head = remove(head, num);
    }
}

void clear() {
    fill(key + 1, key + cnt + 1, 0);
    fill(key_count + 1, key_count + cnt + 1, 0);
    fill(ls + 1, ls + cnt + 1, 0);
    fill(rs + 1, rs + cnt + 1, 0);
    fill(size + 1, size + cnt + 1, 0);
    fill(priority + 1, priority + cnt + 1, 0);
    cnt = 0;
    head = 0;
}

struct node{
    int l,r,k,id;
}nums[50005];
int ans[50005];

bool cmp(node a,node b){
    return a.l==b.l?a.r<b.r:a.l<b.l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    int n,m;
    cin >> n>>m;
    int arr[n+1];
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].l>>nums[i].r>>nums[i].k;
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int l=nums[1].l,r=nums[1].l-1;
    for(int i=1;i<=m;i++){
        while(l<nums[i].l){
            remove(arr[l]);
            l++;
        }
        while(r>nums[i].r){
            remove(arr[r]);
            r--;
        }
        while(r<nums[i].r){
            add(arr[++r]);
        }
        ans[nums[i].id]=index(nums[i].k);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}

