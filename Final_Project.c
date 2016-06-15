/* FILE HANDLING */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>



void create();	
void delete();
void append();
void display();
void encrypt();
void decrypt();
int send_file();
int recieve_file();
void rename_file();
void merging_files();
void copying_files();

int main(void)
{
	int choice,a;

	while(1)
	{
		printf("\n **************	MENU	*****************\n\n");
		printf("1.Create a file \n");
		printf("2.Display text\n");
		printf("3.Append text\n");
		printf("4.Delete a file\n");
		printf("5.Encrypt file\n");
		printf("6.Decrypt file\n");
		printf("7.Send file\n");
		printf("8.Recieve file\n");
		printf("9.Rename file\n");
		printf("10.Merge files\n");
		printf("11.Copy file\n");
		printf("12.Exit\n");
		printf("\n\n###########----- Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
	          		case 1:
				create();
				break;
			case 2:
				display();
				break;
			case 3:
				append();
				break;
			case 4:
				delete();
				break;
			case 5:
				encrypt();
				break;
			case 6:
				decrypt();
				break;
			case 7 : 
				a=send_file();
				break;
			case 8:
				a=recieve_file();
				break;
			case 9:
				rename_file();
				break;
			case 10:
				merging_files();
				break;
			case 11:
				copying_files();
				break;
			
			case 12:
				fcloseall();
				exit(1);		

			default :
				printf("Wrong choice\n");
		}/*End of switch */
	}/*End of while */
	return 0;
}/*End of main( ) */



	
void create()
{	
		
	
	FILE *fptr;
	char ch;
	char *filename;	
	filename=(char *)malloc(20);
	printf("\n\n ENTER THE NAME OF THE FILE YOU WISH TO DEAL WITH : ");
	scanf("%s",filename);
	

	if((fptr=fopen(filename,"w"))==NULL)
	{
		printf("UNABLE TO OPEN FILE\n");
		exit(1);
	}
	printf("\n\n Enter text (Press Ctrl+z in DOS and Ctrl+d in Unix to stop reading characters !!! ) :\n");
	
	while((ch=getchar())!=EOF)  
		fputc(ch,fptr);
	fclose(fptr);
	
}
void display()
{
	FILE *fptr;
	char str[20];
	char *filename;	
	filename=(char *)malloc(20);
	printf("\n\n ENTER THE NAME OF THE FILE YOU WISH TO DEAL WITH : ");
	scanf("%s",filename);
	
	if( (fptr=fopen(filename,"r"))==NULL)
	{
		printf("Error in opening file\n");
		exit(1);
	}
	while(fgets(str,sizeof(str),fptr)!=NULL)
		puts(str);
	fclose(fptr);
}

void append()
{	
	
	FILE *fptr;
	char ch;
	char *filename;	
	filename=(char *)malloc(20);
	printf("\n\n ENTER THE NAME OF THE FILE YOU WISH TO DEAL WITH : ");
	scanf("%s",filename);
	

	if((fptr=fopen(filename,"a+"))==NULL)
	{
		printf("UNABLE TO OPEN FILE\n");
		exit(1);
	}
	printf("\n\n Enter text (Press Ctrl+z in DOS and Ctrl+d in Unix to stop reading characters !!! ) :\n");
	
	while((ch=getchar())!=EOF)  
		fputc(ch,fptr);
	fclose(fptr);
	
}

void delete()
{
	int ret;
	char *filename;	
	filename=(char *)malloc(20);
	printf("\n\n ENTER THE NAME OF THE FILE YOU WISH TO DEAL WITH : ");
	scanf("%s",filename);
	
	ret = remove(filename);

  	if(ret == 0) 
     		 printf("File deleted successfully\n");

   	else 
   		printf("Error: unable to delete the file\n");

}

void encrypt()
{
	FILE *source,*dest;
	int c;
	char *filename,*filename1;
	int key=0xFACA;
	unsigned int i;
	
	filename=(char *)malloc(20);
	printf("\n\n ENTER THE NAME OF THE FILE YOU WISH TO ENCRYPT : ");
	scanf("%s",filename);
	
	if((source=fopen(filename,"r"))==NULL)
	{
		printf("Can't open source file\n");
		exit(1);
	}

	filename1=(char *)malloc(20);
	printf("\n\n ENTER THE NAME FOR THE ENCRYPTED FILE : ");
	scanf("%s",filename1);
	if((dest=fopen(filename1,"w"))==NULL)
	{
		printf("Can't open destination file\n");
		exit(1);
	}
	while((c=fgetc(source))!=EOF)
	{
		c= c-key;
		fputc(c,dest);
	}
	fclose(source);
	fclose(dest);
}

