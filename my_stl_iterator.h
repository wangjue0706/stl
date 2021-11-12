#include <stddef.h>
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class Category,
            class T,
            class Distance = ptrdiff_t,
            class Pointer = T*,
            class Reference =T&>
struct iterator
{
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::iterator_category  iterator_category;
    typedef typename Iterator::value_type  value_type;
    typedef typename Iterator::difference_type  difference_type;
    typedef typename Iterator::pointer  pointer;
    typedef typename Iterator::reference  reference;
};

template <class T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag iterator;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};

template <class T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag iterator;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};
// 内嵌和变量名 typename, 
// 当系统调用iterator_traits<InputIterator>::difference_type
// 会默认为该参数是一个具体的变量，但是此时我们要使用的是一个变量
// 名，所以需要用typename来额外声明。
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while(first!=last){
        n++;
        first++;
    }
    return n;
}

template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    return last-first;
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last){
    return __distance(first, last, iterator_traits<InputIterator>::category());
}

template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag){
    while(n--)++i;
}

template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag){
    if(n>=0){
        while(n--)++i;
    }else{
        while(n++)--i;
    }
}

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag){
    i+=n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n){
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    __distance(i, n, category());
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}
