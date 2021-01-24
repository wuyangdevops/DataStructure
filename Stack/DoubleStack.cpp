#include<stdio.h>
#include<malloc.h>
 
/*双堆栈
双堆栈的结构只比标准堆栈多了一个栈顶指针
-使两个栈分别从数组的两头开始向中间生长；当两个栈的栈顶指针相遇时，表示两个栈都满了。
-此时，最大化地利用了空间
*/
 
typedef int Position;
typedef int ElementType;
typedef struct SNode * PtrToSNode;
struct SNode
{
	ElementType *Data; /*存储元素的数组*/
	Position Top1;     /*堆栈1的栈顶指针*/
	Position Top2;     /*堆栈2的栈顶指针*/
	int MaxSize;	   /*堆栈的最大容量*/
};
 
ElementType ERROR = -1;
 
typedef PtrToSNode Stack;
 
Stack CreateStack(int MaxSize) {
	/*初始化
	Top1 = -1
	Top2 = MaxSize
	*/
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	S->Top1 = -1;
	S->Top2 = MaxSize;
	S->MaxSize = MaxSize;
	return S;
}
 
bool Push(Stack S, ElementType X, int Tag) {
	/*入栈
	Tag作为区分两个堆栈的标志，取值为1和2*/
	if (S->Top2 - S->Top1 == 1) {
		/*堆栈满*/
		printf("堆栈满\n");
		return false;
	}
	else
	{
		if (Tag == 1)/*对第一个堆栈操作*/
			S->Data[++(S->Top1)] = X;
		else
			S->Data[--(S->Top2)] = X;
		return true;
	}
}
 
ElementType Pop(Stack S, int Tag) {
	/*出栈
	Tag作为区分两个堆栈的标志，取值为1和2
	*/
	if (Tag == 1) {
		/*对第一个堆栈操作*/
		if (S->Top1 == -1) {
			/*堆栈1空*/
			printf("堆栈1空\n");
			return ERROR;
		}
		else
			return S->Data[(S->Top1)--];
	}
	else
		{
			/*对第二个堆栈操作*/
			if (S->Top2 == S->MaxSize) {
				/*堆栈2空*/
				printf("堆栈2空\n");
				return ERROR;
			}
			else
				return S->Data[(S->Top2)++];
		}
	}
 
 
 
void DoubleStackDemo() {
	printf("=============初始化双堆栈==========\n");
	Stack S = CreateStack(10);
	printf("\n==========分别向堆栈两端添加1-5===========\n");
	for (int choice = 1; choice <= 2;choice++)
		for (int i = 1;i <= 5;i++)
			Push(S, i, choice);
	printf("\n**********分别尝试在两端添加6***********\n");
	Push(S, 6, 1);
	Push(S, 6, 2);
	printf("\n==============分别从堆栈两端取元素1-5================\n");
	for (int choice = 1; choice <= 2;choice++)
		for (int i = 1;i <= 5;i++) {
			ElementType x = Pop(S, choice);
			printf("Tag=%d\tElement=%d\n", choice, x);
		}
	printf("\n**************尝试继续取元素************************\n");
	ElementType y = Pop(S, 1);
	y = Pop(S, 2);
}
 
int main() {
	DoubleStackDemo();
	return 1;
}