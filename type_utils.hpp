#ifndef __HJ_TYPE_UTILS_HPP__
#define __HJ_TYPE_UTILS_HPP__

#include <ostream>
#include <type_traits>

namespace hj {

template <typename Head, typename... Tail>
struct TypePrinter {
    static void print(std::ostream& os) {
        TypePrinter<Head>::print(os);
        os << ", ";
        TypePrinter<Tail...>::print(os);
    }
};

template <typename T>
struct TypePrinter<T> {
    static void print(std::ostream& os) {
        using Decayed = typename std::decay<T>::type;
        TypePrinter<Decayed>::print(os);
        if (std::is_const<T>::value) os << " const";
        if (std::is_volatile<T>::value) os << " volatile";
        if (std::is_lvalue_reference<T>::value) os << " &";
        else if (std::is_rvalue_reference<T>::value) os << " &&";
    }
};

template <>
struct TypePrinter<char> {
    static void print(std::ostream& os) { os << "char"; }
};

template <>
struct TypePrinter<short> {
    static void print(std::ostream& os) { os << "short"; }
};

template <>
struct TypePrinter<int> {
    static void print(std::ostream& os) { os << "int"; }
};



}

#endif
