#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define MAX 100001

/*
어떻게 풀어야 할지 막막했는데,
연속된 수여야 하고, 중복되는 수는 없기 때문에,
최대값, 최소값을 사용하면 된다.

6개인데 최소값 : 3 최대값 : 8 이라면 3~8이 모두 있는 것이다.
*/

int loc[MAX];
vector<pii> segTree;

pii init(int node, int s, int e) {
    if (s == e)
        return segTree[node] = {s, s};
    int mid = (s + e) / 2;
    auto l = init(node*2, s, mid);
    auto r = init(node*2 + 1, mid + 1, e);
    return segTree[node] = {min(l.first,r.first), max(l.second, r.second)};
}

pii getMinMax(int node, int s, int e, int left, int right){
    if (left > e || right < s)
        return {1e9,0};  // 답에 영향을 받지 않는 값으로
    if (left <= s && right >= e)
        return segTree[node];
    int mid = (s + e) / 2;
    auto l = getMinMax(node*2, s, mid, left, right);
    auto r = getMinMax(node*2 + 1, mid + 1, e, left, right);
    return {min(l.first, r.first), max(l.second, r.second)};
}

pii update(int node, int s, int e, int idx, int num) {
    if (idx < s || idx > e) return segTree[node];
    if (s == e) return segTree[node] = {num, num};
    int mid = (s + e) >> 1;
    pii left = update(2 * node, s, mid, idx, num);
    pii right = update(2 * node + 1, mid + 1, e, idx, num);
    return segTree[node] = {min(left.first, right.first), max(left.second, right.second)};
}

void solve(){
    int N, K;
    cin >> N >> K;

    // 트리의 크기
    int h = ceil(log2(N));  // ceil : 정수로 올림
    int treeSize = 1 << (h + 1);
    segTree = vector<pii>(treeSize);

    // 트리 생성
    init(1, 0, N-1);

    // 현재 위치를 반환해주는 배열 초기화
    for (int i = 0; i < N; i++) loc[i] = i;

    for (int i=0; i<K; i++){
        int Q, A, B;
        cin >> Q >> A >> B;
        if (Q==0){  // A와 B 바꾸기
            update(1, 0, N-1, loc[A], B);  // A의 위치에 B를 넣기
            update(1, 0, N-1, loc[B], A);  // B의 위치에 A를 넣기
            swap(loc[A], loc[B]);  // A, B 위치 업데이트
        }
        else {  // A~B 선반에 있는 DVD가 A~B인가? (순서 상관 X)
            // 최소값이 A, 최대값이 B가 나와야함
            auto [mini, maxi] = getMinMax(1, 0, N-1, A, B);
            if (mini==A && maxi==B) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    
    return 0;
}