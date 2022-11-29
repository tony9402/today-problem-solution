/* 
 * 이 문제는 DP로 풀고 출력하는 방식으로 풀 수도 있지만
 * N이 작기 때문에 그냥 돌리면 된다.
 * 시간복잡도로 생각을 해보면 N * 3 ^ N이 걸리고 N이 최대 11이기 때문에
 * O(N*3^N) => 1948617으로 1초 안에 돌 수 있다.
 * 
 * 
 * 제한시간 : 1s
 * 시간복잡도 : O(N*3^N)
 */
#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> answer_list;
vector<int> used;
// 가능한 모든 경우를 선택하자.
// cnt : 현재까지 사용한 수(1, 2, 3)의 개수
// sum : N - (현재까지 선택한 수들의 총 합)
void dfs(int cnt, int sum) {
    if(sum == 0) {
        answer_list.push_back(used);
        return;
    }

    // k(1≤k≤3인 정수)를 선택하는 경우
    for(int k = 1; k <= 3; ++k) {
        if(sum >= k) {
            used.push_back(k);
            dfs(cnt + 1, sum - k);
            used.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int N, K; cin >> N >> K;

    dfs(0, N);
    // 답은 K번째에 있다. 하지만, 선택한 조합의 개수가 K보다 크다면 -1을 출력하면 된다.
    sort(answer_list.begin(), answer_list.end());
    if(K > (int)answer_list.size()) cout << -1;
    else {
        cout << answer_list[K - 1][0];
        for(int i = 1; i < (int)answer_list[K - 1].size(); ++i)
            cout << "+" << answer_list[K - 1][i];
    }

    return 0;
}