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
ele* add (ele* a);	//adds element after the provided and returns the pointer to the newly created one
ele* get_prev (ele* a);	//gets address to previous element
ele* del (ele* a); //deletes element returns address to previous element
ele* get_adr(int indx);	//gets addres of a given index
int dspl(ele* a); //displays element
int dsp_all();	//displays all elements
int del_all();	//deletes all elements
int count_all();//counts elements
int save(char*);	//saves to a file
int load(char*,ele* a);	//loads from a file after the element (in case you wanted to load more files)
int ar_sv();	//turns list into array
int ar_gt();	//turnes array into list
char cmp_by[3]="zz";	//string determining order of comparisons
int cmpfunc(const void* a, const void* b); //function for quicksort
int get_indx(ele* adr);	//gets index of a given addres
int mod (ele* a, int num, float frac, char* string); //modifies element (not very useful)
int search(char *hid); //searching function
int dsp_num(ele* a, int j); //
int cl_str();
//now to end user functions
int usr_add();	//
int usr_search();	//
int usr_mod();	//
int usr_del();	//
int usr_sort(); //
int usr_dspl(); //

int main(){
	head=(ele*)malloc(sizeof(ele));
	head->next=NULL;
	load("db.txt",head);

	/*add(head);
	mod(head->next,123,0.234,"pokemon");
	add(head);*/
	int loop=1;
	char cwt='a';
	while(loop){
		printf("co chcesz zrbic?\nd-dodaj element g-szukaj m-modyfikuj ");
		printf("u-usun s-sotuj w-wyswietl e-zamknij program\n");
		cwt='\n';
		scanf(" %c",&cwt);

	//fflush(stdin);
		switch(cwt){
			case 'd':
				usr_add();
				break;
			case 'g':
				usr_search();
				break;
			case 'm':
				usr_mod();
				break;
			case 'u':
				usr_del();
				break;
			case 's':
				usr_sort();
				break;
			case 'w':
				usr_dspl();
				break;
			case 'e':
				loop=0;
				break;
		}
		cl_str();
	}
	//dsp_all();


	save("db.txt");
	del_all();	
	free(head);
	return 0;
}

int usr_dspl (){
	int index;
	dsp_num(head->next,30);
	while(1){
		printf("w bazie jest %d elementow\n Od ktorego elementu chcesz wyswietlic?\n jesli chcesz wyjsc z trybu wyswietlania wpisz cos innego niz liczbe.",count_all());
		if(scanf("%d",&index)==0)
			break;
		dsp_num(get_adr(index),30);
	}
	return 0;
}

int usr_add(){
	int i;
	ele* a;
	a=add(head);
	printf("wpisz nowe dane \n");
	printf("numer:");
	if(scanf("%d",&a->num)==0){
		printf("niepoprawnie wprowadzone dane");
		del(a);
		return 1;
	}
	printf("ulamek:");
	if(scanf("%f",&a->frac)==0){
		printf("niepoprawnie wprowadzone dane");
		del(a);
		return 1;
	}
	printf("slowo:");
	if(scanf("%s",a->string)==0){
		printf("niepoprawnie wprowadzone dane");
		del(a);
		return 1;
	}
	return 0;
}


int usr_search(){
	char fraza[50];
	printf("wpisz fraze ktorej szukasz\n");
	scanf("%s",fraza);
	search(fraza);
	return 0;
}

int usr_mod (){
	int i;
	ele* a; 
	printf("wpisz index elementu ktory chcesz zmienic\n");
	scanf("%d",&i);
	a=get_adr(i);
	if(a==NULL){
		printf("niepoprawny adres\n");
		return 1;
	}
	dspl(a);
	printf("wpisz nowe dane \n");
	printf("numer:");
	if(scanf("%d",&a->num)==0){
		printf("niepoprawnie wprowadzone dane");
		return 1;
	}
	printf("ulamek:");
	if(scanf("%f",&a->frac)==0){
		printf("niepoprawnie wprowadzone dane");
		return 1;
	}
	printf("slowo:");
	if(scanf("%s",a->string)==0){
		printf("niepoprawnie wprowadzone dane");
		return 1;
	}
	return 0;
}

int usr_del (){
	int i;
	ele* a;
	printf("wpisz index elementu ktory chcesz usunac\n");
	scanf("%d",&i);
	a=get_adr(i);
	if(a==NULL){
		printf("niepoprawny index\n");
		return 1;
	}
	del(a);
	return 0;
}

int usr_sort (){
	printf("wpisz litery dla kolejnosci sortowania \n a-liczba b-uamek c-slowo\n");
	cmp_by[0]='z';
	cmp_by[1]='z';
	cmp_by[2]='z';
	scanf("%s", cmp_by);
	ar_sv();
	qsort(array,head->num,sizeof(ele*),cmpfunc);
	ar_gt();
}



