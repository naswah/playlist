#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct playlist{
  char name[20];
  float duration;
  char arname[20], album[20];
  struct playlist *next;
};

typedef struct playlist node;
node *newnode;
node *temp;
node *first=NULL;
node *last=NULL;
node *cnode;
int count=0;

void bringdata(){
  char name[20];
    float duration;
    char arname[20], album[20];
  FILE *ftp;

  first = NULL;
  last = NULL;

  ftp= fopen("songs.txt", "r");

    if (ftp == NULL) {
        printf("FILE NOT FOUND!");
        return;
    }
    while (fscanf(ftp, "%s %s %s %f", name, arname, album, &duration) == 4) {  

    newnode = (node *)malloc(sizeof(node));

    strcpy(newnode->name, name);
    strcpy(newnode->arname, arname);
    strcpy(newnode->album, album);
    newnode->duration = duration;
    count++;

    if (first == NULL) {
        first = newnode;
        last = newnode;
        last->next = first;
    } 
  else {
        last->next = newnode;
        last = newnode;
        
        last->next=first;
    }
    }
    fclose(ftp);
}

void menu() {
    printf("MENU\n");
    printf("1.Insert a song in the playlist.\n");
    printf("2.Delete a song in the playlist.\n");
    printf("3.Search in the playlist.\n");
    printf("4.View next song.\n");
    printf("5.View your playist .\n");
    printf("6.Exit from the program.\n");
}

void newFile() {
  remove("songs.txt");
  FILE *fp = fopen("songs.txt", "w");
  if (fp == NULL) {
    printf("Error opening file \n");
    return;
  }

  temp = first;

 do{
 
    fprintf(fp, "%s\n%s\n%s\n%f\n", temp->name, temp->arname, temp->album, temp->duration);
    temp = temp->next;
    
  }   while (temp != first);

  fclose(fp); 
}

void freelist() {
    if (first == NULL) {
        return;
    }
    temp = first;
    do {
        node *nextnode = temp->next;
        free(temp);
        temp = nextnode;
    } while (temp != first);

    first = NULL;
    last = NULL;
}

void insert() {
  system("CLS");
  menu();
  char name[20];
    float duration;
    char arname[20], album[20];
  FILE *fp;

  fp= fopen("songs.txt", "a");

  if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter song name: ");
    scanf(" %19[^\n]", name);

    printf("Enter artist name: ");
    scanf(" %19[^\n]", arname);

    printf("Enter album name: ");
    scanf(" %19[^\n]", album);

    printf("Enter duration: ");
    scanf("%f", &duration);

    newnode = (node *)malloc(sizeof(node));

    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }

    strcpy(newnode->name, name);
    strcpy(newnode->arname, arname);
    strcpy(newnode->album, album);
    newnode->duration = duration;

    if (first == NULL) {
        first = newnode;
        last = newnode;
        last->next = first;
        count++;
    } 
  else {
        last->next = newnode;
        last = newnode;
        last->next=first;
        count++;
    }

    printf("Data Entered");
    fprintf(fp, "%s\n%s\n%s\n%f\n", name, arname, album ,duration);
    fflush(fp);
    fclose(fp);
}

void deletion() {
  char name[20];
  int num;
  num=count;
    system("CLS");
    menu();

    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 

    printf("Enter song name you want to delete: ");
    scanf(" %19[^\n]", name); 
	
    temp=first;
	
    while(num!=0){
    	if (strcmp(temp->name,name)==0){
    		break;
		}
		temp=temp->next;
		num--;
	}
	
   if(num==0){
   	printf("Invalid Choice!");
   	return;
   }
   
  else{
	   	temp=first;
	   	if(count==1){
	   	     	
	            first = NULL;
	            last = NULL;
	            printf("Deleted song is: %s\n", temp->name);
	            free(temp);
	            count--;
	            
	            remove("songs.txt");
	            
	            FILE *ftp=fopen("songs.txt", "w");
	            fclose(ftp);
	        
	        } 
	        
	        else if(strcmp(temp->name,name)==0){
	        	first=first->next;
	        	last->next=first;
	        	printf("Deleted song is: %s\n", temp->name);
		        count--;
		        free(temp);
		        newFile();
			}
			
	        else{
			   	while (temp->next!= first) {
		            if (strcmp(name, temp->next->name) == 0) {
		                break; // found 
		            }
		            temp = temp->next;
		        }
		
		        cnode = temp->next;
		        temp->next = cnode->next;
		        
			    printf("Deleted song is: %s\n", cnode->name);
		        count--;
		        free(cnode);
		        newFile();
	        }
    }   
}

void search() {
    char name[20];
    system("CLS");
    menu();
    if (first == NULL) {
        printf("The playlist is empty!\n");
        return;
    }

    printf("Enter song name to search: ");
    scanf(" %20[^\n]", name);

    temp = first;
    do {
        if (strcmp(name, temp->name) == 0) {
            printf("Song found!\n");
            printf("\nSong Name: %s\nArtist Name: %s\nAlbum: %s\nDuration: %f", temp->name,temp->arname, temp->album, temp->duration);
            return;
        }
        temp = temp->next;
    } while (temp != first);

    printf("Song not found.\n");
} 

void next() {
    char name[20];
    system("CLS");
    menu();
    node *nexts;
    int num=count;

    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 

    printf("Enter song name: ");
    scanf(" %20[^\n]", name);

    temp = first; 
    while(num!=0){
      if(strcmp(name,temp->name)==0){
        nexts=temp->next;
        printf("\nNext Song Info:\n");
        printf("\n%s\n%s\n%s\n%f", nexts->name,nexts->arname, nexts->album , nexts->duration);
        return;
    }
    temp=temp->next;
    num--;
  }

    if(num==0){
      printf("This song doesn't exist in your playlist!");
  }
}

void display(){
  FILE *ptr;
  char name[20];
    float duration;
    char arname[20], album[20];

  ptr=fopen("songs.txt", "r");

  if(ptr == NULL)
   {
      printf("FILE NOT FOUND!");  
      return;             
   }
  printf("\nThe songs in your playlist are: \n");

  while (fscanf(ptr, "%s %s %s %f", &name, &arname, &album, &duration)==4) {
         printf("\nSong Name: %s\nArtist Name: %s\nAlbum: %s\nDuration: %f\n", name, arname,album, duration);
  }
  
    fclose(ptr);
}

int main(){
  int c;
    bringdata();
    menu();
  do{
    printf("\nEnter your choice from the menu: ");
    scanf("%d", &c);
    switch(c){
      case 1:
        insert();
        break;
      case 2:
        deletion();
        break;
      case 3:
        search();
        break;
        case 4:
          next();
          break;
      case 5:
        display();
        break;
      case 6:
        printf("Quitting the prgram. Perss any key");
        break;
      default:
        printf("Invalid Choice");
    }//end of switch
  }while(c!=6);
  freelist();
}//end of main
