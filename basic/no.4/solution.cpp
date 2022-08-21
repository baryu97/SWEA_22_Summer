#define MAX_NODE 10000

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
}

void addNode2Num(int data, int num)
{
    if (num == 0){
        addNode2Head(data);
        return;
    }
    Node* index = head;
    for (int i = 1; i < num; ++i, index = index->next);
    Node* temp = getNode(data);
    temp->next = index->next;
    index->next = temp;
}

void removeNode(int num)
{
    if (num == 0){
        head = head->next;
        return;
    }
    Node* index = head;
    for (int i = 1; i < num; ++i, index = index->next);
    index->next = index->next->next;
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