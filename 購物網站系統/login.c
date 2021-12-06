#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void SetCode(char *code); 
int login(char *user)
{
	int i=0,j,k,flag_acc=0,flag_code=0,choice=0,logfail=0; //宣告變數 
	// 宣告暫存使用者輸入的帳號及密碼  
    char a1[21]="";
    char a2[21]="";
    char a3[21]="";
    FILE *debug = fopen("account.txt","a");			//防止文件檔被全部消除 
	fprintf(debug,"END\n");							//將"END"寫在句尾，以防止之後程式讀取不到"END "而產生問題 
	fclose(debug);
	struct tatal          
	{
		char *acc;       // 帳號 
		char *code;      // 密碼 
	
	}*item;
	item=malloc(sizeof(struct tatal)*500);    //給予空間  
	printf("如要登入請按1，註冊請按2 :");     // 讓使用者輸入 
	scanf("%d",&choice); //掃入變數 choice
	switch(choice)	//看choice為何數，對應的case將被執行
	{
		case 1:  //choice=1的情況執行下述 
			logfail=0;
			flag_acc=0;
			flag_code=0;
			i=0;
			(item)->acc=malloc(sizeof(struct tatal)*500);       //給予空間  
			(item)->code=malloc(sizeof(struct tatal)*500);       //給予空間
			FILE *fp = fopen("account.txt","r");      			
		 	fscanf(fp,"%s",(item+i)->acc);                  
			while(strcmp((item+i)->acc,"END")!=0)          //若列表的第一行不為END,則執行以下的動作 
			{
				fscanf(fp,"%s",(item+i)->code);	
			
				i++;                                        //i增加1											
				(item+i)->acc=malloc(sizeof(struct tatal)*500);       //給予空間  
				(item+i)->code=malloc(sizeof(struct tatal)*500);       //給予空間
				
				fscanf(fp,"%s",(item+i)->acc);
			}
			fclose(fp);	   
		     
		    printf("請輸入帳號： "); // 讓使用者輸入 
		    scanf("%s", a1);//掃入變數 a1

			for(j=0;j<i;j++)
		    {
		        if (!strcmp(a1, (item+j)->acc)) 
				{	
					flag_acc++;	        	
			        printf("請輸入密碼： "); // 讓使用者輸入 
			        SetCode(a2); 
					logfail=0;
					while(logfail<2&&flag_code==0)
					{										                
				        if (!strcmp(a2, (item+j)->code)) //如果密碼輸入一致時 
						{				  
				            printf("\n\n哈囉， %s ， 歡迎進入購物商城店...\n\n", (item+j)->acc);//密碼一樣就進入程式 
				           	flag_code++;
				       	}	
				       	else //如果密碼不一致時 
				       	{
				       		printf("\n密碼錯誤，請再次輸入密碼:");// 讓使用者重新輸入密碼 
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
			
			if(flag_acc==0)//如果帳號不存在時 
			{
				printf("查無此帳號");//顯示無此帳號 
				return 4;
			}
			if(logfail>=2)//如果輸入密碼超過3次 
			{
				printf("\n登入失敗過多次，請稍後在試"); //密碼輸入3次以後都失敗，顯示登入失敗過多次，請稍後在試
				return 4;
			}		    			
			
			
			if(flag_acc==1&&flag_code==1)
		    {
		    	strcpy(user,a1);
				return 1;
			}
			
		
		case 2 : //choice=2的情況執行下述
			logfail=0;
			flag_acc=0;
			flag_code=0;
			i=0;
			(item)->acc=malloc(sizeof(struct tatal)*500);       //給予空間  
			(item)->code=malloc(sizeof(struct tatal)*500);       //給予空間
			FILE *fp1 = fopen("account.txt","r");      			
		 	fscanf(fp1,"%s",(item+i)->acc);                  
			while(strcmp((item+i)->acc,"END")!=0)          //若列表的第一行不為END,則執行以下的動作 
			{
				fscanf(fp1,"%s",(item+i)->code);	
			
				i++;                                        //i增加1											
				(item+i)->acc=malloc(sizeof(struct tatal)*500);       //給予空間  
				(item+i)->code=malloc(sizeof(struct tatal)*500);       //給予空間
				
				fscanf(fp1,"%s",(item+i)->acc);
			}
			fclose(fp1);
		    
		    printf("請輸入新帳號： ");// 讓使用者輸入
		    scanf("%s", a1); //掃入變數 a1
			for(j=0;j<i;j++)
		    {
		        if (!strcmp(a1, (item+j)->acc)) //如果帳號已擁有 
				{				
					printf("此帳號已被使用過\n");//顯示此帳號已被使用過
					flag_acc++;
		        }			        
			}
			if(flag_acc==0)//如果帳號未被註冊 
			{
				printf("請輸入新密碼： ");// 讓使用者輸入 
			    SetCode(a2); 
			    printf("\n請再次輸入新密碼： ");//再次讓使用者輸入 
			    SetCode(a3);
			    if (strcmp(a2,a3)) //如果2次密碼輸入不一致 
				{				
					printf("\n密碼比對錯誤\n");// 顯示密碼比對錯誤
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
				printf("\n註冊成功\\n\n"); //顯示註冊成功   
				
			}
			
			for(j=0;j<=i;j++)
			{
				free((item+j)->acc);
				free((item+j)->code);
			}
			free(item);	
			return 2;
		default:
			printf("請重新輸入\n");
			return 2;
		
		
	}
	
    free(item);
      
}  
void SetCode(char *code)
{ 
	int n = 0; 
	
	while(n < 20)
	{ 
		code[n] = getch(); //getch輸入時不會再螢幕顯示 
		
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
