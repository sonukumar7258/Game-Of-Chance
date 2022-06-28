#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include <conio.h>
#include <stdbool.h>
#include<windows.h>

void Menu(void);
void SignUp(int s);
void Login(int s);
void Initial(void);
void Slots (void);
void SlotColor(int x);
void EBird(void);
void Roulette(void);
int RouletteColor(int x);
int RoulettePlay(int arr[12][3]);
int RoulettePlay1(int arr[12][3]);
void RouletteBoard(int arr[12][3]);
float ProbCal(float x,float y);
void Probability(void);
int SetColor ( char Color );

struct data {
    char name[20];
    char username[20];
    char pass[20];
    int amount;
    int PEBird[2];		//probabilities of all the three games
    int PSlots[2];		//of every user. 
    int PRoulette[2];	//one for games won and other for total games played.
}user[2],temp;

int main(){
	/*SetColor(15);
	int i;for(i=0; i<256; i++){
		SetColor(i);
		printf("Hello %3d", i); /*SetColor(15);printf("\n");
	}
	getch();
	SetColor(15); 
	printf("\tWelcome To Game Of Chance. Fortunes change here!");
	printf("\n\n\t\tPress any key to begin"); getch();
	Initial(); */
	Roulette();
	return 0;	
}

void Probability(void){
	FILE *fp;
	fp=fopen("data.dat","rb");
	while(fread(&temp,sizeof(temp),1,fp)){
		printf("Name:%s  Games WON:%d   Total Games Played:%d\n",temp.name,temp.PEBird[0],temp.PEBird[1]);
	}	
}

void Initial(void){
	here: system("cls");
	char c; 
	printf("Press 1 for Sign Up\nPress 2 for Login\nPress \"esc\" key to exit\n");
	c = getch();
	if (c == '1'){
		SignUp(0);
	}
	else if (c == '2')
	    Login(0);
	else if ( c == 27){
		return;
	}
	else {
		printf("Wrong Key pressed!"); Sleep(500);
	    goto here;
	}
	Menu();
}

void SignUp(int s){
    system("cls");
	int i,j;
    FILE*fp;
    fp=fopen("data.dat","ab+");
    // L1:
    printf("Enter your name: ");fflush(stdin); gets(user[s].name);
    /*if(strcmp(user[s].name," ")==0);
    {
    	printf("Invalid! User Name");
    	goto L1;
    } */
    printf("Enter your username: ");fflush(stdin); gets(user[s].username); 
    printf("Enter your password: ");
    for(i=0 ; user[s].pass[i-1]!=13 ; i++){
    	user[s].pass[i] = getch();
        if(user[s].pass[i]==13) /*ascii value of enter*/ printf("\n");
        else if(user[s].pass[i]==8){  // acii value of backspace to delete.
            system("cls");
            printf("Enter your name: ");     puts(user[s].name); 	 // this line repeats due to pasword corretion
            printf("Enter your username: "); puts(user[s].username); // this line repeats due to pasword corretion
            printf("Enter your password: ");                    	// this line repeats due to pasword corretion
            i = i-1;             //because after backspace we have to remove (one backslash and enter pressed)
            for(j=0; j<i ; j++){
            	printf("*");
			}
            user[s].pass[i]='\0';
            i=i-1;
        }else printf("*");
    }
    printf("Enter your account balance: $"); scanf("%d",&user[s].amount);
    user[s].PEBird[0] = 0;	user[s].PSlots[0] = 0;	user[s].PRoulette[0] = 0;
    user[s].PEBird[1] = 0;	user[s].PSlots[1] = 0;	user[s].PRoulette[1] = 0;
	fwrite(&user[s],sizeof(user[s]),1,fp);
    fclose(fp);
    printf("Account created successfully!\n");
    printf("Press any key to continue");
    getch();
    system("cls");
    printf("Now Login to your account\n");
    Login(s);
}

