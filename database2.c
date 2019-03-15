#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ele{
	int num;
	float frac;
	char *string;
	struct ele* next;
	struct ele* prev;
	//struct ele *next;
} ele;

ele* head=NULL; //global main pointer

ele* add (ele* a){	//adds element after the provided and returns the pointer to the newly created one
	ele* hold=a->next;
	a->next=malloc(sizeof(ele));
	a->next->next=hold;
	a->next->string=malloc(sizeof(char)*100);
	return a->next;
}

ele* get_prev (ele* a){	//gets address to previous element
	ele* i;
	for(i=head;i->next!=a&&i->next!=NULL;i=i->next);
	return i;
}

ele* del (ele* a){ //deletes element returns address to previous element
	ele* b=get_prev(a);
	b->next=a->next;
	free(a->string);
	free(a);
	return b;
}

int mod (ele* a, int num, float frac, char* string){
	int er;
	a->num=num;
	a->frac=frac;
	if(strcpy(a->string,string))er=1;
	return er;
}

int display(ele* a){
	int i;
	for(i=0;i<100&&a!=NULL;++i){
		printf("%d %f %s\n",a->num,a->frac,a->string);
		a=a->next;
		if(i==99)printf("there are more elements");
	}
}

int del_all(){
	ele* a=head->next;
	while(a!=NULL)
		a=del(a)->next;
}

int save(){
	FILE* ptr;
	ptr=fopen("db.txt","w");
	ele* a=head->next;
	while(a!=NULL){
		fprintf(ptr,"%d %f %s\n",a->num,a->frac,a->string);
		a=a->next;
	}
	fclose(ptr);
}

int load(ele* a){
	FILE* ptr;
	ptr=fopen("db.txt","r");
	a=add(a);
	int i=0;
	while(fscanf(ptr,"%d %f %s\n",&a->num,&a->frac,a->string)==3){
		a=add(a); printf("loop %d\n",i++);}
	del(a);
	fclose(ptr);
}


int main(){
	head=malloc(sizeof(ele));
	head->next=NULL;
	load(head);

	/*add(head);
	mod(head->next,123,0.234,"pokemon");
	add(head);
	mod(head->next,86,0.4,"lapras");
	display(head->next);*/
	display(head->next);

	//save();
	del_all();	
	free(head);
	return 0;
}
