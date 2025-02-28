#ifndef String_h
#define String_h
#include<utility>
#include<stddef.h>
#include<string.h>
#include <iostream>

class String{
    char *arr;
    size_t len;

    public:
        String(){
            arr = nullptr;
            len = 0;
        }
        String(const String &s){
            arr = new char[s.len+1];
            for(int i = 0; i <= s.len; i++){
                arr[i] = s.arr[i];
            }
            len = s.len;
        }

        String (const char s[]){
            len = strlen(s);
            arr = new char[len+1];
            for(int i = 0; i <= len; i++){
                arr[i] = s[i];
            }
        }

        void strrev(){
            for(int i = 0; i < len/2; i++)
                std::swap(arr[i], arr[len - i -1]);
        }
        
        String& operator = (const String &s){
            if(this != &s){ // this check is to verify for the case str = str;
                delete[] arr;
                arr = new char[s.len + 1];
                strcpy(arr, s.arr);
                len = s.len;
            }
            return *this;
        }

        char operator [](size_t i){
            if(i <= len)
                return arr[i];
            else    
                std::cout<<"Index out of range"<<std::endl;
        }
        size_t length(){
            return len;
        }

        ~String(){
            delete[] arr;
        }
        friend std::ostream& operator <<(std::ostream &blah,String &s);
        friend std::istream& operator >>(std::istream &blah, String &s);
};

std::ostream & operator <<(std::ostream &blah, String &s){
    blah<<s.arr;
    return blah;
}
std::istream & operator >>(std::istream &blah, String &s){

    char temp[1000];
    blah>>temp;
    delete[] s.arr;
    size_t length = strlen(temp);
    s.arr = new char[length + 1];
    strcpy(s.arr, temp);
    s.len = length;
    return blah;
}
#endif