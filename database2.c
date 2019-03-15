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

ele* head=NULL; //global main pointer to the list

ele** array=NULL;	//array pointer

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

int mod (ele* a, int num, float frac, char* string){ //modifies element
	int er;
	a->num=num;
	a->frac=frac;
	if(strcpy(a->string,string))er=1;
	return er;
}

int dspl(ele* a){ //displays
	printf("%d %f %s\n",a->num,a->frac,a->string);
}


int dsp_all(ele* a){	//displays all
	int i;
	for(i=0;i<25&&a!=NULL;++i){
		printf("%d| ",i+1);
		dspl(a);
		a=a->next;
		if(i==25)printf("there are more elements");
	}
}

int del_all(){	//deletes all
	ele* a=head->next;
	while(a!=NULL)
		a=del(a)->next;
}

int save(){	//saves to a file
	FILE* ptr;
	ptr=fopen("db.txt","w");
	ele* a=head->next;
	while(a!=NULL){
		fprintf(ptr,"%d %f %s\n",a->num,a->frac,a->string);
		a=a->next;
	}
	fclose(ptr);
}

int count_all(){	//counts elements
	int i=0;
	ele* a;
	for(a=head;a->next!=NULL;a=a->next)++i;
	return i;
}
int ar_sv(){	//turns list into array
	/*
	for(a=head->next;a->next!=NULL;a=a->next){
		array[i++]=a;
	if(head->next==NULL) return 1;
	}*/
	if(array!=NULL)free(array);
	array=malloc(count_all()*sizeof(ele*));
	ele* a=head->next;
	int i=0;
	while(a!=NULL){
	array[i++]=a;
	a=a->next;
	}
	head->num=i; // number of elements in array (not including head)
}
int array_print(){
	int i;
	//head->next=array[0];
	for(i=0;i<head->num;++i){
		printf("|%d|\n",array[i]->num);
	}
	printf("head->num=%d",head->num);
}
int ar_gt(){	//turnes array into list
	head->next=array[0];
	int i=0;
	while(i<(head->num-1))
		array[i]->next=array[++i];
	array[i]->next=NULL;
	free(array);	
}
int load(ele* a){	//loads from a file
	FILE* ptr;
	ptr=fopen("db.txt","r");
	a=add(a);
	while(fscanf(ptr,"%d %f %s\n",&a->num,&a->frac,a->string)==3)
		a=add(a);
	del(a);
	fclose(ptr);
}

ele* get_adr(int indx){	//gets addres of a given index
	int i=0;
	ele* a;
	for(a=head->next;a->next!=NULL;a=a->next){
		if(++i==indx)
			return a;
	}
}
int get_indx(ele* adr){	//gets index of a given addres
	ele* a;
	int i=1;
	for(a=head;a->next!=adr&&a->next!=NULL;a=a->next)++i;
	if(a->next==NULL) return -1;
	if(a->next==adr) return i;
}
int cmpfunc(const void* a, const void* b){
	int i= (*(ele**)a)->num;
	int j= (*(ele**)b)->num;	
	//printf("comparing:%d and %d returned value:%d \n",i,j,i-j);
	return (i-j);
}

int main(){
	head=malloc(sizeof(ele));
	head->next=NULL;
	load(head);

	/*add(head);
	mod(head->next,123,0.234,"pokemon");
	add(head);*/
	dsp_all(head->next);
	//dspl(get_adr(6));
	ar_sv();
	qsort(array,head->num,sizeof(ele*),cmpfunc);
	//array_print();
	ar_gt();
	printf("--%d--\n",count_all());
	dsp_all(head->next);

	//save();
	del_all();	
	free(head);
	return 0;
}
