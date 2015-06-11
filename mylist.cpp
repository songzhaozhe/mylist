/*
 * 实现一个list类命名为MyList，其功能与python数组类似。可以用数组实现，也可以用链表实现。
 * 必须使用template <class T>，不允许使用<iostream>以外的库。
 * 需要实现的功能与测试代码见下。请务必搞清楚每一项的意义，比如什么时候需要用友元函数什么时候需要const什么时候需要&。
 * 当某些由用户正常操作可能产生的run time error（如pop一个空数组，或访问一个超出下标的元素），
 * 请使用try-catch-throw处理错误。
 * 以下类定义不保证完全正确，请根据实际需求修改，以实现样例功能为主。
 */

/* 
 * 本练习不涉及到虚类和类继承，但是期末考试我就不知道了。如果有时间可以用书上的shape类来练习。
 */

#include<iostream>
using namespace std;

template<class T>
class MyList{
private:
	T *a;
	int size;
	void double_space();//数组大小不够的时候将数组大小翻倍的操作。
public:
	MyList(){
		size = 100;
		a = new int [size];
	}
	MyList(int num, const T &item);//将item重复num次填入数组中。
	MyList(const MyList &l);//深复制另外一个MyList。
    MyList(T* arr, int len);//以arr的前len个元素构造数组

	void push(const T &item);//将item添加在MyList最后。
	T pop();//将MyList中最后一个元素删除，并返回这个删除的元素。
	void insert(int index, const T &item);//将item插入到place处。
	void clean();//清空数组。
	int get_size();//返回MyList中元素的数量。
	void erase(int start, int end); //删除MyList中第start到第end位的元素，包括两边。
	T get_item(int index);//返回第index个元素。
	MyList get_item(int start, int end);//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
	int count(const T &item);//返回MyList中和item相等的元素的个数。
	void remove(const T &item);//删除MyList中第一个和item相等的元素。


	friend MyList operator + (const MyList &l1, const MyList &l2); //合并两个MyList
    friend MyList operator + (const MyList &l1, const T &item); //同push(T item)，但不修改l1，返回一个新数组
	MyList &operator = (const MyList &l);//赋值
	MyList &operator += (const T &item);//同push(T item)
	MyList &operator += (const MyList &l);//将一个MyList加入到本个MyList之后。
	T &operator [](int index);//返回第index个元素。
	friend ostream & operator<<(ostream &os, const MyList &obj);//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如：
    // [1, 2, 5, 4, 1]

	void sort(bool less=true);//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
    // 若less=true，按照从小到大排列，否则按从大到小排列
	void reverse();//将MyList的元素倒过来。

	~MyList(){delete [] a;}
};

int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}



