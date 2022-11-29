/*
 * 이 문제는 풀이가 여러가지가 존재한다.
 * 예를 들어, 해당 문제를 단방향 그래프로 그려 A에서 
 * 어떤 노드까지 도달할 수 있는지 물어보는 문제로 변경할 수 있다.
 * 
 * 또는 이 문제는 Floyd 알고리즘을 변형하여 O(N^3)으로도 풀 수 있다.
 * 
 * 해당 솔루션은 Floyd 알고리즘을 변형한 O(N^3) 풀이다.
 * 
 * 
 * 시간제한 : 2s
 * 시간복잡도 : O(N^3 + M)
 */
#include<bits/stdc++.h>

using namespace std;

int DP[26][26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        char A, B;
        string is;
        cin >> A >> is >> B;
        DP[A - 'a'][B - 'a'] = 1;
    }

    for(int k = 0; k < 26; ++k) {
        for(int i = 0; i < 26; ++i) {
            for(int j = 0; j < 26; ++j) {
                DP[i][j] |= DP[i][k] & DP[k][j];
            }
        }
    }
    
    // M개의 질의(쿼리)
    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        char A, B;
        string is;
        cin >> A >> is >> B;
        cout << (DP[A - 'a'][B - 'a'] ? 'T' : 'F') << '\n';
    }

    return 0;
}