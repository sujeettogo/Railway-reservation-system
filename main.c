#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int g_rail_id,gg_rail_id;
void write_id();
void read_id();
void signup();
int s_name(char user_name[21],char password[21]);
int trainnum(int x,int y);
float traintime(int x,int y);
void pre();

struct user
{
	int rail_id;
	char username[100];
	char password[100];
	char firstname[50], secondname[50];
	int age;
	char gender;
};

struct ticket
{
	int train_no;
	int rail_id;
	char source[20],destination[20];
	float tod,toa;
	int no_of_passengers;	
	char passengers[10][50];
};

void chart()
{
    int train_number,i=0,m=1;
    printf("Enter the rail number for which train details must be retrieved :\n");
    scanf("%d",&train_number);
    struct ticket t;
    int found=0;
    FILE *fptr;
    fptr=fopen("ticket.bin","rb");
    if(fptr==NULL)
    {
        printf("ERROR OPENING FILE");
    }
    printf("\n\nTrain Chart Details: \n");
    printf("-------------------- \n");
    fread(&t,sizeof(t),1,fptr);
    printf("| Train no: %d from %s to %s \n",t.train_no,t.source,t.destination);
    printf("| Time of departure: %0.2f   \n",t.tod);
    printf("| Time of arrival  : %0.2f   \n",t.toa);
    fclose(fptr);
    //FILE *fptr;
    fptr=fopen("ticket.bin","rb");
    while(1)
    {
        fread(&t,sizeof(t),1,fptr);
        if(feof(fptr))
            break;
        if(t.train_no==train_number)
        {
            found=1;
            //printf("| Passenger Rail Identification number: %d \n",t.rail_id );
            //printf("| No of passengers: %d \n",t.no_of_passengers);
            //printf("| List of passengers: \n");
			for( i=0;i<t.no_of_passengers;i++,m++) printf("|%d: %s \n",m,t.passengers[i]);
        	
		}
    }
if(!found)
    {
    printf("Sorry ,Ticket details could not be retrieved , try again :( \n");
    }
}

void write_ticket(struct ticket t)
{
	FILE *fptr;
	fptr=fopen("ticket.bin","ab");
	if(fptr==NULL)
	{
		printf("ERROR OPENING FILE");
	}
	fwrite(&t,sizeof(t),1,fptr); 
	fclose(fptr);
}

void retrieve_ticket(int rail_id)
{
	//printf("Supplied rail id: %d \n ",rail_id);
	FILE *fptr;
	struct ticket t;
	int found=0,i=0;
	fptr=fopen("ticket.bin","rb");
	if(fptr==NULL)
	{
		printf("ERROR OPENING FILE");
	}
	//printf("Train Ticket Details:");
	while(1)
	{
		fread(&t,sizeof(t),1,fptr);
		if(feof(fptr))
			break;
		//printf("Existing rail id: %d \n",t.rail_id);
		if(t.rail_id==rail_id)
		{
			found=1;
			printf("\n\nTICKET DETAILS: \n");
			printf("------------------------------------------ \n");
			printf("| Passenger Rail Identification number: %d \n",t.rail_id );
			printf("| Train no: %d from %s to %s \n",t.train_no,t.source,t.destination);
			printf("| Time of departure: %0.2f \n",t.tod);
			printf("| Time of arrival  : %0.2f \n",t.toa);
			printf("| No of passengers: %d \n",t.no_of_passengers);
			printf("| List of passengers: \n");
			for( i=0;i<t.no_of_passengers;i++) printf("| %d: %s \n",i+1,t.passengers[i]);
			printf("------------------------------------------ \n");
			
		}
	}

	if(!found)
	{
	printf("Sorry ,Ticket details could not be retrieved , try again :( \n");
	}
}


