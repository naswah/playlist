#include<stdio.h>
#include<conio.h>
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

void newFile() {
    remove("songs.txt");

    FILE *fp = fopen("songs.txt", "w");
    if (fp == NULL) {
        printf("Error opening file \n");
        return;
    }

    temp = first;

    do {
        fprintf(fp, "Song Name: %s\n", temp->name);
        fprintf(fp, "Artist: %s\n", temp->arname);
        fprintf(fp, "Album: %s\n", temp->album);
        fprintf(fp, "Duration: %f\n\n", temp->duration);

        temp = temp->next;
    } while (temp != first);

    fclose(fp);
}

void bringdata(){

	char name[20];
    float duration;
    char arname[20], album[20];
	FILE *ftp;
	ftp= fopen("songs.txt", "r");
	
    if (ftp == NULL) {
        printf("FILE NOT FOUND!");
        return;
    } 
  
    while (fscanf(ftp, "Song Name: %[^\n]%*c", name) == 1 &&
           fscanf(ftp, "Artist: %[^\n]%*c", arname) == 1 &&
           fscanf(ftp, "Album: %[^\n]%*c", album) == 1 &&
           fscanf(ftp, "Duration: %f%*c\n\n", &duration) == 1) {  

    newnode = (node *)malloc(sizeof(node));
    
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        fclose(ftp);
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
    } 
	else {
		
        last->next = newnode;
        last = newnode;
    }
    
    fscanf(ftp, "\n");
    }
    fclose(ftp);
}

void insert()
{
	system("CLS");
	    printf("MENU\n");
		printf("1.Insert a song in the playlist.\n");
		printf("2.Delete a song in the playlist.\n");
		printf("3.Search in the playlist.\n");
		printf("4.Add a fovorite song.\n");
		printf("5.View next song.\n");
		printf("6.View your previous song.\n");
		printf("7.View your playist .\n");
		printf("8.Exit from the program.\n");
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
    } 
	else {
		
        temp = first;
        
        while (temp->next != first) {
            temp = temp->next;
        }
        last = temp;
        last->next = newnode;
        last = newnode;
        last->next = first;
    } 
    printf("Data Entered");
    fprintf(fp, "Song name: %s\nArtist: %s\nAlbum: %s\nDuration: %f\n\n", name, arname, album ,duration);
    fflush(fp);
    fclose(fp);
}

void deletion() {
	char name[20];
    float duration;
    char arname[20], album[20];
    
	system("CLS");
	    printf("MENU\n");
		printf("1.Insert a song in the playlist.\n");
		printf("2.Delete a song in the playlist.\n");
		printf("3.Search in the playlist.\n");
		printf("4.Add a fovorite song.\n");
		printf("5.View next song.\n");
		printf("6.View your previous song.\n");
		printf("7.View your playist .\n");
		printf("8.Exit from the program.\n");
		
    printf("Enter song name you want to delete: ");
    scanf(" %20[^\n]", name);
    
    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 

        temp = first;
     
        if (strcmp(name, temp->name) == 0) {
            first = first->next;
            last->next = first;
            printf("Deleted song is: %s\n", temp->name);
            free(temp);
            newFile();
            return;
        }
        
        // node to delete
        while (temp->next != first) {
            if (strcmp(name, temp->next->name) == 0) {
                break; // found 
            }
            temp = temp->next;
        }

        if (temp->next == first) {
            printf("Invalid song name\n");
            return;
        }
        
        // delete the node
        cnode = temp->next;
        temp->next = cnode->next;
        
        if (cnode == last) {
            last = temp;
        }
        
        printf("Deleted song is: %s\n", cnode->name);
        free(cnode);
        newFile();
}

void search() {
    char name[20];
    
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
            printf("Song Name: %s\n", temp->name);
            printf("Artist Name: %s\n", temp->arname);
            printf("Album Name: %s\n", temp->album);
            printf("Duration: %f\n", temp->duration);
            return;
        }
        temp = temp->next;
    } while (temp != first);
    
    printf("Song not found.\n");
}


