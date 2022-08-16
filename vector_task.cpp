#include <iostream>

template <typename T>
class dynamic_array
{
private:
    unsigned int size = 0;
    unsigned int capacity = 2;
    T* arr;
    void copy();
public:
    dynamic_array();
    ~dynamic_array();
    void push_back(T value);
    void pop_back();
    T& operator [](const int index);
    bool empty();
    unsigned int get_size();
    unsigned int get_capacity();
};

template <typename T>
dynamic_array<T>::dynamic_array() {
    arr = new T[capacity]{};
}

template <typename T>
dynamic_array<T>::~dynamic_array() {
    delete[] arr;
}

template <typename T>
void dynamic_array<T>::copy() {
    T* ptr = new T[capacity]{};
    for(int i = 0; i < size; ++i) {
        ptr[i] = arr[i];
    }
    delete[] arr;
    arr = ptr;
}

template <typename T>
void dynamic_array<T>::push_back(T value) {
    if(size >= capacity) {
        capacity *= 2;
        copy();
    }

    arr[size] = value;
    ++size;
}

template <typename T>
void dynamic_array<T>::pop_back(){
    if(size < (capacity / 2)) {
        capacity /= 2;
        copy();
    }

    arr[size] = 0;
    --size;
}

template <typename T>
unsigned int dynamic_array<T>::get_size() {
    return size;
}

template <typename T>
T& dynamic_array<T>::operator [](const int index) {
    return arr[index];
}

template <typename T>
bool dynamic_array<T>::empty() {
    if(size) {
        return false;
    }
    return true;
}

template <typename T>
unsigned int dynamic_array<T>::get_capacity() {
    return capacity;
}


int main() {
    dynamic_array<int> vec;
    vec.push_back(2000);
    vec.push_back(234);
    vec.push_back(213);
    vec.push_back(453);
    
    for(int i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << "  ";
    }

    vec.pop_back();

    for(int i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << "  ";
    }

    return 0;
}