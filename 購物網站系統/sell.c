#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int sell(char *user)
{
	int i = 0 , j  , k ,temp;
	char find_seller[500];
	FILE *debug = fopen("list.txt","a");			//�������ɳQ�������� 
	fprintf(debug,"END\n");							//�N"END"�g�b�y���A�H�����{��Ū������"END "�Ӳ��Ͱ��D 
	fclose(debug);
	struct total			//�ӫ~�C���ɮ׮榡
	{
		char *name;			//�ӫ~�W��
		char *money;		//�ӫ~���� 
		char *num;			//�ӫ~�ƶq 
		char *seller;		//��a 
		char *date;			//�W�[��� 
		char *info;			//�ӫ~��T 
	}*item;
	item=malloc(sizeof(struct total)*1000); 		//�����Ŷ� 
	while(1)
	{

		printf(" \n�ﶵ�@:��a�W�[\n�ﶵ�G:�ӫ~�C��\n�ﶵ�T:��M��a�ӫ~\n�ﶵ�|:���}\n�п�J�z���ﶵ:");		//��� 
		scanf("%d" , &k);																						//��J���ﶵ 
		printf("\n");
		switch(k)
		{		
	
		case 1:													//�ﶵ�@							
			i = 0;
			j = 0;	
			
			(item)->name=malloc(sizeof(struct total)*500);		//�����Ŷ�	 
			(item)->money=malloc(sizeof(struct total)*500);		//�����Ŷ�
			(item)->num=malloc(sizeof(struct total)*500);		//�����Ŷ�
			(item)->seller=malloc(sizeof(struct total)*500);	//�����Ŷ�
			(item)->date=malloc(sizeof(struct total)*500);		//�����Ŷ�
			(item)->info=malloc(sizeof(struct total)*500);		//�����Ŷ�
			
			FILE *fp2 = fopen("list.txt","r");					//�}�Ұӫ~�C����"list.txt"�÷ǳ�Ū�� 
			fscanf(fp2,"%s",(item+i)->name);					//���y���ñN�Ĥ@���g�J�ӫ~�W�ٰ}�C 
			
			while(strcmp((item+i)->name,"END")!=0)				//�P�_�Ĥ@���O�_������"END"�ð���j�� 
			{
			
				fscanf(fp2,"%s ",(item+i)->money);              // ���y���üg�J�ӫ~����}�C 
				fscanf(fp2,"%s ",(item+i)->num);				// ���y���üg�J�ӫ~�ƶq�}�C
				fscanf(fp2,"%s ",(item+i)->seller);				// ���y���üg�J��a�}�C
				fscanf(fp2,"%s ",(item+i)->date);				// ���y���üg�J�W�[����}�C
				fscanf(fp2,"%s\n",(item+i)->info);				// ���y���üg�J�ӫ~��T�}�C
					
				i++;
				
				(item+i)->name=malloc(sizeof(struct total)*500); 	// �����Ŷ�
				(item+i)->money=malloc(sizeof(struct total)*500);	// �����Ŷ�
				(item+i)->num=malloc(sizeof(struct total)*500); 	// �����Ŷ�
				(item+i)->seller=malloc(sizeof(struct total)*500);	// �����Ŷ�
				(item+i)->date=malloc(sizeof(struct total)*500);	// �����Ŷ�
				(item+i)->info=malloc(sizeof(struct total)*500);	// �����Ŷ�
			
				fscanf(fp2,"%s",(item+i)->name);					// ���y���üg�J�ӫ~�W�ٰ}�C 
			}
		
			fclose(fp2);                                    		//�����ɮ� 
		
	
	
			FILE *fp1 = fopen("list.txt","w");						//�}�Ұӫ~�C����"list.txt"�÷ǳƼg�J 

			printf("�п�J�ӫ~�W��:"); 								//���"�п�J�ӫ~�W��:" 
			scanf("%s",(item+i)->name);								//��J�ӫ~�W�٨�}�C 
			printf("�п�J�ӫ~����:");								//���"�п�J�ӫ~����:"
			scanf("%s",(item+i)->money);							//��J�ӫ~�����}�C 
			printf("�п�J�ӫ~�ƶq:");								//���"�п�J�ӫ~�ƶq:"
			scanf("%s",(item+i)->num);								//��J�ӫ~�ƶq��}�C 
			strcpy((item+i)->seller,user);							//�N�b���W�ٽƻs��}�C 
			printf("�п�J�W�[���:");								//���"�п�J�W�[���:"
			scanf("%s",(item+i)->date);								//��J�W�[�����}�C 
			printf("�п�J�ӫ~��T:");								//���"�п�J�ӫ~��T:"
			scanf("%s",(item+i)->info);								//��J�ӫ~��T��}�C 
			
			for(j=0;j<=i;j++)
			{
				fprintf(fp1,"%s ",(item+j)->name);					//�N�ӫ~�W�ٰ}�C�����r���J��ӫ~�C����"list.txt" 
				fprintf(fp1,"%s ",(item+j)->money);					//�N�ӫ~����}�C�����r���J��ӫ~�C����"list.txt" 
				fprintf(fp1,"%s ",(item+j)->num);					//�N�ӫ~�ƶq�}�C�����r���J��ӫ~�C����"list.txt" 
				fprintf(fp1,"%s ",(item+j)->seller);				//�N��a�}�C�����r���J��ӫ~�C����"list.txt" 
				fprintf(fp1,"%s ",(item+j)->date);					//�N�W�[����}�C�����r���J��ӫ~�C����"list.txt" 
				fprintf(fp1,"%s\n",(item+j)->info);					//�N�ӫ~��T�}�C�����r���J��ӫ~�C����"list.txt" 
				
				free((item+j)->name);								//����Ŷ� 
				free((item+j)->money);								//����Ŷ�
				free((item+j)->num);								//����Ŷ�
				free((item+j)->seller);								//����Ŷ�
				free((item+j)->date);								//����Ŷ� 
				free((item+j)->info);								//����Ŷ� 
			}
			fprintf(fp1,"END\n");									//�g�JEND���󤤳̫�@�� 
			printf("\n�W�[�o!\n");									//���"�W�[�o!"
			fclose(fp1);											//������� 
			break;
	
		case 2 :													//�ﶵ�G 
			i = 0;
			j = 0;
			FILE *fp3 = fopen("list.txt","r");						//�}�Ұӫ~�C����"list.txt"�÷ǳ�Ū�� 

			(item)->name=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->money=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->num=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->seller=malloc(sizeof(struct total)*500);		//�����Ŷ� 
			(item)->date=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->info=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			
			fscanf(fp3,"%s ",(item+i)->name);						//���y���ñN�Ĥ@���g�J�ӫ~�W�ٰ}�C
			
			while(strcmp((item+i)->name,"END")!=0)					//�P�_�Ĥ@���O�_������"END"�ð���j��
			{
				
				fscanf(fp3,"%s ",(item+i)->money);					// ���y���üg�J�ӫ~����}�C 
				fscanf(fp3,"%s ",(item+i)->num);					// ���y���üg�J�ӫ~�ƶq�}�C
				fscanf(fp3,"%s ",(item+i)->seller);					// ���y���üg�J��a�}�C
				fscanf(fp3,"%s ",(item+i)->date);					// ���y���üg�J�W�[����}�C
				fscanf(fp3,"%s\n",(item+i)->info);					// ���y���üg�J�ӫ~��T�}�C
						
				i++;
				
				(item+i)->name=malloc(sizeof(struct total)*500);	//�����Ŷ� 
				(item+i)->money=malloc(sizeof(struct total)*500);	//�����Ŷ�
				(item+i)->num=malloc(sizeof(struct total)*500);		//�����Ŷ�
				(item+i)->seller=malloc(sizeof(struct total)*500);	//�����Ŷ�
				(item+i)->date=malloc(sizeof(struct total)*500);	//�����Ŷ�
				(item+i)->info=malloc(sizeof(struct total)*500);	//�����Ŷ�
				
				fscanf(fp3,"%s",(item+i)->name);					// ���y���üg�J�ӫ~�W�ٰ}�C 
			}
			
			fclose(fp3);											//������� 

			for(j=0;j<i;j++)
			{
				printf("�ӫ~�W��:%s ",(item+j)->name);				//��ܤ�󤤩Ҧs�����ӫ~�W�� 
				printf("�ӫ~����:%s ",(item+j)->money);				//��ܤ�󤤩Ҧs�����ӫ~���� 
				printf("�ӫ~�ƶq:%s ",(item+j)->num);				//��ܤ�󤤩Ҧs�����ӫ~�ƶq 
				printf("��a:%s ",(item+j)->seller);				//��ܤ�󤤩Ҧs������a 
				printf("�W�[���%s ",(item+j)->date);				//��ܤ�󤤩Ҧs�����W�[��� 
				printf("�ӫ~��T:����%s\n",(item+j)->info);				//��ܤ�󤤩Ҧs�����ӫ~��T 
				
				free((item+j)->name);								//����Ŷ� 
				free((item+j)->money);								//����Ŷ� 
				free((item+j)->num);								//����Ŷ� 
				free((item+j)->seller);								//����Ŷ� 
				free((item+j)->date);								//����Ŷ� 
				free((item+j)->info);								//����Ŷ� 
			}
			break;
		case 3 :													//�ﶵ�T 
			temp = 0;												
			i = 0;
			j = 0;
			k = 0;
			FILE *fp4 = fopen("list.txt","r");						//�}�Ұӫ~�C����"list.txt"�÷ǳ�Ū��
		
			(item)->name=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->money=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->num=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->seller=malloc(sizeof(struct total)*500);		//�����Ŷ� 
			(item)->date=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			(item)->info=malloc(sizeof(struct total)*500);			//�����Ŷ� 
			
			fscanf(fp4,"%s ",(item+i)->name);						//���y���ñN�Ĥ@���g�J�ӫ~�W�ٰ}�C 
			
			while(strcmp((item+i)->name,"END")!=0)					//�P�_�Ĥ@���O�_������"END"�ð���j��
			{
				
				fscanf(fp4,"%s ",(item+i)->money);					// ���y���üg�J�ӫ~����}�C
				fscanf(fp4,"%s ",(item+i)->num);					// ���y���üg�J�ӫ~�ƶq�}�C
				fscanf(fp4,"%s ",(item+i)->seller);					// ���y���üg�J��a�}�C
				fscanf(fp4,"%s ",(item+i)->date);					// ���y���üg�J�W�[����}�C
				fscanf(fp4,"%s\n",(item+i)->info);					// ���y���üg�J�ӫ~��T�}�C
						
				i++;
				
				(item+i)->name=malloc(sizeof(struct total)*500);	//�����Ŷ� 
				(item+i)->money=malloc(sizeof(struct total)*500);	//�����Ŷ� 
				(item+i)->num=malloc(sizeof(struct total)*500);		//�����Ŷ� 
				(item+i)->seller=malloc(sizeof(struct total)*500);	//�����Ŷ� 
				(item+i)->date=malloc(sizeof(struct total)*500);	//�����Ŷ� 
				(item+i)->info=malloc(sizeof(struct total)*500);	//�����Ŷ� 
				
				fscanf(fp4,"%s",(item+i)->name);					// ���y���üg�J�ӫ~�W�ٰ}�C
			}
			
	
			printf("�п�J��a:");									//���"�п�J��a:" 
			scanf("%s" ,find_seller );								//��J��a��}�C
			printf("\n");
			for(j=0;j<i;j++)
			{
				if (strcmp((item+j)->seller,find_seller)==0)		//�P�_��J����a�P��󤤪���a�O�_�۵� 
				{
					printf("�ӫ~�W��:%s ",(item+j)->name);			//��ܤ�󤤦���a�Ҧs�����ӫ~�W��
					printf("�ӫ~����:%s ",(item+j)->money);			//��ܤ�󤤦���a�Ҧs�����ӫ~���� 
					printf("�ӫ~�ƶq:%s ",(item+j)->num);			//��ܤ�󤤦���a�Ҧs�����ӫ~�ƶq 
					printf("��a:%s ",(item+j)->seller);			//��ܤ�󤤦���a�Ҧs������a	 
					printf("�W�[���%s ",(item+j)->date);			//��ܤ�󤤦���a�Ҧs�����W�[��� 
					printf("�ӫ~��T:����%s\n",(item+j)->info);			//��ܤ�󤤦���Ҧs�����ӫ~��T 
					temp++;											//���ܪ��A 
				}
			
			}
			if (temp ==0)											//�P�_�ӫ~��󤤬O�_������a���ӫ~ 
			printf("\n����a���W�[����ӫ~\n");						//�p�G�S���h���"����a���W�[����ӫ~" 
			for(j=0 ; j<i ; j++)
			{
				free((item+j)->name);								//����Ŷ� 
				free((item+j)->money);								//����Ŷ� 
				free((item+j)->num);								//����Ŷ� 
				free((item+j)->seller);								//����Ŷ� 
				free((item+j)->date);								//����Ŷ� 
				free((item+j)->info);								//����Ŷ� 
			}
			fclose(fp4);											//�����ɮ� 
			break;
		case 4:														//�ﶵ�| 
			
			break;
			
			default:
				printf("�L���ﶵ�A�ЦA��ܤ@��!\n");
				break;
		}
		if (k == 4) 											//�P�_�ϥΪ̬O�_��ܿﶵ�| 
		break;													//�p�G�O�h���X�j�� 
	}
	free(item);	                                            //����Ŷ� 
	return 0;
}



