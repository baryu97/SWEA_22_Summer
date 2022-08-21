struct user{
    int income;
    int uid;
    user() {}
    user(int a,int b){
        income = a;
        uid = b;
    }
    bool operator< (const user &a) const{
        if (income == a.income)
            return uid > a.uid;
        return income < a.income;
    }
};
void swap(user &a, user &b){
    user temp = a;
    a = b;
    b = temp;
}



class MaxHeap {
#define parent  (i >> 1)
#define left	(i << 1)
#define right   (i << 1 | 1)

    static constexpr int MAX_N = 100000;

    user data[MAX_N + 1];
    int size;

public:

    void init() {
        size = 0;
    }

    // x 삽입
    void push(int x, int y) {
        data[++size] = user(x,y);
        for (int i = size; parent != 0 && data[parent] < data[i]; i >>= 1) {
            swap(data[parent], data[i]);
        }
    }

    // 최대값 리턴
    user top() const {
        return data[1];
    }

    // 최대값 삭제
    void pop() {
        data[1] = data[size--];
        for (int i = 1; left <= size;) {
            const int max_child = left == size || data[right] < data[left] ? left : right;
            if (data[i] < data[max_child]) {
                swap(data[max_child], data[i]);
                i = max_child;
            } else {
                break;
            }
        }
    }

    bool empty() const{
        return size == 0;
    }
#undef parent
#undef left
#undef right
};

MaxHeap *heap;

void init()
{
    heap = new MaxHeap;
}

void addUser(int uID, int height)
{
    heap->push(height,uID);
}

int getTop10(int result[10])
{
    int i;
    int temp[10];
    for (i = 0; i < 10 && !heap->empty(); ++i) {
        result[i] = heap->top().uid;
        temp[i] = heap->top().income;
        heap->pop();
    }
    for (int j = 0; j < i; ++j) {
        heap->push(temp[j], result[j]);
    }
    return i;
}