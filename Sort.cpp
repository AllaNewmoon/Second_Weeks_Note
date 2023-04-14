#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
//1.��������temp=��һ������ǰһ����temp���Ƚ�
//���ǰһ�������һ������ǰһ�����ٱȽ�ǰǰһ����temp
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
//2.�������������ֻ���temp�Ƚ�
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
//3.ð�����򣬲��Ͻ�ǰһ���ͺ�һ���Ƚϣ�����˳��
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
//4.�鲢�����Ƚ����з�Ϊn������Ϊ1�������У��ٽ��������鲢
void Merge(int[], int, int[], int, int, int);
//�鲢˼�룺���������У��ֱ���һ��ָ��ָ�����ײ���ָ��ָ���Ԫ�ؽ��жԱȣ�С�ķ��븨�������ָ����ƣ���Ĳ�����ֱ�������Ա����
//���õݹ���з���
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
//���ø������н��й鲢
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
//5.ϣ������ȷ����������һ���в������飬��ÿ������в������򣬲������ϳ�����
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
//6.ѡ�������ҵ���ǰ���������������С����������¼������λ��
//�������ǰ�棨����棩�������н�����ʹ��С����󣩵�Ԫ���ϸ����³����������������ǰ�棨����棩���Ӷ����һ������
//��Ҫ����n-1������
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
//7.Ͱ�����趨һ�����������鵱��Ͱ������һ�����ŵ���ӦͰ���ٶ�ÿ��Ͱ�����򣬶�Ͱ����
//vector����ʵ�֣�����Ͱ���ò�������
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
	//����maxvalueȷ��Ͱ�Ĵ�С
	while (maxvalue) {
		maxvalue /= 10;
		bucketsize *= 10;
	}
	bucketsize /= 10;
	//����a[i]��Сpushback��Ͱ��ٶ�ÿ��Ͱ��������
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
//8.�����򣬵�һ���Ƚ��������ѻ���ά���ѵ�����
//�±�Ϊi�Ľڵ㸸�ڵ��±�Ϊ(i-1)/2
//�±�Ϊi�Ľڵ������±�i*2+1
//�±�Ϊi�Ľڵ��Һ����±�i*2+2
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
//�Ƚ���(�Ӻ���ǰ����)���ٽ�������(����һ�������һ������������ά���ѵ�����)
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
//9.��������,�ȱȽϸ�λ��������ٱȽ�ʮλ����������
//�������������������ݵ����λ��
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
//��������(��������˼��)
void Radix_Sort(int a[], int n) {
	int d = maxbit(a, n);
	int* temp = new int[n];//��������
	int* count = new int[10];//��������������Ϊtemp�±꣩
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) {
		for (j = 0; j < 10; j++)//��ռ�����
			count[j] = 0;
		for (j = 0; j < n; j++) {//����������
			k = (a[j] / radix) % 10;
			count[k]++;
		}
		for (j = 1; j < 10; j++) {//�Լ����������㣬ʹ������Ϊtemp�±�����˳��
			count[j] = count[j - 1] + count[j];
		}
		for (j = n - 1; j >= 0; j--) {//��Ԫ�ط���temp
			k = (a[j] / radix) % 10;
			temp[count[k] - 1] = a[j];
		}
		for (j = 0; j < n; j++) {//��temp�黹����
			a[j] = temp[j];
		}
		radix = radix * 10;
	}
	delete []temp;
	delete []count;
}
//10.��������ͳ��С�ڵ��ڸ�Ԫ��ֵ��Ԫ�ظ���i������Ԫ�ط���������iλ
void Count_Sort(vector<int>& vecRaw, vector<int>& vecObj) {
	if (vecRaw.size() == 0)
		return;
	//max_element�����ֵ����1��Ϊ����������С
	int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
	vector<int> vecCount(vecCountLength, 0);
	for (int i = 0; i < vecRaw.size(); i++) {
		vecCount[vecRaw[i]]++;//����������
	}
	for (int i = 1; i < vecCountLength; i++) {
		vecCount[i] += vecCount[i - 1];
	}
	for (int i = vecRaw.size(); i > 0; i--) {
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];//vecRaw����vecObj��
	}//�ȼ��������е�temp[count[k] - 1] = a[j];
}
