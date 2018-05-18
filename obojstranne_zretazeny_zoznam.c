#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define FAIL 0

typedef struct TWN {
	float data;
	struct TWN *prev;
	struct TWN *next;
}TWN;

typedef struct CTWL {
	TWN *cur;
}CTWL;

void ctwl_cur_step_right(CTWL *list) {
	if (list->cur == NULL) {
		return;
	}

	list->cur = list->cur->next;
}

void ctwl_cur_step_left(CTWL *list) {
	if (list->cur == NULL) {
		return;
	}

	list->cur = list->cur->prev;
}

TWN *ctwl_insert_right(CTWL* list, float val) {
	TWN *cur, *novy, *dalsi;

	novy = malloc(sizeof(TWN));

	if (novy == NULL) {
		return 0;
	}

	novy->data = val;

	if (list->cur == NULL) {
		list->cur = novy;
		list->cur->next = novy;
		list->cur->prev = novy;

		return novy;
	}
	else {
		cur = list->cur;
		dalsi = list->cur->next;

		novy->prev = cur;
		novy->next = dalsi;
		list->cur->next = novy;
		dalsi->prev = novy;

		ctwl_cur_step_right(list);
		return novy;
	}
}

TWN *ctwl_insert_left(CTWL* list, float val) {
	TWN *cur, *novy, *predosly;

	novy = malloc(sizeof(TWN));

	if (novy == NULL) {
		return 0;
	}

	novy->data = val;

	if (list->cur == NULL) {
		list->cur = novy;
		list->cur->next = novy;
		list->cur->prev = novy;
	}
	else {
		cur = list->cur;
		predosly = list->cur->prev;

		novy->next = cur;
		novy->prev = predosly;
		predosly->next = novy;
		cur->prev = novy;

		ctwl_cur_step_left(list);
	}

	return novy;
}

char ctwl_delete(CTWL *list) {
	TWN *cur, *prev, *next;

	if (list->cur == NULL) {
		return FAIL;
	}

    // TODO problem !
	if (list->cur->next == list->cur && list->cur->prev == list->cur) {
		free(list->cur);
		list->cur = NULL;
		return OK;
	}

	cur = list->cur;
	next = list->cur->next;
	prev = list->cur->prev;

	ctwl_cur_step_right(list);
	list->cur->prev = prev;
	ctwl_cur_step_left(list);
	list->cur->next = next;
	ctwl_cur_step_right(list);

	free(cur);
	return OK;
}

CTWL *ctwl_create_empty(void) {
	CTWL *list;

	if ((list = (CTWL*)malloc(sizeof(CTWL))) == NULL) {
		return NULL;
	}

	list->cur = NULL;
	return list;
}

CTWL *ctwl_create_random(unsigned int size) {
	int i;
	float data;
	CTWL *list;

	list = ctwl_create_empty();

	for (i = 0; i<size; i++) {
		data = rand() % 20;
		list->cur = ctwl_insert_right(list, data);
	}
	return list;
}

void ctwl_destroy(CTWL *list) {
	TWN *cur, *dalsi;

    // TODO: prazdny zoznam nie je neexistujuci zoznam
    //       aj prazdny zoznam sa da zrusit
    //       a nielen, ze da, ale aj ho zrusit treba
	if (list->cur == NULL) {
		free(list);
		return;
	}

    // TODO: ak zoznam nie je prazdny, tento cyklus ani len nezacne bezat
    //       a teda, uzly sa z pamete nevypratavaju, iba sa skoci na riadok
    //       ...
	while (list->cur->next != list->cur) {
		dalsi = list->cur->next;
		ctwl_delete(list);
		list->cur = dalsi;
	}
    // ... na tento riadok a zrusi sa jedine pojitko, ktore nas so zoznamom
    //     spaja
	free(list->cur);
}

void ctwl_print(CTWL *list) {
	TWN *cur;

	if (list->cur == NULL) {
		return;
	}

	cur = list->cur;

	printf("%.3f ", list->cur->data);
	ctwl_cur_step_right(list);

	while (list->cur != cur) {
		printf("%.3f ", list->cur->data);
		ctwl_cur_step_right(list);
	}
}

float ctwl_sum_values(CTWL *list) {
	TWN *cur;
	float sum;

	if (list->cur == NULL) {
		return 0;
	}

	sum = 0;
	cur = list->cur;

	sum = sum + list->cur->data;
	ctwl_cur_step_right(list);
	
	while (cur != list->cur) {
		sum = sum + list->cur->data;
		ctwl_cur_step_right(list);
	}

	return sum;
}

int main() {
	unsigned int size;
	float sum;
	CTWL *list;
	TWN *p;

	srand(time(NULL));
	printf("Zadaj pocet prvkov:");
	scanf("%d", &size);

	list = ctwl_create_random(size);
	printf("Zoznam :\n");
	ctwl_print(list);

	sum = ctwl_sum_values(list);
	printf("\nSum :%.3f\n", sum);
	ctwl_destroy(list);

	getchar();
	getchar();
}
