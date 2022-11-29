/*
 * 이 문제는 풀이가 여러가지가 존재한다.
 * 예를 들어, 해당 문제를 단방향 그래프로 그려 A에서 
 * 어떤 노드까지 도달할 수 있는지 물어보는 문제로 변경할 수 있다.
 * 
 * 또는 이 문제는 Floyd 알고리즘을 변형하여 O(N^3)으로도 풀 수 있다.
 * 
 * 해당 솔루션은 단뱡항 그래프로 만들어 탐색하는 풀이이다.
 * 탐색은 DFS나 BFS 둘다 상관없다.
 * 
 * 
 * 시간제한 : 2s
 * 시간복잡도 : O(NM)
 */
#include<bits/stdc++.h>

using namespace std;

vector<int> G[26];
int used[26];

void dfs(int cur) {
    used[cur] = 1;
    for(int nxt : G[cur]) {
        if(used[nxt]) continue;
        dfs(nxt);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    for(int i = 0; i < N; ++i) {
        char A, B;
        string is;
        cin >> A >> is >> B;
        G[A - 'a'].push_back(B - 'a');
    }

    int M; cin >> M;
    for(int i = 0; i < M; ++i) {
        char A, B;
        string is;
        cin >> A >> is >> B;
        for(int j = 0; j < 26; ++j) used[j] = 0;
        dfs(A - 'a');
        cout << (used[B - 'a'] ? 'T' : 'F') << '\n';
    }
    
    return 0;
}