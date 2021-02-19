/* ... */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spell.h"
#include "hashtbl.h"

// Helper functions
List *deletion(char *word, List *list);

List *substitution(char *word, List *list);

List *insertion(char *word, List *list);

HashTable *initialise_Dictionary(HashTable *hashTable, List *dictionary);

int levenstein_Distance(char *word1, char *word2);

int min_function(int distance_value_One, int distance_value_Two, int distance_value_Three);

// see Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2) {

	int distance = 0;

	distance = levenstein_Distance(word1, word2);
	printf("%d\n", distance);
}

// see Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {

	List *list = new_list();

	list = deletion(word, list);
	// substitution
	list = substitution(word, list);
	//insertion
	list = insertion(word, list);

	for(Node *node = list->head; node; node = node->next) {
		printf("%s\n", (char *)node->data);
		//free(node);
	}

	for(Node *node = list->head; node; node = node->next) {
		free(node->data);
		//free(node);
	}
	free_list(list);

}

// see Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	int hashSize = 0;

	for(Node *bucket = dictionary->head; bucket; bucket = bucket->next) {
		hashSize++;
	}
	hashSize = hashSize * 1.3;

	HashTable *hashTable = new_hash_table(hashSize);

	hashTable = initialise_Dictionary(hashTable, dictionary);

	for(Node *node1 = document->head; node1; node1 = node1->next) {
		char *documentWord = (char *)node1->data;
		if(hash_table_has(hashTable, documentWord) == true) {
			printf("%s\n", documentWord);
		}
		else {
			printf("%s?\n", documentWord);
		}
		//print_hash_table(hashTable, documentWord);

	}
	free_hash_table(hashTable);
}

// see Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {

	int hashSize = 0;
	for(Node *bucket = dictionary->head; bucket; bucket = bucket->next) {
		hashSize++;
	}
	hashSize = hashSize * 1.3;

	HashTable *hashTable = new_hash_table(hashSize);

	hashTable = initialise_Dictionary(hashTable, dictionary);

	for(Node *node1 = document->head; node1; node1 = node1->next) {
		char *anotherWordOne = NULL;
		char *anotherWordTwo = NULL;
		char *anotherWordThree = NULL;
		char *word1 = (char *)node1->data;

		int distance_value_One = 6;
		int distance_value_Two = 6;
		int distance_value_Three = 6;
		if(hash_table_has(hashTable, word1)) {
			printf("%s\n", word1);
		}
		else {
			for(Node *node2 = dictionary->head; node2; node2 = node2->next) {
				char *word2 = (char *)node2->data;
				int lengthWord = strlen(word2);
				int distance = 0;

				distance = levenstein_Distance(word1, word2);

				if(distance == 1 && (distance_value_One != 1)) {
					anotherWordOne = malloc((lengthWord + 1)*sizeof(*anotherWordOne));
					strcpy(anotherWordOne, word2);
					distance_value_One = 1;

					//printf("%s\n", anotherWordOne);

				}
				if(distance == 2 && (distance_value_Two != 2)) {
					anotherWordTwo = malloc((lengthWord + 1)*sizeof(*anotherWordTwo));
					strcpy(anotherWordTwo, word2);
					distance_value_Two = 2;
					//printf("%s\n", anotherWordTwo);

				}
				if(distance == 3 && (distance_value_Three != 3)) {
					anotherWordThree = malloc((lengthWord + 1)*sizeof(*anotherWordThree));
					strcpy(anotherWordThree, word2);
					distance_value_Three = 3;

				}

			}

			int min = min_function(distance_value_One, distance_value_Two, distance_value_Three);
			if(min == 1) {
				printf("%s\n", anotherWordOne);
			} else if(min == 2) {
				printf("%s\n", anotherWordTwo);
			} else if(min == 3) {
				printf("%s\n", anotherWordThree);
			} else {
				printf("%s?\n", word1);
			}//	printf("%s\n", anotherWordOne);
			//} //else if(wordTwo_found )
		}
		free(anotherWordOne);
		free(anotherWordTwo);
		free(anotherWordThree);
	}
	free_hash_table(hashTable);
}

List *deletion(char *word, List *list) {

 	int lengthWord = strlen(word);
	char *newWord = malloc((lengthWord + 1) * sizeof(*newWord));
	memset(newWord, '\0', lengthWord + 1);
	strcpy(newWord, word);

	// deletion
	for(int i = 0; i < lengthWord; i++) {
		// string function from c library
		memmove(&newWord[i],&newWord[i + 1], lengthWord - i);
		char *anotherWord = malloc((lengthWord - 1 + 1) * sizeof(*anotherWord));
		//memset(newWord, '\0', lengthWord - 1 + 1);
		strcpy(anotherWord, newWord);
		list_add_end(list, anotherWord);
		strcpy(newWord, word);
		//free(anotherWord);
	}
	free(newWord);
	return list;
}

