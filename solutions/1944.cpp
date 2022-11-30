/*
 * 해당 문제는 S와 K 또는 K와 K 사이의 이동할 수 있는 거리를 미리 구한 후에 MST를 돌려도 된다.
 * 이때, S와 K는 하나로 간주해도 된다.
 * 
 * 가장 간단한 방법을 생각해보자. 
 * S를 K로 치환하여 K의 최대 개수를 생각해보면 |K| = N ^ 2이다.
 * N은 50으로 N ^ 2 가지의 최단거리를 구하는 것은 오래 걸리지 않는다.
 * 
 * 이 시간복잡도를 계산을 해보면, O(N ^ 2 * N) => O(N^3)이 걸리고
 * N이 50이기 때문에 O(N^3)이 약 125000번의 연산으로 충분히 돌아간다.
 * 
 * 시간제한 : 2s
 * 시간복잡도 : O(M^2N + M^2logM^2 + M^2) = O(M^2(N + 2logM + 1))
 * 
 *  find함수의 시간복잡도는 경로압축만 했을 경우 O(logN)이다. 하지만, 모든 경우에서 O(logN)만에 동작하는 것이 아니라 
 *  상수시간에 매우 가깝게 동작한다. 랭크 압축까지 한다면 더더욱 상수에 가까워진다.(정도만 알아도 문제 없다.)
 */
#include<bits/stdc++.h>

using namespace std;

const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

int N, M;
string Map[51];

int DB[51][51], id = -1;
pair<int, int> posDB[251];

// 모든 열쇠(S 포함)간의 최단거리를 구해놓는 배열
int dist[251][251];

// S번의 K(또는 S)에서 출발하여 E번의 K(또는 S)까지의 가는 최단거리
int BFS(int S, int E) {
    queue<pair<int, int>> Q({posDB[S]});
    vector<vector<int>> cur_dist(N, vector<int>(N, -1));
    cur_dist[posDB[S].first][posDB[S].second] = 0;
    while(!Q.empty()) {
        auto [y, x] = Q.front(); Q.pop();
        for(int k = 0; k < 4; ++k) {
            int nexty = y + dy[k];
            int nextx = x + dx[k];
            if(0 > nexty || nexty >= N || 0 > nextx || nextx >= N) continue;
            if(cur_dist[nexty][nextx] != -1) continue;
            if(Map[nexty][nextx]=='1') continue;
            cur_dist[nexty][nextx] = cur_dist[y][x] + 1;
            Q.emplace(nexty, nextx);
        }
    }
    return cur_dist[posDB[E].first][posDB[E].second];
}

// 아래 코드는 크루스칼 알고리즘을 적용하기 위해 만드는 분리집합(disjoint set)이다.
int par[251]; // 반드시 초기화를 해줘야한다. 나는 -1로 초기화 한다.

// 경로 압축만 해줘도 충분하다.
// 랭크를 이용해서 압축을 해줘도 되지만, 이해가 안된다면 경로 압축 또는 랭크를 이용한 압축 둘 중에 하나만 알고 있으면 된다.
int find(int x) {
    if(par[x] < 0) return x;
    // par[x] = find(par[x])는 경로압축을 적용한 것이다.
    //  return find(par[x])는 틀린 것은 아니나, 경로압축을 하는 것이 아니기 때문에
    //  시간복잡도가 최악 O(N)이다.
    return par[x] = find(par[x]);
}

bool merge(int a, int b) {
    a = find(a); b = find(b);
    if(a == b) return false; // 이미 같은 분류에 속했기 때문에 합치지 못한다.
    par[b] = a;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> N >> M;
    for(int i = 0; i < N; ++i) {
        cin >> Map[i];
        for(int j = 0; j < N; ++j) {
            // S와 K를 제외하면 다 숫자이다.
            if(!isdigit(Map[i][j])) {
                DB[i][j] = ++id;
                posDB[id] = make_pair(i, j);
            }
        }
    }

    // K 사이의 거리를 구했다면 이 정보를 이용해서 MST를 돌리자.
    vector<tuple<int, int, int>> edges; // [가중치(i와 j 사이의 최단거리), i, j]
    for(int i = 0; i <= id; ++i) {
        for(int j = i + 1; j <= id; ++j) {
            // i -> j로 가나 j -> i로 가나 거리는 같다.
            dist[i][j] = dist[j][i] = BFS(i, j);
            // -1인 경우는 가지 못하는 경우이다.
            if(dist[i][j] != -1) edges.emplace_back(dist[i][j], i, j);
        }
    }
    // 여기서 edges의 최대 개수는 M*M개이다.

    // 크루스칼 알고리즘은 가중치가 작은 것부터 선택하면 된다.
    // 선택한 간선의 개수가 정점의 개수(여기선 열쇠 + 출발지)의 개수 - 1이면 
    // 모든 K가 사이에 이동할 수 있다는 뜻이고 모든 로봇이 움직인 횟수의 총 합이 된다.

    // par 배열을 반드시 초기화 하는 것을 까먹지 말자.
    for(int i = 0; i <= 250; ++i) par[i] = -1;
    sort(edges.begin(), edges.end());
    int ans = 0, cnt = 0;
    for(auto [w, a, b] : edges) {
        // 두 그룹이 아직 합쳐지지 않은 경우
        if(merge(a, b)) {
            ans += w;
            cnt ++; // 합친 횟수
        }
    }
    // 만약 모든 정점이 선택되지 않았다면
    if(cnt != M) ans = -1;
    cout << ans;
    
    return 0;
}