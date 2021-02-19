/* * * * * * * * * * *
 * Module providing xor hash functions for strings
 *
 * created for COMP20007 Design of Algorithms
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 *
 * Only hash function xor is kept in this file
 * All other functions are removed
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "strhash.h"

// xor hash from lectures, with seed 73802
unsigned int seed = 73802;
unsigned int xor_hash(const char *key, unsigned int size) {
	unsigned int h = seed;

	int i;
	for (i = 0; key[i] != '\0'; i++) {
		h = h ^ ((h << 5) + key[i] + (h >> 2));
	}

	return h % size;
}
