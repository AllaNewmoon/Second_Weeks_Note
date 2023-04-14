#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
//1.插入排序，temp=后一个，将前一个和temp作比较
//如果前一个大，令后一个等于前一个，再比较前前一个和temp
void Insert_Sort(int arr[], int length) {
	for (int i = 1; i < length; i++) {
		int temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;

	}
}
//2.快速排序，左右轮换与temp比较
void Quick_Sort(int arr[], int begin, int end) {
	if (begin >= end) {
		return;
	}
	int left = begin;
	int right = end;
	int temp = arr[left];
	while (left < right) {
		while (left<right&&arr[right] >= temp) {
			right--;
		}
		if (left<right) {
			arr[left] = arr[right];
		}
		while (left < right && arr[left] <= temp) {
			left++;
		}
		if (left < right) {
			arr[right] = arr[left];
		}
		if (left == right) {
			arr[left] = temp;
		}
	}
	Quick_Sort(arr, begin, left - 1);
	Quick_Sort(arr, left + 1,end);
}
//3.冒泡排序，不断将前一个和后一个比较，交换顺序。
void Bubble_Sort(int arr[],int length) {
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1-i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp;
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
//4.归并排序，先将序列分为n个长度为1的子序列，再将其两两归并
void Merge(int[], int, int[], int, int, int);
//归并思想：两个子序列，分别有一个指针指向其首部，指针指向的元素进行对比，小的放入辅助数组里，指针后移，大的不动，直到两两对比完成
//利用递归进行分离
void Merge_Sort(int arr[], int length, int temp[], int begin, int end) {
	if (arr == nullptr || length <= 0 || begin < 0 || end >= length) {
		throw new exception("invalid input.");
	}
	if (end - begin == 0) {
		return;
	}
	int middle = ((end - begin) / 2) + begin;
	Merge_Sort(arr, length, temp, begin, middle);
	Merge_Sort(arr, length, temp, middle + 1, end);
	Merge(arr, length, temp, begin, end, middle);
}
//利用辅助数列进行归并
void Merge(int arr[], int length, int temp[], int begin, int end, int middle) {
	if (arr == nullptr || length <= 0 || begin < 0 || end >= length) {
		throw new exception("invalid input.");
	}
	int leftIndex = begin;
	int rightIndex = middle + 1;
	int tempIndex = begin;
	while (leftIndex <= middle && rightIndex <= end) {
		if (arr[leftIndex] <= arr[leftIndex]) {
			temp[tempIndex] = arr[leftIndex++];
		}
		else {
			temp[tempIndex] = arr[rightIndex++];
		}
		++tempIndex;

		while (leftIndex <= middle)
			temp[tempIndex++] = arr[leftIndex++];

		while (rightIndex <= end)
			temp[tempIndex++] = arr[rightIndex++];
		for (int i = begin; i <= end; ++i)
			arr[i] = temp[i];
	}
}
//5.希尔排序，确定步长，则一共有步长个组，对每个组进行插入排序，步长不断除二。
void Shell_Sort(int a[], int n) {
	int i, j, gap;
	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = 0; i < gap; i++) {
			for (j = i + gap; j < n; j += gap) {
				if (a[j] < a[j - gap]) {
					int temp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > temp) {
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = temp;
				}
			}
		}
	}
}
//6.选择排序，找到当前数字序列中最大（最小）的数，记录其所在位置
//将其和最前面（最后面）的数进行交换，使最小（最大）的元素上浮（下沉）到本次排序的最前面（最后面），从而完成一趟排序
//需要进行n-1趟排序
void Select_Sort(int a[],int length) {
	int minIndex;
	for (int i = 0; i < length; i++) {
		minIndex = i;
		for (int j = i + 1; j < length; j++) {
			if (a[j] < a[minIndex]) {
				minIndex = j;
			}
		}
		swap(a[i], a[minIndex]);
	}
}
//7.桶排序，设定一定数量的数组当空桶，把数一个个放到对应桶，再对每个桶内排序，对桶排序
//vector容器实现，单个桶内用插入排序
void Bucket_Sort(int a[],int length) {
	if (length <= 0) {
		return;
	}
	int i;
	int maxvalue = a[0];
	for (i = 1; i < length; i++) {
		if (a[i] > maxvalue)
			maxvalue = a[i];
	}
	const int bucketcnt = 10;
	vector<int> buckets[bucketcnt];
	int bucketsize = 1;
	//根据maxvalue确定桶的大小
	while (maxvalue) {
		maxvalue /= 10;
		bucketsize *= 10;
	}
	bucketsize /= 10;
	//根据a[i]大小pushback到桶里，再对每个桶插入排序
	for (int i = 0; i < length; i++) {
		int idx = a[i] / bucketsize;
		buckets[idx].push_back(a[i]);
		for (int j = int(buckets[idx].size() - 1); j > 0; j--) {
			if (buckets[idx][j] < buckets[idx][j - 1]) {
				swap(buckets[idx][j], buckets[idx][j - 1]);
			}
		}
		
		for (int i = 0, k = 0; i < bucketcnt; i++) {
			for (int j = 0; j<int(buckets[idx].size()); j++) {
				a[k++] = buckets[i][j];
			}
		}
	}
}
//8.堆排序，第一步先将二叉树堆化，维护堆的性质
//下标为i的节点父节点下标为(i-1)/2
//下标为i的节点左孩子下标i*2+1
//下标为i的节点右孩子下标i*2+2
void heapify(int a[], int n, int i) {
	if (i >= n)
		return;
	int largest = i;
	int lson = i * 2 + 1;
	int rson = i * 2 + 2;
	if (lson < n && a[largest] < a[lson]) {
		largest = lson;
	}
	if (rson < n && a[largest] < a[rson]) {
		largest = rson;
	}
	if (largest != 1) {
		swap(a[largest], a[i]);
		heapify(a, n, largest);
	}
}
//先建堆(从后往前建堆)，再进行排序(将第一个和最后一个交换，重新维护堆的性质)
void Heap_Sort(int a[], int n) {
	int i;
	for (i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}
	for (i = n - 1; i > 0; i--) {
		swap(a[i], a[0]);
		heapify(a, i, 0);
	}
 }
