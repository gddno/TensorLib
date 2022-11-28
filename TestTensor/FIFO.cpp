#include <Arduino.h>
 
using namespace std;

using FuncType = void(*)();//создаем шаблон для

template <typename T>
struct Queue {
  //конструктор по умолчанию
  Queue(){
      size = 0;
  }
  //дестурктор 
  ~Queue(){
    if(array) {
        delete[] array;     
    }
  }
  
  void push(T value){
      
     T* copy = new T[size+1];
     for(int i = 0; i < size; i++){
         copy[i] = array[i];
     }
     copy[size] = value;
     delete[] array;
     array = copy;
     
     size++;
  }
  
  T pop() {
      T front  = array[0];
      
     T* copy = new T[size-1];
     for(int i = 0; i < size-1; i++){
         copy[i] = array[i+1];
     }
     delete[] array;
     array = copy;
     
     size--;
     
     return front;
      
  }
  
//  void print() {
//      for(size_t i = 0; i < size; i++){
//          cout << array[i] << endl;
//      }
//  }
  
  bool isEmpty(){

    return (size) ? true : false; 
    // return (status == 1) ? "blue" : (status == 2) ? "yellow" : "red";
      
  }

  //
  int indexOf(T value){
    for(int i = 0; i < size; i++){
      if(value == array[i]){
        return i;
      }
    }
    return -1;
  }

  T& operator[](int index) { //переопределение
    return array[index];
  }

  
  T* array = nullptr;//смотрящий куда смотреть смотрит на кружку
  int size = 0;// размер того,что видит он.
  
  
};