void decrypt()
{
	FILE *source,*dest;
	int c;
	char *filename,*filename1;
	int key=0xFACA;
	unsigned int i;
	
	filename=(char *)malloc(20);
	printf("\n\n ENTER THE NAME OF THE FILE YOU WISH TO DECRYPT : ");
	scanf("%s",filename);
	
	if((source=fopen(filename,"r"))==NULL)
	{
		printf("Can't open source file\n");
		exit(1);
	}

	filename1=(char *)malloc(20);
	printf("\n\n ENTER THE NAME FOR THE DECRYPTED FILE : ");
	scanf("%s",filename1);
	if((dest=fopen(filename1,"w"))==NULL)
	{
		printf("Can't open destination file\n");
		exit(1);
	}
	while((c=fgetc(source))!=EOF)
	{
		c= c+key;
		fputc(c,dest);
	}
	fclose(source);
	fclose(dest);
} 

int send_file()
{
char *filename;
    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    filename=(char *)malloc(20);
	printf("\n\nENTER THE NAME OF THE FILE TO BE SEND : ");
	scanf("%s",filename);


    printf("Socket retrieve success\n");


    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }


    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen(filename,"rb");
        if(fp==NULL)
        {
            printf("File opern error");
            return 1;   
        }   

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread);
            }

            /*
             * There is something tricky going on with read .. 
             * Either there was error, or we reached end of file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }

        close(connfd);
        sleep(1);
    }


    return 0;
   
   
 
}
int recieve_file()
{
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    /* Create file where data will be stored */
    FILE *fp;
    fp = fopen("recieved.txt", "ab"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(sockfd, recvBuff, 256)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }


    return 0;
}
void rename_file()
{
	char old_name[80],new_name[80];
	
	printf("Enter the name of file to be renamed : ");
	scanf("%s",old_name);
	
	printf("Enter a new name for the file : ");
	scanf("%s",new_name);
	
	if(rename(old_name,new_name)==0)
		printf("File %s renamed to %s\n",old_name,new_name);
	else
		perror("File not renamed");

}
void merging_files()
{
	char *file1,*file2,*file3;	
	char c;
	file1=(char *)malloc(20);
	file2=(char *)malloc(20);
	file3=(char *)malloc(20);

	printf("\n\nENTER THE NAME OF THE FIRST FILE : ");
	scanf("%s",file1);
        printf("\n\nENTER THE NAME OF THE SECOND FILE : ");
	scanf("%s",file2);
        printf("\n\nENTER THE NAME OF THE NEW MERGED FILE : ");
	scanf("%s",file3);
  
   FILE *fp1 = fopen(file1, "r");
   FILE *fp2 = fopen(file2, "r");
	FILE *fp3 = fopen(file3, "w");
   
   if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
   {
         puts("Could not open files");
         exit(0);
   }
 
   // Copy contents of first file to file3.txt
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp3);
 
   // Copy contents of second file to file3.txt
   while ((c = fgetc(fp2)) != EOF)
      fputc(c, fp3);
 
printf("\n\nFILES MERGED.");  
	fcloseall();
}

void copying_files()
{
	char *file1,*file2;	
	char c;
	file1=(char *)malloc(20);
	file2=(char *)malloc(20);

	printf("\n\nENTER THE NAME OF THE FILE TO BE COPIED : ");
	scanf("%s",file1);
        printf("\n\nENTER THE NAME OF THE FILE IN WHICH YOU WISH TO COPY : ");
	scanf("%s",file2);
    
  
   FILE *fp1 = fopen(file1, "r");
   FILE *fp2 = fopen(file2, "w");
	
   
   if (fp1 == NULL || fp2 == NULL)
   {
         puts("Could not open files");
         exit(0);
   }
 
   // Copy contents of first file to second
   while ((c = fgetc(fp1)) != EOF)
      fputc(c, fp2);

 
printf("\n\nFILE COPIED.");  
	fcloseall();
}











