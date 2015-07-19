
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 80

// Struct Declaration
struct produceItem {
	char produce[20];
	char type[20];
	char soldBy[20];
	float price;
	int quantityInStock;
	struct produceItem *next;
};

//function prototypes
void display(struct produceItem *head);
void export(struct produceItem *head);
void reverse(struct produceItem **head);
int stockProduce(struct produceItem **head);
void add(char *produce, char *type, char *soldBy, float price, int quantity);

void display(struct produceItem *head){
	int count = 1;
	struct produceItem * temp;
	temp = head;
	
	if(temp== NULL){
		printf("Your Inventory is empty!\n");
		return;
	}
	else{
		printf("************************************************************************\n");
		printf("Item #    Produce       Type       Sold By       Price         In Stock\n");
		printf("************************************************************************\n");
		while(temp != NULL){
			printf("%d %13s %13s %13s\t %5.2f\t\t %d\n", count, temp->produce, temp->type, temp->soldBy, temp->price, temp->quantityInStock);
			count++;
			temp = temp->next;
		}
	}
	
	
}

void export(struct produceItem *head){
	FILE *fp;
	fp = fopen("AssignmentTwoOutput.txt", "w+");
	struct produceItem *temp;
	temp = head;
	int count = 1;
	
	if(temp == NULL){
		fprintf(fp,"Your Inventory is empty!\n");
		return;
	}
	else{
		fprintf(fp,"************************************************************************\n");
		fprintf(fp,"Item #    Produce       Type       Sold By       Price         In Stock\n");
		fprintf(fp,"************************************************************************\n");
		while(temp != NULL){
			fprintf(fp,"%d %13s %13s %13s\t %5.2f\t\t %d\n", count, temp->produce, temp->type, temp->soldBy, temp->price, temp->quantityInStock);
			count++;
			temp = temp->next;
		}
	}
	
	
}

int stockProduce(struct produceItem **head){
	FILE *fp;
	char produceInfo[MAXSIZE];
	char *produce, *type, *soldBy, *priceChar, *quantityChar;
	float price;
	int quantityStock;
	
	fp = fopen("AssignmentTwoInput.txt","r");
	if(fp == NULL){
		printf("File Not Found\n");
		return 0;
	}
	
	while(!feof(fp)){
		
		//read in information using fgets then strip using strtok
		fgets(produceInfo,MAXSIZE,fp);
		produce = strtok(produceInfo,",");
		type = strtok(NULL,",");
		soldBy = strtok(NULL,",");
		priceChar = strtok(NULL,",");
		quantityChar = strtok(NULL,",");
		price = atof(priceChar);
		quantityStock = atoi(quantityChar);
		
		if((*head) == NULL){
			(*head) = malloc(sizeof(struct produceItem));
			strcpy((*head)->produce,produce);
			strcpy((*head)->type,type);
			strcpy((*head)->soldBy,soldBy);
			(*head)->price = price;
			(*head)->quantityInStock = quantityStock;
			(*head)->next = NULL;
		}
		else {
			struct produceItem *newItem;
			newItem = (struct produceItem *) malloc(sizeof(struct produceItem));
			strcpy(newItem->produce,produce);
			strcpy(newItem->type,type);
			strcpy(newItem->soldBy,soldBy);
			newItem->price = price;
			newItem->quantityInStock = quantityStock;
			//add new item to top of list
			newItem->next = (*head);
			(*head) = newItem;	
		}
		
	}
	
	return 1;
}

void Reverse(struct produceItem **head){
	struct produceItem *first, *rest;
	if((*head) == NULL)return;
	first = (*head);
	rest = (*head)->next;
	if(rest == NULL)return;
	Reverse(&rest);
	first->next->next = first;
	first->next = NULL;
	(*head) = rest;
}

int main() {
	//create head and set to null
	int choice;
	struct produceItem *top;
	top = NULL;
	
	while(1){
		printf("List Operations\n");
		printf("----------------\n");
		printf("1. Stock Produce Department\n");
		printf("2. Display Produce Inventory\n");
		printf("3. Reverse order of Produce Inventory\n");
		printf("4. Export Produce Inventory\n");
		printf("5. Exit Program\n");
		printf("Enter your choice : ");
		
		if(scanf("%d", &choice) < 1 ){
			printf("Try Again\n");
		}
		else
			switch(choice){
				case 1:
					printf("Trying to open file AssignmentTwoInput.txt\n");
					if(stockProduce(&top) != 0){
						printf("Successfully opened AssignmentTwoInput.txt\n");
						printf("\n");
					}	
					else
						printf("File Not Found!\n");
					break;
				case 2:
					display(top);
					printf("\n");
					break;
				case 3:
					Reverse(&top);
					break;
				case 4:
					export(top);
					printf("Successfully exported AssignmentTwoOutput.txt\n");
					printf("\n");
					break;
				case 5:
					return 0;
					
			}
		}
}
