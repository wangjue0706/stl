#include <iostream>

//using namespace std;

struct _List_node_base
{
    /* data */
    _List_node_base(){
        _M_prev=this;
        _M_next=this;
    }
    _List_node_base* _M_next;
    _List_node_base* _M_prev;
};

template<typename _Tp>
    struct _List_node:public _List_node_base
    {
        /* data */
        _List_node(_Tp& __x):_List_node_base(){
            _M_data=__x;
        }
        _List_node<_Tp>* operator->() const{
            return this;
        }
        _Tp _M_data;
    };

template<typename _Tp>
    struct _List_iterator
    {
        /* data */
        typedef _List_iterator<_Tp>                _Self;
        typedef _Tp                                value_type;
        typedef _Tp*                               pointer;
        typedef _Tp&                               reference;
        /*iterator需要实现的功能，初始化， == ！=，++*2 --*2 *和->*/
        _List_iterator():_M_node(){}
        _List_iterator(_List_node_base* __x):_M_node(__x){}
        bool operator==(_Self& __x){
            return _M_node==__x._M_node;
        }
        bool operator!=(_Self& __x){
            return _M_node!=__x._M_node;
        }
        reference operator*() const {
            return static_cast<_List_node<_Tp>*>(_M_node)->_M_data;
        }
        pointer operator->() const{
            return &static_cast<_List_node<_Tp>*>(_M_node)->_M_data;
        }
        _Self& operator++(){
            //++iter
            _M_node=_M_node->_M_next;
            return *this;
        }
        _Self operator++(int){
            //iter++
            _Self temp = *this;
            _M_node=_M_node->_M_next;
            return temp;
        }
        _Self& operator--(){
            //--iter
            _M_node=_M_node->_M_prev;
            return *this;
        }
        _Self operator--(int){
            //iter--
            _Self temp = *this;
            _M_node=_M_node->_M_prev;
            return temp;
        }  
        _List_node_base* _M_node;
    };
    
template<typename _Tp>
    class List:public _List_node_base{
        typedef _List_iterator<_Tp>   iterator;
        typedef _List_node<_Tp>   node;
        public:
            List():_List_node_base(){ }
            List(_Tp __x){
                node* temp=new node(__x);
                temp->_M_prev=this;
                temp->_M_next=this;
                _M_next=temp;
                _M_prev=temp;
            }
            void print(){
                iterator i = begin();
                iterator ii = end();
                while(i != ii){
                    std::cout << *i << " ";
                    i++;
                }
                std::cout << std::endl;
            }
            iterator begin(){
                return iterator(_M_next);
            }
            iterator end(){
                return iterator(this);
            }
            void insert(_Tp __x){
                node* t = new node(__x);
                iterator e=end();
                _List_node_base* temp=static_cast<_List_node_base*>(t);
                _List_node_base* end1 = e._M_node;
                _List_node_base* before = e._M_node->_M_prev;
                before->_M_next=temp;
                temp->_M_prev=before;
                temp->_M_next=end1;
                end1->_M_prev=temp;
            }
        
    };

    
int main(){
    auto a = new List<int>();
    a->insert(10);
    a->insert(20);
    a->insert(30);
    a->insert(40);
    a->insert(50);
    a->print();
    std::cout<<"Hello and bye"<<std::endl;
    return 0;
}