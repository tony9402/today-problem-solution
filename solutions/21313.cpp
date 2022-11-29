/* 
 * 이 문제는 Ad-hoc이라는 알고리즘 분류이다.
 * N이 짝수일 때 생각을 해보면 1과 2를 이용하여 만들 수 있다.
 *  ex) N = 4 : 1 2 1 2
 *  ex) N = 8 : 1 2 1 2 1 2 1 2
 * 
 * 하지만, N이 홀수일 때 위와 같이 1과 2를 번갈아가며 만들면 맨 처음 수와 맨 마지막 수가 같기 때문에 문제 조건에 어긋난다.
 * 그러면 맨 마지막은 1, 2가 아닌 3을 출력하자.
 *  ex) N = 5 : 1 2 1 2 3
 *  ex) N = 7 : 1 2 1 2 1 2 3
 * 
 * 
 * 제한시간 : 1s
 * 시간복잡도 : O(N)
 */
#include<bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    // 1 2 1 -> 1 1안됨
    // (1 2) 출력하면서 마지막에 남는 하나는 3을 출력
    for(int i = 0; i < N / 2; ++i) cout << "1 2 ";
    if(N % 2 == 1) cout << 3;

    return 0;
}