void Login (int s){
	system("cls");
	int num1,num2,i,j,ch;
    char UserId[20];
    char sec[20];
    FILE*fp;
    fp=fopen("data.dat","rb");
	printf("Enter your username: "); fflush(stdin); gets(UserId); 
    printf("Enter your password: ");
    for(i=0 ; sec[i-1]!=13  ;  i++){
        sec[i] = getch(); 
        if(sec[i]==13){ // asci value of enter
        	printf("\n");}
        else if(sec[i]==8){ //asci value of backspace or to delete
            system("cls");
            printf("Enter your username: "); puts(UserId); // this line repeats due to pasword corretion
            printf("Enter your password: ");    // this line repeats due to password coreection
            i = i-1;
			//After backspace we have to remove, one less character to consider
            for(j=0; j<i ; j++){
            	printf("*");
			}
			sec[i]='\0'; i=i-1; 
        }else printf("*");
    }
    sec[i] = '\0';
    while(fread(&user[s],sizeof(user[s]),1,fp)){
        num1=strcmp(UserId,user[s].username); num2=strcmp(sec,user[s].pass);

	if(num1==0 && num2==0){
         printf("\n");
        printf("Welcome to this game, Mr. %s\n", user[s].name);
        printf("Your current balance is $%d\n",user[s].amount);
			getch();
		 	system("cls");
		break;
			}
    }
    printf("\n");
    if(num1!=0 || num2!=0){
    	printf("Invalid username or password \n"
		"Pess Enter to try again and ESC key to return to signup fuction");
    	ch = getch();
    	if(ch == 13){
    		system("cls");
    		Login(s);	}
    		else if(ch == 27){
    		system("cls");
			SignUp(s);} 
	}
    fclose(fp);
    //return;
}

void Menu(void){
	system("cls");
	char ch;
	printf(" 1 -> ROULETTE GAME \n 2 -> EBIRD GAME \n 3 -> SLOTS AND JACKPOTS GAME  ");
    ch = getch();	fflush(stdin);
	switch(ch){
		case '1':
			 Roulette();		break;
		case '2':	
			 EBird();			break;
		case '3':
			 Slots ();			break;
		default :
			 printf("Sorry! Wrong key pressed...");
	}
	printf("Do You Want To Play More...?\n"
	"Press Enter to Play again. \nPress ESC To Exit");
	ch = getch(); fflush(stdin);
	if(ch == 13){
		Menu();
	}
	else if(ch == 27) exit(1);
}

float ProbCal(float x,float y){
	float prob;
	prob = (x/y)*100; return prob;
}

