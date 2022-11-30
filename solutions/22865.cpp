/*
 * 내가 만든 문제다.
 * 해당 문제는 "다익스트라"를 공부한 사람이면 이 문제는 다익스트라인 것을 케치할 수 있을 것이다.
 * 물론 풀이가 바로 보일 순 없을 수도 있다.
 * 
 * 이 문제는 A, B, C에서 시작하는 다익스트라를 돌려서 나온 dist 배열을 가지고 계산을 해도 되지만,
 * 다익스트라를 한번만 돌리고 구할수도 있다.
 * 
 * 항상 이런 문제는 값의 최대가 몇인지 계산해볼 필요가 있다.
 * 정점 1번부터 정점 N번까지 일직선으로 쭉 나열되어 있고, 
 * 각 정점을 잇는 간선의 가중치가 10,000이라고 했을 때, 값이 최대가 될 것이다.
 * 
 * N * L = 10 ^ 5 * 10 ^ 4 = 10 ^ 9
 * 정점 1에서 출발할 때 가장 먼 곳까지의 거리는 10 ^ 9이라 int로 표현가능하지만,
 * 친구 A, B, C가 정점 1에 살때 가장 먼 곳의 거리는 3 * 10 ^ 9라 int를 벗어날 수 있다. 
 * 
 * 시간제한 : 1.5s
 * 시간복잡도 : O(MlogN)
 */
#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> G[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    int A, B, C; cin >> A >> B >> C;
    int M; cin >> M;
    // 문제에서 주어지는 그래프가 아래 중 어떤 것인지 확인해봐야한다.
    //  - 단뱡향 그래프인지?
    //  - 양방향 그래프인지?
    //   해당 문제는 양방향 그래프이다.
    for(int i = 0; i < M; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    
    priority_queue<pair<int, int>> pq;
    const int INF = 1 << 30;
    // 1-based로 구현하고 있음을 잊어서 안된다.
    // 또는 배열크기를 넉넉히 줘도 되긴 하지만..
    vector<int> dist(N + 1, INF);

    for(int x : {A, B, C}) {
        dist[x] = 0;
        pq.emplace(-dist[x], x);
    }
    while(!pq.empty()) {
        auto [d, cur] = pq.top(); pq.pop();
        if(dist[cur] != -d) continue;
        for(auto [nxt, W]: G[cur]) {
            if(dist[nxt] > dist[cur] + W) {
                dist[nxt] = dist[cur] + W;
                pq.emplace(-dist[nxt], nxt);
            }
        }
    }
    
    int mx = 0, ans = 0;
    for(int i = 1; i <= N; ++i) {
        if(mx < dist[i]) {
            mx = dist[i];
            ans = i;
        }
    }
    cout << ans;
    
    return 0;
}
