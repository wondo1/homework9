/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { // typedef 사용한 Node 구조체 선언
	int key;  // 정수형 변수 선언 
	struct node *left; // 왼쪽 노드 선언
	struct node *right; // 오른쪽 노드 선언
} Node;

int initializeBST(Node** h); // 초기화 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	Node* head = NULL; // 헤드노드 null 값
	Node* ptr = NULL;	/* temp */
    printf("[----- [장원도] [2018038099] -----]");
    
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 문자형 변수 입력 받음

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // bst 노드 초기화
			break;
		case 'q': case 'Q':
			freeBST(head); // 메모리 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insert(head, key); // 입력된 값 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			deleteLeafNode(head, key); // 입력된 값 노드 삭제 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			ptr = searchIterative(head, key); // 반복 함수 
			if(ptr != NULL) // ptr이 null 이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			ptr = searchRecursive(head->left, key); // 순환 함수 
			if(ptr != NULL) // ptr이 null 이 아니면 
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); // 중위 순회 함수 
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 전위 순회 함수 
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 후위 순회 함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { // 초기화 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // *h가 nill이 아니면
		freeBST(*h); // // 동적메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 동적메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;  // right 노드 *h값
	(*h)->key = -9999; // key 값
	return 1;
}



void inorderTraversal(Node* ptr) // 중위 순회 함수 
{
	if(ptr) { // ptr이 null 인지 체크 
		inorderTraversal(ptr->left); // inorderTraversal호출 및 ptr이 가르키는 left 넘김 
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right); // inorderTraversal호출 및 ptr이 가르키는 right 넘김 
	}
}

void preorderTraversal(Node* ptr) // 전위 순회 함수 
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left); // preorderTraversal함수 호출 ptr -> left
		preorderTraversal(ptr->right); // preorderTraversal함수 호출 ptr -> right
	}
}

void postorderTraversal(Node* ptr) // 후위 순회 함수 
{
	if(ptr) {
		postorderTraversal(ptr->left); // postorderTraversal 호출 ptr->left
		postorderTraversal(ptr->right);  // postorderTraversal 함수 호출 ptr -> right
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key) // 노드 삽입 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 동적메모리 할당
	newNode->key = key; // 노드에 입력된 키값 넣음
	newNode->left = NULL; // left값 null
	newNode->right = NULL; // right값 null

	if (head->left == NULL) {  // left가 null 이면
		head->left = newNode; // left에 노드값 넣음
		return 1; // 1값 반환 
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr에 left값 

	Node* parentNode = NULL; // parentNode에 null 값
	while(ptr != NULL) { // ptr이 null이 아니면 반복 

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; // key값이 같으면 1값 반환 

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr값 넣음 

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr이 가르키는 key값이 작으면 key값보다 작으면
			ptr = ptr->right; // ptr에 right값 
		else // 그외 
			ptr = ptr->left; // ptr에 left
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // parentNoderl가 가르키는 key값이 입력 key보다 작으면
		parentNode->left = newNode; // left에 newNode값 넣음
	else // 그외
		parentNode->right = newNode; //right에 newNode값 
	return 1; // 1값 반환 
}

int deleteLeafNode(Node* head, int key) // 노드 삭제 함수 
{
	if (head == NULL) { // head가 null 이면
		printf("\n Nothing to delete!!\n");
		return -1; // -1값 반환
	}

	if (head->left == NULL) { // left가 null 이면
		printf("\n Nothing to delete!!\n");
		return -1; // -1값 반환
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr에 left값


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}





