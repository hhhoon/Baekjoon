#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define MAX 1'000'001

/*
세그먼트 트리로 버블소트할때 swap이 몇번 발생할지
swap의 개수 : 자신보다 작은 수의 개수

pair을 사용하여 second에 인덱스를 찾는다.
*/

int N;
pair<ll,ll> arr[MAX];
vector<ll> segTree;

// i > j를 만족하는 것의 개수만 카운트
ll query(int node, int start, int end, int left, int right){
    if (left > end || right < start)
        return 0;
    if (left <= start && right >= end)
        return segTree[node];
    int mid = (start + end) / 2;
    return query(node*2, start, mid, left, right) 
    + query(node*2 + 1, mid + 1, end, left, right);
}

// 카운트 후 업데이트
void update(int node, int start, int end, int idx){
    if (start==end){
        segTree[node] = 1;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx);
    else update(2 * node + 1, mid + 1, end, idx);
    segTree[node] = segTree[2*node] + segTree[2*node+1];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> N;

    // 트리의 크기
    int h = ceil(log2(N));  // ceil : 정수로 올림
    int treeSize = 1 << (h + 1);
    segTree.resize(treeSize);

    for (int i=0; i<N; i++){
        int num;
        cin >> num;
        arr[i] = {num, i};
    }

    sort(arr, arr+N);

    // i > j이면서 arr[i] < arr[j]인 쌍의 개수
    ll ans = 0;
    for (int i=0; i<N; i++){
        int idx = arr[i].second;
        ans += query(1, 0, N-1, idx+1, N-1);
        update(1, 0, N-1, idx);
    }
    cout << ans;
    
    return 0;
}