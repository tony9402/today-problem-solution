/*
 * (삼성 기출 문제다... 잘 정리하고 풀자...)
 *
 * 게임 조건 정리
 *  - 하나의 말 위에 다른 말을 올릴 수 있음.
 *  - 맨 아래 있는 말만 이동할 수 있으며 그 위에 있는 말들은 같이 움직인다.
 *  - [게임 종료 조건] 게임이 진행되는 도중에 말이 4개 이상 쌓이는 순간 게임은 종료
 * 
 * 게임이 종료가 안될 수 있다는 것에 주의를 해야한다.
 * 게임이 종료가 안되는 경우는 어떤 것일지 생각을 해보자.
 * 바로 떠오르는 방법은 현재 게임 판의 상태가 이미 나온 상태라면 게임이 절대로 종료되지 않는다.
 * 
 * 하지만 더 효율적으로 처리하는 방법을 생각해보면 12x12 보드판에서 1000턴 정도 지나가도 끝나지 않으면 게임이 절대로 끝나지 않는다.
 * 왜냐하면, 보드는 12x12이기 때문에 총 144칸이 존재하기 때문에 1000턴이 되기 전에 종료될 것이다.
 * 그리고, 한 턴에 처리해야하는 양(시간복잡도)을 생각해보면 K개의 말이 한번씩 이동해야한다. 이거의 시간복잡도는 O(K)를 알 수 있다.
 * 따라서, 1000턴을 돌리면 O(1000K)이고 K는 상당히 작은 수이기 때문에 시간제한안에 돌 수 있다.
 * 
 * 구현하는 방법은 여러가지 있지만, 그 중 편한 방법으로 짠다.
 * 
 * 시간제한 : 0.5s
 * 시간복잡도 : O(1000K)
 */
#include<bits/stdc++.h>

using namespace std;

// (0, 0)이 왼쪽 맨 위, (N - 1, N - 1)이 오른쪽 맨 아래를 기준으로 코딩한다.
// [오른쪽, 왼쪽, 위, 아래]
const int dy[] = {0,0,-1,1};
const int dx[] = {1,-1,0,0};

struct Horse { int y, x, dir; };


int N, K;
// 칸의 색상을 담고 있다. (0 : 흰색, 1 : 빨간색, 2 : 파란색)
int board[14][14];
// 말은 최대 10마리
Horse horse_data[10]; 
// 각 칸에 말들의 정보를 저장하는 배열
// horse[y][x] : (y, x) 에 존재하는 말의 정보이다.
//               vector 맨 앞에 있는 말은 가장 아래에 위치해 있다고 생각하자.
vector<int> horse[14][14];

// dir 순서를 잘 정하면 방향 바꾸는 함수를 만들지 않아도 된다.
int reverse_dir(int dir) {
    if(dir > 1) return 5 - dir; // 2 <-> 3
    return 1 - dir; // 0 <-> 1
}

int game() {
    // 게임은 최대 1000턴만 돌리면 된다.
    int step;
    for(step = 1; step <= 1000; ++ step) {
        // 말은 1번부터 K번까지 "순서"대로 움직인다.
        // 만약 x(1≤x≤K)번 말이 다른 말 위에 존재한다면 넘어가면 된다.
        int skip = 0; // 이 경우는 이동하려는 곳이 파란색이거나 보드 밖일 때 체크하는 변수.
        for(int id = 0; id < K; ++id) {
            // 해당 말이 맨 밑에 있는지 판단해보자.
            auto [y, x, dir] = horse_data[id];
            int down = horse[y][x][0] == id;

            // 만약 맨 밑에 있는 말이 아니라면 넘어가기
            if(down == 0) continue;

            // 말이 바라보고 있는 방향으로 한칸 앞을 보자.
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            // A번 말이 이동하려는 칸이 "흰색"인 경우
            if(board[ny][nx] == 0) {
                // 만약 말이 존재한다면 맨 위에 올려줘야한다.
                // 모든 말이 한번에 이동하는 것을 잊지 말자.
                for(int id2 : horse[y][x]) {
                    horse[ny][nx].push_back(id2);
                    horse_data[id2].y = ny;
                    horse_data[id2].x = nx;
                }
                horse[y][x].clear();

                // 만약 (ny, nx)에 쌓이는 말이 개수가 4개 이상이면 게임 종료
                if(horse[ny][nx].size() >= 4) return step;
            }
            // A번 말이 이동하려는 칸이 "빨간색"인 경우
            else if(board[ny][nx] == 1) {
                // 이 경우는 먼저 순서를 뒤집고 보내면 된다.
                reverse(horse[y][x].begin(), horse[y][x].end());
                for(int id2 : horse[y][x]) {
                    horse[ny][nx].push_back(id2);
                    horse_data[id2].y = ny;
                    horse_data[id2].x = nx;
                }
                horse[y][x].clear();

                // 만약 (ny, nx)에 쌓이는 말이 개수가 4개 이상이면 게임 종료
                if(horse[ny][nx].size() >= 4) return step;
            }
            // A번 말이 이동하려는 칸이 "파란색"인 경우 (밖을 나가는 경우도 여기에 포함되어 있다.)
            else if(board[ny][nx] == 2) {
                // 만약 현재 턴에 이 행동을 2번 했다면 넘어간다.
                if(skip < 2)  {
                    // A번 말의 방향을 바꾸고 다시 보면 된다.
                    horse_data[id].dir = reverse_dir(horse_data[id].dir);
                    -- id;
                    ++ skip;
                    continue;
                }
            }
            skip = 0;
        }
    }
    return step;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> K;
    // 보드 밖을 파란색으로 칠하자.
    // 그러면 보드 밖을 나가는지 체크를 생략할 수 있다.
    for(int i = 0; i <= N + 1; ++i) {
        for(int j = 0; j <= N + 1; ++j) {
            board[i][j] = 2;
        }
    }
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < K; ++i) {
        int y, x, dir; cin >> y >> x >> dir;
        // 여기서 말하는 방향(dir)의 순서는 [오른쪽, 왼쪽, 위, 아래] 순이다.
        horse[y][x].push_back(i);
        // 방향은 0-based으로 구현하고 있기 때문에 1을 빼주는 것을 잊지 말자.
        horse_data[i] = {y, x, dir - 1};
    }

    int ans = game();
    if(ans > 1000) ans = -1;
    cout << ans;

    return 0;
}