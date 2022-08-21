/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <string>
#define MOD 1000000007
#define MOD 9223372036854775807
#define MAX 10000
#define MAX 25

using namespace std;
long long dp[4][MAX + 1]; // 0 : next == cur 인 경우의 수, 나머지 : next != cur 이면서 원소의 개수가 index 인 경우의 수

int main(int argc, char** argv)
{
    int test_case;
    int T;
    /*
       아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
       앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
       //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
       freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
       따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
       freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
       단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
    */
    //freopen("input.txt", "r", stdin);
    cin>>T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {

        /////////////////////////////////////////////////////////////////////////////////////////////
        /*
             이 부분에 여러분의 알고리즘 구현이 들어갑니다.
         */
        char N[MAX + 1];
//        string N;
        cin >> N;
        char prev = 'A';
        char cur = N[0];
        char next;
        int i;
        fill(&dp[0][0], &dp[3][MAX + 1], 0);
//        dp[0][0] = 1; dp[1][0] = 0; dp[2][0] = 0, dp[3][0] = 0;
        if (prev == cur)
            dp[0][0] = 1;
        else
            dp[1][0] = 1;
        for (i = 1; N[i] != 0; ++i,prev = cur, cur = next) {
            next = N[i];
            if (cur == next) {
                long long temp = 0;
                for (int j = 0; j < 4; ++j) {
                    temp += dp[j][i - 1];
                }
                dp[0][i] = temp % MOD;
            } else if (prev == next && dp[1][i-1] > 0) {
                dp[0][i] = (dp[0][i-1] * 4 + dp[1][i-1] * 4 + dp[2][i-1] * 4 + dp[3][i-1] * 4) % MOD;
                dp[1][i] = (dp[0][i-1] * 1) % MOD;
                dp[2][i] = (dp[0][i-1] * 2 + dp[2][i-1] * 1 + dp[3][i-1] * 2) % MOD;
                dp[3][i] = (dp[0][i-1] * 1 + dp[2][i-1] * 1 + dp[3][i-1] * 1) % MOD;
            } else {
                dp[0][i] = (dp[0][i - 1] * 4 + dp[1][i - 1] * 2 + dp[2][i - 1] * 4 + dp[3][i - 1] * 4) % MOD;
                dp[1][i] = (dp[0][i - 1] * 1) % MOD;
                dp[2][i] = (dp[0][i - 1] * 2 + dp[1][i - 1] * 1 + dp[2][i - 1] * 1 + dp[3][i - 1] * 2) % MOD;
                dp[3][i] = (dp[0][i - 1] * 1 + dp[1][i - 1] * 1 + dp[2][i - 1] * 1 + dp[3][i - 1] * 1) % MOD;
            }
        }

        long long answer = (dp[0][i - 1] * 8 + dp[1][i - 1] * 4 + dp[2][i - 1] * 6 + dp[3][i - 1] * 7) % 1000000007;
        cout << "#" << test_case << " " << answer << "\n";
        /////////////////////////////////////////////////////////////////////////////////////////////


    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}