void Roulette(void){
	int arr[12][3],x,i,j; bool victory = false;
	RouletteBoard(arr);
	int amount, num[18], ratio, prize, range, temp, result;
	for(i=0;i<18;i++) num[i]=0;
	/* 
	num= seleclted number(s)
	rario= ratio i.e. reward : betting-amount
	amouunt= betting amount
	ratio= explanation present where used
	result= random number generated */
	printf("Enter betting amount: $");scanf("%d", &amount); printf("\n\t");
	printf("Press 'B' for Big prize or Press 'S' for Small prize\n");
	printf("\n");
	char a; fflush(stdin); a = getch();
	if (a ==  's'||a == 'S'){
		printf("\tPress '1' for Type 1 games OR Press '2' for Type 2 games\n");
		printf("\n");
		a = getch(); fflush(stdin);
		if(a == '1'){
			ratio= 1;
			printf("\tPress 'E' for even numbers\n"
			"\tPress 'O' for odd numbers\n"
			"\tPress '1' for first half of numbers\n"
			"\tPress '2' for second half of numbers\n");
			a = getch();
			result = RoulettePlay(arr);
			printf("\tFinal outcome is %d\n", result);
			if(a == 'E' || a == 'e'){
				for(i=0;i<18;i++) num[i]=(i+1)*2;
	            if(result%2 == 0 && result!=0){
			        victory = true;
	            }
			}else if(a == 'O' || a == 'o'){
				for(i=0;i<18;i++) num[i]=1+(i*2);
	            if(result%2 == 1 && result!=0){
			        victory = true;
	            } 
			}else if(a == '1'){
				for(i=0;i<18;i++) num[i]=i+1;
	            if(result > 0 && result <=18 && result!=0){
			        victory = true;
	            }
			}else if(a == '2'){
				for(i=0;i<18;i++) num[i]=i+18;
	            if(result > 18 && result <=36 && result!=0){
		            victory == true;
	            }
			}
		}else if(a == '2'){
			ratio= 2;
			printf("\tPress 'A' for for first column\n"
			"\tPress 'B' for second column\n"
			"\tPress 'C' for third column\n"
			"\tPress '1' for 1st Dozen\n"
			"\tPress '2' for 2nd Dozen\n"
			"\tPress '3' for 3rd Dozen\n");
			a = getch();
			result = RoulettePlay(arr);
			printf("\tFinal outcome is %d\n", result);
			if(a == 'A' || a == 'a'){
			    for(i=0;i<18;i++) num[i]=(i*3)+3;
			    for(i=0;i<12;i++){
				    if(num[i] == result){
					    temp = num[i]; break;
				    }
			    }
				if(temp == result){
			    	victory = true;
	            }else victory==false;
			}else if(a == 'B' || a == 'b'){
	            for(i=0;i<18;i++) num[i]=(i*3)+2;
			    for(i=0;i<12;i++){
				    if(num[i] == result){
					    temp = num[i]; break;
				    }
			    }
				if(temp == result){
			    	victory = true;
	            }else victory==false;
			}else if(a == 'C' || a == 'c'){
	            for(i=0;i<18;i++) num[i]=(i*3)+1;
	            for(i=0;i<18;i++) num[i]=(i*3)+3;
			    for(i=0;i<12;i++){
				    if(num[i] == result){
					    temp = num[i]; break;
				    }
			    }
				if(temp == result){
			    	victory = true;
	            }else victory==false; 
			}else if(a == '1'){
	            if(result > 0 && result <=12 && result!=0){
			        victory = true;
	            }
			}else if(a == '2'){
	            if(result > 12 && result <=24 && result!=0){
		            victory == true;
	            }
			}else if(a == '3'){
	            if(result > 24 && result <=36 && result!=0){
		            victory == true;
	            }
			}
		} 
		if(victory == true){			
			prize = amount*ratio;
			printf("\tVictory! You just won $%d", prize);	
	    }else if(victory == false){
	    	printf("\tSorry! You just lost. Try your luck some other time, maybe\n");
		}
	}else if (a == 'b' ||a == 'B'){
		for(i=0;i<6;i++){
			num[i] = 0;
		}
		printf(
		"Press '1' for Single number bet\n"
		"Press '2' for Row numbers bet\n"
		"Press '3' for Square numbers bet\n"
		"Press '4' for Double-line number bet\n"
		);
		fflush(stdin); a = getch();
		temp = 0; 
		if(a == '1'){ 
			here0:
			RouletteBoard(arr);
			printf("Enter betting number: ");scanf("%d", num[0]); 
			if(num[0] >36 && num[0] <= 36){
				//do nothing
			}else goto here0;
			printf("\n");
			/* No numbers after the pointed one*/ratio = 35;
		}else if(a == '2'){
			here2:
			RouletteBoard(arr);
			printf("Enter 1st betting number: ");scanf("%d", num[0]);printf("\n");
			for(j=0;j<12;j++){
				if(num[0] == arr[j][0]){
					temp = arr[j][0]; break;
				}
			}
			if(temp != num[0]){
				goto here2;
			}
			for(i=1;i<3;i++) num[i]=num[i]+i;
			/* 2 more numbers after than the pointed one*/ratio = 11;
		}else if(a == '3'){ 
			here3:
			RouletteBoard(arr);
			printf("Enter 1st betting number: ");scanf("%d", &num[0]);printf("\n");
			for(j=0;j<11;j++){
				for(i=0;i<2;i++){
					if(num[0] == arr[j][i]){
					    temp = arr[j][i];break;
				    }
				}
			}
			if(temp != num[0]){
				goto here2;
			}
			num[1]= num[0]+1; num[2]= num[0]+3; num[3]= num[0]+4;
			ratio = 8;
		}else if(a == '4'){ 
			here4:
			RouletteBoard(arr);
			printf("Enter 1st betting number: ");scanf("%d", &num[0]);printf("\n");
			for(j=0;j<12;j++){
				if(num[0] == arr[j][0]){
					temp = arr[j][0]; break;
				}
			}
			if(temp != num[0]){
				goto here4;
			}
			for(i=1;i<6;i++) num[i]=num[i]+i;
			/* 5 more numbers after the pointed one*/ ratio = 5;
		}result = RoulettePlay(arr);
	    printf("\n");
	    printf("\tFinal outcome is %d\n", result);
	    if(a =='1' || a=='2' ||a=='3' ||a=='5'){
			if(result!=0 && (result==num[0]||result==num[1]||result==num[2]||
			result==num[3]||result==num[4]||result==num[5])){
			    prize = amount*ratio; printf("\tVictory! You just won $%d", prize);	
	        }else{
	    	    printf("\tSorry! You just lost. Try your luck some other time, maybe\n");
		    }    		
	    }
	}	
}

