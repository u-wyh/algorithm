#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1<<24;

int st[13];
int nums[13][4];
int tmp[13];
int sta[MAXN];
int fa[MAXN];
int from[MAXN];

int nums1[MAXN],cnt1;
int nums2[MAXN],cnt2;
int lt,rt,tl,tr;
bool flag;
int start,over;
deque<int>ans;

inline int compress(int *nums){
    int val=0;
    for(int i=1;i<=12;i++){
        val += nums[i] * (1 << (2*(i-1)));
    }
    return val;
}

void bfs(int val, int op){
    int arr[13], temp[13];
    for(int i=1; i<=12; i++){
        arr[i] = (val >> (2*(i-1))) & 3;
        temp[i] = arr[i];
    }
    if(op == 1){
        for(int i=1; i<=12; i++){
            int original = temp[i];
            temp[i] = (temp[i] + 1) % 4;
            int u = nums[i][original];
            temp[u] = (temp[u] + 1) % 4;
            int num = compress(temp);
            if(sta[num] == 0){
                sta[num] = 1;
                fa[num] = val;
                from[num] = i;
                nums1[++cnt1] = num;
            } else if(sta[num] == 2){
                ans.push_back(i);
                flag = true;
                start = val;
                over = num;
                return;
            }
            temp[i] = original;
            temp[u] = (temp[u] + 3) % 4;
        }
    } else {
        for(int i=1; i<=12; i++){
            int j = temp[i];
            int prev_j = (j - 1 + 4) % 4;
            int u = nums[i][prev_j];
            
            temp[i] = prev_j;
            temp[u] = (temp[u] - 1 + 4) % 4;
            int num = compress(temp);
            
            if(sta[num] == 0){
                sta[num] = 2;
                fa[num] = val;
                from[num] = i;
                nums2[++cnt2] = num;
            } else if(sta[num] == 1){
                ans.push_back(i);
                flag = true;
                start = num;
                over = val;
                return;
            }
            temp[i] = j;
            temp[u] = (temp[u] + 1) % 4;
        }
    }
}

void compute(){
    lt=rt=tl=tr=1;
    while(true){
        for(int i=lt; i<=rt; i++){
            bfs(nums1[i], 1);
            if(flag) return;
        }
        lt=rt+1; rt=cnt1;
        
        for(int i=tl; i<=tr; i++){
            bfs(nums2[i], 2);
            if(flag) return;
        }
        tl=tr+1; tr=cnt2;
    }
}

int main(){
    for(int i=1; i<=12; i++){
        cin >> st[i];
        for(int j=0; j<4; j++){
            cin >> nums[i][j];
        }
        st[i]--;
    }
    int val = compress(st);
    nums1[++cnt1] = val;
    sta[val] = 1;
    fa[val] = -1;
    nums2[++cnt2] = 0;
    sta[0] = 2;
    fa[0] = -1;
    
    compute();
    
    while(start != val){
        ans.push_front(from[start]);
        start = fa[start];
    }
    while(over != 0){
        ans.push_back(from[over]);
        over = fa[over];
    }
    
    cout << ans.size() << endl;
    while(!ans.empty()){
        cout << ans.front() << ' ';
        ans.pop_front();
    }
    return 0;
}