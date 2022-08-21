#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#include <set>
#include <sstream>
#include <iostream>
#include <algorithm>
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



struct Directory{
    char name[NAME_MAXLEN + 1];
    Directory* sub[30];
    int size = 0;
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
    Directory(Directory* dir){
        mstrcpy(name,dir->name);
        for (int i = 0; i < dir->size; ++i) {
            auto temp = new Directory(dir->sub[i]);
            sub[size++] = temp;
        }
    }
};


Directory root("/");
char delimiter = '/';

void init(int n) {
    root.size = 0;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
    Directory* current = &root;
    stringstream path_stream(path);
    string tmp;
    while (getline(path_stream, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        for (int i = 0; i < current->size; ++i) {
            if (tmp.compare(current->sub[i]->name) == 0){
                current = current->sub[i];
                break;
            }
        }
    }
    auto temp = new Directory(name);
    current->sub[current->size++] = temp;
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
    if (mstrcmp(path,"/") == 0){
        init(1);
        return;
    }
    Directory* parent;
    Directory* current = &root;
    stringstream path_stream(path);
    string tmp;
    int i;
    while (getline(path_stream, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        parent = current;
        for (i = 0; i < current->size; ++i) {
            if (tmp.compare(current->sub[i]->name) == 0){
                current = current->sub[i];
                break;
            }
        }
    }
    parent->sub[i] = parent->sub[--parent->size];
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    Directory* parent_src;
    Directory* current_src = &root;
    Directory* current_dst = &root;
    stringstream path_stream_src(srcPath);
    stringstream path_stream_dst(dstPath);
    string tmp;
    int i;

    while (getline(path_stream_dst, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        for (i = 0; i < current_dst->size; ++i) {
            if (tmp.compare(current_dst->sub[i]->name) == 0){
                current_dst = current_dst->sub[i];
                break;
            }
        }
    }
    while (getline(path_stream_src, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        parent_src = current_src;
        for (i = 0; i < current_src->size; ++i) {
            if (tmp.compare(current_src->sub[i]->name) == 0){
                current_src = current_src->sub[i];
                break;
            }
        }
    }
    current_dst->sub[current_dst->size++] = new Directory(parent_src->sub[i]);
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
    Directory* parent_src;
    Directory* current_src = &root;
    Directory* current_dst = &root;
    stringstream path_stream_src(srcPath);
    stringstream path_stream_dst(dstPath);
    string tmp;
    int i;

    while (getline(path_stream_dst, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        for (i = 0; i < current_dst->size; ++i) {
            if (tmp.compare(current_dst->sub[i]->name) == 0){
                current_dst = current_dst->sub[i];
                break;
            }
        }
    }
    while (getline(path_stream_src, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        parent_src = current_src;
        for (i = 0; i < current_src->size; ++i) {
            if (tmp.compare(current_src->sub[i]->name) == 0){
                current_src = current_src->sub[i];
                break;
            }
        }
    }
    current_dst->sub[current_dst->size++] = parent_src->sub[i];
    parent_src->sub[i] = parent_src->sub[--parent_src->size];
}

int count_dir(Directory * dir){
    if (dir->size == 0)
        return 1;
    int sum = 1;
    for (int i = 0; i < dir->size; ++i) {
        sum += count_dir(dir->sub[i]);
    }
    return sum;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
    Directory* current = &root;
    stringstream path_stream(path);
    string tmp;
    int i;
    while (getline(path_stream, tmp, delimiter)) {
        if (tmp.compare("") == 0)
            continue;
        for (i = 0; i < current->size; ++i) {
            if (tmp.compare(current->sub[i]->name) == 0){
                current = current->sub[i];
                break;
            }
        }
    }
    return count_dir(current) - 1;
}