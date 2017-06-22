#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 10
#define RAND_MIN 57

typedef struct TWN{
	float data;
	struct TWN *prev;
	struct TWN *next;
}TWN;

typedef struct CTWL{
	TWN *cur;
}CTWL;

void ctwl_cur_step_right(CTWL *list){
	if(list->cur==NULL){
		break;
	}
	
    list->cur=list->cur->next;
}

void ctwl_cur_step_left(CTWL *list){
	if(list->cur==NULL){
		break;
	}
	
	list->cur=list->cur->prev;
}

TWN *ctwl_insert_right(CTWL* list, float val){
	TWN *novy, *prvy, *druhy;
	
	if(list->cur==NULL){
		return NULL;
	}
	
	novy=malloc(sizeof(TWN));
	if(novy==NULL){
		return NULL;
	}
	
	prvy=list->cur;
	druhy=list->cur->next;
	
	novy->prev=prvy;
	novy->next=druhy;
	druhy->prev=novy;
	prvy->next=novy;
	novy->data=val;
	
	return novy;
}

TWN *ctwl_insert_left(CTWL* list, float val){
	TWN *novy, *prvy, *druhy;
	
	if(list->cur==NULL){
		return NULL;
	}
	
	novy=malloc(sizeof(TWN));
	if(novy==NULL){
		return NULL;
	}
	
	druhy= list->cur;
	prvy=list->cur->next;
	
	novy->prev=prvy;
	novy->next=druhy;
	druhy->prev=novy;
	prvy->next=novy;
	novy->data=val;
	
	return novy;
}

char ctwl_delete(CTWL *list){
	TWN *cur, *prev, *next;
	
	if(list->cur==NULL){
		break;
	}
	
	cur=list->cur;
	next=list->cur->next;
	prev=list->cur->prev;
	
	prev->next=next;
	next->prev=prev;
	
	free(cur);
}

CTWL *ctwl_create_empty(void){
	CTWL *list;
	
	if(list->cur==NULL){
		return NULL;
	}
	
	if((list=(CTWL*)malloc(sizeof(CTWL)))==NULL){
		list->cur=NULL;
		return NULL;
	}
        
	list->cur=NULL;
	list->cur->next=NULL;
	
	return list;
}

CTWL *ctwl_create_random(unsigned int size){
	CTWL *list;
	TWN *start, *prev, *next;
	int i;

	if(list->cur==NULL){
		return NULL;
	}
	
	list=ctwl_create_empty();
	list->cur->data=RANGE*(float)rand()/((float)RAND_MAX)+RAND_MIN;
	start=list->cur;
	
	for(i=0;i<size-1;i++){
		list->cur->next=(TWN*)malloc(sizeof(TWN));
        if(list->cur->next==NULL){
            return NULL;
        }
	
        prev=list->cur;
        ctwl_cur_step_right(list);
        list->cur->prev=prev;
 		list->cur->data=RANGE*(float)rand()/((float)RAND_MAX)+RAND_MIN;
	}
	
	list->cur->next=start;
	prev=list->cur;
	ctwl_cur_step_right(list);
	list->cur->prev=prev;
	
	return list;
}

void ctwl_destroy(CTWL *list){
	TWN *cur;
	
	if(list->cur==NULL){
		break;
	}
	
	cur=list->cur;
	while(list->cur->next==NULL){
		ctwl_cur_step_right(list);
		free(cur);
		list->cur=cur;	
	}
	
	free(list);
	free(list->cur);
}

void ctwl_print(CTWL *list){
	TWN *cur;
	
	if(list->cur==NULL){
		break;
	}
	
	cur=list->cur;
	printf("%.3f ", list->cur->data);
	ctwl_cur_step_right(list);

	while(cur != list->cur){
		printf("%.3f ",list->cur->data);
		ctwl_cur_step_right(list);
	}
}

float ctwl_sum_values(CTWL *list){
	TWN *cur;
	float sum;
	
	if(list->cur==NULL){
		break;
	}
	
	sum=0;
	cur=list->cur;
	sum=sum+list->cur->data;
	ctwl_cur_step_right(list);
	
	while(cur!=list->cur){
		sum=sum+cur->data;
		ctwl_cur_step_right(list);
	}
	
	return sum;
}

main(){
	unsigned int size;
	float sum;
	CTWL *list;
	TWN *p;

	srand(time(NULL));
	printf("Zadaj pocet prvkov:");
	scanf("%d",&size);

	list=ctwl_create_random(size);
	printf("Zoznam :\n");
	ctwl_print(list);
	sum=ctwl_sum_values(list);
	printf("\nSum :%.3f\n",sum);

}
