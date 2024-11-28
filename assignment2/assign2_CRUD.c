#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILENAME "users.txt"
#define MAX_LEN 100

typedef struct {
    int id;
    char name[MAX_LEN];
    int age;
} User;

void createFile();
void addUser();
void display();
void update();
void deleteDetail();
int getChoice();

int main(){
    int choice;

    createFile();

    while (1)
    {
         printf("-- User Management System ---\n");
        printf("1. Add User\n");
        printf("2. Display Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice=getChoice();

        switch(choice){
            case 1: addUser(); break;
            case 2: display(); break;
            case 3: update(); break;
            case 4: deleteDetail(); break;
            case 5: exit(0);
            default: printf("Invalid choice please try again.\n");
        }
    }

    return 0;
    
}

void createFile(){
    FILE *file=fopen(FILENAME,"a");
    if(file==NULL){
        perror("Error creating file");
        exit(1);
    }
    fclose(file);
}

void addUser(){
    FILE *file=fopen(FILENAME,"a");
    if(file==NULL){
        perror("Error opening file");
        return;
    }

    User user;
    printf("Enter ID: ");
    scanf("%d",&user.id);
    printf("Enter Name: ");
    scanf(" %[^\n]",user.name);
    printf("Enter Age: ");
    scanf("%d",&user.age);

    fprintf(file,"%d,%s,%d\n ",user.id,user.name,user.age);
    fclose(file);
    printf("User added successfully.\n");
}

void display(){
    FILE *file=fopen(FILENAME,"r");
    if(file==NULL){
        perror("Error opening file");
        return;

    }

    User user;
    printf("--Users--\n");
    while (fscanf(file,"%d,%99[^,],%d\n",&user.id,user.name,&user.age) != EOF){

        printf("ID: %d,Name: %s,Age: %d\n",user.id,user.name,user.age);
    }

    fclose(file); 
}

void update(){
    FILE *file=fopen(FILENAME,"r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int id,found=0;

    User user;
    FILE *temp=fopen("temp.txt","w");

    if (temp == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    printf("Enter the ID of the user to update: ");
    scanf("%d",&id);

    while (fscanf(file,"%d,%99[^,],%d\n",&user.id,user.name,&user.age) != EOF){


        if(user.id==id){
            found=1;
            printf("Enter new Name: ");
            scanf(" %[^\n]",user.name);
            printf("Enter new Age: ");
            scanf("%d",&user.age);      
            
         }
        
        fprintf(temp,"%d,%s,%d\n",user.id,user.name,user.age);
    }

    fclose(file);
    fclose(temp);

    if(found){
        remove(FILENAME);
        rename("temp.txt",FILENAME);
        printf("User updated successfully.\n");
    }
    else{
        remove("temp.txt");
        printf("User with ID %d not found.\n",id);
    }  
}

void deleteDetail(){
    FILE *file =fopen(FILENAME,"r");
    if(file==NULL){
        perror("Error opening file");
        return;
    }

    int id,found=0;
    User user;
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    printf("Enter the ID of the user to delete: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) != EOF) {
        if (user.id != id) {
            fprintf(temp, "%d,%s,%d\n", user.id, user.name, user.age);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
        printf("User deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("User with ID %d not found.\n", id);
    }
}


int getChoice(){
    int ch;
    scanf("%d",&ch);
    return ch;
}