#include<iostream>
class String{
friend std::ostream& operator<<(std::ostream &os,const String &s);//支持输入输出
friend std::istream& operator>>(std::istream &is,const String &s);
public:
    String(const char *str=nullptr);//create function
    String(const String &other);//copy function
    ~String();
    String& operator=(const String &other);//assignment fun 
    
private:
    char *m_data;
};
