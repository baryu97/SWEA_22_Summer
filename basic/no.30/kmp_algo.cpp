using namespace std;

char * main_str;
int N;

void strcpy1(char *dest, const char *source){
    for (int i = 0; source[i] != '\0'; ++i) {
        dest[i] = source[i];
    }
}

void init(int n, char init_string[]){
    delete main_str;
    main_str = new char [n];
    N = n;
    strcpy1(main_str,init_string);
}
int lps[3];
void make_lps(const char *pat,int size,int *lps){
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < size) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int change(char string_A[], char string_B[]){
    make_lps(string_A,3,lps);
    int i = 0, j = 0;
    int answer = 0;
    while (i < N){
        if (string_A[j] == main_str[i]){
            j++;
            i++;
        }
        if (j == 3){
            strcpy1(main_str + i - j,string_B);
            answer++;
            j = 0;
        } else if (i < N && string_A[j] != main_str[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return answer;
}

void result(char ret[]){
    for (int i = 0; i < N; ++i) {
        ret[i] = main_str[i];
    }
}
