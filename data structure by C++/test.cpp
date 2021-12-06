/*
int main()
{
	nodeptr root ,root1 ,min ,max;// ,flag;
	int a ,choice ,findele ,delele ,leftele ,rightele ,flag;
	char ch = 'y';
	avltree bst;
	//system("clear");
	root = NULL;
	root1 = NULL;
	cout<<"AVL Tree\n";
	cout<<"========\n";
	do
	{
		cout<<" 1.Insertion\n";
		cout<<" 2.FindMin\n 3.FindMax\n 4.Find\n";
		cout<<" 5.Copy\n 6.Delete\n";
		cout<<" 7.Preorder\n 8.Inorder\n 9.Postorder\n";
		cout<<"10.height\n";
		cout<<"Enter the choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"New node's value ?";
				cin>>a;
				bst.insert(a ,root);
				break;
			case 2:
				if (root !=NULL)
				{
					min=bst.findmin(root);
					cout<<"Min element :"<<min->element<<endl;
				}
				break;
			case 3:
				if (root !=NULL)
				{
					max=bst.findmax(root);
					cout<<"Max element :"<<max->element<<endl;
				}
				break;
			case 4:
				cout<<"Search node :";
				cin>>findele;
				if (root !=NULL)
					bst.find(findele ,root);
				break;
			case 5:
				bst.copy(root ,root1);
				bst.inorder(root1);
				cout<<"\n";
				break;
			case 6:
				cout<<"Delete Node ?";
				cin>>delele;
				bst.del(delele ,root);
				bst.inorder(root);
				cout<<"\n";
				break;
			case 7:
				cout<<" Preorder Printing... :";
				bst.preorder(root);
				cout<<"\n";
				break;
			case 8:
				cout<<" Inorder Printing.... :";
				bst.inorder(root);
				cout<<"\n";
				break;
			case 9:
				cout<<" Postorder Printing... :";
				bst.postorder(root);
				cout<<"\n";
				break;
			case 10:
				cout<<" Height and Depth is ";
				cout<<bst.bsheight(root)<<endl;
				cout<<"No. of nodes:- "<<bst.nonodes(root)<<endl;
				break;
			default:
				cout<<"error"<<endl;	
		}
		//	cout<<" Do u want to continue (y/n) ?";
		//	cin>>ch;
	}while(1);
		
	return 0;
}
*/
/*
int main()  
{  
	classroom a;
	int x;
	cin>>x;
	a.set_warning(x);
	cout<<a.priority;
	a.Allleared();
	cout<<a.priority;

	queue<string>myqueue;
  	string myint;

  	cout<<"Please enter some integers (enter 0 to end):\n";

	do 
	{
	   cin>>myint;
	   myqueue.push (myint);
	} while (myint!="0");
	cout<<"myqueue contains: ";
	while (!myqueue.empty())
	{
		cout<<' '<<myqueue.front();
		myqueue.pop();
	}
	cout<<'\n';
	
	return 0;
}
*/
