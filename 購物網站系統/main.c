#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  
#include <conio.h> 

int login(char *user);
int buy();
int sell(char *user);


int main(void)
{
	char *user;
	int choice,flag=0;
	user=malloc(sizeof(char)*20);
	flag=login(user);
	while(flag==2)
	{
		flag=login(user);
	}
	while(flag==1)
	{
		printf("歡迎來到NTUT商城\n1.購買\n2.販賣\n3.登出\n");		//顯示目錄 
	    printf("請輸入數字 :");			//輸入指定數字1,2,3 
	    scanf("%d",&choice);		//輸入指定數字1,2,3 
	
	
	    switch(choice) 
		{
	
	        case 1:			//a為1時，顯示購買 
	        	{
		         	buy();
		            break;
				}
	           
	        case 2:						//a為2時，顯示販賣 
	           	{
				    sell(user);
		            break;
				}
	        case 3:						//a為3時，顯示登出 ，並結束 
	            {
					printf("\n已登出\n歡迎下次再來\n");		
					flag=0;
					break;	
			    }
			default:                  //a為其他數字時，顯示輸入錯誤 
				{
					printf("輸入錯誤，請輸入數字1/2/3\n\n" ); 
					break;
				}
	        
	
	
	    }

	}
    
  
    return 0;		//結束程式 
}
