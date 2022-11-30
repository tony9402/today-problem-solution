/*
 * (a, b)와 (c, d)가 있을 때 a > c and b > d인 개수를 구하면 된다.
 * N이 작기 때문에 O(N^2)만에 정답을 구 할 수 있다.
 * 
 * 시간제한 : 1s
 * 시간복잡도 : O(N^2)
 */
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<pair<int, int>> V(N);
    for(auto &[a, b] : V) cin >> a >> b;

    for(int i = 0; i < N; ++i) {
        int cnt = 0;
        auto [a, b] = V[i];
        for(int j = 0; j < N; ++j) {
            // c > a and d > b인 경우를 세자
            auto [c, d] = V[j];
            if(c > a && d > b) ++cnt;
        }
        cout << cnt + 1 << ' ';
    }

    return 0;
}