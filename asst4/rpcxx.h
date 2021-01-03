// -*- c++ -*-
#ifndef RPCXX_SAMPLE_H
#define RPCXX_SAMPLE_H
#include <string>
#include <cstdlib>
#include "rpc.h"
#include <iostream>

#include <typeinfo>

using namespace std;

namespace rpc {

// Protocol is used for encode and decode a type to/from the network.
//
// You may use network byte order, but it's optional. We won't test your code
// on two different architectures.

// TASK1: add more specializations to Protocol template class to support more
// types.
template <typename T> struct Protocol;

template <typename T> struct Protocol {
    static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const T &x) {
        return false;
    }
    static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, T &x) {
        *ok = false;
        return false;
    }
};

template <> struct Protocol<bool> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const bool &x) {
    if (*out_len < 1) return false;
    uint64_t bx = 0;
    memcpy(&bx, &x, 1);
    memcpy(out_bytes, &bx, 1);
    *out_len = 1;
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, bool &x) {
    if (*in_len < 1) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, 1);
    memcpy(&x, &bx, 1);
    *in_len = 1;
    return true;
  }
};

template <> struct Protocol<int> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const int &x) {
    if (*out_len < 4) return false;
    uint32_t bx = htonl((uint32_t) x);
    memcpy(out_bytes, &bx, 4);
    *out_len = 4;
    return true; 
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, int &x) {
    if (*in_len < 4) return false;
    uint32_t bx = 0;
    memcpy(&bx, in_bytes, 4);
    x = ntohl(bx);
    *in_len = 4;
    return true;
  }
};

template <> struct Protocol<unsigned int> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const unsigned int &x) {
    if (*out_len < 4) return false;
    uint32_t bx = htonl((uint32_t) x);
    memcpy(out_bytes, &bx, 4);
    *out_len = 4;
    return true; 
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, unsigned int &x) {
    if (*in_len < 4) return false;
    uint32_t bx = 0;
    memcpy(&bx, in_bytes, 4);
    x = ntohl(bx);
    *in_len = 4;
    return true;
  }
};

template <> struct Protocol<short> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const short &x) {
    if (*out_len < 4) return false;
    uint32_t bx = htonl((uint32_t) x);
    memcpy(out_bytes, &bx, 4);
    *out_len = 4;
    return true;
    
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, short &x) {
    if (*in_len < 4) return false;
    uint32_t bx = 0;
    memcpy(&bx, in_bytes, 4);
    x = ntohl(bx);
    *in_len = 4;
    return true;
  }
};

template <> struct Protocol<unsigned short> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const unsigned short &x) {
    if (*out_len < 4) return false;
    uint32_t bx = htonl((uint32_t) x);
    memcpy(out_bytes, &bx, 4);
    *out_len = 4;
    return true;
    
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, unsigned short &x) {
    if (*in_len < 4) return false;
    uint32_t bx = 0;
    memcpy(&bx, in_bytes, 4);
    x = ntohl(bx);
    *in_len = 4;
    return true;
  }
};

template <> struct Protocol<float> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const float &x) {
    if (*out_len < 4) return false;
    uint64_t bx;
    memcpy(&bx, &x, 4);
    memcpy(out_bytes, &bx, 4);
    *out_len = 4;
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, float &x) {
    if (*in_len < 4) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, 4);
    memcpy(&x, &bx, 4);
    *in_len = 4;
    return true;
  }
};

template <> struct Protocol<double> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const double &x) {
    if (*out_len < 8) return false;
    uint64_t bx;
    memcpy(&bx, &x, 8);
    memcpy(out_bytes, &bx, 8);
    *out_len = 8;
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, double &x) {
    if (*in_len < 8) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, 8);
    memcpy(&x, &bx, 8);
    *in_len = 8;
    return true;
  }
};

template <> struct Protocol<long> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const long &x) {
    if (*out_len < sizeof(long)) return false;
    uint64_t bx;
    memcpy(&bx, &x, sizeof(long));
    memcpy(out_bytes, &bx, sizeof(long));
    *out_len = sizeof(long);
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, long &x) {
    if (*in_len < sizeof(long)) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, sizeof(long));
    memcpy(&x, &bx, sizeof(long));
    *in_len = sizeof(long);
    return true;
  }
};

