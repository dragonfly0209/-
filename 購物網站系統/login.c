#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void SetCode(char *code); 
int login(char *user)
{
	int i=0,j,k,flag_acc=0,flag_code=0,choice=0,logfail=0; //�ŧi�ܼ� 
	// �ŧi�Ȧs�ϥΪ̿�J���b���αK�X  
    char a1[21]="";
    char a2[21]="";
    char a3[21]="";
    FILE *debug = fopen("account.txt","a");			//�������ɳQ�������� 
	fprintf(debug,"END\n");							//�N"END"�g�b�y���A�H�����{��Ū������"END "�Ӳ��Ͱ��D 
	fclose(debug);
	struct tatal          
	{
		char *acc;       // �b�� 
		char *code;      // �K�X 
	
	}*item;
	item=malloc(sizeof(struct tatal)*500);    //�����Ŷ�  
	printf("�p�n�n�J�Ы�1�A���U�Ы�2 :");     // ���ϥΪ̿�J 
	scanf("%d",&choice); //���J�ܼ� choice
	switch(choice)	//��choice����ơA������case�N�Q����
	{
		case 1:  //choice=1�����p����U�z 
			logfail=0;
			flag_acc=0;
			flag_code=0;
			i=0;
			(item)->acc=malloc(sizeof(struct tatal)*500);       //�����Ŷ�  
			(item)->code=malloc(sizeof(struct tatal)*500);       //�����Ŷ�
			FILE *fp = fopen("account.txt","r");      			
		 	fscanf(fp,"%s",(item+i)->acc);                  
			while(strcmp((item+i)->acc,"END")!=0)          //�Y�C���Ĥ@�椣��END,�h����H�U���ʧ@ 
			{
				fscanf(fp,"%s",(item+i)->code);	
			
				i++;                                        //i�W�[1											
				(item+i)->acc=malloc(sizeof(struct tatal)*500);       //�����Ŷ�  
				(item+i)->code=malloc(sizeof(struct tatal)*500);       //�����Ŷ�
				
				fscanf(fp,"%s",(item+i)->acc);
			}
			fclose(fp);	   
		     
		    printf("�п�J�b���G "); // ���ϥΪ̿�J 
		    scanf("%s", a1);//���J�ܼ� a1

			for(j=0;j<i;j++)
		    {
		        if (!strcmp(a1, (item+j)->acc)) 
				{	
					flag_acc++;	        	
			        printf("�п�J�K�X�G "); // ���ϥΪ̿�J 
			        SetCode(a2); 
					logfail=0;
					while(logfail<2&&flag_code==0)
					{										                
				        if (!strcmp(a2, (item+j)->code)) //�p�G�K�X��J�@�P�� 
						{				  
				            printf("\n\n���o�A %s �A �w��i�J�ʪ��ӫ���...\n\n", (item+j)->acc);//�K�X�@�˴N�i�J�{�� 
				           	flag_code++;
				       	}	
				       	else //�p�G�K�X���@�P�� 
				       	{
				       		printf("\n�K�X���~�A�ЦA����J�K�X:");// ���ϥΪ̭��s��J�K�X 
				       		logfail++;
							SetCode(a2); 					       		
						}								  
					}													         
		        }			        
			}
			for(j=0;j<i;j++)
			{
				free((item+j)->acc);
				free((item+j)->code);
			}
			free(item);
			
			if(flag_acc==0)//�p�G�b�����s�b�� 
			{
				printf("�d�L���b��");//��ܵL���b�� 
				return 4;
			}
			if(logfail>=2)//�p�G��J�K�X�W�L3�� 
			{
				printf("\n�n�J���ѹL�h���A�еy��b��"); //�K�X��J3���H�᳣���ѡA��ܵn�J���ѹL�h���A�еy��b��
				return 4;
			}		    			
			
			
			if(flag_acc==1&&flag_code==1)
		    {
		    	strcpy(user,a1);
				return 1;
			}
			
		
		case 2 : //choice=2�����p����U�z
			logfail=0;
			flag_acc=0;
			flag_code=0;
			i=0;
			(item)->acc=malloc(sizeof(struct tatal)*500);       //�����Ŷ�  
			(item)->code=malloc(sizeof(struct tatal)*500);       //�����Ŷ�
			FILE *fp1 = fopen("account.txt","r");      			
		 	fscanf(fp1,"%s",(item+i)->acc);                  
			while(strcmp((item+i)->acc,"END")!=0)          //�Y�C���Ĥ@�椣��END,�h����H�U���ʧ@ 
			{
				fscanf(fp1,"%s",(item+i)->code);	
			
				i++;                                        //i�W�[1											
				(item+i)->acc=malloc(sizeof(struct tatal)*500);       //�����Ŷ�  
				(item+i)->code=malloc(sizeof(struct tatal)*500);       //�����Ŷ�
				
				fscanf(fp1,"%s",(item+i)->acc);
			}
			fclose(fp1);
		    
		    printf("�п�J�s�b���G ");// ���ϥΪ̿�J
		    scanf("%s", a1); //���J�ܼ� a1
			for(j=0;j<i;j++)
		    {
		        if (!strcmp(a1, (item+j)->acc)) //�p�G�b���w�֦� 
				{				
					printf("���b���w�Q�ϥιL\n");//��ܦ��b���w�Q�ϥιL
					flag_acc++;
		        }			        
			}
			if(flag_acc==0)//�p�G�b�����Q���U 
			{
				printf("�п�J�s�K�X�G ");// ���ϥΪ̿�J 
			    SetCode(a2); 
			    printf("\n�ЦA����J�s�K�X�G ");//�A�����ϥΪ̿�J 
			    SetCode(a3);
			    if (strcmp(a2,a3)) //�p�G2���K�X��J���@�P 
				{				
					printf("\n�K�X�����~\n");// ��ܱK�X�����~
		        }
				else 
				{
					flag_code++;
				}			    
			}
		    if(flag_code==1)
		    {
		    	FILE *fp2 = fopen("account.txt","w");
		    	strcpy((item+i)->acc,a1);
		    	strcpy((item+i)->code,a2);
		    	for(j=0;j<=i;j++)
				{
					fprintf(fp2,"%s %s\n",(item+j)->acc,(item+j)->code);
				}
				fprintf(fp2,"END\n");
				fclose(fp2);
				printf("\n���U���\\\n\n"); //��ܵ��U���\   
				
			}
			
			for(j=0;j<=i;j++)
			{
				free((item+j)->acc);
				free((item+j)->code);
			}
			free(item);	
			return 2;
		default:
			printf("�Э��s��J\n");
			return 2;
		
		
	}
	
    free(item);
      
}  
void SetCode(char *code)
{ 
	int n = 0; 
	
	while(n < 20)
	{ 
		code[n] = getch(); //getch��J�ɤ��|�A�ù���� 
		
		if(code[n] == 8)
		{ 		
			if(n > 0)
			{ 
				printf("\b \b"); 
				n--; 
			} 
			else 
				printf(""); 
		} 
		else if(code[n] == 13)
		{ 
			code[n] = '\0'; 
			break; 
		} 
		else
		{ 
			printf("*"); 
			n++; 
		} 
	}
 } 
