#include <iostream>
#include <stdexcept>
#include <stack>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;
    
public:
    CircularArray();                   
    CircularArray(int _capacity);       
    virtual ~CircularArray();           
    void push_front(T data);            
    void push_back(T data);             
    void insert(T data, int pos);       
    T pop_front();                      
    T pop_back();                      
    bool is_full();                     
    bool is_empty();                    
    int size();                         
    void clear();                       
    T &operator[](int i);                  
    void sort();                          
    bool is_sorted();                   
    void reverse();                         
    string to_string(string sep=" ");   

    void display();


private:
    int next(int);
    int prev(int);
};

template <class T>
void CircularArray<T>::display()
{
    int a=front;
    for (int i = 0; i < size(); i++){
        cout << (*this)[a] << ",";
        a=next(a);
    }
}

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->array = new T[_capacity];
    this->capacity = _capacity;
    this->front = this->back = -1;
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep)
{
    int a=front;
    string result = ""; 
    for (int i = 0; i < size(); i++){
        result += std::to_string((*this)[a]) + sep;
        a=next(a);
    }
    return result;    
}



template <class T>
bool CircularArray<T>::is_full(){
    return back == prev(front);
}


template <class T>
bool CircularArray<T>::is_empty(){
    return (front == -1) && (back==-1);
}


template<class T>
void CircularArray<T>::push_back(T data){
    if(is_empty()){
        front=0;
        back=0;
        array[back]=data;
    }
    else{
        if(is_full()){
            array[front]=data;
            front=next(front);
            back=next(back);
        }
        else{
            back=next(back);
            array[back]=data;
        }
    }
}



template <class T>
void CircularArray<T>::push_front(T data){
    if(is_empty()){
        front=next(front);
        back=next(back);
        array[0]=data;
    }
    else{
        if(is_full()){
            front=prev(front);
            back=prev(back);
            array[front]=data;
        }
        else{
            front=prev(front);
            array[front]=data;
        }
    }
}  


template <class T>
T CircularArray<T>::pop_front(){
    if(is_empty()){
        throw("is empty");
    }
    else{
        T elim=array[front];
        front=next(front);
        return elim;
    }  
}


template <class T>
T CircularArray<T>::pop_back(){
    if(is_empty()){
        throw("is empty");
    }
    else{
        T elim=array[back];
        back=prev(back);
        return elim;
    }
}


template <class T>
void CircularArray<T>::clear(){
    front = back = -1;
}

template <class T>
int CircularArray<T>::size(){
    if(is_empty())  return 0;
    return front > back ? (capacity-front+back+1) : (back-front+1);
}



template <class T>
T &CircularArray<T>::operator[](int i){
    return array[i];
}


template <class T>
void CircularArray<T>::sort(){
    if(is_empty()){
        throw("is empty");
    }
    int a=front;
    for (int i=0; i<size(); i++){
        int b=a;
        for(int j=i+1; j<size(); j++){
            b=next(b);
            if(array[b]<array[a]){
                T temp = array[a];
                array[a] = array[b];
                array[b] = temp;
            }
        }
        a=next(a);
    }
    
}

template <class T>
bool CircularArray<T>::is_sorted(){
    CircularArray<T>* array2 = new CircularArray<int>(capacity);
    int front2=front;
    for (int i = 0; i < size(); i++){
        array2->push_back(array[front2]);
        front2=next(front2);
    }
    array2->sort();
    for (int i = 0; i < size(); i++){
        if( array[front + i] != (*array2)[front + i]){
            return false;
        }
    }
    return true;
}

template <class T>
void CircularArray<T>::reverse(){
    stack<int> stack;
    int a=front;
    for (int i = 0; i < size(); i++) {
        stack.push(array[a]);
        a=next(a);
    }
    a=front;
    while (!stack.empty()){
        array[a] = stack.top();
        stack.pop();
        a=next(a);
    }
}

template <class T>
void CircularArray<T>::insert(T data, int pos){
    int a=front;
    for (int i = 0; i <pos; i++)
    {
        a=next(a);
    }
    array[a]=data;
}