template <> struct Protocol<unsigned long> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const unsigned long &x) {
    if (*out_len < sizeof(unsigned long)) return false;
    uint64_t bx;
    memcpy(&bx, &x, sizeof(unsigned long));
    memcpy(out_bytes, &bx, sizeof(unsigned long));
    *out_len = sizeof(unsigned long);
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, unsigned long &x) {
    if (*in_len < sizeof(unsigned long)) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, sizeof(unsigned long));
    memcpy(&x, &bx, sizeof(unsigned long));
    *in_len = sizeof(unsigned long);
    return true;
  }
};

template <> struct Protocol<long long> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const long long &x) {
    if (*out_len < sizeof(long long)) return false;
    uint64_t bx;
    memcpy(&bx, &x, sizeof(long long));
    memcpy(out_bytes, &bx, sizeof(long long));
    *out_len = sizeof(long long);
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, long long &x) {
    if (*in_len < sizeof(long long)) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, sizeof(long long));
    memcpy(&x, &bx, sizeof(long long));
    *in_len = sizeof(long long);
    return true;
  }
};

template <> struct Protocol<unsigned long long> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const unsigned long long &x) {
    if (*out_len < sizeof(unsigned long long)) return false;
    uint64_t bx;
    memcpy(&bx, &x, sizeof(unsigned long long));
    memcpy(out_bytes, &bx, sizeof(unsigned long long));
    *out_len = sizeof(unsigned long long);
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, unsigned long long &x) {
    if (*in_len < sizeof(unsigned long long)) return false;
    uint64_t bx = 0;
    memcpy(&bx, in_bytes, sizeof(unsigned long long));
    memcpy(&x, &bx, sizeof(unsigned long long));
    *in_len = sizeof(unsigned long long);
    return true;
  }
};

template <> struct Protocol<char> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const char &x) {
    if (*out_len < sizeof(char)) return false;
    memcpy(out_bytes, &x, sizeof(char));
    *out_len = sizeof(char);
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, char &x) {
    if (*in_len < sizeof(char)) return false;
    memcpy(&x, in_bytes, sizeof(char));
    *in_len = sizeof(char);
    return true;
  }
};

template <> struct Protocol<unsigned char> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const unsigned char &x) {
    if (*out_len < sizeof(unsigned char)) return false;
    memcpy(out_bytes, &x, sizeof(unsigned char));
    *out_len = sizeof(unsigned char);
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, unsigned char &x) {
    if (*in_len < sizeof(unsigned char)) return false;
    memcpy(&x, in_bytes, sizeof(unsigned char));
    *in_len = sizeof(unsigned char);
    return true;
  }
};

template <> struct Protocol<std::string> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len, const string &x) {
    std::cout << "Entering String Protocol" << std::endl;
    if (*out_len < x.length()+4) return false;

    int size = x.length();

    memcpy(out_bytes, &size, 4); //copies size of string
    memcpy(out_bytes+4, x.c_str(), x.length()); //copies actual string

    *out_len = x.length()+4;
    std::cout << "Leaving String Protocol, outlen" <<*out_len << std::endl;
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok, string &x) {
    if (*in_len < 4) return false;
    
    int size;

    memcpy(&size, in_bytes, 4);
    if (*in_len < size+4) return false;

    char cstr[size];

    x = "";

    memset(cstr, 0, size);
    memcpy(cstr, in_bytes+4, size);

    for (int i = 0; i < size; ++i) {
        x += cstr[i];
        cout << x << endl;
    }

    *in_len = size+4;

    return true;
    
  }
};

template <> struct Protocol<void> {
  static bool Encode(uint8_t *out_bytes, uint32_t *out_len) {
    // if (*out_len < sizeof(unsigned char)) return false;
    // memcpy(out_bytes, &x, sizeof(unsigned char));
    *out_len = 0;
    return true;
  }
  static bool Decode(uint8_t *in_bytes, uint32_t *in_len, bool *ok) {
    // if (*in_len < sizeof(unsigned char)) return false;
    // memcpy(&x, in_bytes, sizeof(unsigned char));
    *in_len = 0;
    return true;
  }
};

// TASK2: Client-side
class IntParam : public BaseParams {
  int p;
 public:
  IntParam(int p) : p(p) {}

  bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
    return Protocol<int>::Encode(out_bytes, out_len, p);
  }
};

