#pragma once
#include <iostream>
#include <assert.h>

#define initial_capacity 1 //this value is assigned to "_capacity" parameter when default constructor is called

template <typename T>

class _vector {
private:

T* _base = nullptr; // the adress, where the first vector's element is situated
size_t _capacity =0; // vector's capacity
size_t _size =0; // vector's size

void recapacitor () {    // function to double capacity in case capacity is equal or smaller then size
   while (_capacity <= _size) {
    _capacity *= 2;
   // std::cout << "New capacity = " << _capacity << "\tnew size =" << _size << '\n'; 
   }
}

public: //********************************** constructors **********************************//

_vector() : _capacity(initial_capacity), _size(0) {               // default constructor
    _base = new T [_capacity];
    for (size_t i = 0; i < _capacity; ++i) _base[i] = 0;
    // std::cout << "Default constructor with no parameters was called\n";
}

_vector(size_t recieved_size_val) : _capacity(initial_capacity), _size(recieved_size_val) {    // constrctor for vector of fixed size
    if (_capacity <= _size) recapacitor();
    _base = new T [_capacity];
    for (size_t i = 0; i < _capacity; ++i) _base[i] = 0;
    // std::cout << "Default constructor with recieved size parameter was called\n";   
}

_vector(size_t recieved_size_val, T value) : _capacity(initial_capacity), _size(recieved_size_val) {    // constrctor for vector of fixed size, filled with recieved value
    if (_capacity <= _size) recapacitor();
    _base = new T [_capacity];
    for (size_t i = 0; i < _size; ++i) _base[i] = value;
    for (size_t i = _size; i < _capacity; ++i) _base[i] = 0;
    // std::cout << "Default constructor with recieved size and filling in value parameters was called\n"; 
}

_vector(const _vector& other_vector) : _capacity(other_vector._capacity), _size(other_vector._size) { // copy constructor
    if (this->_base != nullptr) delete [] _base;
    _base = new T [_capacity];
    for (size_t i = 0; i < _size; ++i) _base[i] = other_vector[i];
    // std::cout << "Copy constructor was called\n";   
}

_vector(_vector&& other_vector) noexcept : _capacity(other_vector._capacity), _size(other_vector._size) {    // move constructor
    if (this->_base != nullptr) delete [] _base;
    _base = other_vector._base;
    other_vector._base = nullptr;   
    other_vector._capacity = 0;
    other_vector._size = 0;
    // std::cout << "Move constructor was called\n";   
}
//******************************    destructor  ********************************************//
~_vector() {
    delete [] _base;
    _base = nullptr;
    // std::cout << "Destructor was called\n";
}

//******************************    operator's overloading     ****************************//
_vector<T>& operator = (const _vector<T>& other_vector) { // copy assigment
    if (this->_base != nullptr) delete [] _base;
    _capacity = other_vector._capacity;
    _size = other_vector._size;
    _base = new T [_capacity];
    for (size_t i = 0; i < _size; ++i) _base[i] = other_vector[i];
    // std::cout << "Copy assigment was called\n"; 
    return *this;
}

_vector<T>& operator = (_vector&& other_vector) noexcept {   // move assigment
    if (this->_base != nullptr) delete [] _base;
    _base = other_vector._base;
    _capacity = other_vector._capacity;
    _size = other_vector._size;
    other_vector._base = nullptr;
    other_vector._capacity = 0;
    other_vector._size = 0;
    // std::cout << "Move assigment was called\n"; 
    return *this;
}

T& operator[] (size_t index)  { // []
    return _base[index];
}

const T& operator[] (size_t index) const { // const []
    return _base[index];
}

//****************************      iterators       *****************************************//
T* begin() {
		return &_base[0];
}

T* rbegin() {
    return &_base[_size-1];
}

const T* cbegin() const {
    return &_base[0];
}

const T* crbegin() const { 
    return &_base[_size-1];
}

T* end() {
   return &_base[_size];
}

T* rend() { 
    return &(_base[-1]);
}

const T* cend() const {
    return &_base[_size];
}

const T* crend() const { 
    return &(_base[-1]);
}

//***************************** getter and setter *********************//

T* base () const {                // returns adress of the vector's [0] element
    return this->_base;
}

size_t capacity () const {        // returns vector's capacity
    return this->_capacity;
}

void reserve (size_t new_capacity) {        //assigns a new capacity to current vector
    _capacity = new_capacity;
    T* temp_base = _base;
    _base = new T [_capacity];
    for (size_t i = 0; i < _size; ++i) _base[i] = temp_base[i];
    for (size_t i = _size; i < _capacity; ++i) _base[i] = 0;
    delete [] temp_base;
    temp_base = nullptr;
}

size_t size () const {            // returns vector's size
    return this->_size;
}

void resize (size_t new_size_val) {
    size_t previous_size = _size;
    _size = new_size_val;
    if (_capacity <=_size) {
        recapacitor();
        T* temp_base = _base;
        _base = new T [_capacity];
        for (size_t i = 0; i < previous_size; ++i) _base[i] = temp_base[i];
        for (size_t i = previous_size; i < _capacity; ++i) _base[i] = 0;
        delete [] temp_base;
        temp_base = nullptr;
    }
}

void resize (size_t new_size_val, T value_to_add) {
    size_t previous_size = _size;
    _size = new_size_val;
    if (_capacity <=_size) {
        recapacitor();
        T* temp_base = _base;
        _base = new T [_capacity];
        for (size_t i = 0; i < previous_size; ++i) _base[i] = temp_base[i];
        for (size_t i = previous_size; i < _capacity; ++i) _base[i] = 0;
        delete [] temp_base;
        temp_base = nullptr;
    }
    for (size_t i = previous_size; i < _size; ++i) _base[i] = value_to_add;
}
//**************************** methods ***********************************************************//

bool is_empty () const {
    return !_size;
}

void push_back (const T& value) {
     if (_size >= _capacity) {
        recapacitor();
        T* temp_base = _base;
        _base = new T [_capacity];
        for (size_t i = 0; i < _size; ++i) _base[i] = temp_base[i];
        for (size_t i = _size+1; i < _capacity; ++i) _base[i] = 0;
        delete [] temp_base;
        temp_base = nullptr;
    }
     _base[_size] = value;
     ++_size;
    // std::cout << "& push_back was called\n";
}

void push_back (T&& value) {
    if (_size >= _capacity) {
        recapacitor();
        T* temp_base = _base;
        _base = new T [_capacity];
        for (size_t i = 0; i < _size; ++i) _base[i] = temp_base[i];
        for (size_t i = _size+1; i < _capacity; ++i) _base[i] = 0;
        delete [] temp_base;
        temp_base = nullptr;
    }
     _base[_size] = std::move(value);
     ++_size;
     // std::cout << "&& push_back was called\n";
}

T pop_back () {
    T temp = _base[_size-1];
    _base[_size-1] = 0;
    --_size;
    return temp;
}

void remove (size_t index) {            //removes an element, using it's index in _vector
    size_t index_max_val = _size -1;
    assert (!(index > index_max_val));
    if(index != index_max_val) {
        for (size_t i = index; i < index_max_val; ++i) _base[i] = _base[i+1];
    _base[index_max_val] = 0;
    --_size;
}}

void fill (T value) {                   // fills all the position in this _vector in limits of size with value "value"
    for (int i = 0; i < _size; ++i) _base[i] = value;
}

T& at (size_t index) {
    size_t index_max_val = _size-1;
    assert(!(index > index_max_val));
    return _base[index];
}};
