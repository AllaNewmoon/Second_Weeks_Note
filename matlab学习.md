# 数字计算
1.加减乘除

2.**format + 类型**进行数字显示的转换。

（eg：format short/format long/shortE/longE）

用rat显示分数，bank保留两位小数，hex转换16进制。

# 简单Function
1.clc用于清除命令行窗口

2.clear清除所有工作区变量

3.who显示工作区变量，whos显示变量详细信息

# 数组和矩阵
## 基本知识
1.行矩阵eg:[1 2 3 4]，列矩阵eg:[1;2;3;4] (中间用;隔开)

2.用a*b进行矩阵运算

3.m*n型矩阵定义eg:A = [1 2 3;4 5 6;7 8 9]

4.利用A(3,2)查找指定行，列的元素。利用A([1 2;2 3])生成A的子矩阵。利用A([1 3],[1 2])生成第一行和第三行与第一列和第二列相交形成的子矩阵。

5.等差数列的构造eg:b = 1:2:99，表示从1到99，公差为2

6.用A(3,:) = []清除第三行，同理可清除列。

7.利用[A B]或[A;B]构造增广矩阵

## 基本运算
1.A + B为矩阵相加，`A*B`为矩阵乘法，`A.*B`为矩阵对应元素相乘，A/B为A*B的逆矩阵，`A./B`为矩阵对应元素相除

2.A+常数a表示A的每个元素加常数a，`A/a = A./a`，`A^a`等于a个A矩阵相乘，`A.^a`为每个元素乘a次方，A'表示A的转置。

## 特殊矩阵
1.eye(n)创建单位矩阵

2.zero(n1, n2)构造n1 * n2的零矩阵，ones(n1, n2)构造1矩阵

3.diag([a b c])构造对角线元素是a b c的矩阵

4.linspace(a,b,c)构造线性向量，从a到b分成c步

## 矩阵的Function
1.max(A)计算矩阵中每一列的最大元素, max(max(A))返回A的最大元素，min用法相同

2.sum(A)计算每一列相加，sum(sum(A))计算所有元素相加，mean(A)计算平均

3.sort(A)将每一列从小到大排序，sortrows(A)按第一列元素的大小排序行。

4.size(A)计算行与列的大小，size(A,1)计算行，size(A,2)计算列。length(A)测量长度，find(A==b)找到A中第b个元素。

# 编辑器内容
## 基本内容
1.点击行数字旁边的按钮设置breakpoint，使函数运行到此行并进入debug mode。

2.用%%对编辑器进行分块

## 基本语法
1.基本同C语言，不等于是~=

2.if，while，for等结尾处要加上end

3.matlab中没有+=和++等，直接用=号进行操作

4.for用法:

```
for variable=start : increment : end
    commands
end
```

5.提前划分空间，运行速度更快。(程序首尾分别加tic，toc可以计时程序)

eg：
```
for ii = 1:2000
    for jj = 1:2000
        A(ii,jj) = ii+jj;
```
可以替换成
```
A = zeros(2000,2000);
for ii = 1:size(A,1)
    for jj = 1:size(A,2)
        A(ii,jj) = ii+jj;
```
6.break和while连用，用于跳出循环。

## 构造函数
1.定义函数：function output = name(input)

2.尽量用.*代替乘号计算

3.**input函数**用法：x=input(prompt, )

eg:华氏温度与摄氏度之间的转换函数：
```
function C=F2C(F)
while 1
    a=('tempreature in F is:');
    F = input(a);
    if F
        C = (F-32)*5/9;
        X=['tempreature in C is:',num2str(C)];
        disp(X);
    else
        fprintf('输入不为数字！')
        break;
    end
end
```

**其它常用函数**：
1.nargin函数用来判断输入变量的个数，nargout判断输出变量的个数

eg：
```
function fout=examp(a,b,c)
    if nargin==1
       fout=a;
    else if nargin==2
       fout=a+b;
    else if nargin==3
       fout=(a*b*c)/2;
end
```
2.varargin函数可以实现可变的输入个数，varargout实现可变的输出个数

eg：
```
function a=convs(varargin)
   a=1;
   for i=1:length(varargin), a=conv(a,varargin{i}); end
```
(conv函数用于计算多项式与向量卷积)

**Function Handle**：function handle是一个指向函数的指针。

eg:
```
f = @(x) exp(-2*x);
x = 0:0.1:2;
plot(x,f(x));
```
f是指向exp(-2*x)的指针，f(x)就是将x值代入函数。