void book_train()
{
	int a[30][30];
	int choice1,choice2;
	int x;
	int y;
	int no_of_passengers,c_class;
	struct ticket t;
	char passenger[30];
	
	char places[6][20]={"","Chennai","Coimbatore","Tuticorin","Madurai","Tirunelveli"};
	
	for(x=0;x<5;x++)
	{
	  for(y=0;y<5;++y)
	  a[x][y]=0;
	}
	
	a[0][1]=a[1][0]=1750; a[0][2]=a[2][0]=1425;	
	a[0][3]=a[3][0]=780;  a[0][4]=a[4][0]=975;
	a[1][2]=a[2][1]=650; a[1][3]=a[3][1]=420;
	a[1][4]=a[4][1]=990; a[2][3]=a[3][2]=800;
	a[2][4]=a[4][2]=1120; a[3][4]=a[4][3]=495;
	
	do
	{
	printf("Choose your starting point -:\n");

	printf("1)Chennai \n2)Coimbatore \n3)Tuticorin \n4)Madurai \n5)Tirunelveli \n");
	scanf("%d",&choice1);

	printf("Choose your destination -:\n");

	printf("1)Chennai \n2)Coimbatore \n3)Tuticorin \n4)Madurai \n5)Tirunelveli \n");
	scanf("%d",&choice2);
	
	if(choice1==choice2)
	{
		printf("\nYour starting point and destination cannot be the same \n");
		printf("\nPlease try again \n\n");
	}
	}while(choice1==choice2);
	
	printf("Choose first/second/third class[1/2/3]: ");
	scanf("%d",&c_class);
	
	printf("Enter the number of passengers: ");
	scanf("%d",&t.no_of_passengers);
	
	int i=0;
	for( i=0;i<t.no_of_passengers;i++){
	printf("Enter the name of the %d passengers: ",i+1);
	scanf("%s",passenger); strcpy(t.passengers[i],passenger);
	}
	
	strcpy(t.source,places[choice1]);
	strcpy(t.destination,places[choice2]);
	t.tod= traintime(choice1-1,choice2-1);
	t.toa= t.tod+3.0;
	t.train_no=trainnum(choice1-1,choice2-1);
	t.rail_id=gg_rail_id;
	
	printf("You have chosen to travel between %s and %s \n",places[choice1],places[choice2]);
	printf("The cost of the journey for %d people is: %d \n",t.no_of_passengers,t.no_of_passengers*(a[choice1-1][choice2-1]/c_class));
	printf("The train number is: %d \n",t.train_no);
	printf("The time of departure is: %0.2f and time of arrival is: %0.2f \n",t.tod,t.toa);
	printf("Your ticket has been added to the system \n"); 
	FILE *fptr;
	fptr=fopen("ticket.bin","ab");
	if(fptr==NULL)
	{
		printf("ERROR OPENING FILE");
	}
	fwrite(&t,sizeof(t),1,fptr); 
	fclose(fptr);
}

void signed_in()
{
	printf("Welcome. Choose one of the following : \n")	;
	int choice,trig=0,loop=1;
	while(loop) {
	printf("\nMENU: \n");
	printf("1: Book a new railway ticket \n");
	printf("2: Check the status for a booked ticket \n");
	printf("3: Print the reservation chart for a given train \n");
	printf("4: Log out of current session \n");
	printf("Please enter one of the choices: ");
	do{
		if(trig) printf("Invalid choice.Please enter again: ");
		scanf("%d",&choice);
		if(choice!=1 &&choice!=2 &&choice!=3&&choice!=4) trig=1;
	}while(choice!=1&&choice!=2&&choice!=3&&choice!=4);
	
	switch(choice)
	{
		case 1: printf("\n\nBooking a new ticket. \n"); book_train(); break;
		case 2: printf("Checking status for your booked ticket. \n"); retrieve_ticket(gg_rail_id); break;
		case 3: printf("Print the reservation chart for a given train. \n");chart(); break;
		case 4: printf("Log out of current session. \n"); loop=0; break;
	}
	}
}

void forgot_password()
{
	//system("@cls||clear");
	char email[100];
	getchar();
	printf("Please enter your email id: ");
	scanf("%s",&email);
	printf("We have sent an email with a new password \n");
	printf("Please obtain the password to login \n \n");
}

void start()
{
	int choice,trig=0;
	printf("\n------RAILWAY RESERVATION SYSTEM------ \n");
	printf("Welcome to the Indian Railways System \n");
	printf("Choose one of the following options: \n");
	printf("1- Log in as existing user \n");
	printf("2- Sign up as new user \n");
	printf("3- Forgot password \n");
	do{
	if(trig) printf("Your choice is invalid \n");
	printf("Enter your choice please: ");
	scanf("%d",&choice);
	if(choice!=1 && choice!=2 && choice!=3) trig=1;
	}while(choice!=1 && choice!=2 && choice!=3);
	
	switch(choice)
	{
		case 1: printf("\nYou have chosen to sign in as existing user \n"); pre(); break;
		case 2: printf("\nYou have chosen to sign up as new user \n"); signup(); break;
		case 3: printf("\nYou have chosen to retrieve password \n"); forgot_password(); break;
	}
}
int main()
{
	read_id();
	while(1) {
	start(); }
	return 0;
}

