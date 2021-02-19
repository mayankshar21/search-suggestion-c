/* ... */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spell.h"
#include "hashtbl.h"

/* * *
 * HELPER FUNCTIONS DECLARATION
 */

List *generate_words(char *word, List *list);

HashTable *initialise_dictionary(HashTable *hashTable, List *dictionary);

int levenshtein_distance(char *word1, char *word2);

int min_function(int integer1, int integer2, int integer3);

List *deletion(char *word, List *list);

List *substitution(char *word, List *list);

List *insertion(char *word, List *list);

/* * *
 * ASSIGNMENT TASKS
 */

// Assignment Task 1: Computing edit distance
void print_edit_distance(char *word1, char *word2) {
	//Initialise edit distance value to zero
	int distance = 0;
	/* Calculate the edit distance using
	 * levenstein_distance helper function
	 */
	distance = levenshtein_distance(word1, word2);
	// Print out the edit distance
	printf("%d\n", distance);
}

// Assignment Task 2: Enumerating all possible edits
void print_all_edits(char *word) {

	// Create a new list
	List *list = new_list();
	/* Generate words of edit distance one
	 * and add to the list
	 */
	list = generate_words(word, list);

	// Run a for loop using node and traverse through the list
	for(Node *node = list->head; node; node = node->next) {
		// Print out the generated words from the list
		printf("%s\n", (char *)node->data);

	}

	// Run a for loop using node1 and traverse through the list
	for(Node *node1 = list->head; node1; node1 = node1->next) {
		/* Free all the pointers to the generated words
		 * in the linked list
		 */
		free(node1->data);

	}
	// Free the list
	free_list(list);
}

// Assignment Task 3: Spell checking
void print_checked(List *dictionary, List *document) {
	// Initialise the hashtable size to zero
	int hashSize = 0;

	// Run a for loop using node and traverse through the dictionary
	for(Node *node = dictionary->head; node; node = node->next) {
		/* Increase the hashtable size
		 * as the loop traverses through each node
		 */
		hashSize++;
	}

	/* Create a hashtable with the hashtable size hashSize
	 * calculated in the previous loop
	 */
	HashTable *hashTable = new_hash_table(hashSize);
	// Add the words of the dictionary list to the hashtable
	hashTable = initialise_dictionary(hashTable, dictionary);

	// Run a loop using node1 and traverse through the document
	for(Node *node1 = document->head; node1; node1 = node1->next) {
		char *documentWord = (char *)node1->data;

		// Search the already corrected words in the hashtable if it exists
		if(hash_table_has(hashTable, documentWord) == true) {
			// If it exists, print the documentWord
			printf("%s\n", documentWord);
		}
		else {
			// Else print it with documentWord
			printf("%s?\n", documentWord);
		}
	}

	// Free the hashtable
	free_hash_table(hashTable);
}