template<typename T>
class InputParam : public BaseParams {
  T p;
 public:
  InputParam(T p) : p(p) {}

  bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
    std::cout << "Encoding " << p << std::endl;
    return Protocol<T>::Encode(out_bytes, out_len, p);
  }
};

template<>
class InputParam<void> : public BaseParams {
 public:
  bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
    return Protocol<void>::Encode(out_bytes, out_len);
  }
};

// class VoidParam : public BaseParams {
//  public:

//   bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
//     return Protocol<void>::Encode(out_bytes, out_len);
//   }
// };

/*  THIS IS WHAT ADRIAN ORIGINALLY ADDED: THIS IS THE HARD CODED WAY TO GET MAX 47/50

// class VoidParam : public BaseParams {
//  public:

//   bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
//     return true;
//   }
// };
class UnsignedIntParam : public BaseParams {
  unsigned int p;
 public:
  UnsignedIntParam(unsigned int p) : p(p) {}

  bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
    return Protocol<unsigned int>::Encode(out_bytes, out_len, p);
  }
};

class StringParam : public BaseParams {
  std::string p;
 public:
  StringParam(std::string p) : p(p) {}

  bool Encode(uint8_t *out_bytes, uint32_t *out_len) const override {
    return Protocol<std::string>::Encode(out_bytes, out_len, p);
  }
};
*/

// TASK2: Server-side
template <typename Svc>
class IntIntProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {
    // cout << "--------------------Entering DecodeAndExecute: Int Int----------" << endl;                      

    int x;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<int>::Decode(in_bytes, in_len, ok, x) || !*ok) {
      return false;
    }
    // Now we cast the function pointer func_ptr to its original type.
    //
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = int (Svc::*)(int);
    auto p = func_ptr.To<FunctionPointerType>();
    int result = (((Svc *) instance)->*p)(x);
    std::cout << "int result is " << result <<std::endl;

    if (!Protocol<int>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false; 
      return false;
    }

    // cout << "--------------------Exiting DecodeAndExecute: Int Int----------" << endl;   
    return true;
  }
};

//One in one out arg
template <typename Svc, typename RT, typename FA>
class RTFAProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {
    // cout << "--------------------Entering DecodeAndExecute: Int Int----------" << endl;                      
    FA x;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<FA>::Decode(in_bytes, in_len, ok, x) || !*ok) {
      return false;
    }
    // Now we cast the function pointer func_ptr to its original type.
    //
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = RT (Svc::*)(FA);
    auto p = func_ptr.To<FunctionPointerType>();
    RT result = (((Svc *) instance)->*p)(x);
    if (!Protocol<RT>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false; 
      return false;
    }
    // cout << "--------------------Exiting DecodeAndExecute: Int Int----------" << endl;   
    return true;
  }
};

template <typename Svc>
class VoidVoidProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    // cout << "--------------------Entering DecodeAndExecute: Int Int----------" << endl;                      
    // int x;

    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<void>::Decode(in_bytes, in_len, ok) || !*ok) {
      return false;
    }
    // Now we cast the function pointer func_ptr to its original type.
    using FunctionPointerType = void (Svc::*)(void);
    auto p = func_ptr.To<FunctionPointerType>();
    (((Svc *) instance)->*p)();

    if (!Protocol<void>::Encode(out_bytes, out_len)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false; 
      return false;
    }
    // cout << "--------------------Exiting DecodeAndExecute: Int Int----------" << endl;   
    return true;

  }
};

template <typename Svc>
class BoolVoidProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {
    cout << "--------------------Entering DecodeAndExecute: Bool Void----------" << endl;                      
    // bool x;
    // Return false if buffer isn't large enough, or fatal error happens during parsing.
    // if (!Protocol<void>::Decode(in_bytes, in_len, ok, x) || !*ok) {
    if (!Protocol<void>::Decode(in_bytes, in_len, ok) || !*ok) {
      return false;
    }
    // Cast the function pointer func_ptr to its original type.
    using FunctionPointerType = bool (Svc::*)(void);
    auto p = func_ptr.To<FunctionPointerType>();
    bool result = (((Svc *) instance)->*p)();
    std::cout << "bool result is " << result <<std::endl;

    if (!Protocol<bool>::Encode(out_bytes, out_len, result)) {
        //if out_len not large enough (Should not be here)
      *ok = false; 
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: Bool Void----------" << endl;   
    return true;

  }
};

