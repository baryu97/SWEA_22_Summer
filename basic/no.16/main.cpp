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

#include<iostream>
#include <vector>
using namespace std;

int processor[12][12];
vector<pair<int,int>> core;
int connected_cores;
int answer;
vector<pair<pair<int,int>,pair<int,int>>> lines;

bool is_between(int a,int b,int x){
    if (a < b){
        return a <= x && x <= b;
    } else{
        return b <= x && x <= a;
    }
}

bool is_cross(pair<int,int> p1,pair<int,int> p2){
    bool ret = false;
     for (int i = 0; i < core.size(); ++i) {
         if (core[i].first == p2.first && core[i].second == p2.second)
             continue;
         ret = ret || (is_between(p1.first,p2.first,core[i].first) && is_between(p1.second,p2.second,core[i].second));
     }
    for (int i = 0; i < lines.size(); ++i) {
        if (p1.first == p2.first){
            if (lines[i].first.first == lines[i].second.first){
                ret = ret || (p1.first == lines[i].first.first && (is_between(p1.second,p2.second,lines[i].first.second) ||
                                                                   is_between(p1.second,p2.second,lines[i].second.second)));
            } else{
                ret = ret || (is_between(lines[i].first.first,lines[i].second.first,p1.first) && is_between(p1.second,p2.second,lines[i].first.second));
            }
        } else{
            if (lines[i].first.first == lines[i].second.first){
                ret = ret || (is_between(lines[i].first.second,lines[i].second.second,p1.second) && is_between(p1.first,p2.first,lines[i].first.first));
            } else{
                ret = ret || (p1.second == lines[i].first.second && (is_between(p1.first,p2.first,lines[i].first.first) ||
                                                                     is_between(p1.first,p2.first,lines[i].second.first)));
            }
        }
    }
    return ret;
}

void dfs(int size,int core_num,int connected_cores_count, int length){
    if (core_num >= core.size()){
        if (connected_cores_count > connected_cores){
            connected_cores = connected_cores_count;
            answer = length;
        } else if (connected_cores == connected_cores_count)
            answer = min(answer,length);
        return;
    }
    int cur_x = core[core_num].first;
    int cur_y = core[core_num].second;
    if (cur_x == 0 || cur_x == size -1 || cur_y == 0 || cur_y == size -1){
        dfs(size,core_num + 1,connected_cores_count + 1, length);
    } else {
        pair<int, int> d[4] = {{cur_x,    0},
                               {0,        cur_y},
                               {cur_x,    size - 1},
                               {size - 1, cur_y}};
        bool check = true;
        for (int i = 0; i < 4; ++i) {
            if (is_cross(d[i], core[core_num])) {
                continue;
            }
            check = false;
            lines.emplace_back(d[i], core[core_num]);
            dfs(size, core_num + 1, connected_cores_count + 1, length + abs(d[i].first + d[i].second - cur_x - cur_y));
            lines.pop_back();
        }
        if (check) {
            dfs(size, core_num + 1, connected_cores_count, length);
        }
    }
}

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
//    freopen("input.txt", "r", stdin);
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
        int size;
        cin >> size;
        core.clear();
        lines.clear();
        connected_cores = 0;
        answer = 987654321;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cin >> processor[i][j];
                if (processor[i][j] == 1)
                    core.emplace_back(i,j);
            }
        }
        dfs(size,0,0,0);
        cout << "#" << test_case << " " << answer << "\n";
        /////////////////////////////////////////////////////////////////////////////////////////////


    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}