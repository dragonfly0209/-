#ifndef BsClass_h
#define BsClass_h
#include <iostream>
using namespace std;

typedef class classroom *cla;

class classroom
{
	public:		
		int priority,class_num;
		int object[8]; //0:non ,1:windows ,2:table ,3:fan ,4:air_conditioner ,5:blackboard ,6:projector ,7:lecture_table
		//int windows ,table ,fan ,air_conditioner ,blackboard ,projector ,lecture_table;
		classroom()
		{
			for(int i=0;i<=7;i++)
			{
				object[i]=0;
			}
		//	windows=table=fan=air_conditioner=blackboard=projector=lecture_table=priority=0;
		}
	
		void set_warning(int w)
		{
			object[w]++;
			set_priority();
		}   
		void set_priority()
		{
			priority=0;
			for(int i=0;i<=7;i++)
			{
				priority+=object[i]*i;
			}
		}
		void AllCleared()
		{
			for(int i=1;i<=7;i++)
			{
				object[i]=0;
			}
		}
		void PartCleared(int w)
		{
			object[w]=0;
			set_priority();
		}
		void print_object(int x)
		{
			if(x==1)
				cout<<"此教室需要維修的有：\n" ;
			else if(x==2)
				cout<<"此教室需要回報的有：\n" ;
			if(object[1]>0)
				cout<<"窗戶\n";
			if(object[2]>0)
				cout<<"桌子\n";	
			if(object[3]>0)
				cout<<"電風扇\n";
			if(object[4]>0)
				cout<<"冷氣\n";		
			if(object[5]>0)
				cout<<"黑板\n";
			if(object[6]>0)
				cout<<"投影機\n";
			if(object[7]>0)
				cout<<"講台(電腦)\n";
		}
		
};

int binary_search(cla arr[], int start, int end, int khey) 
{
	if (start > end)
		return 0;
	
	int mid = start + (end - start) / 2;    
	if (arr[mid]->class_num > khey)
		return binary_search(arr, start, mid - 1, khey);
	else if (arr[mid]->class_num < khey)
		return binary_search(arr, mid + 1, end, khey);
	else
	    return mid;        
}

#endif
