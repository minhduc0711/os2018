#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUFFER_SIZE 10

typedef struct{
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
int pCount = 0;
int cCount = 0;

item *createItem(char type,int amount,char unit){
	item *temp = malloc(sizeof(item));
	temp->type = type;
	temp->amount = amount;
	temp->unit = unit;
	return temp;
}

void logPrint(char *s,int val){
	printf("%s %d : first = %d, last = %d\n",s,val,first,last);
}

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i,sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	logPrint("Produce",++pCount);
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last],sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	logPrint("Consume",++cCount);
	return i;
}

void *producer(void *para){
	produce(createItem(0,5,0));
	produce(createItem(1,20,1));
	produce(createItem(0,10,0));
	return NULL;
}

void *consumer(void *para){
	consume();
	consume();
	return NULL;
}


int main(){
	pthread_t tid1,tid2;
	pthread_create(&tid1, NULL, producer, NULL);
	pthread_create(&tid2, NULL, consumer, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}