#ifndef AvlClass_h
#define AvlClass_h
#include <iostream>
#include "binary_search.h"
#include<string.h>

using namespace std;

typedef struct node_e *nodeptr;
typedef struct engineer *eng;
typedef struct classroom *cla;
struct node_e
{
   int element;
   node_e *left;
   node_e *right;
   int height;
   eng eee;
};

struct engineer
{
	int num,status;
	int password;
	cla cla;
};

class avltree
{

   public:
	int insert(eng &,nodeptr &);
	void del(int, nodeptr &);
	int deletemin(nodeptr &);
	eng find(int,nodeptr &);
	int bsheight(nodeptr);
	nodeptr srl(nodeptr &);
	nodeptr drl(nodeptr &);
	nodeptr srr(nodeptr &);
	nodeptr drr(nodeptr &);
	int max(int,int);
	int nonodes(nodeptr);
};


int avltree::insert(eng &eee,nodeptr &p)
{
	int x=eee->num;
   	if (p == NULL)
	{
		p = new node_e;
		p->element = x;
		p->left=NULL;
		p->right = NULL;
		p->height=0;
		if (p==NULL)
			cout<<"Out of Space"<<endl;
		p->eee=eee;	
		return 1;
	}
   	else
   	{
		if (x<p->element)
		{
			insert(eee,p->left);
			if ((bsheight(p->left) - bsheight(p->right))==2)
			{
				if (x < p->left->element)
					p=srl(p);
				else
					p = drl(p);
			}	
		}
		else if (x>p->element)
		{
		    insert(eee,p->right);
		    if ((bsheight(p->right) - bsheight(p->left))==2)
		    {
				if (x > p->right->element)
					p=srr(p);
				else
					p = drr(p);
		    }
		}
		else
		{ 
			cout<<"此編號已存在"<<endl;
			return 0;
		} 
	}
	int m,n,d;
	m=bsheight(p->left);
	n=bsheight(p->right);
	d=max(m,n);
	p->height = d + 1;

}

//		Finding an element
eng avltree::find(int x,nodeptr &p)
{
	if (p==NULL)
	{ 
	   	//cout<<"查無此員工"<<endl;
	   	return 0; 
	} 
	else if (x < p->element)
	   	find(x,p->left);
	else if (x>p->element)
	   	find(x,p->right);
	else
	{
		//cout<<"1"<<endl;
		return p->eee;
	}

}


//		Deleting a node
void avltree::del(int x,nodeptr &p)
{
	nodeptr d;
	if (p==NULL)
	   	cout<<"Element not found"<<endl;
	else if ( x < p->element)
	   	del(x,p->left);
	else if (x > p->element)
	   	del(x,p->right);
	else if ((p->left == NULL) && (p->right == NULL))
	{
		d=p;
		free(d);
		p=NULL;
		cout<<"Element deleted !"<<endl;
	}
	else if (p->left == NULL)
	{
		d=p;
		free(d);
		p=p->right;
		cout<<"Element deleted !"<<endl;
	}
	else if (p->right == NULL)
	{
		d=p;
		p=p->left;
		free(d);
		cout<<"Element deleted !"<<endl;
	}
	else
	  	p->element = deletemin(p->right);
}
int avltree::deletemin(nodeptr &p)
{
	int c;
	cout<<"inside deltemin"<<endl;
	if (p->left == NULL)
	{
		c=p->element;
		p=p->right;
		return c;
	}
	else
	{
		c=deletemin(p->left);
		return c;
	}
}


int avltree::max(int value1, int value2)
{
	return ((value1 > value2) ? value1 : value2);
}
int avltree::bsheight(nodeptr p)
{
	int t;
	if (p == NULL)
		return -1;
	else
	{
		t = p->height;
		return t;
	}
}


nodeptr avltree:: srl(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(bsheight(p1->left),bsheight(p1->right)) + 1;
	p2->height = max(bsheight(p2->left),p1->height) + 1;
	return p2;
}
nodeptr avltree:: srr(nodeptr &p1)
{
	nodeptr p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(bsheight(p1->left),bsheight(p1->right)) + 1;
	p2->height = max(p1->height,bsheight(p2->right)) + 1;
	return p2;
}
nodeptr avltree:: drl(nodeptr &p1)
{
	p1->left=srr(p1->left);
	return srl(p1);
}
nodeptr avltree::drr(nodeptr &p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}

#endif
