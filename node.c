
#include "node.h"


void addSon(Node *parent, Node *son)
{
	Node *current = parent->son;
	while (current != NULL)
	{
		current = current->bro;
	}
	current = son;
	return;
}


void addBroNode(Node *origin, Node *bro)
{
	Node *current = origin->bro; 
	while(current != NULL){
		current = current->bro; 
	}
	current = bro; 
	return; 
}


Node *makeLeaf(N_KIND kind, N_VALUE value)
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->kind = kind;
	n->value = value; 
	n->bro = NULL;
	n->son = NULL;
	return n;
}


Node *makeNode(N_KIND kind)
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->kind = kind;
	return n;
}


Node* makeSeq_Leaf(N_KIND under, N_VALUE value){
	Node* seq = makeNode(B_SEQ); 
	Node* leaf = makeLeaf(under, value); 
	addSon(seq, leaf); 
	return seq; 
} 


Node* makeSeq_Node(N_KIND under){
	Node* seq = makeNode(B_SEQ); 
	Node* node = makeNode(under); 
	addSon(seq, node); 
	return seq; 
}


void printNode(Node *here, int spaceCnt)
{
	const char *tab = "  ";
	for (int i = 0; i < spaceCnt; i++)
	{
		printf(tab);
	}

	switch (here->kind)
	{
	} 

	Node *s = here->son;
	while (s != NULL)
	{
		printNode(s, spaceCnt + 1);
		s = s->son;
	}

	Node *b = here->bro;
	while (b != NULL)
	{
		printNode(b, spaceCnt + 1);
		b = b->bro;
	}
	return;
}
