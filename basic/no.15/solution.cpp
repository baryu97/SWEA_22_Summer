
using namespace std;
int plane[10][10];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

class queue{
    int front = 0;
    int end = 0;
    int x[500];
    int y[500];
public:
    void push(int a, int b){
        x[end] = a;
        y[end++] = b;
    }
    int front_x(){
        return x[front];
    }
    int front_y(){
        return y[front];
    }
    void pop(){
        if (!empty())
            front++;
        else;
    }
    bool empty(){
        return end <= front;
    }
};

int visit[10][10];

void bfs_init(int map_size, int map[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i >= map_size || j >= map_size){
                plane[j][i] = 1;
            }
            plane[j][i] = map[i][j];
        }
    }
}

int bfs(int x1, int y1, int x2, int y2) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            visit[i][j] = -1;
        }
    }
    queue bfs_queue;
    bfs_queue.push(x1 - 1,y1 - 1);
    visit[x1-1][y1-1] = 0;
    while (!bfs_queue.empty()){
        int cur_x = bfs_queue.front_x();
        int cur_y = bfs_queue.front_y();
        bfs_queue.pop();
        if (cur_x == x2 - 1 && cur_y == y2 - 1){
            return visit[cur_x][cur_y];
        }
        for (int i = 0; i < 4; ++i) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            if (nx < 0 || ny < 0 || nx >= 10 || ny >= 10)
                continue;
            if (plane[nx][ny] == 1)
                continue;
            if (visit[nx][ny] != -1)
                continue;
            bfs_queue.push(nx,ny);
            visit[nx][ny] = visit[cur_x][cur_y] + 1;
        }
    }
    return -1;
}
/*
#include <iostream>
void print_visit(){

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout.width(2);
            cout.fill(' ');
            cout << visit[j][i] << " ";
        }
        cout << endl;
    }
}*/
