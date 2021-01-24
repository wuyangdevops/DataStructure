#include<stdio.h>
#include<malloc.h>
 
/*堆栈顺序存储*/
 
typedef int Position;
typedef int ElementType;
typedef struct SNode *PtrToSNode;
 
ElementType ERROR = -1;
 
struct SNode
{
	ElementType *Data; /*存储元素的数组*/
	Position Top;      /*栈顶指针*/
	int MaxSize;		/*堆栈最大容量*/
};
typedef PtrToSNode Stack;
 
Stack CreateStack(int MaxSize) {
	/*创建堆栈*/
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType *)malloc(sizeof(MaxSize * sizeof(ElementType)));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}
 
bool IsFull(Stack S) {
	/*判断堆栈是否满*/
	return(S->Top == S->MaxSize - 1);
}
 
bool Push(Stack S, ElementType X) {
	/*入栈*/
	if (IsFull(S)) {
		printf("堆栈满");
		return false;
	}
	else {
		S->Data[++(S->Top)] = X;
		return true;
	}
}
 
bool IsEmpty(Stack S) {
	/*判断堆栈是否为空*/
	return(S->Top == -1);
}
 
ElementType Pop(Stack S) {
	/*出栈*/
	if (IsEmpty(S)) {
		printf("堆栈空");
		return ERROR;
	}
	else
		return(S->Data[(S->Top)--]);
}
 
void SequentialStackDemo() {
	/*顺序存储堆栈Demo*/
	printf("=================顺序存储堆栈Demo======================\n");
	printf("===========1. 初始化堆栈=======================\n");
	Stack S = CreateStack(10);
	printf("========2. 入栈0-9元素==============\n");
	for(int i=0;i<=9;i++)
		Push(S, i);
	printf("************尝试继续入栈元素 10=============\n");
	Push(S, 10);
	printf("\n==============3. 依次取出栈顶元素=============\n");
	for (int j = 0;j <= 9;j++) {
		ElementType x = Pop(S);
		printf("当前元素是%d\n", x);
	}
	printf("================4. 尝试继续取出栈顶元素===================\n");
	ElementType x = Pop(S);
}
 
 
int main() {
	SequentialStackDemo();
	return 1;
}