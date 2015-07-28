/*
 * ʵ��һ��list������ΪMyList���书����python�������ơ�����������ʵ�֣�Ҳ����������ʵ�֡�
 * ����ʹ��template <class T>��������ʹ��<iostream>����Ŀ⡣
 * ��Ҫʵ�ֵĹ�������Դ�����¡�����ظ����ÿһ������壬����ʲôʱ����Ҫ����Ԫ����ʲôʱ����Ҫconstʲôʱ����Ҫ&��
 * ��ĳЩ���û������������ܲ�����run time error����popһ�������飬�����һ�������±��Ԫ�أ���
 * ��ʹ��try-catch-throw�������
 * �����ඨ�岻��֤��ȫ��ȷ�������ʵ�������޸ģ���ʵ����������Ϊ����
 */

/* 
 * ����ϰ���漰���������̳У�������ĩ�����ҾͲ�֪���ˡ������ʱ����������ϵ�shape������ϰ��
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
friend std::ostream & operator<< <T>(std::ostream &os, const MyList<T> &obj);//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺 // [1, 2, 5, 4, 1]
friend MyList operator + <T>(const MyList<T> &l1, const MyList<T> &l2); //�ϲ�����MyList
friend MyList operator + <T>(const MyList<T> &l1, const T &item); //ͬpush(T item)�������޸�l1������һ��������
private:
	T *a;
	int size;
	int capacity;
	void resize(int goal);//�����С������ʱ�������С�����Ĳ�����
	void quicksort(T a[],int low,int high);
public:
	MyList(){
		size = 0;
		capacity=100;
		a = new T [capacity];
	}
	MyList(int num, const T &item);//��item�ظ�num�����������С�
	MyList(const MyList &l);//�������һ��MyList��
    MyList(T* arr, int len);//��arr��ǰlen��Ԫ�ع�������
	void push(const T &item);//��item�����MyList���
	T pop();//��MyList�����һ��Ԫ��ɾ�������������ɾ����Ԫ�ء�
	void insert(int index, const T &item);//��item���뵽place����
	void clean();//������顣
	int get_size()const;//����MyList��Ԫ�ص�������
	void erase(int start, int end); //ɾ��MyList�е�start����endλ��Ԫ�أ��������ߡ�
	T get_item(int index)const;//���ص�index��Ԫ�ء�
	MyList get_item(int start, int end)const;//����MyList�е�start����endλ��Ԫ�أ��������ߡ��˴���Ҫ��pythonһ�����ܸ�������������Դ��롣
	int count(const T &item)const;//����MyList�к�item��ȵ�Ԫ�صĸ�����
	void remove(const T &item);//ɾ��MyList�е�һ����item��ȵ�Ԫ�ء�
	MyList &operator = (const MyList &l);//��ֵ
	MyList &operator += (const T &item);//ͬpush(T item)
	MyList &operator += (const MyList &l);//��һ��MyList���뵽����MyList֮��
	T &operator [](int index);//���ص�index��Ԫ�ء�
	const T&operator [](int index)const;
	void sort(bool less);//ʵ��һ�����������鲢���򣬶�֧�ֱȽ��������>=<�������������
    // ��less=true�����մ�С�������У����򰴴Ӵ�С����
	void reverse();//��MyList��Ԫ�ص�������
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
MyList<T>::MyList(int num, const T &item)//��item�ظ�num�����������С�
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
MyList<T>::MyList(const MyList<T> &l)//�������һ��MyList��
{
	capacity=l.capacity;
	size=l.size;
	a=new T [capacity];
	for(int i=0;i<size;++i)
	a[i]=l.a[i];	
}

template <class T>
MyList<T>::MyList(T* arr, int len)//��arr��ǰlen��Ԫ�ع�������
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
void MyList<T>::push(const T &item)//��item�����MyList���
{
	if(capacity==size)resize();
	a[size++]=item;
	return;	
}

template <class T>
T MyList<T>::pop()//��MyList�����һ��Ԫ��ɾ�������������ɾ����Ԫ�ء�
{	
	if(size==0)throw PopEmptyListException();
	return a[--size];
}

template <class T>
void MyList<T>::insert(int index, const T &item)//��item���뵽place����
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
void MyList<T>::clean()//������顣
{
	for(int i=0;i<size;++i)
	a[i].~T();
	size=0;
}

template <class T>
int MyList<T>::get_size()const//����MyList��Ԫ�ص�������
{
	return size; 
}

template <class T>
void MyList<T>::erase(int start, int end) //ɾ��MyList�е�start����endλ��Ԫ�أ��������ߡ�
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
T MyList<T>::get_item(int index)const//���ص�index��Ԫ�ء�
{
	if(index<0||index>=size)throw OutOfRangeException();
	return a[index];
}

template <class T>
MyList<T> MyList<T>::get_item(int start, int end)const//����MyList�е�start����endλ��Ԫ�أ��������ߡ��˴���Ҫ��pythonһ�����ܸ�������������Դ��롣
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
int MyList<T>::count(const T &item)const//����MyList�к�item��ȵ�Ԫ�صĸ�����
{
	int cnt=0;
	for(int i=0;i<size;++i)
	if(a[i]==item)++cnt;
	return cnt;
}

template <class T>
void MyList<T>::remove(const T &item)//ɾ��MyList�е�һ����item��ȵ�Ԫ�ء�
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
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2) //�ϲ�����MyList
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
MyList<T> operator + (const MyList<T> &l1, const T &item) //ͬpush(T item)�������޸�l1������һ��������
{
	MyList<T> tmp(l1);
	tmp.resize(l1.size+1);
	tmp.a[tmp.size]=item;
	++tmp.size;
	return tmp;	
}

template<class T>
MyList<T> & MyList<T>::operator = (const MyList<T> &l)//��ֵ
{
	capacity=l.capacity;
	size=l.size;
	a=new T [capacity];
	for(int i=0;i<size;++i)
	a[i]=l.a[i];
	return *this;	
}

template<class T>
MyList<T> & MyList<T>::operator += (const T &item)//ͬpush(T item)
{
	if(size==capacity)resize();
	a[size]=item;
	++size;
	return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const MyList &l)//��һ��MyList���뵽����MyList֮��
{
	resize(size+l.size);
	for(int i=size;i<size+l.size;++i)
	a[i]=l.a[i-size];
	size+=l.size;
	return *this;	
}

template<class T>
T &MyList<T>::operator [](int index)//���ص�index��Ԫ�ء�
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
std::ostream & operator<< (std::ostream &os, const MyList<T> &obj)//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺 // [1, 2, 5, 4, 1]
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
void MyList<T>::sort(bool less=true)//ʵ��һ�����������鲢���򣬶�֧�ֱȽ��������>=<�������������  
  // ��less=true�����մ�С�������У����򰴴Ӵ�С����
{
	quicksort(a,0,size-1);
	if(!less)reverse();
}

template <class T>
void MyList<T>::reverse()//��MyList��Ԫ�ص�������
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
    b = a.get_item(4, -3); // b = [] *��start > end�����ؿ�����
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



