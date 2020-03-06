#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<iostream>
#include<string.h>
using namespace std;
template<typename T>
class Vector{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    Vector()=default;//无参构造函数
    Vector(const Vector<T>& v){//拷贝构造函数
        _start=new T[v.Capacity()];
        for(size_t i=0;i<v.Size();i++){
            _start[i]=v._start[i];
        }
        _finish=_start+v.Size();
        _endofStorage=_start+v.Capacity();
    }
    Vector<T> & operator=(Vector<T> v){//重构=
        Swap(v);
        return *this;
    }
        void Swap(Vector<T> &v){
            std::swap(_finish,v._finish);
            std::swap(_start,v._start);
            std::swap(_endofStorage,v._endofStorage);
        }
    
    ~Vector(){
        if(_start){
            delete[] _start;
            _start=_finish=_endofStorage=nullptr;
        }
    }
    void Reserve(size_t n){//扩容
        if(n>Capacity()){
            size_t size=Size();//size 为原数组长度
            T* tmp=new T[n];
            if(_start){
                for(size_t i=0;i<Size();i++){
                    tmp[i]=_start[i];
                }
                delete[] _start;
            }
            _start=tmp;
            _finish=_start+size;
            _endofStorage=_start+n;
        }
    }
    void Resize(size_t n,const T& value=T()){
        if(n<=Size()){
            _finish=_start+n;
            return;
        }
        else{
            if(n>Capacity()){
                Reserve(n);
            }
            while(_finish!=_start+n){
                *_finish=value;
                ++_finish;
            }
        }
    }
    void PushBack(const T &x){
        Insert(end(),x);
    }
        void Insert(iterator pos,const T& x){//在pos前插入x
            assert(pos<=_finish);//断言参数pos<尾，若此处为假则直接跳出
            size_t posindex=pos-_start;
            if(_finish==_endofStorage){//若有效尾=存储限制，则需要扩容
                size_t newCapacity=Capacity()==0?2:Capacity()*2;
                Reserve(newCapacity);//调用扩容函数
                pos=_start+posindex;
            }
            iterator end=_finish;
            while(end>pos){//pos和其后的均后移1位
                *end=*(end-1);
                --end;
            }
            *pos=x;
            ++_finish;
        }
    void popBack(){
        Erase(--end());
    }
        iterator Erase(iterator pos){
            assert(pos<end());
            iterator next=pos;
            while(pos<_finish-1){
                *pos=*(pos+1);
                ++pos;
            }
            --_finish;
            return next;
        }
    T& operator[](size_t pos){
        assert(pos<Size());
        return _start[pos];
    }
        const T&operator[](size_t pos)const{
            assert(pos<Size());
            return _start[pos];
        }
    iterator begin(){return _start;}
    iterator end(){return _finish;}
    const_iterator cbegin()const{return _start;}
    const_iterator cend()const{return _finish;}
    size_t Size(){return _finish-_start;}
    size_t Capacity(){return _endofStorage-_start;}
    size_t Size()const{return _finish-_start;}
    size_t Capacity()const{return _endofStorage-_start;}
private:
    iterator _start=nullptr;
    iterator _finish=nullptr;//指向有效数字的尾
    iterator _endofStorage=nullptr;//指向存储空间尾

};

int main(){
    Vector<int> vec;
    
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    vec.PushBack(5);
    for(size_t i=0;i<vec.Size();i++){
        cout<<vec[i]<<" ";
    
    }
    cout<<endl;
    vec.Resize(3);
    Vector<int>::iterator it=vec.begin();
    while(it!=vec.end()){
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
    vec.Resize(10,5);
    for(auto i:vec){
        cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}