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
		printf("�w��Ө�NTUT�ӫ�\n1.�ʶR\n2.�c��\n3.�n�X\n");		//��ܥؿ� 
	    printf("�п�J�Ʀr :");			//��J���w�Ʀr1,2,3 
	    scanf("%d",&choice);		//��J���w�Ʀr1,2,3 
	
	
	    switch(choice) 
		{
	
	        case 1:			//a��1�ɡA����ʶR 
	        	{
		         	buy();
		            break;
				}
	           
	        case 2:						//a��2�ɡA��ܳc�� 
	           	{
				    sell(user);
		            break;
				}
	        case 3:						//a��3�ɡA��ܵn�X �A�õ��� 
	            {
					printf("\n�w�n�X\n�w��U���A��\n");		
					flag=0;
					break;	
			    }
			default:                  //a����L�Ʀr�ɡA��ܿ�J���~ 
				{
					printf("��J���~�A�п�J�Ʀr1/2/3\n\n" ); 
					break;
				}
	        
	
	
	    }

	}
    
  
    return 0;		//�����{�� 
}