template <typename Svc>
class UnsignedIntStringProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    cout << "--------------------Entering DecodeAndExecute: Uint String----------" << endl;                        
    unsigned int x;
    std::cout << "Before: in_bytes is " << *in_len << std::endl;
    std::cout << "Before: in_len is " << *in_bytes << std::endl;


    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<unsigned int>::Decode(in_bytes, in_len, ok, x) || !*ok) {
      return false;
    }

    std::cout << "X is now " << x << std::endl;
    std::cout << "After: out_bytes is " << *out_bytes << std::endl;
    std::cout << "After: out_len is " << *out_len << std::endl;


    // Now we cast the function pointer func_ptr to its original type.
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = std::string (Svc::*)(unsigned int);
    auto p = func_ptr.To<FunctionPointerType>();
    std::string result = (((Svc *) instance)->*p)(x);

    if (!Protocol<std::string>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: Uint String----------" << endl;
    return true;
  }
};

template <typename Svc>
class StringStringProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {
    std::string x;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<std::string>::Decode(in_bytes, in_len, ok, x) || !*ok) {
      return false;
    }
    // Now we cast the function pointer func_ptr to its original type.
    //
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = std::string (Svc::*)(std::string);
    auto p = func_ptr.To<FunctionPointerType>();
    std::string result = (((Svc *) instance)->*p)(x);

    if (!Protocol<std::string>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    return true;
  }
};

template <typename Svc>
class StringIntStringProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    cout << "--------------------Entering DecodeAndExecute: String Int String----------" << endl;                        
    std::string x;
    int y;
    uint32_t remain = 256;
    uint32_t ret_len = remain;

    std::cout << "Before: in_bytes is " << *in_len << std::endl;
    std::cout << "Before: in_len is " << *in_bytes << std::endl;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<std::string>::Decode(in_bytes, &ret_len, ok, x) || !*ok) {
      return false;
    }
    // std::cout << "ret lem is  " << in_len; 

    // buffer_length -= in_len;
    in_bytes += *in_len - 4;
    remain -= ret_len;
    *in_len = remain;


    std::cout << "X is now " << x << "." << std::endl;
    std::cout << "After: in_bytes is " << *in_bytes << std::endl;
    std::cout << "After: in_len is " << *in_len << std::endl;


    if (!Protocol<int>::Decode(in_bytes, in_len, ok, y) || !*ok) {
      return false;
    }

    std::cout << "y is now " << y << std::endl;
    

    // Now we cast the function pointer func_ptr to its original type.
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = std::string (Svc::*)(std::string, int);
    auto p = func_ptr.To<FunctionPointerType>();
    std::string result = (((Svc *) instance)->*p)(x, y);

    if (!Protocol<std::string>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: String int String----------" << endl;
    return true;
  }
};

template <typename Svc>
class StringIntUnsignedIntProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    cout << "--------------------Entering DecodeAndExecute: String Int String----------" << endl;                        
    std::string x;
    int y;
    uint32_t remain = 256;
    uint32_t ret_len = remain;

    std::cout << "Before: in_bytes is " << *in_len << std::endl;
    std::cout << "Before: in_len is " << *in_bytes << std::endl;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<std::string>::Decode(in_bytes, &ret_len, ok, x) || !*ok) {
      return false;
    }
    // std::cout << "ret lem is  " << in_len; 

    // buffer_length -= in_len;
    in_bytes += *in_len - 4;
    remain -= ret_len;
    *in_len = remain;


    std::cout << "X is now " << x << "." << std::endl;
    std::cout << "After: in_bytes is " << *in_bytes << std::endl;
    std::cout << "After: in_len is " << *in_len << std::endl;


    if (!Protocol<int>::Decode(in_bytes, in_len, ok, y) || !*ok) {
      return false;
    }

    std::cout << "y is now " << y << std::endl;
    

    // Now we cast the function pointer func_ptr to its original type.
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = unsigned int (Svc::*)(std::string, int);
    auto p = func_ptr.To<FunctionPointerType>();
    unsigned int result = (((Svc *) instance)->*p)(x, y);

    if (!Protocol<unsigned int>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: String int String----------" << endl;
    return true;
  }
};

