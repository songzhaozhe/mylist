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
//using namespace std;

template<class T>class MyList;
template<class T> std::ostream & operator<< (std::ostream &os, const MyList<T> &obj);
//template<class T> MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2);
template<class T> MyList<T> operator + (const MyList<T> &l1, const T &item);

class OutOfRangeException{
	public:
		OutOfRangeException():message("index out of range"){}
		const char *what()const{return message;}
	private:
		const char *message;
};
class PopEmptyListException{
	public:
		PopEmptyListException():message("attempted to pop an empty list"){}
		const char *what()const{return message;}
	private:
		const char *message;
}; 
class NegativeSizeException{
	public:
		NegativeSizeException():message("list initialized with a negative number"){}
		const char *what()const{return message;}
	private:
		const char *message;
}; 

template<class T>
class MyList{	
friend std::ostream & operator<< <T>(std::ostream &os, const MyList<T> &obj);//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如： // [1, 2, 5, 4, 1]
friend MyList operator + <T>(const MyList<T> &l1, const MyList<T> &l2); //合并两个MyList
friend MyList operator + <T>(const MyList<T> &l1, const T &item); //同push(T item)，但不修改l1，返回一个新数组
private:
	T *a;
	int size;
	int capacity;
	void resize(int goal);//数组大小不够的时候将数组大小翻倍的操作。
	void quicksort(T a[],int low,int high);
public:
	MyList(){
		size = 0;
		capacity=100;
		a = new T [capacity];
	}
	MyList(int num, const T &item);//将item重复num次填入数组中。
	MyList(const MyList &l);//深复制另外一个MyList。
    MyList(T* arr, int len);//以arr的前len个元素构造数组
	void push(const T &item);//将item添加在MyList最后。
	T pop();//将MyList中最后一个元素删除，并返回这个删除的元素。
	void insert(int index, const T &item);//将item插入到place处。
	void clean();//清空数组。
	int get_size()const;//返回MyList中元素的数量。
	void erase(int start, int end); //删除MyList中第start到第end位的元素，包括两边。
	T get_item(int index)const;//返回第index个元素。
	MyList get_item(int start, int end)const;//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
	int count(const T &item)const;//返回MyList中和item相等的元素的个数。
	void remove(const T &item);//删除MyList中第一个和item相等的元素。
	MyList &operator = (const MyList &l);//赋值
	MyList &operator += (const T &item);//同push(T item)
	MyList &operator += (const MyList &l);//将一个MyList加入到本个MyList之后。
	T &operator [](int index);//返回第index个元素。
	const T&operator [](int index)const;
	void sort(bool less);//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。
    // 若less=true，按照从小到大排列，否则按从大到小排列
	void reverse();//将MyList的元素倒过来。
	~MyList(){delete [] a;}
};
template <class T>
void MyList<T>::resize (int goal = -1)
{
	T *tmp=a;
	if(goal==-1)
	capacity*=2;
	else while(capacity<goal)
	capacity*=2;
	a=new T[capacity];
	for(int i=0;i<size;++i)
	a[i]=tmp[i];
	delete [] tmp;
	return;	
}

template <class T>
MyList<T>::MyList(int num, const T &item)//将item重复num次填入数组中。
{
	if(num<0)throw NegativeSizeException();	
	capacity = 100;
	size=num;
	while(capacity<num)capacity*=2;	
	a = new T [capacity];
	for(int i=0;i<size;++i)
	a[i]=item;
}

template <class T>
MyList<T>::MyList(const MyList<T> &l)//深复制另外一个MyList。
{
	capacity=l.capacity;
	size=l.size;
	a=new T [capacity];
	for(int i=0;i<size;++i)
	a[i]=l.a[i];	
}

template <class T>
MyList<T>::MyList(T* arr, int len)//以arr的前len个元素构造数组
{
	if(len<0)throw NegativeSizeException();	
	capacity=100;
	size=len;
	while(capacity<len)size*=2;
	a=new T[capacity];
	for(int i=0;i<size;++i)
	a[i]=arr[i];	
}

template <class T>
void MyList<T>::push(const T &item)//将item添加在MyList最后。
{
	if(capacity==size)resize();
	a[size++]=item;
	return;	
}

template <class T>
T MyList<T>::pop()//将MyList中最后一个元素删除，并返回这个删除的元素。
{	
	if(size==0)throw PopEmptyListException();
	return a[--size];
}

template <class T>
void MyList<T>::insert(int index, const T &item)//将item插入到place处。
{
	if(index<0||index>size)throw OutOfRangeException();	
	if(capacity==size)resize();
	for(int i=size;i>index;--i)
	{
		a[i]=a[i-1];
	}
	a[index]=item;
	++size;
}

template <class T>
void MyList<T>::clean()//清空数组。
{
	for(int i=0;i<size;++i)
	a[i].~T();
	size=0;
}

template <class T>
int MyList<T>::get_size()const//返回MyList中元素的数量。
{
	return size; 
}

