typedef enum
{
    NAME,
    NUMBER,
    BIRTHDAY,
    EMAIL,
    MEMO
} FIELD;

typedef struct
{
    int count;
    char str[20];
} RESULT;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>

size_t djb2(const char* str) {
    size_t hash = 5381;
    for (; *str; ++str) {
        hash = ((hash << 5) + hash) + *str;
    }
    return hash;
}

constexpr size_t MAX_N = 100000;
constexpr size_t MAX_LEN = 19;

struct Node {
    char str[MAX_LEN + 1];
    char name[MAX_LEN + 1];
    char birth[MAX_LEN + 1];
    char number[MAX_LEN + 1];
    char email[MAX_LEN + 1];
    char memo[MAX_LEN + 1];
    int data;
    Node* next;
};

int node_count = 0;
Node nodes[MAX_N];

Node* new_node(const char str[MAX_LEN + 1], int data) {
    std::strcpy(nodes[node_count].str, str);
    nodes[node_count].data = data;
    nodes[node_count].next = nullptr;

    return &nodes[node_count++];
}

class HashMap {
    static constexpr size_t TABLE_SIZE = 1 << 12;
    static constexpr size_t DIV = TABLE_SIZE - 1;

    Node hash_table[TABLE_SIZE];

public:
    HashMap() = default;

    void init() {
        std::memset(hash_table, 0, sizeof hash_table);
        node_count = 0;
    }

    void insert(const char str[MAX_LEN + 1], int data) {
        Node* const prev_node = get_prev_node(str);
        if (prev_node->next == nullptr) {
            prev_node->next = new_node(str, data);
        } else {
            prev_node->next->data = data;
        }
    }

    void remove(const char str[MAX_LEN + 1]) {
        Node* const prev_node = get_prev_node(str);
        if (prev_node->next != nullptr) {
            prev_node->next = prev_node->next->next;
        }
    }

    Node* get(const char str[MAX_LEN + 1]) {
        return get_prev_node(str)->next;
    }

private:
    Node* get_prev_node(const char str[MAX_LEN + 1]) {
        Node* prev_ptr = &hash_table[djb2(str) & DIV];
        while (prev_ptr->next != nullptr && std::strcmp(prev_ptr->next->str, str) != 0) {
            prev_ptr = prev_ptr->next;
        }
        return prev_ptr;
    }
};
HashMap name_hash{};
HashMap number_hash{};
HashMap birth_hash{};
HashMap email_hash{};
HashMap memo_hash{};

void InitDB()
{
    name_hash.init();
    number_hash.init();
    birth_hash.init();
    email_hash.init();
    memo_hash.init();
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{

}

int Delete(FIELD field, char* str)
{
    return -1;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
    return -1;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
    RESULT result;
    result.count = -1;

    return result;
}