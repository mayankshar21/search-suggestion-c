/* * * * * * * * * * *
 * Module providing xor hash functions for strings
 *
 * created for COMP20007 Design of Algorithms
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 *
 * Only hash function xor is kept in this file
 * All other functions are removed
 */


// generate a hash value for key (a string) to a hash table of size entries,
// using hash method 'xor'
// guarantees a return value between 0 (inclusive) and size (non inclusive)
// xor hash from lectures, with seed 73802
unsigned int xor_hash(const char *key, unsigned int size);
