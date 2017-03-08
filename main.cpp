#include<iostream>
using namespace std;

template<class T>
void myswap(T &a,T &b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}
template<class T>
void insertion(T a[], int n)
{
	int j=0;
	for (int p = 1; p < n; p++)
	{
		T tmp = a[p];
		for (j = p; j > 0 && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

template<class T>
void shellsort(T a[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
		for (int i = gap; i < n; i++)
		{
			T tmp = a[i];
			int j = i;
			for (; j >= gap&&tmp < a[j - gap]; j -= gap)
				a[j] = a[j - gap];
			a[j] = tmp;
		}
}



//shell与insert分开
template<class T>
void inssort2(T a[],int n,int incr)
{
    for(int i=incr; i<n; i+=incr)
        for(int j=i; (j>=incr)&&a[j]<a[j-incr]; j-=incr)
        myswap(a[j],a[j-1]);
}

template<class T>
void Shellsort(T a[], int n)
{
    for(int i=n/2;i>2;i/=2)
        for(int j=0;j<i;j++)
        inssort2(&a[j],n-j,i);
    inssort2(a,n,1);

}

template<class T>
void bubblesort(T a[], int n)
{
	for (int i = 0; i < n - 1 ; i++)
		for (int j = n-1; j >i ; j--)
		{
			if (a[j] < a[j-1 ])
				myswap(a[j], a[j - 1]);
		}
}
template<class T>
void Bubblesort(T a[], int n)
{
	for (int i = 0; i < n - 1 ; i++)
		for (int j = 0; j < n-i-1 ; j++)
		{
			if (a[j] > a[j+1 ])
				myswap(a[j], a[j + 1]);
		}
}


template<class T>
void selectsort(T a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int Min = i;
		for (int j = i; j < n; ++j)
			if (a[Min] > a[j])
				Min = j;
		myswap(a[Min],a[i]);
	}
}

template <class T>
void Merge(T a[],T tmpArray[],int leftPos,int rightPos,int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    //合并
    while(leftPos <= leftEnd && rightEnd <= rightEnd)
        if(a[leftPos] < a[rightPos])
            tmpArray[tmpPos++]=a[leftPos++];
        else
            tmpArray[tmpPos++]=a[rightPos++];
    while(leftPos<=leftEnd)
        tmpArray[tmpPos++]=a[leftPos++];
    while(rightPos<=rightEnd)
        tmpArray[tmpPos++]=a[rightPos++];
    //copy tmparray back
    for(int i=0;i<numElements;i++,rightEnd--)
        a[rightEnd]=tmpArray[rightEnd];
        /*
    for(int k=left;k<=right;k++)
	L2[k]=L1[k];
    int s1= left,s2= mid+1,t = left;
	while (s1<= mid && s2 <= right)	   //两两比较
        if (L2[s1] <= L2[s2]) L1[t++] = L2[s1++];
        else L1[t++] = L2[s2++];
    while (s1 <= mid) L1[t++] = L2[s1++];
		//若第一个表未检测完,复制
    while (s2 <= right) L1[t++] = L2[s2++];
		//若第二个表未检测完,复制
    }
*/
}

template<class T>
void mergesort(T a[],T temp[],int left,int right)
{
    if(left<right)
    {
        int mid = (left+right)/2;
        mergesort(a,temp,left,mid);
        mergesort(a,temp,mid+1,right);
        Merge(a,temp,left,mid+1,right);
    }
}
#define THRESHOLD 4
//归并优化，二分法
template<class T>
void newmergesort(T a[],T temp[],int left,int right)
{
    if((right-left) <= THRESHOLD )
    {
        insertion(&a[left],right-left +1);
        return;
    }
    int i,j,k,mid = (left+right)/2;
    newmergesort(a,temp,left,mid);
    newmergesort(a,temp,mid+1,right);
    //copy 2 halves to temp
    for(i = mid;i>=left;i--) temp [i]= a[i];
    for(j=1;j<=right-mid;j++) temp [right-j+1] = a[j+mid];
    for(i=left,j = right,k=left;k<=right;k++)
        if(temp[i]<temp[j]) a[k]=temp[i++];
        else a[k] =temp[j--];
}

template<class T>
void mergesort(T a[],int n)
{
  //  T b[8];
    T* b = new T[n];
    mergesort(a,b,0,n-1);
    delete []b;
}



template<class T>
inline int findpivot(T a[],int i,int j)
{
    return (i+j)/2;
}
template<class T>
int Partition(T a[],int l,int r,T& pivot)
{
    do{
        while(a[++l]<pivot);
        while(l<r && pivot<a[--r]);
        myswap(a[l],a[r]);
    }while(l<r);
    return l;
}
template<class T>
void quicksort(T a[],int i,int j)
{
    if(j<=i) return;
    int privotindex = findpivot(a,i,j);
    myswap(a[privotindex],a[j]);
    int k = Partition(a,i-1,j,a[j]);
    myswap(a[k],a[j]);
    quicksort(a,i,k-1);
    quicksort(a,k+1,j);
}

template<class T>
void quicksort(T a[],int n)
{
    quicksort(a,0,n-1);
}
//快速排序的优化,还需要思考，以上面为准，+实现非递归
template<class T>
int midian3(T a[],int left,int right)
{
    int center=(left+right)/2;
    if(a[center]<a[left])
        myswap(a[center],a[left]);
    if(a[right]<a[left])
        myswap(a[left],a[right]);
    if(a[right]<a[center])
        myswap(a[left],a[right]);
        //place pivot at position right -1
    myswap(a[center],a[right-1]);
    return a[right-1];
}
template <class T>
void Qsort(T a[],int left,int right)
{
    if(left+4<=right)
    {
        T pivot = midian3(a,left,right);
        /*//a[i]=a[j]时无限循环
        int i = left+1,j = right -2;
        for(;;)
        {
            while(a[i]<pivot) i++;
            while(a[j]>pivot) j--;
            if(i<j)
                myswap(a[i],a[j]);
            else
                break;
        }*/
        int i = left,j = right -1;
        for (;;)
		{
			while (a[++i] < pivot){}
			while (a[--j] > pivot){}
			if (i<j)
				myswap(a[i], a[j]);
			else
				break;
		}
        myswap(a[i], a[right - 1]);
        Qsort(a,left,i-1);
        Qsort(a,i+1,right);
    }
    else
        insertion(a,right+1);
}
template<class T>
void Qsort(T a[],int n)
{
    Qsort(a,0,n-1);
}

template <class Elem>
void siftdown (Elem A[], const int start, const int m)
{
    int i = start;  int j = 2*i+1;	 //j是i的左子女
	Elem temp = A[i];	 //暂存子树根结点
    while (j <= m)
    {		   	 //逐层比较
        if (j < m && A[j] < A[j+1]) j++;
			//让j指向两子女中的大者
	    if (temp >= A[j])
            break;
	    else
        {	    //否则子女中的大者上移
           A[i] = A[j];
		  i = j;  j = 2*j+1;  	    //i下降到子女位置
        }
    }
	A[i] = temp;
}//temp放到合适位置

template <class Elem >
void heapsort (Elem A[], int n)
{
//对A [0]到A[n-1]进行排序, 使得各个元素按其排序码非递减有序
    int i;
    for (i = (n-2)/2; i >= 0; i--) 	//将表转换为堆
        siftdown (A, i, n-1);
    for (i = n-1; i >= 0; i--) {		//对表排序
        myswap(A[0], A[i]);  siftdown (A, 0, i-1);
    }
}

template<class T>
void print(T a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << a[i] <<" ";
	}

}

int main()
{
	int eg[8] = { 15,21,6,30,23,12,20,17 };
	/*cout << "insertionsort:" << endl;
	insertion(eg,8);
	print(eg,8);
	cout << endl;

	cout << "shellsort:" << endl;
	shellsort(eg, 8);
	print(eg, 8);
	cout << endl;

	cout << "bubblesort:" << endl;
	Bubblesort(eg, 8);
	print(eg, 8);
	cout << endl;*/

/*	cout<< "mergesort:"<<endl;
	mergesort(eg,8);
	print(eg, 8);
	cout << endl;

	cout << "selectsort:" << endl;
	selectsort(eg, 8);
	print(eg, 8);
	cout << endl;

	cout << "quicksort:" << endl;
	quicksort(eg,8);
	//quicksort(eg, 8);
	print(eg, 8);
	cout << endl;*/

	cout << "heapsort:" << endl;
	heapsort(eg,8);
	//quicksort(eg, 8);
	print(eg, 8);
	cout << endl;
//	getchar();
//	getchar();
	return 0;
}