int s_name(char user_name[21],char pass_word[21])
{
	int flag=0;
	FILE *f1;
	struct user u;
	f1=fopen("username_database.bin","rb");
	while(fread(&u,sizeof(struct user),1,f1))
	{
		if(strcmp(user_name,u.username)==0)
		{
			if(strcmp(pass_word,u.password)==0)	
			{
				flag=1;
				gg_rail_id=u.rail_id;
				break;
			}
		}	
		else
		{
			flag=0;
		}
	}
	fclose(f1);
	return flag;
}
void pre()
{
	char m[21];
	char user[21];
	char pass_word[21];
	printf("\nEnter the username ");
	scanf("%s",user);
	printf("\nEnter the password ");
	scanf("%s",pass_word);
	if(s_name(user,pass_word)==0)
	{
		printf("Log in Unsuccessful ..... \n");
		printf("You will be given one more attempt . \n");
		printf("\nEnter the username ");
		scanf("%s",user);
		printf("\nEnter the password ");
		scanf("%s",pass_word);
		if(s_name(user,pass_word)==0)
		{
			printf("\n\n Log in unsuccessful...redirecting to home page... \n");
		}
		else
		{
			printf("\n\n Logged in successfully..Redirecting... \n");
			signed_in();
		}
		
	}
	else
	{
		printf("\n\nLogged in successfully ..Redirecting... \n");
		signed_in();
	}
	
}
void signup()
{
	int i=0;
    struct user u;
	printf("\n Enter the username ");
	scanf("%s",u.username);
	do
	{
	if(i==1)
	{
		printf("\nyour username can not be your password\nplease try again \n");
	}	
	printf("\n Enter the password ");
	scanf("%s",u.password);
	i=1;
	}while(strcmp(u.username,u.password)==0);
	printf("\n Enter the firstname ");
	scanf("%s",u.firstname);
	printf("\n Enter the secondname ");
	scanf("%s",u.secondname);
	i=0;
	do
	{
	if(i==1)
	{
		printf("\n Invalid entry \n try again!!!");
	}
	char q;
	printf("\n Enter the gender(M of F) ");
	scanf(" %c",&q);
	u.gender=toupper(q);
	i=1;
	}while(u.gender!='M' && u.gender!='F');
	i=0;
	do
	{
	if(i==1)
	{
		printf(" \nYour age should be 18 or above \n");
	}
	printf("\n Enter the age: ");
	scanf("%d",&u.age); 
	i=1;
	}while(u.age<18);
	FILE *f1;
	u.rail_id=g_rail_id;
	g_rail_id++;
	f1=fopen("username_database.bin","ab");
	fwrite(&u,sizeof(struct user),1,f1);
	fclose(f1);
}
int trainnum(int x,int y)
{
	int a[21][21];
	int i,j;
	for(i=0;i<5;++i)
	{
		for(j=0;j<5;++j)
		{
			a[i][j]=0;
		}
	}
	a[0][1]=a[1][0]=4200 ; a[0][2]=a[2][0]=3021 ;  
	a[0][3]=a[3][0]=2048 ; a[0][4]=a[4][0]=4096 ; 
	a[1][2]=a[2][1]=8192 ; a[1][3]=a[3][1]=2525 ; 
	a[1][4]=a[4][1]=5050 ; a[2][3]=a[3][2]=7070 ; 
	a[2][4]=a[4][2]=1234 ; a[3][4]=a[4][3]=4321 ;
	i=0;
	j=0;
	return a[x][y];
}
float traintime(int x,int y)
{
	float b[21][21];
	int i,j;
	for (i=0;i<5;++i)
	{
		for(j=0;j<5;++j)
		{
			b[i][j]=0;
		}
	} 
	b[0][1]= 8.40; b[1][0]= 16.50; b[0][2]= 9.00;
	b[2][0]= 19.45; b[3][0]=12.10 ; b[0][3]=21.15 ; 
	b[4][0]= 10.00; b[0][4]= 20.00; b[1][2]= 6.30;
	b[2][1]= 23.10; b[1][3]=8.45 ; b[3][1]=19.25;
	b[1][4]= 8.45; b[4][1]=17.50 ; b[2][3]=4.20 ;
	b[3][2]=14.35 ; b[2][4]=3.05 ; b[4][2]= 21.30;
	b[3][4]=5.00 ;            b[4][3]=23.00 ;
	i=0;
	j=0;
	return b[x][y];
}
void write_id()
{
	FILE *fp;
	fp=fopen("id.txt","w");
	putw(g_rail_id,fp);
	fclose(fp);
}
void read_id()
{
	FILE *fp;
	fp=fopen("id.txt","r");
	g_rail_id=getw(fp);
	fclose(fp);
}
