#include<cstdlib>
#include<iostream>
#include<string.h>

#include<queue>

#include "AvlTree.h"
#include "binary_search.h"
#include "Merge_Sort.h"

using namespace std; 
nodeptr engineer_root;
avltree engineer_avl;
cla z[35]={};
cla temp[35]={};

void init()
{
	for(int i=0;i<=10;i++)
	{
		temp[i]=new classroom;
	}
	temp[1]->class_num=2203;
	temp[1]->set_warning(1);
	temp[1]->set_warning(3);
	temp[2]->class_num=3204;
	temp[2]->set_warning(5);
}

void class_init()
{
	int i,j,x;
	j=2100;
	x=1;
	cla c;
	for(i=2101;i<=3305;i++)
	{
		z[i-j]=new classroom;
		z[i-j]->class_num=i;
		if(i==2305)
		{
			i=i+1000-205;
			j=j+1000-205;
			x++;
		}
		if(i==j+x*5)
		{
			i=i+100-5;
			j=j+100-5;
			x++;
		}
	}
}

void engineer_init()
{
	eng x;
	for(int i=10000;i<=10042;i=i+3)
	{
		x=new engineer;
		x->num=i;
		x->password=i;
		engineer_avl.insert(x,engineer_root);
	}
}

int main(int argc ,char *argv[])
{
	int first=1;
	init();
	queue<cla>myqueue;
	myqueue.push(temp[1]);
	myqueue.push(temp[2]);
	
  	char classname[]="";
  	char floor[]="��";
	char *Token;
  	int choice,warning,search_num,queue_size;
  	class_init();
	cla a1;
	
	int eng_num,login=0;
	int pass,suc=1;
	engineer_init();
	eng eee;
	int choice_eng,choice_re,y=0;
  	while(first)
  	{
		cout<<"�w��i�J���רt��"<<endl;
		cout<<"�аݬO�n�����٬O����?"<<endl;
		cout<<"0.�h�X\n1.����\n2.����"<<endl;
		cin>>choice;
		system("cls");
		switch(choice)
		{
			case 0:
				first=0;
			break;	
			case 1:
				suc=1;
				system("cls");
				while(suc)
				{			
					cout<<"�аݻݭn���׭����Ы�(�ҡG2��101�A��J0��^)"<<endl; 
					/*for(int i=1;i<=30;i++)
					{
						cout<<z[i]->class_num<<endl;
					}*/
					cin>>classname;
					if(!strcmp(classname,"0"))
					{
						suc=0;
						break;
					}
					
					queue_size=myqueue.size();
					if(queue_size>0)
					{
						for(int i=1;i<=queue_size;i++)
						{
							temp[i]=myqueue.front();
							myqueue.pop();
						}
					}
						
					
					a1=new classroom;
					Token = strtok(classname,floor);
					if(Token != NULL) 
					{
						a1->class_num=atoi(Token);
						Token = strtok(NULL,floor);	
						a1->class_num=a1->class_num*1000+atoi(Token);
					}
					//cout<<a1->class_num;
					if(binary_search(z,1,30,a1->class_num))
					{		
					
						if(binary_search(temp,1,queue_size+1,a1->class_num))
						{
							search_num=binary_search(temp,1,queue_size+1,a1->class_num);
							a1=new classroom;
							a1=temp[search_num];
							if(temp[queue_size+1]->class_num==0||temp[queue_size+1]->priority==0)
								queue_size--;
						}
						else
							temp[queue_size+1]=a1;
							
						system("cls");
						cout<<"�аݬO�n����"<<a1->class_num/1000<<"��"<<a1->class_num%1000<<"������F��?"<<endl;
						cout<<"1.����\n2.��l\n3.�q����\n";
						cout<<"4.�N��\n5.�ªO\n6.��v��\n";
						cout<<"7.���x(�q��)\n";
						cin>>warning;
						if(warning<=7&&warning>0)
						{
							a1->set_warning(warning);
							
							Merge_Sort(temp,1,queue_size+1);
							for(int i=queue_size+1;i>0;i--)
							{
								myqueue.push(temp[i]);
							}	
							system("cls");
							cout<<"���צ��\\\n";
							suc=0;
						}
						else
						{
							system("cls");	
							cout<<"�Э��s��J"<<endl; 
						}
					}
					else if(suc)	
					{
						system("cls");
						cout<<"�d�L���Ы�"<<endl;
						suc=0;
					}
				}
				break;
			case 2:
				suc=1;
				system("cls");
				while(suc)
				{
					
					cout<<"�п�J����Ƥ����u�s��(��J0��^)"<<endl; 
					cin>>eng_num;
					if(eng_num==0)
						suc=0;
					eee=new engineer;
					eee=engineer_avl.find(eng_num,engineer_root);
					if(eee!=0)
					{	
						cout<<"�п�J�Ʀr�K�X"<<endl; 
						cin>>pass;
						if(pass==eee->password)
						{ 
							system("cls");
							cout<<"�w��i�J���רt��"<<endl;
							cout<<"�|��"<<myqueue.size()<<"���Ыǻݭn����"<<endl; 
							login=1;
							suc=0;
						} 
						else
						{
							system("cls"); 
							cout<<"�K�X���~"<<endl;
						} 
					}
					else if(suc)
					{
						system("cls");
						cout<<"�d�L�����u"<<endl;
						suc=0;
					}
				}
				break;	
			default:
				system("cls");
				cout<<"��J���~�A�Э��s���"<<endl; 
				break;	
		}

		while(login==1)
		{
			cout<<"�п�ܶ���"<<endl;
			cout<<"0.��^\n1.����\n2.�^��\n3.�s�W���u\n";
			cin>>choice_eng;
			system("cls");
			switch(choice_eng)
			{
				case 0:
					login=0;
				break;	
				case 1:
					if(eee->status==0)
					{
						
						if(myqueue.size()==0||myqueue.front()->class_num==0||myqueue.front()->priority==0)
							cout<<"�L�Ыǻݭn����"<<endl;
						else
						{
							eee->cla=new classroom;
							eee->cla= myqueue.front();
							myqueue.pop();
							cout<<"����������"<<eee->cla->class_num/1000<<"��"<<eee->cla->class_num%1000<<endl;
							eee->cla->print_object(1);
							eee->status=1;
						}
					}
					else
					{
						cout<<"�Х��N"<<eee->cla->class_num/1000<<"��"<<eee->cla->class_num%1000<<"���ק�\n";
						eee->cla->print_object(1);
					}
				break;
				case 2:
					if(eee->status==1)
					{
						cout<<"�аݬO�_���ק�?\n0.�h�X\n1.�������ק�\n2.�������ק�\n";
						cin>>choice_re;
						switch(choice_re)
						{
							case 0:
								system("cls");
							break;
							case 1:
								eee->cla->AllCleared();
								eee->status=0;
								system("cls");
								cout<<"�^�����\\\n";
							break;	
							case 2:
								do
								{
									system("cls");
									eee->cla->print_object(2);
									cout<<"�аݬO���Ӷ��ؤw����?"<<endl;
									cout<<"0.�h�X\n";
									cout<<"1.����\n2.��l\n3.�q����\n";
									cout<<"4.�N��\n5.�ªO\n6.��v��\n";
									cout<<"7.���x(�q��)\n";
									cin>>warning;
									if(warning<=7&&warning>0)
									{
										eee->cla->PartCleared(warning);
										system("cls");
										cout<<"�^�����\\\n"; 
										cout<<"�O�_�~��^��?\n0.�h�X\n1.�~��\n"; 
										cin>>y;
									}
									else if(warning==0)
										y=0;
									else
									{
										system("cls");
										cout<<"�Э��s��J"<<endl; 
									}
										
								}while(y);
								system("cls");
								
								queue_size=myqueue.size();
								for(int i=1;i<=queue_size;i++)
								{
									temp[i]=myqueue.front();
									myqueue.pop();
								}
								if(eee->cla->priority>0)
									temp[queue_size+1]=eee->cla;
								Merge_Sort(temp,1,queue_size+1);
								for(int i=queue_size+1;i>0;i--)
								{
									myqueue.push(temp[i]);
								}	
								
								eee->status=0;		
															
							break;
							default:
								cout<<"��J���~�A�Э��s��J"<<endl;
							break;	
						}
					}
					else 
						cout<<"�L���^��"<<endl; 
				break;	
				case 3:
					cout<<"�п�J�s���u������ƽs��"<<endl;
					eee=new engineer;
					cin>>eee->num;
					if(eee->num>99999)
					{
						system("cls");
						cout<<"��J���~�A�Э��s��J"<<endl; 
					}
					else if(engineer_avl.find(eee->num,engineer_root)==0)
					{
						engineer_avl.insert(eee,engineer_root);
						cout<<"�п�J�s���u���Ʀr�K�X(�ФŶW�L9�Ӧr��)"<<endl;
						cin>>eee->password;
						system("cls");
						cout<<"�إߦ��\\�A�Э��s�n�J"<<endl;
						login=0; 
					}
					else 
					{
						system("cls");
						cout<<"���s���w�s�b"<<endl;
					}
					
				break;
				default:
					cout<<"��J���~�A�Э��s���"<<endl; 
				break;	
			}
		}
		
	}
	system("cls");
	cout<<"�P�±z������"<<endl; 
}


