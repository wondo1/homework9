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

typedef struct node { // typedef ����� Node ����ü ����
	int key;  // ������ ���� ���� 
	struct node *left; // ���� ��� ����
	struct node *right; // ������ ��� ����
} Node;

int initializeBST(Node** h); // �ʱ�ȭ �Լ�

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
	char command; // ������ ���� ����
	int key; // ������ ���� ����
	Node* head = NULL; // ����� null ��
	Node* ptr = NULL;	/* temp */
    printf("[----- [�����] [2018038099] -----]");
    
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
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // bst ��� �ʱ�ȭ
			break;
		case 'q': case 'Q':
			freeBST(head); // �޸� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insert(head, key); // �Էµ� �� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			deleteLeafNode(head, key); // �Էµ� �� ��� ���� 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			ptr = searchIterative(head, key); // �ݺ� �Լ� 
			if(ptr != NULL) // ptr�� null �� �ƴϸ�
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			ptr = searchRecursive(head->left, key); // ��ȯ �Լ� 
			if(ptr != NULL) // ptr�� null �� �ƴϸ� 
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); // ���� ��ȸ �Լ� 
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // ���� ��ȸ �Լ� 
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // ���� ��ȸ �Լ�
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { // �ʱ�ȭ �Լ�

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // *h�� nill�� �ƴϸ�
		freeBST(*h); // // �����޸� ����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // �����޸� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;  // right ��� *h��
	(*h)->key = -9999; // key ��
	return 1;
}



void inorderTraversal(Node* ptr) // ���� ��ȸ �Լ� 
{
	if(ptr) { // ptr�� null ���� üũ 
		inorderTraversal(ptr->left); // inorderTraversalȣ�� �� ptr�� ����Ű�� left �ѱ� 
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right); // inorderTraversalȣ�� �� ptr�� ����Ű�� right �ѱ� 
	}
}

void preorderTraversal(Node* ptr) // ���� ��ȸ �Լ� 
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left); // preorderTraversal�Լ� ȣ�� ptr -> left
		preorderTraversal(ptr->right); // preorderTraversal�Լ� ȣ�� ptr -> right
	}
}

void postorderTraversal(Node* ptr) // ���� ��ȸ �Լ� 
{
	if(ptr) {
		postorderTraversal(ptr->left); // postorderTraversal ȣ�� ptr->left
		postorderTraversal(ptr->right);  // postorderTraversal �Լ� ȣ�� ptr -> right
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key) // ��� ���� �Լ�
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // �����޸� �Ҵ�
	newNode->key = key; // ��忡 �Էµ� Ű�� ����
	newNode->left = NULL; // left�� null
	newNode->right = NULL; // right�� null

	if (head->left == NULL) {  // left�� null �̸�
		head->left = newNode; // left�� ��尪 ����
		return 1; // 1�� ��ȯ 
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr�� left�� 

	Node* parentNode = NULL; // parentNode�� null ��
	while(ptr != NULL) { // ptr�� null�� �ƴϸ� �ݺ� 

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; // key���� ������ 1�� ��ȯ 

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //ptr�� ���� 

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ptr�� ����Ű�� key���� ������ key������ ������
			ptr = ptr->right; // ptr�� right�� 
		else // �׿� 
			ptr = ptr->left; // ptr�� left
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // parentNoderl�� ����Ű�� key���� �Է� key���� ������
		parentNode->left = newNode; // left�� newNode�� ����
	else // �׿�
		parentNode->right = newNode; //right�� newNode�� 
	return 1; // 1�� ��ȯ 
}

int deleteLeafNode(Node* head, int key) // ��� ���� �Լ� 
{
	if (head == NULL) { // head�� null �̸�
		printf("\n Nothing to delete!!\n");
		return -1; // -1�� ��ȯ
	}

	if (head->left == NULL) { // left�� null �̸�
		printf("\n Nothing to delete!!\n");
		return -1; // -1�� ��ȯ
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr�� left��


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





