#include<stdio.h>
#include<malloc.h>
 
/*
堆栈的链式存储实现
为了简化算法，链栈也可以带一空的表头结点，表头结点后面的第一个结点就是链栈的栈顶结点。
栈中的其他结点通过它们的指针Next链接起来，栈底结点的Next为NULL。
*/
 
typedef struct SNode *PtrToSNode;
typedef int ElementType;
 
ElementType ERROR = -1;
 
struct SNode
{
	ElementType Data;
	PtrToSNode Next;
};
 
typedef PtrToSNode Stack;
 
Stack CreateStack() {
	/*构建一个堆栈的头结点，返回该结点的指针*/
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}
 
bool IsEmpty(Stack S) {
	/*判断堆栈是否为空*/
	return (S->Next == NULL);
}
 
bool Push(Stack S, ElementType X) {
	/*入栈*/
	Stack TmpCell = (Stack)malloc(sizeof(struct SNode));
	TmpCell->Data = X;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;
	return true;
}
 
 
ElementType Pop(Stack S) {
	/*出栈*/
	Stack FirstCell;
	ElementType TopElem;
 
	if (IsEmpty(S)) {
		printf("堆栈空\n");
		return ERROR;
	}
 
	else
	{
		FirstCell = S->Next;
		TopElem = FirstCell->Data;
		S->Next = FirstCell->Next;
		free(FirstCell);
		return TopElem;
	}
}
 
void LinkStackDemo() {
	printf("=============初始化链式存储栈===============\n");
	Stack S = CreateStack();
	printf("=================依次入栈1-5================\n");
	for (int i = 1; i <= 5;i++)
		Push(S, i);
	printf("==================依次出栈=====================\n");
	ElementType x = 0;
	while (true)
	{
		x = Pop(S);
		if (x == -1)
			break;
		printf("%d\t", x);
	}
}
 
int main() {
	LinkStackDemo();
	return 1;
}