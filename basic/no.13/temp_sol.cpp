#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#include <set>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;
// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}

void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}
struct Directory;

bool dirCmp(Directory*,Directory*);

struct Directory{
    char name[NAME_MAXLEN + 1];
    set<Directory *, decltype(&dirCmp)> sub;
    bool operator<(const Directory &b) const {
        for (int i = 0; name[i] != '\0'; i++)
        {
            if (name[i] != b.name[i])
                return name[i] < b.name[i];
        }
        return false;
    }
    bool operator==(const Directory &b) const {
        int i;
        for (i = 0; name[i] != '\0'; i++)
        {
            if (name[i] != b.name[i])
                return false;
        }
        if (b.name[i] != '\0')
            return false;
        return true;
    }
    Directory(char filename[]){
        mstrcpy(name,filename);
    }
    Directory(string filenames){
        for (int i = 0; i < NAME_MAXLEN + 1; ++i) {
            name[i] = filenames[i];
        }
    }
};

bool dirCmp(Directory* a, Directory* b){
    return *a < *b;
}

Directory root("/");


void init(int n) {
    root.sub.clear();
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    Directory* current = &root;
/*    if (mstrcmp(path, "/") == 0){

    } else {*/
        stringstream path_stream(path);
        char delimiter = '/';
        string tmp;
        while (getline(path_stream, tmp, delimiter)) {
            if (tmp.compare("") == 0)
                continue;

            auto temp_dir = new Directory(tmp);
            auto iter = current->sub.upper_bound(temp_dir);
            current = *iter;
        }
//    }
    auto temp = new Directory(name);
    current->sub.insert(temp);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {

}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {

}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {

}

int cmd_find(char path[PATH_MAXLEN + 1]) {

    return 0;
}