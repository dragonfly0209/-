#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  //�O�o�[
int buy()
{
    int i=0,j=0,k,o=0,l,choice=4,flag=0;  
	int total=0,a,randthings;
	srand(time(NULL));
	
	FILE *debug = fopen("list.txt","a");			//�������ɳQ�������� 
	fprintf(debug,"END\n");							//�N"END"�g�b�y���A�H�����{��Ū������"END "�Ӳ��Ͱ��D 
	fclose(debug);
	FILE *debug2 = fopen("shopping_cart.txt","a");
	fprintf(debug2,"END\n");
	fclose(debug2);
	
	struct total          //�ӫ~�C���ɮ׮榡 
	{
		char *name;       //�ӫ~�W�� 
		char *money;      //���� 
		char *num;        //�ƶq 
		char *seller;     //�c��H 
		char *date;       //�W�[�ɶ� 
		char *info;	      //�ӫ~��T 	
	}*item;
	item=malloc(sizeof(struct total)*1000);    //�����Ŷ�  
	
    (item)->name=malloc(sizeof(struct total)*500);       //�����Ŷ�     
	(item)->money=malloc(sizeof(struct total)*500);      //�����Ŷ�  
	(item)->num=malloc(sizeof(struct total)*500);        //�����Ŷ�  
	(item)->seller=malloc(sizeof(struct total)*500);     //�����Ŷ�  
	(item)->date=malloc(sizeof(struct total)*500);       //�����Ŷ�  
	(item)->info=malloc(sizeof(struct total)*500);       //�����Ŷ�  
	
	struct total2      //�ʪ������ɮ׮榡
	{
		char *name;    //�ӫ~�W��     
		char *money;   //���� 
		char *num;     //�ƶq 
		char *seller;  //�c��H
	}*item2;
	item2=malloc(sizeof(struct total2)*1000);    //�����Ŷ�  
	FILE *fp = fopen("list.txt","r");      			//�}�ӫ~�C��ǳ�Ū��
 	fscanf(fp,"%s",(item+i)->name);                 //���y�ӫ~�C���Ĥ@���x�s���ӫ~�W 
	while(strcmp((item+i)->name,"END")!=0)          //�Y�ӫ~�C���Ĥ@�椣��END,�h����H�U���ʧ@ 
	{
		fscanf(fp,"%s",(item+i)->money);            //���۱��y�ӫ~�C���x�s������ 
		fscanf(fp,"%s",(item+i)->num);				//���۱��y�ӫ~�C���x�s���ƶq 
		fscanf(fp,"%s",(item+i)->seller);			//���۱��y�ӫ~�C���x�s����a 
		fscanf(fp,"%s",(item+i)->date);				//���۱��y�ӫ~�C���x�s���c���� 
		fscanf(fp,"%s",(item+i)->info);				//���۱��y�ӫ~�C���x�s���ӫ~��T  
				
		i++;                                        //i�W�[1
		
	    (item+i)->name=malloc(sizeof(struct total)*500);			//�����Ŷ�
		(item+i)->money=malloc(sizeof(struct total)*500);			//�����Ŷ�
		(item+i)->num=malloc(sizeof(struct total)*500);				//�����Ŷ�
		(item+i)->seller=malloc(sizeof(struct total)*500);			//�����Ŷ�
		(item+i)->date=malloc(sizeof(struct total)*500);			//�����Ŷ�
		(item+i)->info=malloc(sizeof(struct total)*500);			//�����Ŷ�				
		fscanf(fp,"%s",(item+i)->name);								//���y�ӫ~�C���U�@���x�s���ӫ~�W
	}
	fclose(fp); 				//�����ӫ~�C���ɮ� 
	while(flag == 0){           //��flag=0��,������� 
    	switch(choice)
    	{
        	case 1:				//��choice=1�ɰ��� 
		
	    	for(k=0;k<i;k++)							//��ܰӫ~��T����S���ӫ~ 
	    	{
				printf("%s ",(item+k)->name);			//��ܰӫ~�W 
				printf("������%s ",(item+k)->money);	//��ܰӫ~�W
				printf("��%s�� ",(item+k)->num);		//��ܰӫ~�W
				printf("��a�O%s ",(item+k)->seller);	//��ܰӫ~�W
				printf("�W�[���:%s ",(item+k)->date);	//��ܰӫ~�W
				printf("����:%s\n",(item+k)->info);		//��ܰӫ~�W
        	}
			printf("\n�ЬD��z�n���ӫ~�O�ĴX��,�Y�L�Q�n���ӫ~�Ы�0���}\n");		 
    		scanf("%d",&k);		//��J�n���ʪ��ӫ~
    		printf("\n");
    		if(k == 0){choice = 4;break;}//��0�^���� 
    		printf("�z�D�諸�ӫ~����%d��:%s\n��1��J�ʪ���\n��2��^\n��3�T�{�ʪ���\n�z����ܬO:",k,(item+k-1)->name);
    		scanf("%d",&j);		//��J��� 
			printf("\n");
    		if(j == 1)			//���1�ɰ���	
			{
				a = atoi ( (item+k-1)->num );		//�N�ƶq���r��אּ��� 
    		    a--;								//�ƶq-1 
    		    sprintf((item+k-1)->num , "%d", a); //�N�ƶq����Ƨאּ�r�� 
    		    
				FILE *fp3 = fopen("list.txt","w");      	//�}�ӫ~�C��ǳƼg�J 
				for(l=0;l<=i;l++)
				{
					fprintf(fp3,"%s ",(item+l)->name);		//�N�ӫ~�W�g�J�ӫ~�C��
					fprintf(fp3,"%s ",(item+l)->money);		//�N�����g�J�ӫ~�C��
					fprintf(fp3,"%s ",(item+l)->num);		//�N�ƶq�g�J�ӫ~�C��
					fprintf(fp3,"%s ",(item+l)->seller);	//�N��a�g�J�ӫ~�C�� 
					fprintf(fp3,"%s ",(item+l)->date);		//�N�c�����g�J�ӫ~�C��
					fprintf(fp3,"%s\n",(item+l)->info);		//�N�ӫ~��T�g�J�ӫ~�C��
				}
				fclose(fp3);								//�����ӫ~�C��
				
				FILE *fp1 = fopen("shopping_cart.txt","r");      		//�}�ӫ~�C��ǳƼg�J
				o=0;
				(item2)->name=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				(item2)->money=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				(item2)->seller=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				fscanf(fp1,"%s",(item2)->name);							//���y�ʪ������Ĥ@���x�s���ӫ~�W
				while(strcmp((item2+o)->name,"END")!=0)					//�Y�ʪ������Ĥ@�椣��END,�h����H�U���ʧ@
				{
					fscanf(fp1,"%s",(item2+o)->money);					//���۱��y�ӫ~�C���x�s������ 
					fscanf(fp1,"%s",(item2+o)->seller);					//���۱��y�ӫ~�C���x�s����a
					o++;
				    (item2+o)->name=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				    (item2+o)->money=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				    (item2+o)->seller=malloc(sizeof(struct total2)*500);	//�����Ŷ�
					fscanf(fp1,"%s",(item2+o)->name);					//���y�ʪ������U�@���x�s���ӫ~�W
				}
				fclose(fp1);					//�����ʪ���
				FILE *fp2 = fopen("shopping_cart.txt","w");		//�}���ʪ����ǳƼg�J 
				fprintf(fp2,"%s ",(item+k-1)->name);			//�N�o���n�R���ӫ~�W�g�J�ʪ��� 
				fprintf(fp2,"%s ",(item+k-1)->money);			//�N�o���n�R���ӫ~���B�g�J�ʪ���
				fprintf(fp2,"%s\n",(item+k-1)->seller);			//�N�o���n�R���ӫ~��a�g�J�ʪ���
				for(l=0;l<=o;l++)
				{
					fprintf(fp2,"%s ",(item2+l)->name);			//�N�ӫ~�W�g�J�ʪ���
					fprintf(fp2,"%s ",(item2+l)->money);		//�N�����g�J�ʪ���
					fprintf(fp2,"%s\n",(item2+l)->seller);		//�N��a�g�J�ʪ��� 
				}
				
				fclose(fp2);				//�����ʪ���
				printf("�w�[�J�ʪ���\n\n"); 
				break;
			}
			else if(j == 2){break;}		    //���2�^��C�� 
			else if(j == 3){      }			//���3���U 
	
    	case 2:								//��choice=2�ɰ���
    		printf("�ثe�b�ʪ��������ӫ~��\n");
    		FILE *fp1 = fopen("shopping_cart.txt","r");			//�}���ʪ����ǳ�Ū�� 
    		(item2)->name=malloc(sizeof(struct total2)*500);	//�����Ŷ� 
    		(item2)->money=malloc(sizeof(struct total2)*500);	//�����Ŷ� 
    		(item2)->seller=malloc(sizeof(struct total2)*500);	//�����Ŷ� 
	    	fscanf(fp1,"%s",(item2)->name);			//���y�ʪ������Ĥ@���x�s���ӫ~�W
	    	o=0; 
			while(strcmp((item2+o)->name,"END")!=0)		//�Y�ʪ������Ĥ@�椣��END,�h����H�U���ʧ@
			{
				fscanf(fp1,"%s",(item2+o)->money);				//���y�ʪ����x�s������ 
				fscanf(fp1,"%s",(item2+o)->seller);				//���y�ʪ����x�s����a 
				o++;				//o�W�[1 
				(item2+o)->name=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				(item2+o)->money=malloc(sizeof(struct total2)*500);		//�����Ŷ�
				(item2+o)->seller=malloc(sizeof(struct total2)*500);	//�����Ŷ�
			    fscanf(fp1,"%s",(item2+o)->name);		//���y�ʪ������U�@���x�s���ӫ~�W
			}
			fclose(fp1);				//�����ʪ���
    		for(k=0;k<o;k++)
	    	{
				printf("%s ",(item2+k)->name);
				printf("������%s ",(item2+k)->money);
				printf("��a:%s\n",(item2+k)->seller);
        	}
        	total = 0;					//�ttotal=0 
        	for(k=0;k<o;k++)
        	{
        		a = atoi ( (item2+k)->money ); // �N�������r������
        		total = a + total;				//�N�ӫ~�������@�@�ۥ[ 
			}
			printf("�`������%d",total);
        	printf("\n��1�ʶR\n��2�����Ҧ��ʪ���\n�z����ܬO:");
        	scanf("%d",&l);
        	if(total==0)						//�Ytotal=0��,��� �L���ʰӫ~! �æ^���� 
        	{
        		printf("\n�L���ʰӫ~!\n\n");
        		choice = 4;
        		break;
			}
        	if(l==1)					//�Y���1��,���� 
			{
				FILE *fp2 = fopen("shopping_cart.txt","w");			//�}���ʪ����ǳƼg�J	
				fprintf(fp2,"END\n");								//�NEND�g�J�ʪ��� 
				fclose(fp2);										//�����ʪ���
				printf("\n�ʶR����!\n\n");
				randthings=(rand()%i)-3; //�o�䪺i���`�ӫ~�ƶq
				printf("������˰ӫ~\n");
	    	    for(j=0;j<3;j++) //�L�X����ӫ~ 
				{
				printf("�W��:%s  ",(item+randthings+j)->name); //�L�X�ӫ~�W��
				printf("����:%s\n",(item+randthings+j)->money); //�L�X�ӫ~���� 
				}
				printf("\n");
			}
			else if(l==2)				//�Y���2��,����
			{
			  FILE *fp2 = fopen("shopping_cart.txt","w");		//�}���ʪ����ǳƼg�J
			  fprintf(fp2,"END\n");								//�NEND�g�J�ʪ���
			  fclose(fp2);										//�����ʪ���
			  printf("\n�w�g�����Ҧ��ʪ���\n\n");	
			}
			choice = 4;
    	break;
    
    	case 3:					//��choice=3�ɰ���
    		flag=1; 			//�Nflag�אּ1�H�h�Xwhile 
    	break;
    
    	case 4:					//��choice=4�ɰ���
    		printf("\n�w��Ө��ʪ��t��\n1:��ܰӫ~�C��\n2:�T�{�ʪ���\n3:���}�ʪ��t��\n�z����ܬ�");
    		scanf("%d",&choice);
    		printf("\n");
    	break;   
		default:									//���J��L�F��ɰ���
    		printf("�L���ﶵ\n\n");
    		choice = 4;								//�Nchoice�אּ4�w�^���� 
    	break;    	
    	}
 
	}
	for(j=0;j<i;j++)
	{
		free((item+j)->name);		//����Ŷ�
		free((item+j)->money);		//����Ŷ�
		free((item+j)->num);		//����Ŷ�
		free((item+j)->seller);		//����Ŷ�
		free((item+j)->date);		//����Ŷ�
		free((item+j)->info);		//����Ŷ�
	}
		for(j=0;j<o;j++)
	{
		free((item2+j)->name);		//����Ŷ�
		free((item2+j)->money);		//����Ŷ�
		free((item2+j)->num);		//����Ŷ�
		free((item2+j)->seller);	//����Ŷ�
	}
    free(item);						//����Ŷ� 
    free(item2);					//����Ŷ�
    return 0;
}
