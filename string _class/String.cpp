#include"String.h"
#include<cstring>
using namespace std;

String::String(const char* str){
    if(str==nullptr){
        m_data=new char[1];
        *m_data='\0';// 若为空，则赋值为空
    }
    else{
        int len=strlen(str);
        m_data=new char[len+1];
        strcpy(m_data,str);
    }
}
String::String(const String &other){
    int len=strlen(other.m_data);
    m_data=new char[len+1];
    strcpy(m_data,other.m_data);//将后者拷贝到前者
}
String::~String(){
    delete[] m_data;
}
String& String::operator=(const String &other){
    if(this==&other){
        return *this;//this为一个指针，返回未string，需要提领指针
    }
    if (m_data)
        delete[] m_data;//释放原有的内存资源 
    int length = strlen(other.m_data);
    m_data = new char[length + 1];//对m_data加NULL判断 
    strcpy(m_data, other.m_data);
    return *this;//返回本对象的引用   

}

ostream& operator<<(ostream & os,const String &s){
    os<<s.m_data;
    return os;
}
istream& operator>>(istream &is,const String &s){
    is>>s.m_data;
    return is;
}
