/*
 * lab6.c
 *
 *  Created on: Nov 11, 2017
 *      Author: Sheida
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct node {
	char *string;
	int freq;
	struct node *next;
}node_t;

node_t *readfile (FILE *);
node_t *search (char *,node_t *);
void output(node_t *,FILE *);
void clean(node_t *);

int main(int argc,char *argv[]){
FILE *fin,*fout;
char word[101];
node_t *head=NULL;

if (argc >3 ){
	fprintf(stderr,"ERROR ! \n");
	return EXIT_FAILURE;
}



fin=fopen("input.txt","r");
if(fin==NULL){
	printf("Error! File is Empty\n");
	exit (EXIT_FAILURE);
}

head=readfile (fin);

fout=fopen("output.txt","w");
if (fout != NULL){
	fprintf(stderr,"Error ! File is not empty!\n");
	return EXIT_FAILURE;
}

output(head,fout);

fclose (fin);
fclose(fout);
clean(head);

return 0;
}

node_t *readfile (FILE *fp){
	char word[101];
	node_t *head=NULL,*new_node;
	int i;

	while (fscanf(fp,"%s",word[101]) !=EOF){

		for (i=0;i<strlen(word);i++){
			word[i]=tolower(word[i]);
		}
		new_node=search(word,head);
		//if our new node isn't null it means there is a word on it
		if (new_node != NULL){
			new_node->freq++;
		}else{
		//malloc list
		new_node=(node_t*)malloc(sizeof(node_t));
		//malloc string list
		new_node->string=(node_t*)malloc(strlen(word)*sizeof(node_t));
		//Error
		if(new_node ==NULL || new_node->string == NULL){
			printf("Memory allocation Error \n");
			return EXIT_FAILURE;
		}
		new_node->freq=1;
		//head insertion or tail insertion order
		//strcpy(new_node->string,word);
		new_node->next=head;
		head=new_node;
		}

	}


return head;
}

node_t *search (char *word,node_t *head){
	node_t *buff=head;
	while (buff != NULL){
		if (strcpy(buff->string , word)==0){
			return buff;
		}
		buff=buff->next;
	}
	return NULL;
}
void output(node_t *head,FILE *fp){
	node_t *new_node=head;
while (new_node != NULL)	{
	fprintf(fp,"%s %d\n",new_node->string,new_node->freq);
	new_node=new_node->next;
}

}
void clean (node_t *head){
	node_t *new_node;
	while (head != NULL){
		new_node = head;
		head=head->next;
		free(new_node->string);
		free(new_node);
	}
}
