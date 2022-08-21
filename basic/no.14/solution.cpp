class stack{
    int top_pointer = -1;
    int array[100];
public:
    bool empty(){
        if (top_pointer == -1)
            return true;
        else return false;
    }
    void push(int n){
        array[++top_pointer] = n;
    }
    int top(){
        return array[top_pointer--];
    }
};

using namespace std;

struct tree{
    int child[5];
    int size = 0;
};

tree whtkd_tree[100];

void dfs_init(int N, int path[100][2])
{
    for (int i = 0; i < 100; ++i) {
        whtkd_tree[i].size = 0;
    }
    for (int i = 0; i < N-1; ++i) {
        whtkd_tree[path[i][0]].child[whtkd_tree[path[i][0]].size++] = path[i][1];
    }
}

int dfs(int n)
{
    stack dfs_stack;
    dfs_stack.push(n);
    while (!dfs_stack.empty()){
        int cur = dfs_stack.top();
        if (cur > n){
            return cur;
        }
        for (int i = whtkd_tree[cur].size - 1; i >= 0; --i) {
            dfs_stack.push(whtkd_tree[cur].child[i]);
        }
    }
    return -1;
}
