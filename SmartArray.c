//Henry Jetmundsen
//COP 3502C Section 0001
//PID: 3780876

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SmartArray.h"

SmartArray *createSmartArray(int length){
	int i;
	int greater;
	SmartArray *smarty = malloc(sizeof(SmartArray));

	if(smarty == NULL)
		return NULL;

	if(length > DEFAULT_INIT_LEN)
		greater = length;
	else
		greater = DEFAULT_INIT_LEN;

	smarty->array = malloc(sizeof(char *) * greater);

	if(smarty->array == NULL)
		return NULL;

	for(i = 0; i < greater; i++){
		smarty->array[i] = NULL;
	}

	smarty->size = 0;
	smarty->capacity = greater;

	printf("-> Created new SmartArray of size %d.\n", greater);
	return smarty;
}

SmartArray *destroySmartArray(SmartArray *smarty){
	int i;

	if(smarty == NULL)
		return NULL;

	if(smarty->array == NULL){
		free(smarty);
		return NULL;
	}

	for(i = 0; i < smarty->capacity; i++){
		if(smarty->array[i] != NULL)
			free(smarty->array[i]);
	}

	free(smarty->array);
	free(smarty);
	return NULL;
}

SmartArray *expandSmartArray(SmartArray *smarty, int length){
	int i;

	if(smarty == NULL)
		return NULL;

	if(length > smarty->capacity && smarty->array != NULL){
		SmartArray *newSmarty = malloc(sizeof(SmartArray));

		if(newSmarty == NULL)
			return NULL;

		newSmarty->array = malloc(sizeof(char *) * length);
		newSmarty->size = smarty->size;
		newSmarty->capacity = length;

		if(newSmarty->array == NULL)
			return NULL;

		for(i = 0; i < length; i++){
			newSmarty->array[i] = NULL;
		}

		for(i = 0; i < smarty->size; i++){
			newSmarty->array[i] = malloc(sizeof(char) * (strlen(smarty->array[i]) + 1));

			if(newSmarty->array[i] == NULL)
				return NULL;

			strcpy(newSmarty->array[i], smarty->array[i]);
		}

		for(i = 0; i < smarty->capacity; i++){
				free(smarty->array[i]);
		}

		free(smarty->array);

		smarty->array = newSmarty->array;
		smarty->capacity = length;

		printf("-> Expanded SmartArray to size %d.\n", length);

		return smarty;
	}

		return smarty;
}

SmartArray *trimSmartArray(SmartArray *smarty){
	int i;

	if(smarty == NULL)
		return NULL;

	if(smarty->capacity > smarty->size){
		SmartArray *newSmarty = malloc(sizeof(SmartArray));

		if(newSmarty == NULL)
			return NULL;

		newSmarty->array = malloc(sizeof(char *) * smarty->size);

		if(newSmarty->array == NULL)
			return NULL;

		for(i = 0; i < smarty->size; i++){
			newSmarty->array[i] = malloc(sizeof(char) * strlen(smarty->array[i]) + 1);
			strcpy(newSmarty->array[i], smarty->array[i]);
		}

		newSmarty->size = smarty->size;
		newSmarty->capacity = smarty->size;

		for(i = 0; i < smarty->capacity; i++){
			if(smarty->array[i] != NULL)
				free(smarty->array[i]);
		}

		smarty->array = newSmarty->array;
		smarty->capacity = smarty->size;

		printf("-> Trimmed SmartArray to size %d.\n", newSmarty->capacity);

		return smarty;

	} else {
		return smarty;
	}
}

char *put(SmartArray *smarty, char *str){
	int i;

	if(smarty == NULL || smarty->array == NULL || str == NULL)
		return NULL;

	char copy[strlen(str) + 1];
	strcpy(copy, str);

	if(smarty->array[smarty->capacity - 1] != NULL){
		smarty = expandSmartArray(smarty, smarty->capacity * 2 + 1);
	}

	i = smarty->size;

	smarty->array[i] = malloc(sizeof(char) * (strlen(copy) + 1));
	strcpy(smarty->array[i], copy);
	smarty->size++;
	return smarty->array[i];
}

char *get(SmartArray *smarty, int index){
	if(smarty == NULL || index < 0 || index >= smarty->capacity || smarty->array[index] == NULL){
		return NULL;
	} else {
		return smarty->array[index];
	}
}

char *set(SmartArray *smarty, int index, char *str){
	int i;

	if(smarty == NULL || index < 0 ||index >= smarty->size || smarty->array[index] == NULL || str == NULL){
		return NULL;
	} else {
		smarty->array[index] = NULL;
		smarty->array[index] = malloc(sizeof(char) * (strlen(str) + 1));
		strcpy(smarty->array[index], str);
		return smarty->array[index];
	}
}

char *insertElement(SmartArray *smarty, int index, char *str){
	int i;

	if(smarty == NULL || index < 0 || str == NULL)
		return NULL;

	if(smarty->capacity == smarty->size){
		smarty = expandSmartArray(smarty, smarty->capacity * 2 + 1);
	}

	if(index > smarty->size){
		// smarty->array[smarty->size] = malloc(sizeof(char) * strlen(str) + 1);
		// strcpy(smarty->array[smarty->size], str);
		// smarty->size++;
		// return smarty->array[smarty->size];
		return put(smarty, str);
	}

	else if(smarty->array[index] == NULL){
		for(i = 0; smarty->array[i] != NULL; i++)
			;

		smarty->array[i] = malloc(sizeof(char) * strlen(str) + 1);
		strcpy(smarty->array[i], str);
		smarty->size++;
		return smarty->array[i];
	} else {
		for(i = smarty->size; i != index; i--){
			smarty->array[i] = smarty->array[i - 1];
		}

		smarty->array[i] = malloc(sizeof(char) * strlen(str) + 1);
		strcpy(smarty->array[i], str);
		smarty->size++;
		return smarty->array[index];
	}
}

int removeElement(SmartArray *smarty, int index){
	int i;

	if(smarty == NULL || index < 0)
		return 0;

	else if(index >= smarty->size || smarty->array[index] == NULL){
		return 0;
	}

	else if(index == smarty->size - 1){
		free(smarty->array[index]);
		smarty->array[index] = NULL;
		smarty->size--;
		return 1;

	} else {
			free(smarty->array[index]);
			smarty->array[index] = NULL;

		for(i = index + 1; i < smarty->size; i++)
			smarty->array[i - 1] = smarty->array[i];

		smarty->array[smarty->size - 1] = NULL;
		smarty->size--;
		return 1;
	}
}

int getSize(SmartArray *smarty){
	int i;

	if(smarty == NULL || smarty->array == NULL)
		return -1;
	else{
		for(i = 0; smarty->array[i] != NULL && i != smarty->capacity; i++)
			;

		return i;
	}
}

void printSmartArray(SmartArray *smarty){
	int i;

	if(smarty == NULL || smarty->array == NULL || smarty->array[0] == NULL || smarty->size == 0){
		printf("(empty array)\n");
	} else {
		for(i = 0; i < smarty->size; i++){
			printf("%s\n", smarty->array[i]);
		}
	}
}

double difficultyRating(void){
	return 3.5;
}

double hoursSpent(void){
	return 6.0;
}
