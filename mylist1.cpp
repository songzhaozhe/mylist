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
using namespace std;
template<class T>
class MyList;
template<class T>
ostream & operator<< (ostream &os, const MyList<T> &obj);


template<class T>
class MyList{
	
friend ostream & operator<< <T>(ostream &os, const MyList<T> &obj);//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺
    // [1, 2, 5, 4, 1]
private:
	T *a;
	int size;
	int currentsize;
	void double_space();//�����С������ʱ�������С�����Ĳ�����
public:
	MyList(){
		size = 100;
		currentsize=0;
		a = new T [size];
	}
	MyList(int num, const T &item);//��item�ظ�num�����������С�
	MyList(const MyList &l);//�������һ��MyList��
    MyList(T* arr, int len);//��arr��ǰlen��Ԫ�ع�������

	void push(const T &item);//��item�����MyList���
	T pop();//��MyList�����һ��Ԫ��ɾ�������������ɾ����Ԫ�ء�
	void insert(int index, const T &item);//��item���뵽place����
	void clean();//������顣
	int get_size();//����MyList��Ԫ�ص�������
	void erase(int start, int end); //ɾ��MyList�е�start����endλ��Ԫ�أ��������ߡ�
	T get_item(int index);//���ص�index��Ԫ�ء�
	MyList get_item(int start, int end);//����MyList�е�start����endλ��Ԫ�أ��������ߡ��˴���Ҫ��pythonһ�����ܸ�������������Դ��롣
	int count(const T &item);//����MyList�к�item��ȵ�Ԫ�صĸ�����
	void remove(const T &item);//ɾ��MyList�е�һ����item��ȵ�Ԫ�ء�


	friend MyList operator + (const MyList &l1, const MyList &l2); //�ϲ�����MyList
    friend MyList operator + (const MyList &l1, const T &item); //ͬpush(T item)�������޸�l1������һ��������
	MyList &operator = (const MyList &l);//��ֵ
	MyList &operator += (const T &item);//ͬpush(T item)
	MyList &operator += (const MyList &l);//��һ��MyList���뵽����MyList֮��
	T &operator [](int index);//���ص�index��Ԫ�ء�
	friend ostream & operator<<(ostream &os, const MyList &obj);//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺
    // [1, 2, 5, 4, 1]

	void sort(bool less=true);//ʵ��һ�����������鲢���򣬶�֧�ֱȽ��������>=<�������������
    // ��less=true�����մ�С�������У����򰴴Ӵ�С����
	void reverse();//��MyList��Ԫ�ص�������

	~MyList(){delete [] a;}
};

template <class T>
MyList<T>::MyList(int num, const T &item)//��item�ظ�num�����������С�
{
	size = 100;
	currentsize=num;
	a = new T [size];
	for(int i=0;i<currentsize;++i)
	a[i]=item;
}
template <class T>
MyList<T>::MyList(const MyList<T> &l)//�������һ��MyList��
{
	size=l.size;
	currentsize=l.currentsize;
	a=new T [size];
	for(int i=0;i<currentsize;++i)
	a[i]=l.a[i];	
}





    MyList(T* arr, int len);//��arr��ǰlen��Ԫ�ع�������

	void push(const T &item);//��item�����MyList���
	T pop();//��MyList�����һ��Ԫ��ɾ�������������ɾ����Ԫ�ء�
	void insert(int index, const T &item);//��item���뵽place����
	void clean();//������顣
	int get_size();//����MyList��Ԫ�ص�������
	void erase(int start, int end); //ɾ��MyList�е�start����endλ��Ԫ�أ��������ߡ�
	T get_item(int index);//���ص�index��Ԫ�ء�
	MyList get_item(int start, int end);//����MyList�е�start����endλ��Ԫ�أ��������ߡ��˴���Ҫ��pythonһ�����ܸ�������������Դ��롣
	int count(const T &item);//����MyList�к�item��ȵ�Ԫ�صĸ�����
	void remove(const T &item);//ɾ��MyList�е�һ����item��ȵ�Ԫ�ء�


	friend MyList operator + (const MyList &l1, const MyList &l2); //�ϲ�����MyList
    friend MyList operator + (const MyList &l1, const T &item); //ͬpush(T item)�������޸�l1������һ��������
	MyList &operator = (const MyList &l);//��ֵ
	MyList &operator += (const T &item);//ͬpush(T item)
	MyList &operator += (const MyList &l);//��һ��MyList���뵽����MyList֮��
	T &operator [](int index);//���ص�index��Ԫ�ء�

template <class T>
ostream & operator<< (ostream &os, const MyList<T> &obj)//���T�ǿ���ֱ��cout����Ļ�������int������Python����ĸ�ʽ���MyList�е�ÿһ��Ԫ�أ����磺 // [1, 2, 5, 4, 1]
{
	os<<'[';
	int i;
	for(i=0;i<obj.currentsize-1;++i)
	os<<obj.a[i]<<',';
	os<<obj.a[i]<<']'<<endl;
	return os;	
}

	void sort(bool less=true);//ʵ��һ�����������鲢���򣬶�֧�ֱȽ��������>=<�������������
    // ��less=true�����մ�С�������У����򰴴Ӵ�С����
	void reverse();//��MyList��Ԫ�ص�������







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
    b = a.get_item(4, -3); // b = [] *��start > end�����ؿ�����
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