// Assignment Task 4: Spelling correction
void print_corrected(List *dictionary, List *document) {
	// Initialise the hashtable size to zero
	int hashSize = 0;

	// Run a for loop using node and traverse through the dictionary
	for(Node *node = dictionary->head; node; node = node->next) {
		/* Increase the hashtable size
		 * as the loop traverses through each node
		 */
		hashSize++;
	}

	/* Create a hashtable with the hashtable size hashSize
	 * calculated in the previous loop
	 */
	HashTable *hashTable = new_hash_table(hashSize);
	// Add the words of the dictionary list to the hashtable
	hashTable = initialise_dictionary(hashTable, dictionary);

	// Run a loop using node1 and traverse through the document
	for(Node *node1 = document->head; node1; node1 = node1->next) {
		char *word1 = (char *)node1->data;

		// Initialise three words for storage of words with different edit distances
		char *anotherWordOne = NULL;
		char *anotherWordTwo = NULL;
		char *anotherWordThree = NULL;

		// Initialise three variables to store the edit distances
		int distanceValueOne = 6;
		int distanceValueTwo = 6;
		int distanceValueThree = 6;

		// Search the already corrected words in the hashtable if it exists
		if(hash_table_has(hashTable, word1) == true) {
			// If it exists, print the documentWord
			printf("%s\n", word1);
		}
		else {
			// Else run a for loop using node2 and traverse through the dictionary list
			for(Node *node2 = dictionary->head; node2; node2 = node2->next) {
				char *word2 = (char *)node2->data;
				// Measure the length of the word2
				int lengthWord = strlen(word2);
				// Initialise edit distance with zero
				int distance = 0;

				// Evaluate the edit distance for word1 and word2
				distance = levenshtein_distance(word1, word2);

				// if distance is one, store correct word2 in anotherWordOne
				if(distance == 1 && distanceValueOne != 1) {
					anotherWordOne = malloc((lengthWord + 1)*sizeof(*anotherWordOne));
					strcpy(anotherWordOne, word2);
					distanceValueOne = 1;
				}

				// If distance is two, store correct word2 in anotherWordTwo
				if(distance == 2 && distanceValueTwo != 2) {
					anotherWordTwo = malloc((lengthWord + 1)*sizeof(*anotherWordTwo));
					strcpy(anotherWordTwo, word2);
					distanceValueTwo = 2;
				}

				// If distance is three, store correct word2 in anotherWordThree
				if(distance == 3 && distanceValueThree != 3) {
					anotherWordThree = malloc((lengthWord + 1)*sizeof(*anotherWordThree));
					strcpy(anotherWordThree, word2);
					distanceValueThree = 3;
				}
			}

			// Find the minimum edit distance out of the three
			int minimumDistance = min_function(distanceValueOne, distanceValueTwo, distanceValueThree);

			// Print the least minimum distance out of the three
			if(minimumDistance == 1) {
				printf("%s\n", anotherWordOne);
			} else if(minimumDistance == 2) {
				printf("%s\n", anotherWordTwo);
			} else if(minimumDistance == 3) {
				printf("%s\n", anotherWordThree);
			} else {
				printf("%s?\n", word1);
			}
		}

		// Free anotherWordOne, anotherWordTwo, anotherWordThree
		free(anotherWordOne);
		free(anotherWordTwo);
		free(anotherWordThree);
	}

	// Free hashtable
	free_hash_table(hashTable);
}

// Function to generate all combinations of words of edit distance one
List *generate_words(char *word, List *list) {

	/* Delete one character and store
	 * all possible combinations in the list
	 */
	list = deletion(word, list);

	/* Substitute one character and store
	 * all possible combinations in the list
	 */
	list = substitution(word, list);

	/* insertion one character and store
	 * all possible combinations in the list
	 */
	list = insertion(word, list);

	// return the list
	return list;
}

/* * *
 * HELPER FUNCTIONS DEFINATION
 */

// Function to initialise the hashtable dictionary
HashTable *initialise_dictionary(HashTable *hashTable, List *dictionary) {

	// Initialise word frequency with zero
	int totalWordFrequency = 0;

	// Run a for loop and traverse through the dictionary list
	for(Node *node = dictionary->head; node; node = node->next) {
		// Store the word in node->data to dictionaryWord char array (string)
		char *dictionaryWord = (char *)node->data;

		// Search for the word if exists in the hashtable
		if(hash_table_has(hashTable, dictionaryWord) == true) {

			/* If true, get the frequency of the word and update
			 * the new frequency of the word
			 * Put the word in the hashtable
			 */
			totalWordFrequency = hash_table_get(hashTable, dictionaryWord);
			totalWordFrequency++;
			hash_table_put(hashTable, dictionaryWord, totalWordFrequency);
		} else {
			// Else assign the frequency as one and put the word into the hashtable
			totalWordFrequency = 1;
			hash_table_put(hashTable, dictionaryWord, totalWordFrequency);
		}
	}
	// Return the hashtable
	return hashTable;
}

/* * *
 * Function to generate levenshtein edit distance of one
 * Algorithm for levenshtein edit distance taken from week 7 workshop solution
 * Algorithm created for COMP20007 Design of Algorithms
 * Code written by Mayank Sharma <mayanks1@student.unimelb.edu.au>
 */
int levenshtein_distance(char *word1, char *word2) {

	// Find edit distance of word1 and word2
	int lengthWordOne = strlen(word1);
	int lengthWordTwo = strlen(word2);
	// Assign substitute_cost to zero
	int substitute_cost = 0;
	// Declaring levenshtein distance array
	int levenshtein[lengthWordOne + 1][lengthWordTwo + 1];
	// Run a for loop to fill the first column
	for (int i = 0; i <= lengthWordOne; i++) {
		levenshtein[i][0] = i;
	}
	// Run a for loop to fill the first row
	for (int j = 1; j <= lengthWordTwo; j++) {
		levenshtein[0][j] = j;
	}
	// Run two nested loops to calculate the levenshtein distance
	for (int i = 1; i <= lengthWordOne; i++) {
		for (int j = 1; j <= lengthWordTwo; j++) {

			if(word1[i-1] == word2[j-1]) {
				substitute_cost = 0;
			}
			else {
				substitute_cost = 1;
			}

			int substitution =	levenshtein [i - 1][j - 1];
			int deletion = levenshtein [i - 1][j];
			int insertion = levenshtein [i][j - 1];

			// Find the minimum of substitution, deletion and insertion
			levenshtein[i][j] = min_function((substitution + substitute_cost), (deletion + 1), (insertion + 1));
		}
	}
	// Return the levenshtein distance of the last index
	return levenshtein[lengthWordOne][lengthWordTwo];
}

