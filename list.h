#include <iostream>
#include <string.h>
using namespace std;
#define Maxsize 100
template <class T> class LinearList { //线性表抽象类
  public: //抽象类里面不能放构造函数除非函数名相同
    virtual int Size() const = 0;
    virtual int Lenth() const = 0;
    virtual int Search(T &x) const = 0;    //在表中搜索x;
    virtual int Locate(int i) const = 0;   //定位i;
    virtual T getdata(int i) const = 0;    //获得第i个值,通过x返回
    virtual void setdata(int i, T &x) = 0; //修改第i个位置值为x
    virtual bool Insert(int i, T &x) = 0;  //在i之后插入x
    virtual bool Remove(int i, T &x) = 0;  //删除i的值，通过x返回
    virtual bool Isempty() = 0;            // list是否为空
    virtual bool Isfull() = 0;             //表满
    // virtual void Sort() = 0;                     //表排序
    virtual void input() = 0;  //表输入
    virtual void output() = 0; //表输出
    // virtual LinearList<T> operator=(LinearList<T> &L) = 0; //表复制
};


template <class T> struct Linknode {
    T data;
    Linknode<T> *next;
    Linknode(Linknode<T> *p = NULL) { next = p; }
    Linknode(T &item, Linknode<T> *p = NULL) { data = item, next = p; }
};
// template <class T> typedef struct Linknode<T> *list;
template <class T> class List : public LinearList<T> { //
  protected:
    Linknode<T> *first;

  public:
    List() { first = new Linknode<T>; } //构造函数,建立头结点
    /*List(const T &x) {
        first = new Linknode<T>(x);
    } //构造函数，建立无头结点，有第一个节点*/
    List(List<T> &L);
    void makeempty();        //释放空间的函数
    ~List() { makeempty(); } //析构函数
    int Lenth() const;       //表长
    int Size() const {
        cout << "budediaoyong" << endl;
        return 0;
    }
    int Locate(int i) const {
        cout << "budediaoyong" << endl;
        return 0;
    }
    bool Isfull() {
        cout << "budediaoyong" << endl;
        return false;
    }
    int Search(T &x) const;            //在表中搜索x;
    Linknode<T> *Locatep(int i) const; //定位i;
    Linknode<T> *getfirst() const{return first;}
    T getdata(int i) const;    //获得第i个值
    void setdata(int i, T &x); //修改第i个位置值为x
    bool Insert(int i, T &x);  //在第i个元素之后的位置插入x
    bool Remove(int i, T &x);  //删除i的值，通过x返回
    bool Isempty() { return (first->next == NULL) ? true : false; } //表空
    void input();                                                   //表输入
    void output();                                                  //表输出
    // SeqList<T> operator=(SeqList<T> &L) ; //表复制 感觉没必要
};
template <class T> List<T>::List(List<T> &L) { //逐个节点复制
    T value;
    Linknode<T> *cur1 = L.Locatep(0);
    Linknode<T> *cur2 = first;
    while (cur1->next != NULL) {
        value = cur1->next->data;
        Linknode<T> *newcur = new Linknode<T>(value);
        cur2->next = newcur;
        cur2 = cur2->next;
        cur1 = cur1->next;
    }
}
template <class T> void List<T>::makeempty() {
    Linknode<T> *del;
    while (first->next) {
        del = first->next;
        first->next = del->next;
        delete del;
    }
    delete first;
}
template <class T> int List<T>::Lenth() const {
    Linknode<T> *cur = first->next;
    int count = 0;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}
template <class T>
int List<T>::Search(T &x) const { //搜索成功返回数据位置，否则返回0
    Linknode<T> *cur = first->next;
    int count = 0;
    while (cur != NULL) {
        count++;
        if (cur->data == x) {
            break;
        }
        cur = cur->next;
    }
    return count;
}
template <class T>
Linknode<T> *List<T>::Locatep(int i) const { //返回i个节点的指针，0为头结点
    if (i < 0)
        return NULL;
    Linknode<T> *cur = first;
    for (int k = 0; k < i; k++)
        cur = cur->next;
    return cur;
}
template <class T> T List<T>::getdata(int i) const { //获得第i个值
    Linknode<T> *cur = Locatep(i);
    if (cur == NULL || i == 0) { //头结点为空节点
        cout << "chazhaobudao" << endl;
        return 0;
    } else
        return cur->data;
}
template <class T> void List<T>::setdata(int i, T &x) {
    Linknode<T> *cur = Locatep(i);
    if (cur == NULL || i == 0) {
        cout << "chazhaobudao" << endl;
        return;
    } else
        cur->data = x;
}
template <class T> bool List<T>::Insert(int i, T &x) {
    Linknode<T> *cur = Locatep(i);
    if (cur == NULL) {
        cout << "chazhaobudao" << endl;
        return false;
    }
    Linknode<T> *temp = new Linknode<T>(x);
    if (temp == NULL) {
        cerr << "no space" << endl;
        exit(1);
    }
    temp->next = cur->next;
    cur->next = temp;
    return true;
}
template <class T> bool List<T>::Remove(int i, T &x) {
    Linknode<T> *cur = Locatep(i - 1);
    Linknode<T> *temp = cur->next;
    if (cur == NULL || temp == NULL) {
        cout << "chazhaobudao" << endl;
        return false;
    }
    x = temp->data;
    cur->next = temp->next;
    delete temp;
    return true;
}
template <class T> void List<T>::input() {
    cout << "please enter the number of data:" << endl;
    int k;
    cin >> k;
    T x;
    cout << "please enter " << k << " data" << endl;
    Linknode<T> *cur = first;
    for (int j = 0; j < k; j++) {
        cin >> x;
        Linknode<T> *newcur = new Linknode<T>(x);
        cur->next = newcur;
        cur = cur->next;
    }
}
template <class T> void List<T>::output() {
    Linknode<T> *cur = first->next;
    while (cur) {
        cout << cur->data << ' ';
        cur = cur->next;
    }
}
/*void union_list(SeqList<int> &LA, SeqList<int> &LB) { // b并入A
    int n = LA.Lenth(), m = LB.Lenth(), s, k;
    for (int j = 1; j <= m; j++) {
        k = LB.getdata(j);
        s = LA.Search(k);
        if (s == 0) {
            LA.Insert(n, k);
            n++;
        }
    }
}*/
