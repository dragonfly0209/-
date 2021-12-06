#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  //記得加
int buy()
{
    int i=0,j=0,k,o=0,l,choice=4,flag=0;  
	int total=0,a,randthings;
	srand(time(NULL));
	
	FILE *debug = fopen("list.txt","a");			//防止文件檔被全部消除 
	fprintf(debug,"END\n");							//將"END"寫在句尾，以防止之後程式讀取不到"END "而產生問題 
	fclose(debug);
	FILE *debug2 = fopen("shopping_cart.txt","a");
	fprintf(debug2,"END\n");
	fclose(debug2);
	
	struct total          //商品列表的檔案格式 
	{
		char *name;       //商品名稱 
		char *money;      //價錢 
		char *num;        //數量 
		char *seller;     //販賣人 
		char *date;       //上架時間 
		char *info;	      //商品資訊 	
	}*item;
	item=malloc(sizeof(struct total)*1000);    //給予空間  
	
    (item)->name=malloc(sizeof(struct total)*500);       //給予空間     
	(item)->money=malloc(sizeof(struct total)*500);      //給予空間  
	(item)->num=malloc(sizeof(struct total)*500);        //給予空間  
	(item)->seller=malloc(sizeof(struct total)*500);     //給予空間  
	(item)->date=malloc(sizeof(struct total)*500);       //給予空間  
	(item)->info=malloc(sizeof(struct total)*500);       //給予空間  
	
	struct total2      //購物車的檔案格式
	{
		char *name;    //商品名稱     
		char *money;   //價錢 
		char *num;     //數量 
		char *seller;  //販賣人
	}*item2;
	item2=malloc(sizeof(struct total2)*1000);    //給予空間  
	FILE *fp = fopen("list.txt","r");      			//開商品列表準備讀取
 	fscanf(fp,"%s",(item+i)->name);                 //掃描商品列表的第一行儲存為商品名 
	while(strcmp((item+i)->name,"END")!=0)          //若商品列表的第一行不為END,則執行以下的動作 
	{
		fscanf(fp,"%s",(item+i)->money);            //接著掃描商品列表儲存為價錢 
		fscanf(fp,"%s",(item+i)->num);				//接著掃描商品列表儲存為數量 
		fscanf(fp,"%s",(item+i)->seller);			//接著掃描商品列表儲存為賣家 
		fscanf(fp,"%s",(item+i)->date);				//接著掃描商品列表儲存為販售日期 
		fscanf(fp,"%s",(item+i)->info);				//接著掃描商品列表儲存為商品資訊  
				
		i++;                                        //i增加1
		
	    (item+i)->name=malloc(sizeof(struct total)*500);			//給予空間
		(item+i)->money=malloc(sizeof(struct total)*500);			//給予空間
		(item+i)->num=malloc(sizeof(struct total)*500);				//給予空間
		(item+i)->seller=malloc(sizeof(struct total)*500);			//給予空間
		(item+i)->date=malloc(sizeof(struct total)*500);			//給予空間
		(item+i)->info=malloc(sizeof(struct total)*500);			//給予空間				
		fscanf(fp,"%s",(item+i)->name);								//掃描商品列表的下一行儲存為商品名
	}
	fclose(fp); 				//關閉商品列表檔案 
	while(flag == 0){           //當flag=0時,持續執行 
    	switch(choice)
    	{
        	case 1:				//當choice=1時執行 
		
	    	for(k=0;k<i;k++)							//顯示商品資訊直到沒有商品 
	    	{
				printf("%s ",(item+k)->name);			//顯示商品名 
				printf("價錢為%s ",(item+k)->money);	//顯示商品名
				printf("剩%s個 ",(item+k)->num);		//顯示商品名
				printf("賣家是%s ",(item+k)->seller);	//顯示商品名
				printf("上架日期:%s ",(item+k)->date);	//顯示商品名
				printf("評價:%s\n",(item+k)->info);		//顯示商品名
        	}
			printf("\n請挑選您要的商品是第幾個,若無想要的商品請按0離開\n");		 
    		scanf("%d",&k);		//輸入要選購的商品
    		printf("\n");
    		if(k == 0){choice = 4;break;}//選0回到選單 
    		printf("您挑選的商品為第%d件:%s\n按1放入購物車\n按2返回\n按3確認購物車\n您的選擇是:",k,(item+k-1)->name);
    		scanf("%d",&j);		//輸入選擇 
			printf("\n");
    		if(j == 1)			//選擇1時執行	
			{
				a = atoi ( (item+k-1)->num );		//將數量的字串改為整數 
    		    a--;								//數量-1 
    		    sprintf((item+k-1)->num , "%d", a); //將數量的整數改為字串 
    		    
				FILE *fp3 = fopen("list.txt","w");      	//開商品列表準備寫入 
				for(l=0;l<=i;l++)
				{
					fprintf(fp3,"%s ",(item+l)->name);		//將商品名寫入商品列表
					fprintf(fp3,"%s ",(item+l)->money);		//將價錢寫入商品列表
					fprintf(fp3,"%s ",(item+l)->num);		//將數量寫入商品列表
					fprintf(fp3,"%s ",(item+l)->seller);	//將賣家寫入商品列表 
					fprintf(fp3,"%s ",(item+l)->date);		//將販賣日期寫入商品列表
					fprintf(fp3,"%s\n",(item+l)->info);		//將商品資訊寫入商品列表
				}
				fclose(fp3);								//關閉商品列表
				
				FILE *fp1 = fopen("shopping_cart.txt","r");      		//開商品列表準備寫入
				o=0;
				(item2)->name=malloc(sizeof(struct total2)*500);		//給予空間
				(item2)->money=malloc(sizeof(struct total2)*500);		//給予空間
				(item2)->seller=malloc(sizeof(struct total2)*500);		//給予空間
				fscanf(fp1,"%s",(item2)->name);							//掃描購物車的第一行儲存為商品名
				while(strcmp((item2+o)->name,"END")!=0)					//若購物車的第一行不為END,則執行以下的動作
				{
					fscanf(fp1,"%s",(item2+o)->money);					//接著掃描商品列表儲存為價錢 
					fscanf(fp1,"%s",(item2+o)->seller);					//接著掃描商品列表儲存為賣家
					o++;
				    (item2+o)->name=malloc(sizeof(struct total2)*500);		//給予空間
				    (item2+o)->money=malloc(sizeof(struct total2)*500);		//給予空間
				    (item2+o)->seller=malloc(sizeof(struct total2)*500);	//給予空間
					fscanf(fp1,"%s",(item2+o)->name);					//掃描購物車的下一行儲存為商品名
				}
				fclose(fp1);					//關閉購物車
				FILE *fp2 = fopen("shopping_cart.txt","w");		//開啟購物車準備寫入 
				fprintf(fp2,"%s ",(item+k-1)->name);			//將這次要買的商品名寫入購物車 
				fprintf(fp2,"%s ",(item+k-1)->money);			//將這次要買的商品金額寫入購物車
				fprintf(fp2,"%s\n",(item+k-1)->seller);			//將這次要買的商品賣家寫入購物車
				for(l=0;l<=o;l++)
				{
					fprintf(fp2,"%s ",(item2+l)->name);			//將商品名寫入購物車
					fprintf(fp2,"%s ",(item2+l)->money);		//將價錢寫入購物車
					fprintf(fp2,"%s\n",(item2+l)->seller);		//將賣家寫入購物車 
				}
				
				fclose(fp2);				//關閉購物車
				printf("已加入購物車\n\n"); 
				break;
			}
			else if(j == 2){break;}		    //選擇2回到列表 
			else if(j == 3){      }			//選擇3往下 
	
    	case 2:								//當choice=2時執行
    		printf("目前在購物車內的商品有\n");
    		FILE *fp1 = fopen("shopping_cart.txt","r");			//開啟購物車準備讀取 
    		(item2)->name=malloc(sizeof(struct total2)*500);	//給予空間 
    		(item2)->money=malloc(sizeof(struct total2)*500);	//給予空間 
    		(item2)->seller=malloc(sizeof(struct total2)*500);	//給予空間 
	    	fscanf(fp1,"%s",(item2)->name);			//掃描購物車的第一行儲存為商品名
	    	o=0; 
			while(strcmp((item2+o)->name,"END")!=0)		//若購物車的第一行不為END,則執行以下的動作
			{
				fscanf(fp1,"%s",(item2+o)->money);				//掃描購物車儲存為價錢 
				fscanf(fp1,"%s",(item2+o)->seller);				//掃描購物車儲存為賣家 
				o++;				//o增加1 
				(item2+o)->name=malloc(sizeof(struct total2)*500);		//給予空間
				(item2+o)->money=malloc(sizeof(struct total2)*500);		//給予空間
				(item2+o)->seller=malloc(sizeof(struct total2)*500);	//給予空間
			    fscanf(fp1,"%s",(item2+o)->name);		//掃描購物車的下一行儲存為商品名
			}
			fclose(fp1);				//關閉購物車
    		for(k=0;k<o;k++)
	    	{
				printf("%s ",(item2+k)->name);
				printf("價錢為%s ",(item2+k)->money);
				printf("賣家:%s\n",(item2+k)->seller);
        	}
        	total = 0;					//另total=0 
        	for(k=0;k<o;k++)
        	{
        		a = atoi ( (item2+k)->money ); // 將價錢的字串轉整數
        		total = a + total;				//將商品的價錢一一相加 
			}
			printf("總價錢為%d",total);
        	printf("\n按1購買\n按2取消所有購物車\n您的選擇是:");
        	scanf("%d",&l);
        	if(total==0)						//若total=0時,顯示 無選購商品! 並回到表單 
        	{
        		printf("\n無選購商品!\n\n");
        		choice = 4;
        		break;
			}
        	if(l==1)					//若選擇1時,執行 
			{
				FILE *fp2 = fopen("shopping_cart.txt","w");			//開啟購物車準備寫入	
				fprintf(fp2,"END\n");								//將END寫入購物車 
				fclose(fp2);										//關閉購物車
				printf("\n購買完成!\n\n");
				randthings=(rand()%i)-3; //這邊的i指總商品數量
				printf("本日推薦商品\n");
	    	    for(j=0;j<3;j++) //印出五件商品 
				{
				printf("名稱:%s  ",(item+randthings+j)->name); //印出商品名稱
				printf("價格:%s\n",(item+randthings+j)->money); //印出商品價錢 
				}
				printf("\n");
			}
			else if(l==2)				//若選擇2時,執行
			{
			  FILE *fp2 = fopen("shopping_cart.txt","w");		//開啟購物車準備寫入
			  fprintf(fp2,"END\n");								//將END寫入購物車
			  fclose(fp2);										//關閉購物車
			  printf("\n已經取消所有購物車\n\n");	
			}
			choice = 4;
    	break;
    
    	case 3:					//當choice=3時執行
    		flag=1; 			//將flag改為1以退出while 
    	break;
    
    	case 4:					//當choice=4時執行
    		printf("\n歡迎來到購物系統\n1:顯示商品列表\n2:確認購物車\n3:離開購物系統\n您的選擇為");
    		scanf("%d",&choice);
    		printf("\n");
    	break;   
		default:									//當輸入其他東西時執行
    		printf("無此選項\n\n");
    		choice = 4;								//將choice改為4已回到表單 
    	break;    	
    	}
 
	}
	for(j=0;j<i;j++)
	{
		free((item+j)->name);		//釋放空間
		free((item+j)->money);		//釋放空間
		free((item+j)->num);		//釋放空間
		free((item+j)->seller);		//釋放空間
		free((item+j)->date);		//釋放空間
		free((item+j)->info);		//釋放空間
	}
		for(j=0;j<o;j++)
	{
		free((item2+j)->name);		//釋放空間
		free((item2+j)->money);		//釋放空間
		free((item2+j)->num);		//釋放空間
		free((item2+j)->seller);	//釋放空間
	}
    free(item);						//釋放空間 
    free(item2);					//釋放空間
    return 0;
}
