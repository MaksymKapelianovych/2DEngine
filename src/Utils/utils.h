#ifndef UTILS_H
#define UTILS_H
#include <type_traits>

namespace utils {

template <class T, class S>
bool check(T t, S s){
    return std::is_same<T, S>::value;
}

}


#endif // UTILS_H
