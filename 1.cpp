/*
1.Write a program in C or C++ language for the following functions without using
string.h header file:
a: "to get the length of a string, you use the strlen() function"
b: "To concatenate (combine) two strings, you can use the strcat() function
c: "To copy the value of one string to another, you can use the strcpy()" 
d: "To compare two strings, you can use the strcmp() function.
and other related functions."
*/
#include <iostream>
using namespace std;

int strlen(char* str){
    int len=0;
    while(str[len]!='\0'){
        len++;
    }
    return len;
}

void strconcat(char* dest, char* src){
    int idx = strlen(dest);
    int i=0;
    while(src[i]!='\0'){
        dest[idx+i]=src[i];
        i++;
    }
    dest[idx+i]='\0';
}

void strcpy(char* src, char* dest){
    int i=0;
    while(src[i]!='\0'){
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0';
}

int strcmpy(char* str1, char* str2){
    int i = 0;
    while(str1[i]!='\0' && str2[i]!='\0'){
        if(str1[i]!=str2[i])
            return str1[i]-str2[i];
        i++;
    }
    return str1[i]-str2[i];
    
}

int main()
{
    char str1[100] = "hello";
    char str2[100] = "world";
    char str3[100];
    cout<<"Length of str1 = "<<strlen(str1)<<endl;
    strconcat(str1, str2);
    cout<<"Concatenated string: "<<str1<<endl;
    strcpy(str2, str3);
    cout<<"Copied String: "<<str3<<endl;
    cout<<"Comparison of strings:"<<strcmpy("hello", "Hello")<<endl;
}