template <typename Svc>
class StringIntVoidProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    cout << "--------------------Entering DecodeAndExecute: String Int String----------" << endl;                        
    std::string x;
    int y;
    uint32_t remain = 256;
    uint32_t ret_len = remain;

    std::cout << "Before: in_bytes is " << *in_len << std::endl;
    std::cout << "Before: in_len is " << *in_bytes << std::endl;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<std::string>::Decode(in_bytes, &ret_len, ok, x) || !*ok) {
      return false;
    }
    // std::cout << "ret lem is  " << in_len; 

    // buffer_length -= in_len;
    in_bytes += *in_len - 4;
    remain -= ret_len;
    *in_len = remain;


    std::cout << "X is now " << x << "." << std::endl;
    std::cout << "After: in_bytes is " << *in_bytes << std::endl;
    std::cout << "After: in_len is " << *in_len << std::endl;


    if (!Protocol<int>::Decode(in_bytes, in_len, ok, y) || !*ok) {
      return false;
    }

    std::cout << "y is now " << y << std::endl;
    

    // Now we cast the function pointer func_ptr to its original type.
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = unsigned int (Svc::*)(std::string, int);
    auto p = func_ptr.To<FunctionPointerType>();
    (((Svc *) instance)->*p)(x, y);

    if (!Protocol<void>::Encode(out_bytes, out_len)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: String int String----------" << endl;
    return true;
  }
};

template <typename Svc>
class IntUnsignedIntLongUnsignedIntProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    cout << "--------------------Entering DecodeAndExecute: int uInt LUINT----------" << endl;                        
    int x;
    unsigned int y;
    uint32_t remain = 256;
    uint32_t ret_len = remain;

    std::cout << "Before: in_bytes is " << *in_len << std::endl;
    std::cout << "Before: in_len is " << *in_bytes << std::endl;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<int>::Decode(in_bytes, &ret_len, ok, x) || !*ok) {
      return false;
    }
    // std::cout << "ret lem is  " << in_len; 

    // buffer_length -= in_len;
    in_bytes += *in_len - 4;
    remain -= ret_len;
    *in_len = remain;


    std::cout << "X is now " << x << "." << std::endl;
    std::cout << "After: in_bytes is " << *in_bytes << std::endl;
    std::cout << "After: in_len is " << *in_len << std::endl;


    if (!Protocol<unsigned int>::Decode(in_bytes, in_len, ok, y) || !*ok) {
      return false;
    }

    std::cout << "y is now " << y << std::endl;
    

    // Now we cast the function pointer func_ptr to its original type.
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = long unsigned int (Svc::*)(int, unsigned int);
    auto p = func_ptr.To<FunctionPointerType>();
    long unsigned int result = (((Svc *) instance)->*p)(x, y);

    if (!Protocol<long unsigned int>::Encode(out_bytes, out_len, result)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: int uInt LUINT----------" << endl;
    return true;
  }
};

template <typename Svc>
class StringStringVoidProcedure : public BaseProcedure {
  bool DecodeAndExecute(uint8_t *in_bytes, uint32_t *in_len,
                        uint8_t *out_bytes, uint32_t *out_len,
                        bool *ok) override final {

    cout << "--------------------Entering DecodeAndExecute: String String Void----------" << endl;                        
    std::string x;
    std::string y;
    uint32_t remain = 256;
    uint32_t ret_len = remain;

    std::cout << "Input in len is  " << *in_len << std::endl;

    std::cout << "Before: in_bytes is " << *in_len << std::endl;
    std::cout << "Before: in_len is " << *in_bytes << std::endl;
    // This function is similar to Decode. We need to return false if buffer
    // isn't large enough, or fatal error happens during parsing.
    if (!Protocol<std::string>::Decode(in_bytes, &ret_len, ok, x) || !*ok) {
      return false;
    }
    std::cout << "ret len is  " << *in_len <<std::endl; 
    std::cout << "X is now " << x << "." << std::endl;
    std::cout << "After: in_bytes is " << *in_bytes << std::endl;
    std::cout << "After: in_len is " << *in_len << std::endl;


    // buffer_length -= in_len;
    in_bytes += *in_len - 143;
    remain -= ret_len;
    *in_len = remain;

    if (!Protocol<std::string>::Decode(in_bytes, in_len, ok, y) || !*ok) {
      return false;
    }

    std::cout << "y is now " << " with in len" << *in_len << y << std::endl;
    

    // Now we cast the function pointer func_ptr to its original type.
    // This incomplete solution only works for this type of member functions.
    using FunctionPointerType = void (Svc::*)(std::string, std::string);
    auto p = func_ptr.To<FunctionPointerType>();
    (((Svc *) instance)->*p)(x, y);

    if (!Protocol<void>::Encode(out_bytes, out_len)) {
      // out_len should always be large enough so this branch shouldn't be
      // taken. However just in case, we return an fatal error by setting *ok
      // to false.
      *ok = false;
      return false;
    }
    cout << "--------------------Exiting DecodeAndExecute: String String Void----------" << endl;
    return true;
  }
};

