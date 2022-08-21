#include <cstring>
using namespace std;


char main_str[500002];
int N;

int hash(const char *s){
    int ret = (s[0] - 'a') + ((s[1] - 'a') << 4) + ((s[2] - 'a') << 8);
    return ret;
}

void strcpy1(char *dest, const char *source){
    for (int i = 0; source[i] != '\0'; ++i) {
        dest[i] = source[i];
    }
}

void init(int n, char init_string[]){
    N = n;
    strcpy(main_str,init_string);
}


int change(char string_A[], char string_B[]){
    int hash_a = hash(string_A);
    int hash_m = hash(main_str);
    int answer = 0;
    int i = 1;
    if (hash_m == hash_a){
        strcpy1(main_str, string_B);
        answer++;
        i = 3;
        hash_m = hash(main_str + i - 1);
    }
    for (; i < N - 2; ++i) {
        hash_m = (hash_m >> 4) + ((main_str[i + 2] - 'a') << 8);
        if (hash_m == hash_a){
            strcpy1(main_str + i, string_B);
            answer++;
            i += 2;
            hash_m = hash(main_str + i);
        }
    }
    return answer;
}

void result(char ret[]){
    strcpy(ret,main_str);
}