void RouletteBoard(int arr[12][3]){
	system("cls");
	int i,j,ArrValue=0; 
	for(i=0; i<12; i++){
		for(j=0; j<3; j++){
			ArrValue++;
			arr[i][j] = ArrValue;
		}
	}
	for(i=3; i>0; i--){
		printf("\n\t");
		for(j=0; j<12; j++){
			if(arr[j][i-1]%2 == 0 ){
				SetColor(RouletteColor(arr[j][i-1]));
				printf("| *%d\t", arr[j][i-1]);
			}else{
				SetColor(RouletteColor(arr[j][i-1]));
				printf("| ~%d\t", arr[j][i-1]);
			}
		}printf("|");SetColor(15);
	} 
	printf("\n\t");
}

int RouletteColor(int x){
	int red[18]= {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
	int black[18]= {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
	int i; for(i=0; i<18; i++){
		if(x == red[i]){
			return 79; 
		}else if(x == black[i]){
			return 15;
		}
	}
}

int RoulettePlay(int arr[12][3]){
    int i,j,cnt=0;
	int x;
	while(cnt<50){
		srand(time(0));
        x = rand()%37;
        system("cls");
    	for(i=3; i>0; i--){
		    printf("\n\t");
		    for(j=0; j<12; j++){
		    	if(x == arr[j][i-1]){
		    		SetColor(26);
		    		printf("| $$$\t", arr[j][i-1]); 
				}else{
					SetColor(RouletteColor(arr[j][i-1]));
					if(arr[j][i-1]%2 == 0 ){
				        printf("| *%d\t", arr[j][i-1]);
			        }else{
				        printf("| ~%d\t", arr[j][i-1]);
			        }
				}
		    }printf("|");SetColor(15);
	    }
	    Sleep(100); /*pause*/ cnt++;
	}printf("\n");
	return x;
}

void EBird(void){
	FILE *fp,*fs;
    struct data update;			//to update the data. 
    fp = fopen("data.dat" , "ab+");
    fs = fopen("temp.dat","ab+");
	int ch, x;
	printf("EBird game requires two players\n"
	"press 1 for Login and 2 for signup to login for any other player \n ");	
	input: ch = getch(); fflush(stdin);
	if(ch == '1') Login(1);
	else if(ch == '2') SignUp(1);
	else goto input;
    char u1, u2;
    char str[4][5]={{"UP"},{"LEFT"},{"DOWN"},{"RIGHT"}};
    //printf("CLEARLY READ THE INSTRUCTIONS\n");
    // printf("If you both players press wrong keys the game will not run\n The compition will start from start if one is pressing true\n And other user not\n so it is no matter whether he is pressing first or last he wins in the end\n so play actively");
    StartEB: 	//start of EBird game 
	srand(time(0));
    x = rand()%4;
    if (x ==0){
        u1= 'w';
        u2= 72; 
    }
    else if (x == 1){
        u1 = 'a';
        u2 = 75;
    }
    else if (x == 2){
        u1= 's';
        u2 = 80;
    }
    else if (x == 3){
        u1 = 'd';
        u2 = 77;
    }    
    printf("\n%s press %c\n%s press %s\n",user[0].name, u1,user[1].name, str[x]);
    int c, c1 =0;
    key:
    fflush(stdin); c = getch(); 
	// 72/UP WAS PRESSED
    // case 80: ; break;//DOWN WAS PRESSED
    // case 75: ; break;//LEFT WAS PRESSED
    // case 77: ; break;//RIGHT WAS PRESSED
    if (c == 224){
    	c1 = getch(); fflush(stdin);
        if(c1 == 72 || c1 == 80 || c1 == 75 || c1 == 77){
		    if(u2==c1){
      	        printf("%s won", user[1].name);
				user[1].PEBird[0]+=1;	
		    }
        }
    }
	if (c == 'w' || c == 'a' || c == 's' || c == 'd' ){
        if(u1 == c){
    	    printf("%s won", user[0].name);
			user[0].PEBird[0]+=1;
    }}
    if(u2!=c1 && u1!=c) goto key;
    user[0].PEBird[1] += 1; user[1].PEBird[1]+=1;
    printf("\nProbabilities of Both Users\n%s = %.2f%	%s = %.2f%\n",user[0].name,ProbCal(user[0].PEBird[0] ,user[0].PEBird[1]) ,user[1].name,ProbCal(user[1].PEBird[0] ,user[1].PEBird[1]));
    while ( fread(&update,sizeof(update),1,fp) ){
    	if(strcmp(user[0].username , update.username)==0 ){
    		fwrite(&user[0],sizeof(user[0]),1,fs);
		}else if(strcmp(user[1].username,update.username)==0){
			fwrite(&user[1],sizeof(user[1]),1,fs);
		}else{
			fwrite(&update,sizeof(update),1,fs);
	    }	  
	}
	fclose(fs);
	fclose(fp);
	remove("data.dat");
	rename("temp.dat","data.dat");	
	printf("Do You Want To Play More...?\nPress Enter to Play this same game again.\n"
	"Press backspace to Go to main menu.\nPress ESC To Exit");  
	getch();
    if(c == 'w' || c == 'a' || c == 's' || c == 'd'  ){
    	//BECAUSE OF THE DOUBLE INPUT GIVEN BY USER  
       	getch();
	}
	ch = getch();
	fflush(stdin);
	system("cls");	
	if(ch == 13)goto StartEB;
	else if(ch == 27) exit(1);
	else if(ch == 8) exit(1);
}

void Slots(void){
	system("cls");
	FILE *fp,*fs;
    fp = fopen("data.dat","ab+");
    fs = fopen("temp.dat","ab+");	
    int i, x[3] , j , count = 0 ;char n;
    printf("\t****************Slots & Jackpots**************** "); printf("\n");
    printf("\tPress Enter to continue\n");
	n = getch();
    if(n == 13){
        srand(time(0));
        for(i=0;i<=10;i++){
        	system("cls");	// clears screen after every trial
        	for(j=0;j<3;j++){
        		x[j] = rand()%10;
        		SlotColor(x[j]);
                printf("\t$%d$\t",x[j]);
            }
            SetColor(15);
            Sleep(700); //pause
            system("cls");
        }
        if(x[0] == x[1] || x[1] == x[2] || x[0] == x[2]) count++;
        if(count==3){
        	x[0] = x[1];
     	    x[2] = x[1];
     	    count = 0;
        }
	    for(j=0;j<3;j++){SlotColor(x[j]);printf("\t$%d$\t",x[j]);SetColor(15);}
 	        user[0].PSlots[1]+=1;
	        if (x[0] == x[1] && x[0] == x[2]){
	        	printf("\n\n\tCongratulations! Victory!\n");
		        count = 0;
		        user[0].PSlots[0]+=1;
	        }
	        else printf("\n\n\tSorry! Hard Luck!\n\n\n"); 
	        printf( "\n\tProbability of Winning = %.2f%", //next line as well ...
			ProbCal(user[0].PSlots[0],user[0].PSlots[1]) ); 
            struct data update;			//to update the data. 
            while ( fread(&update , sizeof(update) , 1 , fp) ){
            	if(strcmp(user[0].username , update.username)==0 ){
            		fwrite(&user[0],sizeof(user[0]),1,fs);
			    }
		        else fwrite(&update,sizeof(update),1,fs);	  
			}
		    fclose(fs);
		    fclose(fp);
		    remove("data.dat");
		    rename("temp.dat","data.dat");	
            printf("\n\tif you want to play more press Enter key.\n"
			"\tPress any other key to return to MAin Menu.\n"
			"\tPress ESC key to exit \n\n");
	        n = getch();
            system("cls");
            if(n == 13) Slots();
            else if(n == 27) exit(1);
	        else return;
	} 		 
}

void SlotColor(int x){
	int color[10]= {0,1,2,3,4,5,6,7,8,9};
	int i; for(i=0; i<10; i++){
		if(x == color[i]){
			SetColor(i+1);break;
		}
	}
}

int SetColor(char Color){
    HANDLE h;
    h = GetStdHandle ( STD_OUTPUT_HANDLE ); 
    return SetConsoleTextAttribute ( h, Color );
}

