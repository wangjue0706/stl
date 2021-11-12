#include "my_stl_construct.h"
#include <memory>
template<class InputIterator, class ForwardIterator>
ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
    for(InputIterator i=first;i<last;++i){
        construct(&*(result+(i-first)), *i);
    }
    return result+(last-first);
}

template<class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x){
    for(ForwardIterator i=first;i<last;++i){
        construct(&*i, x);
    }
    return first;
}

template<class ForwardIterator, class Size, class T>
ForwardIterator
uninitialized_fill_n(ForwardIterator first, Size n, const T& x){
    for(ForwardIterator i=first;i-first<n;++i){
        construct(&*i, x);
    }
    return first;
}

