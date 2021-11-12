#include "my_stl_alloc.h"
#include "my_stl_uninitialized.h"
//定义list的结点
template <class T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

//定义list的iterator
template<class T, class Ref, class Ptr>
struct __list_iterator{
    typedef __list_iterator<T, T&, T*> iterator;
    typedef __list_iterator<T, Ref, Ptr> self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T>* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node;

    __list_iterator(link_type x):node(x) { }
    __list_iterator() { }
    __list_iterator(const iterator& x):node(x.node) { }

    bool operator==(const self & x) const { return node==x.node; }
    bool operator!=(const self & x) const { return node!=x.node; }
    reference operator*() const { return node->data; }
    pointer operator->() const { return &(node->data);}
    self& operator++() { node = (link_type)node->next; return *this; }
    self operator++(int) { self tmp = *this; ++*this; return tmp;}
    self& operator--() { node = (link_type)node->prev; return *this; }
    self operator--(int) { self tmp = *this; --*this; return tmp;}
};

//定义list
template<class T,class Alloc=alloc>
class list{
protected:
    typedef __list_node<T> list_node;
public:
    typedef list_node* link_type;
    typedef __list_iterator<T, T&, T*> iterator;
    typedef size_t size_type;
    typedef T& reference;

protected:
    link_type node;

public:
    iterator begin(){ return (link_type)(node->next); }
    iterator end(){ return node; }
    bool empty() const { return node->next==node; }
    size_type size() const { return (size_type)distance(begin(),end());}
    reference front() { return *begin(); }
    reference back() { return *end(); }
};