// Minimum function to find minimum of three integers
int min_function(int integer1, int integer2, int integer3) {

	int temp = 0;
	int min = 0;

	// Find minimum of interger1 and integer2
	if(integer1 < integer2) {
		temp = integer1;
	} else {
		temp = integer2;
	}

	/* Find minimum of integer3 and temporary variable
	 * from previous if condition
	 */
	if(temp < integer3) {
		min = temp;
	} else {
		min = integer3;
	}
	// Return min
	return min;
}

// Function to create generate words with one character deleted
List *deletion(char *word, List *list) {

 	int lengthWord = strlen(word);
	char *newWord = malloc((lengthWord + 1) * sizeof(*newWord));
	// String function from C library
	memset(newWord, '\0', lengthWord + 1); // Set the string with '\0'
	strcpy(newWord, word);

	// Run a for loop to delete one character
	for(int i = 0; i < lengthWord; i++) {
		// String function from C library
		// Moves one character in the previous position
		memmove(&newWord[i],&newWord[i + 1], lengthWord - i);
		char *anotherWord = malloc((lengthWord + 1) * sizeof(*anotherWord));
		// Copy the word into another variable and add to list
		strcpy(anotherWord, newWord);
		list_add_end(list, anotherWord);
		strcpy(newWord, word);

	}
	// Free the newWord
	free(newWord);
	// Return the list
	return list;
}

// Function to create generate words with one character substituted
List *substitution(char *word, List *list) {

	int lengthWord = strlen(word);
	char *newWord = malloc((lengthWord + 1) * sizeof(*newWord));
	// String function from C library
	memset(newWord, '\0', lengthWord + 1); // Set the string with '\0'
	strcpy(newWord, word);

	// Store all the alphabets as a single string
	char alphabets[27] = "abcdefghijklmnopqrstuvwxyz\0";
	int lengthAlphabets = strlen(alphabets);

	// Run nested for loop to substitute one character
	for(int i = 0; i < lengthWord; i++) {
		for(int j = 0; j < lengthAlphabets; j++) {
			// substitute a word in the string
			newWord[i] = alphabets[j];
			char *anotherWord = malloc((lengthWord + 1) * sizeof(*anotherWord));
			// Copy the word into another variable and add to list
			strcpy(anotherWord, newWord);
			list_add_end(list, anotherWord);
			strcpy(newWord, word);

		}
	}
	// Free the newWord
	free(newWord);
	// Return the list
	return list;
}

// Function to create generate words with one character inserted
List *insertion(char *word, List *list) {

	int lengthWord = strlen(word);
	char *newWord = malloc((lengthWord + 1 + 1) * sizeof(*newWord));
	// String function from C library
	memset(newWord, '\0', lengthWord + 2); // Set the string with '\0'
	int position = 0; // Initialise position to zero
	strcpy(newWord, word);

	// Store all the alphabets as a single string
	char alphabets[27] = "abcdefghijklmnopqrstuvwxyz\0";
	int lengthAlphabets = strlen(alphabets);

	// Run nested for loop to insert one character
	for(int i = 0; i <= lengthWord; i++) {
		for(int j = lengthWord - 1 ; j >= position; j--) {
			newWord[j + 1] = newWord[j];
		}

		for(int k = 0; k < lengthAlphabets; k++) {
			newWord[position] = alphabets[k];
			char *anotherWord = malloc((lengthWord + 1 + 1) * sizeof(*anotherWord));
			// Copy the word into another variable and add to list
			strcpy(anotherWord, newWord);
			list_add_end(list, anotherWord);
		}
		strcpy(newWord, word);

		position++; // Increment position
	}

	// Free the newWord
	free(newWord);
	// Return the list
	return list;
}