ele* add (ele* a){	//adds element after the provided and returns the pointer to the newly created one
	ele* hold=a->next;
	a->next=(ele*)malloc(sizeof(ele));
	a->next->next=hold;
	a->next->string=(ele*)malloc(sizeof(char)*100);
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


int dspl (ele* a){ //displays
	printf("%6d %10.*f %15s\n",a->num,3,a->frac,a->string);
}

int dsp_num (ele* a, int j){
	int i;
	for(i=0;i<j&&a!=NULL;++i){
		printf("%5d| ",get_indx(a));
		dspl(a);
		a=a->next;
	}
	return 0;
}
int dsp_all (){	//displays all
	int i=0;
	ele* a;
	for(a=head->next;a!=NULL;a=a->next){
		printf("%4d| ",++i);
		dspl(a);
	}
}

int del_all (){	//deletes all
	ele* a=head->next;
	while(a!=NULL)
		a=del(a)->next;
}

int save (const char* file){	//saves to a file
	FILE* ptr;
	ptr=fopen(file,"w");
	ele* a;
	for(a=head->next;a!=NULL;a=a->next)
		fprintf(ptr,"%d %f %s\n",a->num,a->frac,a->string);
	fclose(ptr);
}

int count_all (){	//counts elements
	int i=0;
	ele* a;
	for(a=head->next;a!=NULL;a=a->next)
		++i;
	return i;
}

int ar_sv (){
	head->num=count_all();			// number of elements will be stored here
	array=(ele*)malloc(head->num*sizeof(ele*));
	ele* a;
	int i=0;
	for(a=head->next;a!=NULL;a=a->next)
		array[i++]=a;
}

int ar_gt (){
	int i;
	head->next=array[0];
	for(i=0;i<(head->num-1);++i)
		array[i]->next=array[i+1];
	array[i]->next=NULL;
	free(array);
}


int load (const char* file, ele* a){	//loads from a file
	FILE* ptr;
	ptr=fopen(file,"r");
	if(ptr==NULL){
		printf("nie mozna znalezc bazy danych\n");
		return 0;
	}
	a=add(a);
	while(fscanf(ptr,"%d %f %s\n",&a->num,&a->frac,a->string)==3)
		a=add(a);
	del(a);
	fclose(ptr);
}

ele* get_adr (int index){	//gets addres of a given index
	int i=0;
	ele* a;
	for(a=head->next;a!=NULL;a=a->next){
		if(++i==index)
			return a;
	}
	return NULL;
}

int get_indx (ele* adr){	//gets index of a given addres
	ele* a;
	int i=1;
	for(a=head;a->next!=adr&&a->next!=NULL;a=a->next)++i;
	if(a->next==NULL) return -1;
	if(a->next==adr) return i;
}

int cmpfunc (const void* a, const void* b){
	ele* e1= *(ele**)a;
	ele* e2= *(ele**)b;
	int i;
	for(i=0;i<3;++i){
		switch(cmp_by[i]){
			case 'a':
				if(e1->num-e2->num!=0)
					return (e1->num-e2->num);
			case 'b':
				if(e1->frac!=e2->frac)
					return(e1->frac>e2->frac?1:-1);
			case 'c':
				if(strcmp(e1->string,e2->string)!=0)
					return strcmp(e1->string,e2->string);
		}
	}
	return 0;
}

	//printf("comparing:%d and %d returned value:%d \n",i,j,i-j);
int mod (ele* a, int num, float frac, char* string){ //modifies element
	int er;
	a->num=num;
	a->frac=frac;
	if(strcpy(a->string,string))er=1;
	return er;
}
int search (char *hid){
	char line[512];
	int i=0;
	ele* a;
	for(a=head->next;a!=NULL;a=a->next){
		sprintf(line,"%6d %10.*f %15s\n",a->num,3,a->frac,a->string);
		if(strstr(line, hid)!=NULL){
			++i;
			printf("%4d| ", get_indx(a));
			dspl(a);
		}
	}
	printf("znaleziono %d lini pasujacych do wyszukania\n",i);
}

int cl_str(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}


/*int Search_in_File(char *fname, char *str) {
	FILE *fp;
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	
	//gcc users
	if((fp = fopen(fname, "r")) == NULL) {
		return(-1);
	}

	//Visual Studio users
	//if((fopen_s(&fp, fname, "r")) != NULL) {
	//	return(-1);
	//}

	while(fgets(temp, 512, fp) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) {
		printf("\nSorry, couldn't find a match.\n");
	}
	
	//Close the file if still open.
	if(fp) {
		fclose(fp);
	}
   	return(0);
}*/
/*int array_print(){
	int i;
	//head->next=array[0];
	for(i=0;i<head->num;++i){
		printf("|%d|\n",array[i]->num);
	}
	printf("head->num=%d",head->num);
}*/
/*int ar_gt(){	//turnes array into list
	head->next=array[0];
	int i=0;
	while(i<(head->num-1)){
		array[i]->next=array[i+1]; ++i; printf("%d\n",i);}
	array[i]->next=NULL;
	free(array);	
}*/
	/*for(i=1;i<4;++i){
		if((cmp_by-cmp_by%100)/100==i)
			if(e1->num-e2->num!=0)
				return (e1->num-e2->num);
		if((cmp_by%100-cmp_by%10)/10==i)
			if(e1->frac!=e2->frac)
				return(e1->frac>e2->frac?1:-1);
		if(cmp_by%10==i)
			if(strcmp(e1->string,e2->string)!=0)
				return strcmp(e1->string,e2->string);
	}*/
