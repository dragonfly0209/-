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
  	char floor[]="教";
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
		cout<<"歡迎進入報修系統"<<endl;
		cout<<"請問是要報修還是維修?"<<endl;
		cout<<"0.退出\n1.報修\n2.維修"<<endl;
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
					cout<<"請問需要報修哪間教室(例：2教101，輸入0返回)"<<endl; 
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
						cout<<"請問是要報修"<<a1->class_num/1000<<"教"<<a1->class_num%1000<<"的什麼東西?"<<endl;
						cout<<"1.窗戶\n2.桌子\n3.電風扇\n";
						cout<<"4.冷氣\n5.黑板\n6.投影機\n";
						cout<<"7.講台(電腦)\n";
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
							cout<<"報修成功\\n";
							suc=0;
						}
						else
						{
							system("cls");	
							cout<<"請重新輸入"<<endl; 
						}
					}
					else if(suc)	
					{
						system("cls");
						cout<<"查無此教室"<<endl;
						suc=0;
					}
				}
				break;
			case 2:
				suc=1;
				system("cls");
				while(suc)
				{
					
					cout<<"請輸入五位數之員工編號(輸入0返回)"<<endl; 
					cin>>eng_num;
					if(eng_num==0)
						suc=0;
					eee=new engineer;
					eee=engineer_avl.find(eng_num,engineer_root);
					if(eee!=0)
					{	
						cout<<"請輸入數字密碼"<<endl; 
						cin>>pass;
						if(pass==eee->password)
						{ 
							system("cls");
							cout<<"歡迎進入維修系統"<<endl;
							cout<<"尚有"<<myqueue.size()<<"間教室需要維修"<<endl; 
							login=1;
							suc=0;
						} 
						else
						{
							system("cls"); 
							cout<<"密碼錯誤"<<endl;
						} 
					}
					else if(suc)
					{
						system("cls");
						cout<<"查無此員工"<<endl;
						suc=0;
					}
				}
				break;	
			default:
				system("cls");
				cout<<"輸入錯誤，請重新選擇"<<endl; 
				break;	
		}

		while(login==1)
		{
			cout<<"請選擇項目"<<endl;
			cout<<"0.返回\n1.維修\n2.回報\n3.新增員工\n";
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
							cout<<"無教室需要維修"<<endl;
						else
						{
							eee->cla=new classroom;
							eee->cla= myqueue.front();
							myqueue.pop();
							cout<<"請幫忙維修"<<eee->cla->class_num/1000<<"教"<<eee->cla->class_num%1000<<endl;
							eee->cla->print_object(1);
							eee->status=1;
						}
					}
					else
					{
						cout<<"請先將"<<eee->cla->class_num/1000<<"教"<<eee->cla->class_num%1000<<"維修完\n";
						eee->cla->print_object(1);
					}
				break;
				case 2:
					if(eee->status==1)
					{
						cout<<"請問是否維修完?\n0.退出\n1.全部維修完\n2.部分維修完\n";
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
								cout<<"回報成功\\n";
							break;	
							case 2:
								do
								{
									system("cls");
									eee->cla->print_object(2);
									cout<<"請問是哪個項目已完成?"<<endl;
									cout<<"0.退出\n";
									cout<<"1.窗戶\n2.桌子\n3.電風扇\n";
									cout<<"4.冷氣\n5.黑板\n6.投影機\n";
									cout<<"7.講台(電腦)\n";
									cin>>warning;
									if(warning<=7&&warning>0)
									{
										eee->cla->PartCleared(warning);
										system("cls");
										cout<<"回報成功\\n"; 
										cout<<"是否繼續回報?\n0.退出\n1.繼續\n"; 
										cin>>y;
									}
									else if(warning==0)
										y=0;
									else
									{
										system("cls");
										cout<<"請重新輸入"<<endl; 
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
								cout<<"輸入錯誤，請重新輸入"<<endl;
							break;	
						}
					}
					else 
						cout<<"無須回報"<<endl; 
				break;	
				case 3:
					cout<<"請輸入新員工之五位數編號"<<endl;
					eee=new engineer;
					cin>>eee->num;
					if(eee->num>99999)
					{
						system("cls");
						cout<<"輸入錯誤，請重新輸入"<<endl; 
					}
					else if(engineer_avl.find(eee->num,engineer_root)==0)
					{
						engineer_avl.insert(eee,engineer_root);
						cout<<"請輸入新員工之數字密碼(請勿超過9個字元)"<<endl;
						cin>>eee->password;
						system("cls");
						cout<<"建立成功\，請重新登入"<<endl;
						login=0; 
					}
					else 
					{
						system("cls");
						cout<<"此編號已存在"<<endl;
					}
					
				break;
				default:
					cout<<"輸入錯誤，請重新選擇"<<endl; 
				break;	
			}
		}
		
	}
	system("cls");
	cout<<"感謝您的幫忙"<<endl; 
}