// TASK2: Client-side
// class IntResult : public BaseResult {
//   int r;
//  public:
//   bool HandleResponse(uint8_t *in_bytes, uint32_t *in_len, bool *ok) override final {
//     // std::cout << "Going to Decode: "<< r << std::endl;
//     return Protocol<int>::Decode(in_bytes, in_len, ok, r);
//   }
//   int &data() { return r; }
// };

template<typename T>
class Result : public BaseResult {
  T r;
public:
  bool HandleResponse(uint8_t *in_bytes, uint32_t *in_len, bool *ok) override final {
    // std::cout << "Going to Decode" << std::endl;
    return Protocol<T>::Decode(in_bytes, in_len, ok, r);
  }

  T &data() { return r; }
};

template<>
class Result<void> : public BaseResult{
  bool HandleResponse(uint8_t *in_bytes, uint32_t *in_len, bool *ok) override final {
    // std::cout << "Going to Decode" << std::endl;
    return Protocol<void>::Decode(in_bytes, in_len, ok);
  }

};

// TASK2: Client-side
class Client : public BaseClient {
 public:
  template <typename Svc>
  Result<int> *Call(Svc *svc, int (Svc::*func)(int), int x) {
    // cout << "--------------------Entering Call: Int Int----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // This incomplete solution only works for this type of member functions.
    // So the result must be an integer.
    auto result = new Result<int>;

    // We also send the paramters of the functions. For this incomplete
    // solution, it must be one integer.
    if (!Send(instance_id, func_id, new InputParam<int>(x), result)) {
      // Fail to send, then delete the result and return nullptr.
      delete result;
      return nullptr;
    }
    // std::cout << "Res data is " << result->data() << std::endl;
    // cout << "--------------------Exiting Call: Int Int----------" << endl;   
    return result;
  }

