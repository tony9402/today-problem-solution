/*
 * N이 20인 것을 확인하자.
 * i번째 원소를 선택하고 안하고 경우의 수는 2가지이고 이게 N개가 있기 때문에
 * O(2^N)의 시간복잡도로 모든 부분 수열을 선택할 수 있다.
 * 
 * 이렇게 뽑힌 부분 수열을 가지고 1부터 시작하여 수가 없는지 확인하면 된다.
 * S를 이루고있는 수는 최대 100,000이다.
 * 그러면 수열의 총합은 2,000,000이기 때문에 배열 크기를 2,000,000로 잡고
 * 해당 수가 존재하는지 기록을 한 후에 1부터 2,000,000까지 탐색하면 된다.
 * 
 * !! 부분 수열의 "합"인 것을 놓치지 말자....
 * 
 * 시간제한 : 1s
 * 시간복잡도 : O(K2^N)
 */
#include<bits/stdc++.h>

using namespace std;

int arr[21], N;
// 최대 2,000,000 + 1를 잡아도 되지만, 답이 2,000,001일 수 있다는 가정하에 +1을 더 해도 좋다.
// 물론 나올 수 있는 최댓값을 계산을 했다면, 그 값으로 해도 좋다.
int check[2000002];

// 수열에서 가능한 모든 합을 구한다.
void dfs(int cnt, int idx, int sum) {
    if(idx == N) {
        check[sum] = 1;
        return;
    }
    dfs(cnt + 1, idx + 1, sum + arr[idx]);
    dfs(cnt, idx + 1, sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> N;
    for(int i = 0; i < N; ++i) cin >> arr[i];

    dfs(0, 0, 0);
    // k는 1부터 시작하여 하나씩 보면 된다.
    for(int k = 1; ; ++k) {
        if(!check[k]) {
            cout << k;
            return 0;
        }
    }

    return 0;
}