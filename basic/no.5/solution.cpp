#define MAX_NODE 10000

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
    node[nodeCnt].data = data;
    node[nodeCnt].prev = nullptr;
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
    if (head == nullptr) {
        head = temp;
        return;
    }
    temp->next = head;
    head->prev = temp;
    head = temp;
}

void addNode2Tail(int data)
{
    if (head == nullptr){
        addNode2Head(data);
        return;
    }
    Node* tail;
    for (tail = head; tail->next != nullptr; tail = tail->next);
    Node* temp = getNode(data);
    tail->next = temp;
    temp->prev = tail;
}

void addNode2Num(int data, int num)
{
    if (num == 1){
        addNode2Head(data);
        return;
    }
    Node* index = head;
    for (int i = 2; i < num; ++i, index = index->next);
    Node* temp = getNode(data);
    temp->next = index->next;
    temp->prev = index;
    index->next = temp;
    if (temp->next != nullptr)
        temp->next->prev = temp;
}

int findNode(int data)
{
    if (head->data == data) {
        return 1;
    }
    Node* index;
    int i;
    for (index = head, i = 1; index != nullptr && index->data != data; ++i, index = index->next);
    if (index == nullptr)
        return 0;
    return i;
}

void removeNode(int data)
{
    if (head->data == data) {
        head = head->next;
        return;
    }
    Node* index;
    for (index = head; index->next != nullptr && index->next->data != data; index = index->next);
    if (index->next == nullptr)
        return;
    index->next = index->next->next;
    if (index->next != nullptr)
        index->next->prev = index;
}

int getList(int output[MAX_NODE])
{
    int i;
    Node* cur;
    for (i = 0,cur = head; cur != nullptr; ++i,cur = cur->next) {
        output[i] = cur->data;
    }
    return i;
}

int getReversedList(int output[MAX_NODE])
{
    int i;
    Node* cur;
    Node* tail;
    for (tail = head; tail->next != nullptr; tail = tail->next);
    for (i = 0,cur = tail; cur != nullptr; ++i,cur = cur->prev) {
        output[i] = cur->data;
    }
    return i;
}