  template <typename Svc>
  Result<void> *Call(Svc *svc, void (Svc::*func)(void)) {
    cout << "--------------------Entering Call: Void Void----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // This incomplete solution only works for this type of member functions.
    // So the result must be an integer.
    auto result = new Result<void>;

    int x;
    // We also send the paramters of the functions. For this incomplete
    // solution, it must be one integer.
    if (!Send(instance_id, func_id, new InputParam<void>(), result)) {
      // Fail to send, then delete the result and return nullptr.
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: Void Void----------" << endl;
    return result;
  };

  template <typename Svc>
  Result<bool> *Call(Svc *svc, bool (Svc::*func)(void)) {
    cout << "--------------------Entering Call: Void bool----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<bool>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<void>(), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }

    cout << "--------------------Exiting Call: Void bool----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl;

    return result;
  };

  template <typename Svc>
  Result<std::string> *Call(Svc *svc, std::string (Svc::*func)(unsigned int), unsigned int x) {
    cout << "--------------------Entering Call: String UInt----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<std::string>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<unsigned int>(x), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String UInt----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl;
    return result;
  };

  template <typename Svc>
  Result<std::string> *Call(Svc *svc, std::string (Svc::*func)(std::string), std::string x) {
    cout << "--------------------Entering Call: String String----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<std::string>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<std::string>(x), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String String----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl; // 
    return result;
  };

  template <typename Svc>
  Result<std::string> *Call(Svc *svc, std::string (Svc::*func)(std::string, int), std::string x, int y) {
    cout << "--------------------Entering Call: String Int, String----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<std::string>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<std::string>(x), result) 
        || !Send(instance_id, func_id, new InputParam<int>(y), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String Int, String----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl; //
    return result;
  };

  template <typename Svc>
  Result<unsigned int> *Call(Svc *svc, unsigned int (Svc::*func)(std::string, int), std::string x, int y) {
    cout << "--------------------Entering Call: String Int, Uint----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<unsigned int>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<std::string>(x), result) 
        || !Send(instance_id, func_id, new InputParam<int>(y), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String Int, Uint----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl; //
    return result;
  };

  template <typename Svc>
  Result<void> *Call(Svc *svc, void (Svc::*func)(std::string, int), std::string x, int y) {
    cout << "--------------------Entering Call: String Int, Uint----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<void>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<std::string>(x), result) 
        || !Send(instance_id, func_id, new InputParam<int>(y), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String Int, Uint----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl; //
    return result;
  };

  template <typename Svc>
  Result<long unsigned int> *Call(Svc *svc, long unsigned int (Svc::*func)(int, unsigned int), int x, unsigned int y) {
    cout << "--------------------Entering Call: LUInt Int, Uint----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<long unsigned int>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<int>(x), result) 
        || !Send(instance_id, func_id, new InputParam<unsigned int>(y), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String Int, Uint----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl; //
    return result;
  };

  template <typename Svc>
  Result<void> *Call(Svc *svc, void (Svc::*func)(std::string, std::string), std::string x, std::string y) {
    cout << "--------------------Entering Call: LUInt Int, Uint----------" << endl;
    // Lookup instance and function IDs.
    int instance_id = svc->instance_id();
    int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

    // So the result is a bool.
    auto result = new Result<void>;

    // We also send the paramters of the functions. 
    if (!Send(instance_id, func_id, new InputParam<std::string>(x), result) 
        || !Send(instance_id, func_id, new InputParam<std::string>(y), result)) {
      // Fail to send, then delete the result and return nullptr.
      std::cout << "Failed to send" << std::endl;
      delete result;
      return nullptr;
    }
    cout << "--------------------Exiting Call: String Int, Uint----------" << endl;
    // std::cout << "Res data is " << result->data() << std::endl; //
    return result;
  };

  // template<typename Svc, typename RT, typename ... FA> 
  // Result<RT> * Call(Svc *svc, RT (Svc::*func)(FA...), FA... inArgs) {
  //   std::cout << "WARNING: Calling (Packed FA)" 
  //         << typeid(decltype(func)).name()
  //         << " is not supported\n";
  //   return nullptr;
  // }

  // template<typename Svc, typename RT> 
  // Result<RT> * Call(Svc *svc, RT (Svc::*func)()) {

  //   // Lookup instance and function IDs.
  //   int instance_id = svc->instance_id();
  //   int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

  //   // This incomplete solution only works for this type of member functions.
  //   // So the result must be an integer.
  //   auto result = new Result<RT>();

  //   // std::cout << "FA inArg is " << inArgs << std::endl;
  //   std::cout << "Result is " << result << std::endl;

  //   // We also send the paramters of the functions. For this incomplete
  //   // solution, it must be one integer.
  //   // if (!Send(instance_id, func_id, new InputParam<FA>(inArgs), result)) {
  //   //   // Fail to send, then delete the result and return nullptr.
  //   //   delete result;
  //   //   return nullptr;
  //   // }
  //   // cout << "--------------------Exiting Call: Int Int----------" << endl;   
  //   return result;

  //   std::cout << "WARNING: Calling (No FA)" 
  //         << typeid(decltype(func)).name()
  //         << " is not supported\n";
  //   // return nullptr;
  // }

  // template<typename Svc, typename RT, typename FA> 
  // Result<RT> * Call(Svc *svc, RT (Svc::*func)(FA), FA inArgs) {

  //   // Lookup instance and function IDs.
  //   int instance_id = svc->instance_id();
  //   int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

  //   // This incomplete solution only works for this type of member functions.
  //   // So the result must be an integer.
  //   auto result = new Result<RT>();

  //   std::cout << "FA inArg is " << inArgs << std::endl;
  //   std::cout << "Result is " << result << std::endl;

  //   // We also send the paramters of the functions. For this incomplete
  //   // solution, it must be one integer.
  //   // if (!Send(instance_id, func_id, new InputParam<FA>(inArgs), result)) {
  //   //   // Fail to send, then delete the result and return nullptr.
  //   //   delete result;
  //   //   return nullptr;
  //   // }
  //   // cout << "--------------------Exiting Call: Int Int----------" << endl;   
  //   return result;

  //   std::cout << "WARNING: Calling (Single FA)" 
  //         << typeid(decltype(func)).name()
  //         << " is not supported\n";
  //   // return nullptr;
  // }

  // template<typename Svc, typename RT, typename FA, typename FA2> 
  // Result<RT> * Call(Svc *svc, RT (Svc::*func)(FA), FA inArgs, FA2 inArgs2) {

  //   // Lookup instance and function IDs.
  //   int instance_id = svc->instance_id();
  //   int func_id = svc->LookupExportFunction(MemberFunctionPtr::From(func));

  //   // This incomplete solution only works for this type of member functions.
  //   // So the result must be an integer.
  //   auto result = new Result<RT>();

  //   std::cout << "FA inArg is " << inArgs << std::endl;


  //   // We also send the paramters of the functions. For this incomplete
  //   // solution, it must be one integer.
  //   if (!Send(instance_id, func_id, new InputParam<FA>(inArgs), result)) {
  //     // Fail to send, then delete the result and return nullptr.
  //     delete result;
  //     return nullptr;
  //   }
  //   // cout << "--------------------Exiting Call: Int Int----------" << endl;   
  //   return result;

  //   std::cout << "WARNING: Calling (Double FA)" 
  //         << typeid(decltype(func)).name()
  //         << " is not supported\n";
  //   // return nullptr;
  // }
};


// TASK2: Server-side
template <typename Svc>
class Service : public BaseService {
 protected:
  void Export(int (Svc::*func)(int)) {
    cout << "--------------------Entering Export: Int Int----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new RTFAProcedure<Svc, int, int>());
    cout << "--------------------Exiting Export: Int Int----------" << endl;
  }

  // template<typename MemberFunction>
  // void Export(MemberFunction f) {
  //   std::cout << "In generic Export" << std::endl;
  //   std::cout << "MemberFunction f is " << decltype(f) << std::endl;

  //   ExportRaw(MemberFunctionPtr::From(f), new RTFAProcedure<Svc, int, int>());

  //   std::cout << "WARNING: Exporting " 
  //             << typeid(MemberFunction).name()
  //             << " is not supported\n";
  // }

  // template<>
  void Export(void (Svc::*func)(void)) {
    cout << "--------------------Entering Export: void void----------" << endl;
    cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new VoidVoidProcedure<Svc>());
    cout << "--------------------Exiting Export: void void----------" << endl;
  }

  // template<>
  void Export(bool (Svc::*func)(void)) {
    cout << "--------------------Entering Export: bool void----------" << endl;
    cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new BoolVoidProcedure<Svc>());
    cout << "--------------------Exiting Export: bool void----------" << endl;
  }

  void Export(std::string (Svc::*func)(unsigned int)) {
    cout << "--------------------Entering Export: UnInt String----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new UnsignedIntStringProcedure<Svc>());
  
  }

  void Export(std::string (Svc::*func)(std::string)) {
    cout << "--------------------Entering Export: String String----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new StringStringProcedure<Svc>());
  
  }

  void Export(std::string (Svc::*func)(std::string, int)) {
    cout << "--------------------Entering Export: String,Int String----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new StringIntStringProcedure<Svc>());
  
  }

  void Export(unsigned int (Svc::*func)(std::string, int)) {
    cout << "--------------------Entering Export: String,Int UnInt----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new StringIntUnsignedIntProcedure<Svc>());
  
  }

  void Export(void (Svc::*func)(std::string, int)) {
    cout << "--------------------Entering Export: String,Int Void----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new StringIntVoidProcedure<Svc>());
  
  }

  void Export(long unsigned int (Svc::*func)(int, unsigned int)) {
    cout << "--------------------Entering Export: Int,UnInt LongUnInt----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new IntUnsignedIntLongUnsignedIntProcedure<Svc>());
  
  }

  void Export(void (Svc::*func)(std::string, std::string)) {
    cout << "--------------------Entering Export: String,String Void----------" << endl;
    // cout << "func is " << func << endl;
    
    ExportRaw(MemberFunctionPtr::From(func), new StringStringVoidProcedure<Svc>());
  
  }

};

}

#endif /* RPCXX_SAMPLE_H */