void favorite() {
    char name[20];
    
    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 
    
	else {
        temp = first;
        
        printf("Enter song name you want to add to favorites: ");
        scanf(" %19[^\n]", name);
        
        while (temp != first) {
            if (strcmp(name, temp->name) == 0) {
                printf("%s is added to favorites!\n", temp->name);
                //
                return;
            }
            temp = temp->next;
        }
        
        if (strcmp(name, temp->name) != 0) {
            printf("This song doesn't exist in your playlist!'\n");
        }
    }
}

void next() {
    char name[20];
    node *nexts;
    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 
    
    printf("Enter song name: ");
    scanf(" %20[^\n]", name);
    
    temp = first;
    while (temp->next != first) {
        if (strcmp(name, temp->name) == 0) {
            nexts = temp->next;
            
//            if (nexts == first) {
//                nexts = nextSong->next; 
//            }
            
            if (nexts != NULL) {
                printf("\nNext song info: \n");
                printf("Song Name: %s\n", nexts->name);
                printf("Artist Name: %s\n", nexts->arname);
                printf("Album Name: %s\n", nexts->album);
                printf("Duration: %f\n\n", nexts->duration);
            } 
			else {
                printf("No next song available.\n");
            }
            return;
        }
        temp = temp->next;
    }
    if (temp->next == first){
    	nexts = first;
    	printf("\nNext song info: \n");
                printf("Song Name: %s\n", first->name);
                printf("Artist Name: %s\n", first->arname);
                printf("Album Name: %s\n", first->album);
                printf("Duration: %f\n\n", first->duration);
	}
    
    printf("\nThis song doesn't exist in your playlist!\n");
}

void previous(){
	
	char name[20];
    node *prevSong;
    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 
    
    printf("Enter song name: ");
    scanf(" %20[^\n]", name);
    
    temp = first;
    while (temp->next != first) {
        if (strcmp(name, temp->name) == 0) {
        	
        	while(prevSong->next != temp ){
        		  prevSong = temp->next;
			}
          
            
//            if (nextSong == first) {
//                nextSong = nextSong->next; 
//            }
            
            if (prevSong != NULL) {
                printf("\nPrevoius song info: \n");
                printf("Song Name: %s\n", prevSong->name);
                printf("Artist Name: %s\n", prevSong->arname);
                printf("Album Name: %s\n", prevSong->album);
                printf("Duration: %f\n\n", prevSong->duration);
            } 
            return;
        }
        temp = temp->next;
    }
    if (temp->next == first){
    	prevSong = last;
    	printf("\nPrevious song info: \n");
                printf("Song Name: %s\n", last->name);
                printf("Artist Name: %s\n", last->arname);
                printf("Album Name: %s\n", last->album);
                printf("Duration: %f\n\n", last->duration);
	}
    
    printf("\nThis song doesn't exist in your playlist!\n");
	
	
}
void display()
{
    char ch;
	FILE *ptr;
	
	ptr=fopen("songs.txt", "r");
	
	if(ptr == NULL)
   {
      printf("FILE NOT FOUND!");  
      return;             
   }
        printf("\nThe songs in your playlist are: \n\n");
 
		do{
		
		ch = fgetc(ptr);
		putchar(ch);
		
	    }while(ch!=EOF);
	
		fclose(ptr);
	}

int main()
{
	int c;
	bringdata();
	
	    printf("MENU\n");
		printf("1.Insert a song in the playlist.\n");
		printf("2.Delete a song in the playlist.\n");
		printf("3.Search in the playlist.\n");
		printf("4.Add a fovorite song.\n");
		printf("5.View next song.\n");
		printf("6.View your previous song.\n");
		printf("7.View your playist .\n");
		printf("8.Exit from the program.\n");
		
	
	do{
		printf("\nEnter your choice from the menu: ");
		scanf("%d", &c);
		switch(c){
			case 1:
			{
				insert();
				break;
			}
			
			case 2:
			{
				deletion();
				break;
		}
			case 3:
			{
				search();
				break;
			}
		    case 4:
        	{
				favorite();
				break;
			}
			case 5:
        	{
				next();
				break;
			}
			case 6:
        	{
				previous();
				break;
			}
			case 7:
			{
				display();
				break;
			}
			case 8:
			{
				printf("Quitting the prgram. Perss any key");
				getch();
				break;
			}
		}//end of switch
	}while(c!=8);
}//end of main
