# Second_Weeks_Note

# 时间与运动
**篇章总结：** 本章主要探讨随时间变化的位姿，第一个是轨迹，即机器人要跟从的位姿，其要保证随时间连续变化。第二个是

## 轨迹
### 1.平滑一维轨迹：
用S(t)的五阶多项式表示，保证了其一阶，二阶导数光滑，其六个系数易于满足速度与加速度的**边界条件**。

*1.（在matlab中用tpoly生成五次多项式轨迹，tpoly（0，1，50）表示值在0到1内分50时间步平滑变化）*

*2.（[s,sd,sdd]三个输出选项可用于接受速度，加速度）*

*3.(用lspb生成直线与抛物线的混合轨迹，能满足在最大速度上的时间尽可能长，其可以额外指定直线段速度)*

### 2.多维情况：
利用mtraj将一维标量扩展成多维向量情况, eg:mtraj(@lspb, [0 2], [1 -1], 50)，得到50*2的矩阵，并可用plot绘制。（二维情况）

对于三维，可以将位姿齐次矩阵转换为六维向量(x = [transl(T); tr2rpy(T)'])再生成轨迹。

## 多段轨迹情况:
对于多个**中间点**，为了实现速度连续，舍弃让轨迹到达中间点。到达中间点前t/2时刻进入多项式曲线，经过t时刻进入另一段直线。
![](https://github.com/AllaNewmoon/Image/blob/main/QQ%E5%9B%BE%E7%89%8720230326180556.png?raw=true)

*1.（mstraj可基于中间点生成多段多轴轨迹，二维下eg:mstraj(via, [2.1], [], [4.1], 0.05, 0)，via是中间点矩阵，其余是最大速度向量，运动时间向量，起点坐标，采样间隔，加速时间）*

## 姿态插值：
**1.线性插值法**：对于三角度表示法可采用线性插值

eg：对于两个姿态R0，R1，可先用tr2rpy算出横滚-俯仰-偏航角，再分50个时间步用mtraj生成轨迹，用tranimate生成动画。
![](https://github.com/AllaNewmoon/Image/blob/main/QQ%E5%9B%BE%E7%89%8720230326181336.png?raw=true)

也可采用四元数插值法。

## 笛卡尔运动:
对于同时涉及位置，姿态变化的运动称为笛卡尔运动。

对于齐次变换矩阵T0，T1，可以用trinterp进行位姿插值得到轨迹Ts，再用transl(Ts)和tr2rpy(Ts)分别得到其平移部分和姿态变化。
![](https://github.com/AllaNewmoon/Image/blob/main/QQ%E5%9B%BE%E7%89%8720230326181715.png?raw=true)

也可以用ctraj进行插值，eg:ctraj(T0,T1,50);

## 旋转坐标系:
物体在旋转时有一个角速度向量，该向量的方向定义了瞬时旋转轴。

**时变矩阵微分表达式**：
![](https://github.com/AllaNewmoon/Image/blob/main/QQ%E5%9B%BE%E7%89%8720230326182353.png?raw=true)

可通过skew函数由角速度向量求得S(w)

若仅考虑坐标系的微小旋转，对上式用vex求逆，可得一个微小角度的表达式。若位姿微小变化用Rdelta表示，则旋转角为vex(Rdelta - eye(3,3))'
![](https://github.com/AllaNewmoon/Image/blob/main/QQ%E5%9B%BE%E7%89%8720230326182842.png?raw=true)

对于差异极小的位姿，可用位移增量与旋转增量构成的六维向量表示，可以写成齐次变换矩阵的形式，并用tr2delta(T0,T1);计算该六维向量。
![](https://github.com/AllaNewmoon/Image/blob/main/QQ%E5%9B%BE%E7%89%8720230326183241.png?raw=true)

# 移动机器人载体
机器人平台的运动和控制。
## 机动性
**位形空间**：所有可能的位置形态合集，又称C空间。（eg：火车沿轨道运动，其可能的位置可以由一个参数标量q确定，称为其的广义坐标。）

**任务空间**：所有可能的机器人位姿构成的集合，三维世界里则任务空间属于SE(3)。当位形空间维度小于任务空间，则存在q到位姿的映射。

**欠驱动系统**：驱动器数量比自由度少，限制其自由运动的能力（eg：1.气垫船有两个驱动器，位形空间有三个维度(x,y,theta)，即有三个自由度

2.直升机有四个驱动器，有六个广义坐标（x,y,z,theta x,theta y, theta z），但其任务空间还是SE(3)）

**非完整系统**：1.不能直接从一个位形到另一个位形。

2.受到一个或以上的非完整约束（只能用位形变量的微分方程描述，而无法积分成关于x,y,theta的约束方程）

3.通过时变控制策略操纵（eg：移动车体）

## 移动机器人小车
抽象出小车模型，由于小车不能侧移，故Vy = 0，可以算出其角速度与转弯半径。当车越长，y越小，转弯半径越大。
![](https://github.com/AllaNewmoon/123/blob/main/QQ%E5%9B%BE%E7%89%8720230326192032.png?raw=true)

写出小车在世界坐标系中的运动方程，可以构造出一个沿y方向的速度表达式，其为非完整约束，无法积分。
![](https://github.com/AllaNewmoon/123/blob/main/QQ%E5%9B%BE%E7%89%8720230326192054.png?raw=true)

**向一点移动**：采用sl_drivepoint模块实现，可以指定目标点和初始位姿。*（书中的tout和yout用t和y代替）*

**跟踪一条直线**: 

齐次坐标系知识：可以从欧拉坐标向量构建齐次坐标向量（eg：欧拉坐标(x1,x2...xn)转换为齐次坐标向量x = (x1,x2...xn,1)）

将一条线用三元组lT表示，直线方程可写成矩阵乘积形式lT*x = 0, 则两直线交点和经过两点的直线可由叉乘求出

另外有**点到线的距离公式：**
![](https://github.com/AllaNewmoon/123/blob/main/QQ%E5%9B%BE%E7%89%8720230329181740.png?raw=true)

利用sl_driveline模块计算，给指定直线三元组和起始位姿，可以同理画出轨迹。

**跟踪一般曲线**：类比于向一点移动，将点看成动点。定义一个跟踪误差，用比例积分控制器提供一个速度需求量，使跟踪误差趋于0。模型为sl_pursuit。

**运动到一个位姿**：将世界坐标系下的x，y方向速度与角度方程写成矩阵形式，再用极坐标代换，得到新的矩阵式，再用线性控制法表示。对于任意位姿，采取坐标变换。
![](https://github.com/AllaNewmoon/123/blob/main/QQ%E5%9B%BE%E7%89%8720230329181721.png?raw=true)

在matlab中用sl_drivepose实现，需指定目标位姿，初始位姿。

## 飞行机器人
推力与转速成正比，比例系数为**升力常数**，推力向量相对于机体坐标系，可以转换为世界坐标系，运用牛顿第二定律得到动力学方程。

同时由于推力差异会导致飞行器旋转，故有x轴上的横滚力矩和y轴的俯仰力矩，为dT~4~-dT~2~，和dT~1~-dT~3~，再带入推力与转速关系。

同时绕旋翼轴转动的力矩与转速也成正比，可计算出z轴总转矩。结合欧拉运动方程可得旋转加速度，结合该方程与动力学方程即得飞行器运动模型。

matlab中的四旋翼飞行器用mdl_quadrotor加载，sim('sl_quadrotor')仿真，用plot(result(:,1),result(:,2:3))绘制。

#1.时间复杂度
时间复杂度是一个函数，定量描述算法运行时间，为算法中基本操作的*执行次数*。

eg:

```
void func1(int N)
{
    int count = 0;
    for (int i = 0; i < N; ++i){
        for(int j = 0; j< N; ++j){
            ++count;
        }
    }
}
```
该函数时间复杂度为**N*N**

##渐进表示法
只需大概执行次数时，使用大O渐进表示法，eg：**O(N*N)**

1.只保留最高阶

2.去除与项目相乘的常数

3.只有常数是用1代替(**O(1)**)

4.有时会有最好，平均，最坏情况。一般情况关注最坏情况。

eg2:
```
int BinarySearch(int* a, int n, int x) {
	assert(a);
	int begin = 0;
	int end = n;
	while (begin < end) {
		int mid = begin + ((end - begin) >> 1);
		if (a[mid] < x)
			begin = mid;
		else if (a[mid] > x)
			end = mid;
		else return mid;
	}
}
```
设数组大小为N，则设最坏找了x次，==有2^x^=N，即x=log2N==

## 递归算法
**O = 递归次数*每次递归调用次数**

eg：斐波那契数列：相当于以2为公比的等比数列求和。O(N) = 2^N^

#2.空间复杂度

是对算法运行过程中*临时额外占用存储空间大小*的度量。

eg1:
```
long long* fibArray = (long long*)malloc((n + 1) * sizeof(long long));
```
空间复杂度为**O(N)**

eg2:斐波那契数列空间复杂度:**O(N)**

(空间可以重复利用，fib（1）到fib（N）有N个空间)

#3.顺序表
**1.线性表**：n个具有相同特性的数据元素的有限序列，在逻辑上是线性结构，通常以数组和链式结构的形式存储。（*顺序表，链表，栈，队列，字符串......*）

**2.顺序表**:相当于数组，但要求数据连续存储。

顺序表实现：
1.头插实现(pushfront)：
```
#pragma once
typedef int SLDataType;
//静态顺序表
typedef struct SeqList {
	SLDataType *a;
	int size;//数组中存了多少个数据
	int capacity;//数组实际能存数据的空间容量
}SL;
//接口函数
void SeqListPushBack(SL* ps, int x) {
	int end = ps->size - 1;
	while (end >= 0) {
		ps->a[end + 1] = ps->a[end];
		--end;
	}
	ps->a[0] = x;
	ps->size++;
}
```
2.尾插实现(pushback)：
```
void SeqListPushBack(SL* ps, int x) {
	if (ps->size == ps->capacity) {
		int newcapacity = ps->capacity == 0 ? 4: ps->capacity * 2;
		SLDataType* tmp = (SLDataType*)realloc(ps->a, newcapacity*sizeof(SLDataType));
		if (tmp == NULL) {
			cout << "realloc fail" << endl;
			exit(1);
		}
		ps->a = tmp;
		ps->capacity = newcapacity;
	}
	ps->a[ps->size] = x;
	ps->size++;
}
```
注意用realloc开辟动态内存空间前需加上(type*), 空间容量要乘以sizeof(type)。如果realloc第一个参数是空，相当于malloc。

3.头删实现(popfront):
```
void SeqListPopFront(SL* ps){
	assert(ps->size > 0);
	int begin = 0;
	while(begin<ps->size){
		ps->a[begin-1] = ps->a[begin];
		++begin;
	}
	ps->size--
}
```
将后一个元素挪到前一个元素的位置。assert函数若为假，则终止程序。

4.尾删实现(popback)：
