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

#define MAX_NODE 10000

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].next = nullptr;
    return &node[nodeCnt++];
}

void init()
{
    head = nullptr;
    nodeCnt = 0;
}

void addNode2Head(int data)
{
    Node* temp = getNode(data);
    temp->next = head;
    head = temp;
}

void addNode2Tail(int n,int* data)
{
    /*if (head == nullptr){
    }*/
    Node* tail;
    for (tail = head; tail->next != nullptr; tail = tail->next);
    Node* temp1 = getNode(data[0]);
    Node* temp2 = temp1;
    Node* temp = temp1;
    for (int i = 1; i < n; ++i) {
        temp2 = getNode(data[i]);
        temp->next = temp2;
        temp = temp2;
    }
    tail->next = temp1;
}

void addNode2Num(int num,int n,int* data)
{
    Node* temp1 = getNode(data[0]);
    Node* temp2 = temp1;
    Node* temp = temp1;
    for (int i = 1; i < n; ++i) {
        temp2 = getNode(data[i]);
        temp->next = temp2;
        temp = temp2;
    }
    if (num == 0){
        temp2->next = head;
        head = temp1;
        return;
    }
    Node* index = head;
    for (int i = 1; i < num; ++i, index = index->next);
    temp2->next = index->next;
    index->next = temp1;
}

void removeNode(int index, int num)
{
    Node* start = head;
    for (int i = 1; i < index; ++i, start = start->next);
    Node* last = start->next;
    for (int i = 0; i < num; ++i,last = last->next);
    if (index == 0){
        head = last;
        return;
    }
    start->next = last;
}

int N, M;
char command;
int input[MAX_NODE];

int main(int argc, char** argv)
{
    int test_case;
    int T = 10;
    /*
       아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
       앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
       //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
       freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
       따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
       freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
       단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
    */
    freopen("input.txt", "r", stdin);
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for(test_case = 1; test_case <= T; ++test_case)
    {

        /////////////////////////////////////////////////////////////////////////////////////////////
        /*
             이 부분에 여러분의 알고리즘 구현이 들어갑니다.
         */
        init();
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> input[i];
        }
        addNode2Num(0,N,input);
        cin >> M;
        for (int i = 0; i < M; ++i) {
            cin >> command;
            if (command == 'I') {
                int x, y;
                cin >> x >> y;
                int s[y];
                for (int j = 0; j < y; ++j) {
                    cin >> s[j];
                }
                addNode2Num(x, y, s);
            } else if (command == 'D'){
                int x, y;
                cin >> x >> y;
                removeNode(x,y);
            } else if (command == 'A'){
                int y;
                cin >> y;
                int s[y];
                for (int j = 0; j < y; ++j) {
                    cin >> s[j];
                }
                if (head == nullptr)
                    addNode2Num(0,y,s);
                else
                    addNode2Tail(y,s);
            }
        }
        cout << "#" << test_case << " ";
        Node* cur = head;
        for (int i = 0; i < 10; ++i, cur = cur->next) {
            cout << cur->data << " ";
        }
        cout << "\n";
        /////////////////////////////////////////////////////////////////////////////////////////////


    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}