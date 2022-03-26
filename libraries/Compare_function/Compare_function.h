#ifndef Compare_function_h 
#define Compare_function_h
#include "Arduino.h"

template <typename T> T abs_temp(T arg){
  if(arg >= 0)return arg;
  else return -arg;
}

//渡された配列の絶対値の最大値を戻り値とする関数
template <typename T> T max_ele_abs(T* list, size_t len){
  T max_ele = abs_temp(list[0]);

  for(size_t i = 1;i < len;i++){
    if(max_ele < abs_temp(list[i]))max_ele = abs_temp(list[i]);
  }
  
  return max_ele; 
  }

//渡された配列の絶対値の最小値を戻り値とする関数
template <typename T> T min_ele_abs(T* list, size_t len){
  T min_ele = abs_temp(list[0]);

  for(size_t i = 1;i < len;i++){
    if(min_ele > abs_temp(list[i]))min_ele = abs_temp(list[i]);
    }
  
  return min_ele; 
  }

//渡された配列の最大値を戻り値とする関数
template <typename T> T max_ele(T* list, size_t len){
  T max_ele = list[0];

  for(size_t i = 1;i < len;i++){
    if(max_ele < list[i])max_ele = list[i];
    }
  
  return max_ele; 
  }

//渡された配列の最小値を戻り値とする関数
template <typename T> T min_ele(T* list, size_t len){
  T min_ele = list[0];

  for(size_t i = 1;i < len;i++){
    if(min_ele > list[i])min_ele = list[i];
    }
  
  return min_ele; 
  }

//渡された配列の絶対の最大値の位置を戻り値とする関数
template <typename T> size_t max_index_abs(T* list, size_t len){
  size_t max_index = 0;

  for(size_t i = 1;i < len;i++){
    if(abs_temp(list[max_index]) < abs_temp(list[i]))max_index = i;
    }
  
  return max_index; 
  }

//渡された配列の絶対値の最小値の位置を戻り値とする関数
template <typename T> size_t min_index_abs(T* list, size_t len){
  size_t min_index = 0;

  for(size_t i = 1;i < len;i++){
    if(abs_temp(list[min_index]) > abs_temp(list[i]))min_index = i;
    }
  
  return min_index; 
  }

//渡された配列の最大値の位置を戻り値とする関数
template <typename T> size_t max_index(T* list, size_t len){
  size_t max_index = 0;

  for(size_t i = 1;i < len;i++){
    if(list[max_index] < list[i])max_index = i;
    }
  
  return max_index; 
  }

//渡された配列の最小値の位置を戻り値とする関数
template <typename T> size_t min_index(T* list, size_t len){
  size_t min_index = 0;

  for(size_t i = 1;i < len;i++){
    if(list[min_index] > list[i])min_index = i;
    }
  
  return min_index; 
  }

#endif