template <class T>
void MyList<T>::erase(int start, int end) //删除MyList中第start到第end位的元素，包括两边。
{
	if(start<0||end<0||start>=size||end>=size)throw OutOfRangeException();	
	int len=end-start+1;
	if(len<0)return;
	for(int i=start;i<=end;++i)
	{
		a[i]=a[i+len];
	}
	size-=len;
}

template <class T>
T MyList<T>::get_item(int index)const//返回第index个元素。
{
	if(index<0||index>=size)throw OutOfRangeException();
	return a[index];
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end)const//返回MyList中第start到第end位的元素，包括两边。此处需要像python一样接受负数，具体见测试代码。
{
	if(end<0)end+=size;
	if(start<0)start+=size;
	if(start<0||end<0||start>=size||end>=size)throw OutOfRangeException();
	int len=end-start+1;
	if(len<0)len=0;
	MyList<T> B(a+start,len);
	return B;
}

template <class T>
int MyList<T>::count(const T &item)const//返回MyList中和item相等的元素的个数。
{
	int cnt=0;
	for(int i=0;i<size;++i)
	if(a[i]==item)++cnt;
	return cnt;
}

template <class T>
void MyList<T>::remove(const T &item)//删除MyList中第一个和item相等的元素。
{
	int index;
	for(index=0;index<size;++index)
	if(a[index]==item)break;
	if(index==size)return;
	for(;index<size-1;++index)
	a[index]=a[index+1];
	--size;
}

template <class T>
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2) //合并两个MyList
{
	MyList<T> tmp;
	tmp.resize(l1.size+l2.size);
	tmp.size=l1.size+l2.size;
	int i;
	for(i=0;i<l1.size;++i)
	tmp.a[i]=l1.a[i];
	for(;i<l1.size+l2.size;++i)
	tmp.a[i]=l2.a[i-l1.size];
	return tmp;	
}

template<class T> 
MyList<T> operator + (const MyList<T> &l1, const T &item) //同push(T item)，但不修改l1，返回一个新数组
{
	MyList<T> tmp(l1);
	tmp.resize(l1.size+1);
	tmp.a[tmp.size]=item;
	++tmp.size;
	return tmp;	
}

template<class T>
MyList<T> & MyList<T>::operator = (const MyList<T> &l)//赋值
{
	capacity=l.capacity;
	size=l.size;
	a=new T [capacity];
	for(int i=0;i<size;++i)
	a[i]=l.a[i];
	return *this;	
}

template<class T>
MyList<T> & MyList<T>::operator += (const T &item)//同push(T item)
{
	if(size==capacity)resize();
	a[size]=item;
	++size;
	return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const MyList &l)//将一个MyList加入到本个MyList之后。
{
	resize(size+l.size);
	for(int i=size;i<size+l.size;++i)
	a[i]=l.a[i-size];
	size+=l.size;
	return *this;	
}

template<class T>
T &MyList<T>::operator [](int index)//返回第index个元素。
{
	if(index<0||index>=size)throw OutOfRangeException();	
	return a[index];
}

template<class T>
const T &MyList<T>::operator [](int index)const
{
	if(index<0||index>=size)throw OutOfRangeException();	
	return a[index];
}

template <class T>
std::ostream & operator<< (std::ostream &os, const MyList<T> &obj)//如果T是可以直接cout的类的话（比如int），按Python数组的格式输出MyList中的每一个元素，例如： // [1, 2, 5, 4, 1]
{
	os<<'[';
	int i;
	for(i=0;i<obj.size-1;++i)
	os<<obj.a[i]<<',';
	if(obj.size>0)os<<obj.a[i];
	os<<']';	
	return os;
}

template <class T>
void MyList<T>::quicksort(T a[],int low,int high)
{
	int mid,L=low,H=high;
	if(low>=high)return;
	T k=a[low];
	do{
		while(low<high&&a[high]>=k){--high;}
		if(low<high){a[low]=a[high];++low;}
		while(low<high&&a[low]<=k){++low;}
		if(low<high){a[high]=a[low];--high;}
	}while(low!=high);
	a[low]=k;
	mid=low;
	quicksort(a,L,mid-1);
	quicksort(a,mid+1,H);
}

template <class T>
void MyList<T>::sort(bool less=true)//实现一个快速排序或归并排序，对支持比较运算符（>=<）的类进行排序。  
  // 若less=true，按照从小到大排列，否则按从大到小排列
{
	quicksort(a,0,size-1);
	if(!less)reverse();
}

template <class T>
void MyList<T>::reverse()//将MyList的元素倒过来。
{
	MyList<T> tmp(*this);
	for(int i=0;i<size;++i)
	a[i]=tmp[size-i-1];	
}

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
		std::cout<<a[i]<<std::endl;
    b = a.get_item(4, -3); // b = [] *若start > end，返回空数组
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		std::cout<<a.get_item(i)<<std::endl;
	std::cout<<a.count(5)<<std::endl;
	b.clean(); // b = []
	std::cout<<b.get_size()<<std::endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	std::cout<<b<<std::endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	std::cout<<c.get_item(100, 105)<<std::endl;
	
	return 0;
}