//9.基数排序,先比较个位，排序后再比较十位，依次类推
//辅助函数，用于求数据的最大位数
int maxbit(int a[], int n) {
	int maxData = a[0];
	for (int i = 1; i < n; ++i) {
		if (maxData < a[i])
			maxData = a[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p) {
		maxData /= 10;
		++d;
	}
	return d;
}
//进行排序(计数排序思想)
void Radix_Sort(int a[], int n) {
	int d = maxbit(a, n);
	int* temp = new int[n];//辅助数列
	int* count = new int[10];//计数器（用来作为temp下标）
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) {
		for (j = 0; j < 10; j++)//清空计数器
			count[j] = 0;
		for (j = 0; j < n; j++) {//自增计数器
			k = (a[j] / radix) % 10;
			count[k]++;
		}
		for (j = 1; j < 10; j++) {//对计数器的运算，使其能作为temp下标且有顺序
			count[j] = count[j - 1] + count[j];
		}
		for (j = n - 1; j >= 0; j--) {//将元素放入temp
			k = (a[j] / radix) % 10;
			temp[count[k] - 1] = a[j];
		}
		for (j = 0; j < n; j++) {//将temp归还数组
			a[j] = temp[j];
		}
		radix = radix * 10;
	}
	delete []temp;
	delete []count;
}
//10.计数排序：统计小于等于该元素值的元素个数i，将该元素放入索引第i位
void Count_Sort(vector<int>& vecRaw, vector<int>& vecObj) {
	if (vecRaw.size() == 0)
		return;
	//max_element求最大值，加1作为计数容器大小
	int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
	vector<int> vecCount(vecCountLength, 0);
	for (int i = 0; i < vecRaw.size(); i++) {
		vecCount[vecRaw[i]]++;//自增计数器
	}
	for (int i = 1; i < vecCountLength; i++) {
		vecCount[i] += vecCount[i - 1];
	}
	for (int i = vecRaw.size(); i > 0; i--) {
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];//vecRaw排序到vecObj中
	}//等价于数组中的temp[count[k] - 1] = a[j];
}
