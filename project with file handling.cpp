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

void insert()
{
	system("CLS");
	char name[20];
    float duration;
    char arname[20], album[20];
	FILE *fp;
	
	fp= fopen("songs.txt", "a");
	
	 if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("Enter song name: ");
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
    fprintf(fp, "%s\n %s\n %s\n %f\n", name, arname, album ,duration);
    fflush(fp);
    fclose(fp);
}

void deletion() {
    char name[20];
    
    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 
	else {
        temp = first;
        printf("Enter song name you want to delete: ");
        scanf(" %19[^\n]", name);
        
        // to check if  first node is the one to deleted
        if (strcmp(name, temp->name) == 0) {
            first = first->next;
            last->next = first;
            printf("Deleted song is: %s\n", temp->name);
            free(temp);
            return;
        }
        
        // for finding the node to delete
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
    }
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
    node *nextSong;
    if (first == NULL) {
        printf("List is empty!\n");
        return;
    } 
    
    printf("Enter song name: ");
    scanf(" %20[^\n]", name);
    
    temp = first;
    while (temp->next != first) {
        if (strcmp(name, temp->name) == 0) {
            nextSong = temp->next;
            
//            if (nextSong == first) {
//                nextSong = nextSong->next; 
//            }
            
            if (nextSong != NULL) {
                printf("\nNext song info: \n");
                printf("Song Name: %s\n", nextSong->name);
                printf("Artist Name: %s\n", nextSong->arname);
                printf("Album Name: %s\n", nextSong->album);
                printf("Duration: %f\n\n", nextSong->duration);
            } 
			else {
                printf("No next song available.\n");
            }
            return;
        }
        temp = temp->next;
    }
    if (temp->next == first){
    	nextSong = first;
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
        	
        	while(temp->next != temp ){
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
   	if(first==NULL){
		printf("List is empty!");
		return;
	} 
	else{
    
        printf("\nThe songs in your playlist are: \n\n");
        temp = first;
        do {
            printf("Song Name: %s\n", temp->name);
            printf("Artist Name: %s\n", temp->arname);
            printf("Album Name: %s\n", temp->album);
            printf("Duration: %f\n\n", temp->duration);
            temp = temp->next;
        } while (temp!= first);
    }
}

int main()
{
	int c;
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