List *substitution(char *word, List *list) {

	int lengthWord = strlen(word);
	char *newWord = malloc((lengthWord + 1) * sizeof(*newWord));
	memset(newWord, '\0', lengthWord + 1);
	strcpy(newWord, word);

	char alphabets[27] = "abcdefghijklmnopqrstuvwxyz";
	int lengthAlphabets = strlen(alphabets);

	for(int i = 0; i < lengthWord; i++) {
		for(int j = 0; j < lengthAlphabets; j++) {
			newWord[i] = alphabets[j];
			//printf("%s\n",newWord);
			char *anotherWord = malloc((lengthWord + 1) * sizeof(*anotherWord));
			//memset(newWord, '\0', lengthWord + 1 + 1);
			strcpy(anotherWord, newWord);
			list_add_end(list, anotherWord);
			strcpy(newWord, word);

		}
	}
	free(newWord);
	return list;
}

List *insertion(char *word, List *list) {

	int lengthWord = strlen(word);
	char *newWord = malloc((lengthWord + 1) * sizeof(*newWord));
	memset(newWord, '\0', lengthWord + 1);
	int position = 0;
	strcpy(newWord, word);

	char alphabets[27] = "abcdefghijklmnopqrstuvwxyz";
	int lengthAlphabets = strlen(alphabets);

	for(int i = 0; i <= lengthWord; i++) {

		for(int j = lengthWord - 1 ; j >= position; j--) {
			newWord[j + 1] = newWord[j];
		}

		for(int k = 0; k < lengthAlphabets; k++) {
			newWord[position] = alphabets[k];
			//printf("%s\n", newWord);
			char *anotherWord = malloc((lengthWord + 1 + 1) * sizeof(*anotherWord));
			//memset(newWord, '\0', lengthWord + 1 + 1);
			strcpy(anotherWord, newWord);
			list_add_end(list, anotherWord);

		}
		strcpy(newWord, word);
		position++;
	}

	free(newWord);
	return list;
}

HashTable *initialise_Dictionary(HashTable *hashTable, List *dictionary) {

	int totalWordFrequency = 0;
	Node *node = dictionary->head;
	while(node != NULL) {
		char *dictionaryWord = (char *)node->data;

		if(hash_table_has(hashTable, dictionaryWord) == true) {

			totalWordFrequency = hash_table_get(hashTable, dictionaryWord);
			totalWordFrequency++;
			hash_table_put(hashTable, dictionaryWord, totalWordFrequency);
		} else {
			totalWordFrequency = 1;
			hash_table_put(hashTable, dictionaryWord, totalWordFrequency);
		}
		node = node->next;
	}
	return hashTable;
}

int levenstein_Distance(char *word1, char *word2) {

	int lengthWordOne = strlen(word1);
	int lengthWordTwo = strlen(word2);
	int substitute_cost = 0;
	int levenstein[lengthWordOne + 1][lengthWordTwo + 1];

	for (int i = 0; i <= lengthWordOne; i++) {
		levenstein[i][0] = i;
	}

	for (int j = 1; j <= lengthWordTwo; j++) {
		levenstein[0][j] = j;
	}
	for (int i = 1; i <= lengthWordOne; i++) {
		for (int j = 1; j <= lengthWordTwo; j++) {

			if(word1[i-1] == word2[j-1]) {
				substitute_cost = 0;
			}
			else {
				substitute_cost = 1;
			}

			int substitution =	levenstein [i - 1][j - 1];
			int deletion = levenstein [i - 1][j];
			int insertion = levenstein [i][j - 1];

			levenstein[i][j] = min_function((substitution + substitute_cost), (deletion + 1), (insertion + 1));
		}
	}
	return levenstein[lengthWordOne][lengthWordTwo];
}

int min_function(distance_value_One, distance_value_Two, distance_value_Three) {

	int temp = 0;
	int min = 0;

	if(distance_value_One < distance_value_Two) {
		temp = distance_value_One;
	} else {
		temp = distance_value_Two;
	}
	if(temp < distance_value_Three) {
		min = temp;
	} else {
		min = distance_value_Three;
	}

	return min;
}
