#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int sell(char *user)
{
	int i = 0 , j  , k ,temp;
	char find_seller[500];
	FILE *debug = fopen("list.txt","a");			//防止文件檔被全部消除 
	fprintf(debug,"END\n");							//將"END"寫在句尾，以防止之後程式讀取不到"END "而產生問題 
	fclose(debug);
	struct total			//商品列表的檔案格式
	{
		char *name;			//商品名稱
		char *money;		//商品價格 
		char *num;			//商品數量 
		char *seller;		//賣家 
		char *date;			//上架日期 
		char *info;			//商品資訊 
	}*item;
	item=malloc(sizeof(struct total)*1000); 		//給予空間 
	while(1)
	{

		printf(" \n選項一:賣家上架\n選項二:商品列表\n選項三:找尋賣家商品\n選項四:離開\n請輸入您的選項:");		//表單 
		scanf("%d" , &k);																						//輸入表單選項 
		printf("\n");
		switch(k)
		{		
	
		case 1:													//選項一							
			i = 0;
			j = 0;	
			
			(item)->name=malloc(sizeof(struct total)*500);		//給予空間	 
			(item)->money=malloc(sizeof(struct total)*500);		//給予空間
			(item)->num=malloc(sizeof(struct total)*500);		//給予空間
			(item)->seller=malloc(sizeof(struct total)*500);	//給予空間
			(item)->date=malloc(sizeof(struct total)*500);		//給予空間
			(item)->info=malloc(sizeof(struct total)*500);		//給予空間
			
			FILE *fp2 = fopen("list.txt","r");					//開啟商品列表文件"list.txt"並準備讀取 
			fscanf(fp2,"%s",(item+i)->name);					//掃描文件並將第一項寫入商品名稱陣列 
			
			while(strcmp((item+i)->name,"END")!=0)				//判斷第一項是否不等於"END"並執行迴圈 
			{
			
				fscanf(fp2,"%s ",(item+i)->money);              // 掃描文件並寫入商品價格陣列 
				fscanf(fp2,"%s ",(item+i)->num);				// 掃描文件並寫入商品數量陣列
				fscanf(fp2,"%s ",(item+i)->seller);				// 掃描文件並寫入賣家陣列
				fscanf(fp2,"%s ",(item+i)->date);				// 掃描文件並寫入上架日期陣列
				fscanf(fp2,"%s\n",(item+i)->info);				// 掃描文件並寫入商品資訊陣列
					
				i++;
				
				(item+i)->name=malloc(sizeof(struct total)*500); 	// 給予空間
				(item+i)->money=malloc(sizeof(struct total)*500);	// 給予空間
				(item+i)->num=malloc(sizeof(struct total)*500); 	// 給予空間
				(item+i)->seller=malloc(sizeof(struct total)*500);	// 給予空間
				(item+i)->date=malloc(sizeof(struct total)*500);	// 給予空間
				(item+i)->info=malloc(sizeof(struct total)*500);	// 給予空間
			
				fscanf(fp2,"%s",(item+i)->name);					// 掃描文件並寫入商品名稱陣列 
			}
		
			fclose(fp2);                                    		//關閉檔案 
		
	
	
			FILE *fp1 = fopen("list.txt","w");						//開啟商品列表文件"list.txt"並準備寫入 

			printf("請輸入商品名稱:"); 								//顯示"請輸入商品名稱:" 
			scanf("%s",(item+i)->name);								//輸入商品名稱到陣列 
			printf("請輸入商品價格:");								//顯示"請輸入商品價格:"
			scanf("%s",(item+i)->money);							//輸入商品價格到陣列 
			printf("請輸入商品數量:");								//顯示"請輸入商品數量:"
			scanf("%s",(item+i)->num);								//輸入商品數量到陣列 
			strcpy((item+i)->seller,user);							//將帳號名稱複製到陣列 
			printf("請輸入上架日期:");								//顯示"請輸入上架日期:"
			scanf("%s",(item+i)->date);								//輸入上架日期到陣列 
			printf("請輸入商品資訊:");								//顯示"請輸入商品資訊:"
			scanf("%s",(item+i)->info);								//輸入商品資訊到陣列 
			
			for(j=0;j<=i;j++)
			{
				fprintf(fp1,"%s ",(item+j)->name);					//將商品名稱陣列中的字串輸入到商品列表文件"list.txt" 
				fprintf(fp1,"%s ",(item+j)->money);					//將商品價格陣列中的字串輸入到商品列表文件"list.txt" 
				fprintf(fp1,"%s ",(item+j)->num);					//將商品數量陣列中的字串輸入到商品列表文件"list.txt" 
				fprintf(fp1,"%s ",(item+j)->seller);				//將賣家陣列中的字串輸入到商品列表文件"list.txt" 
				fprintf(fp1,"%s ",(item+j)->date);					//將上架日期陣列中的字串輸入到商品列表文件"list.txt" 
				fprintf(fp1,"%s\n",(item+j)->info);					//將商品資訊陣列中的字串輸入到商品列表文件"list.txt" 
				
				free((item+j)->name);								//釋放空間 
				free((item+j)->money);								//釋放空間
				free((item+j)->num);								//釋放空間
				free((item+j)->seller);								//釋放空間
				free((item+j)->date);								//釋放空間 
				free((item+j)->info);								//釋放空間 
			}
			fprintf(fp1,"END\n");									//寫入END到文件中最後一行 
			printf("\n上架囉!\n");									//顯示"上架囉!"
			fclose(fp1);											//關閉文件 
			break;
	
		case 2 :													//選項二 
			i = 0;
			j = 0;
			FILE *fp3 = fopen("list.txt","r");						//開啟商品列表文件"list.txt"並準備讀取 

			(item)->name=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->money=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->num=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->seller=malloc(sizeof(struct total)*500);		//給予空間 
			(item)->date=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->info=malloc(sizeof(struct total)*500);			//給予空間 
			
			fscanf(fp3,"%s ",(item+i)->name);						//掃描文件並將第一項寫入商品名稱陣列
			
			while(strcmp((item+i)->name,"END")!=0)					//判斷第一項是否不等於"END"並執行迴圈
			{
				
				fscanf(fp3,"%s ",(item+i)->money);					// 掃描文件並寫入商品價格陣列 
				fscanf(fp3,"%s ",(item+i)->num);					// 掃描文件並寫入商品數量陣列
				fscanf(fp3,"%s ",(item+i)->seller);					// 掃描文件並寫入賣家陣列
				fscanf(fp3,"%s ",(item+i)->date);					// 掃描文件並寫入上架日期陣列
				fscanf(fp3,"%s\n",(item+i)->info);					// 掃描文件並寫入商品資訊陣列
						
				i++;
				
				(item+i)->name=malloc(sizeof(struct total)*500);	//給予空間 
				(item+i)->money=malloc(sizeof(struct total)*500);	//給予空間
				(item+i)->num=malloc(sizeof(struct total)*500);		//給予空間
				(item+i)->seller=malloc(sizeof(struct total)*500);	//給予空間
				(item+i)->date=malloc(sizeof(struct total)*500);	//給予空間
				(item+i)->info=malloc(sizeof(struct total)*500);	//給予空間
				
				fscanf(fp3,"%s",(item+i)->name);					// 掃描文件並寫入商品名稱陣列 
			}
			
			fclose(fp3);											//關閉文件 

			for(j=0;j<i;j++)
			{
				printf("商品名稱:%s ",(item+j)->name);				//顯示文件中所存取的商品名稱 
				printf("商品價格:%s ",(item+j)->money);				//顯示文件中所存取的商品價格 
				printf("商品數量:%s ",(item+j)->num);				//顯示文件中所存取的商品數量 
				printf("賣家:%s ",(item+j)->seller);				//顯示文件中所存取的賣家 
				printf("上架日期%s ",(item+j)->date);				//顯示文件中所存取的上架日期 
				printf("商品資訊:評價%s\n",(item+j)->info);				//顯示文件中所存取的商品資訊 
				
				free((item+j)->name);								//釋放空間 
				free((item+j)->money);								//釋放空間 
				free((item+j)->num);								//釋放空間 
				free((item+j)->seller);								//釋放空間 
				free((item+j)->date);								//釋放空間 
				free((item+j)->info);								//釋放空間 
			}
			break;
		case 3 :													//選項三 
			temp = 0;												
			i = 0;
			j = 0;
			k = 0;
			FILE *fp4 = fopen("list.txt","r");						//開啟商品列表文件"list.txt"並準備讀取
		
			(item)->name=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->money=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->num=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->seller=malloc(sizeof(struct total)*500);		//給予空間 
			(item)->date=malloc(sizeof(struct total)*500);			//給予空間 
			(item)->info=malloc(sizeof(struct total)*500);			//給予空間 
			
			fscanf(fp4,"%s ",(item+i)->name);						//掃描文件並將第一項寫入商品名稱陣列 
			
			while(strcmp((item+i)->name,"END")!=0)					//判斷第一項是否不等於"END"並執行迴圈
			{
				
				fscanf(fp4,"%s ",(item+i)->money);					// 掃描文件並寫入商品價格陣列
				fscanf(fp4,"%s ",(item+i)->num);					// 掃描文件並寫入商品數量陣列
				fscanf(fp4,"%s ",(item+i)->seller);					// 掃描文件並寫入賣家陣列
				fscanf(fp4,"%s ",(item+i)->date);					// 掃描文件並寫入上架日期陣列
				fscanf(fp4,"%s\n",(item+i)->info);					// 掃描文件並寫入商品資訊陣列
						
				i++;
				
				(item+i)->name=malloc(sizeof(struct total)*500);	//給予空間 
				(item+i)->money=malloc(sizeof(struct total)*500);	//給予空間 
				(item+i)->num=malloc(sizeof(struct total)*500);		//給予空間 
				(item+i)->seller=malloc(sizeof(struct total)*500);	//給予空間 
				(item+i)->date=malloc(sizeof(struct total)*500);	//給予空間 
				(item+i)->info=malloc(sizeof(struct total)*500);	//給予空間 
				
				fscanf(fp4,"%s",(item+i)->name);					// 掃描文件並寫入商品名稱陣列
			}
			
	
			printf("請輸入賣家:");									//顯示"請輸入賣家:" 
			scanf("%s" ,find_seller );								//輸入賣家到陣列
			printf("\n");
			for(j=0;j<i;j++)
			{
				if (strcmp((item+j)->seller,find_seller)==0)		//判斷輸入的賣家與文件中的賣家是否相等 
				{
					printf("商品名稱:%s ",(item+j)->name);			//顯示文件中此賣家所存取的商品名稱
					printf("商品價格:%s ",(item+j)->money);			//顯示文件中此賣家所存取的商品價格 
					printf("商品數量:%s ",(item+j)->num);			//顯示文件中此賣家所存取的商品數量 
					printf("賣家:%s ",(item+j)->seller);			//顯示文件中此賣家所存取的賣家	 
					printf("上架日期%s ",(item+j)->date);			//顯示文件中此賣家所存取的上架日期 
					printf("商品資訊:評價%s\n",(item+j)->info);			//顯示文件中此賣所存取的商品資訊 
					temp++;											//改變狀態 
				}
			
			}
			if (temp ==0)											//判斷商品文件中是否有此賣家的商品 
			printf("\n此賣家未上架任何商品\n");						//如果沒有則顯示"此賣家未上架任何商品" 
			for(j=0 ; j<i ; j++)
			{
				free((item+j)->name);								//釋放空間 
				free((item+j)->money);								//釋放空間 
				free((item+j)->num);								//釋放空間 
				free((item+j)->seller);								//釋放空間 
				free((item+j)->date);								//釋放空間 
				free((item+j)->info);								//釋放空間 
			}
			fclose(fp4);											//關閉檔案 
			break;
		case 4:														//選項四 
			
			break;
			
			default:
				printf("無此選項，請再選擇一次!\n");
				break;
		}
		if (k == 4) 											//判斷使用者是否選擇選項四 
		break;													//如果是則跳出迴圈 
	}
	free(item);	                                            //釋放空間 
	return 0;
}



