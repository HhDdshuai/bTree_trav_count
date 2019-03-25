#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50
typedef int elemType;
typedef struct BitNode{
	elemType data;
	BitNode *lchild,*rchild;
}BitNode;


void createBTree(BitNode **T,elemType a[],int len,int index){
	if(index >= len)
		return;
	*T = (BitNode *)malloc(sizeof(BitNode));
	if(a[index] == -1)
		(*T) = NULL;
	else{
		(*T)->data = a[index];
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
		createBTree(&((*T)->lchild),a,len,2 * index + 1);
		createBTree(&((*T)->rchild),a,len,2 * index + 2);
	}
}

void printBTree(BitNode *T){
	BitNode *p = T;
	if(p != NULL){
		printf("%d ",p->data);
		printBTree(T->lchild);
		printBTree(T->rchild);
	}
}
elemType max(elemType a,elemType b){
	return (a > b ? a : b);
}
//求二叉树高度
int btDepth(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	left = btDepth(T->lchild);
	right = btDepth(T->rchild);
	return(max(left,right) + 1);
}
//求二叉树叶节点个数
int bt_leafCount(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	if(T->lchild == NULL && T->rchild == NULL)
		return 1;
	left = bt_leafCount(T->lchild);
	right = bt_leafCount(T->rchild);
	return (left + right);
}
//求二叉树结点个数
int btNodeCount(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	left = btNodeCount(T->lchild);
	right = btNodeCount(T->rchild);
	return (left + right + 1);
}
//统计二叉树所有双分支结点个数
int DsonNodeCount(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	left = DsonNodeCount(T->lchild);
	right = DsonNodeCount(T->rchild);
	if(T->lchild != NULL && T->rchild != NULL)
		return (left + right + 1);
	else
		return (left + right);
}
//层次遍历二叉树
void levelOrder(BitNode *T){
	BitNode *Q[MAXSIZE];
	int low,high;
	low = high = 0;
	BitNode *p;
	Q[high++] = T;
	while(low != high){
		p = Q[low++];
		printf("%d ",p->data);
		if(p->lchild != NULL)
			Q[high++] = p->lchild;
		if(p->rchild != NULL)
			Q[high++] = p->rchild;
	}
}
//先序非递归遍历
void preOrderNonRec(BitNode *T){
	BitNode *S[MAXSIZE];
	int top = -1;
	BitNode *p = T;
	while(p || top != -1){
		while(p){
			printf("%d ",p->data);
			S[++top] = p;
			p = p->lchild;
		}
		if(top != -1){
			p = S[top--];
			p = p->rchild;
		}
	}
}
//中序非递归遍历
void inOrderNonRec(BitNode *T){
	BitNode *S[MAXSIZE];
	int top = -1;
	BitNode *p = T;
	while(p || top != -1){
		if(p){
			S[++top] = p;
			p = p->lchild;
		}
		else{
			p = S[top--];
			printf("%d ",p->data);
			p = p->rchild;
		}
	}
}
int main(){
	int depth,btLeafCount,btNodes,dsonNode;
	elemType a[] = {1,2,3,4,5,6,7,-1,8,-1,-1,-1,9,-1,10};
	int len = sizeof(a)/sizeof(a[0]);
	BitNode *T;
	createBTree(&T,a,len,0);
	//printBTree(T);
	//depth = btDepth(T);
	//printf("\n*%d*\n",depth);
	//btLeafCount = bt_leafCount(T);
	//printf("\n*%d*\n",btLeafCount);
	//btNodes = btNodeCount(T);
	//printf("\n*%d*\n",btNodes);
	levelOrder(T);
	printf("\n");
	//inOrderNonRec(T);
	dsonNode = DsonNodeCount(T);
	printf("Double son node count: %d\n",dsonNode);
	preOrderNonRec(T);
}