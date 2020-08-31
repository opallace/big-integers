#ifndef BN_H_INCLUDED
#define BN_H_INCLUDED

typedef struct {

	uint8_t *digits;
	uint8_t sign;
	int size;
	
}BIGNUM;

/*	Initializes the number values ​​and returns a big number pointer	
 *
 *  Input:
 *  Output: a big number pointer
 * 
 */
BIGNUM* init_bn();

/*	Converts a big number to an integer	
 *
 *  Input: a big number pointer
 *  Output: an integer
 * 
 */
int bn_to_int(BIGNUM *num);

/*	Converts an integer to a big number
 *
 *  Input: an integer
 *  Output: a big number pointer
 * 
 */
BIGNUM* int_to_bn(uintmax_t num);

/*	Calculates the bit size of a large number
 *
 *  Input: a big number
 *  Output: an integer containing the length in bits
 * 
 */
int bit_length_bn(BIGNUM *num);

/*	Copy a big number to another big number
 *
 *  Input: two big numbers pointer
 *  Output:
 * 
 */
void copy_bn(BIGNUM *a, BIGNUM *b);

/*	Reverse the order of the digits of the large number
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void rev_bn(BIGNUM *num);

/*	Removes zeros to the left of the large number
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void rmzero_bn(BIGNUM *num);

/*  Compares two large numbers
 *
 *  Input: two big numbers pointer
 *  Output:
 *			1 - if the first number is greater than the second
 *    		0 - if the two numbers are equal
 *   	   -1 - if the first number is less than the second
 * 
 */
int comp_bn(BIGNUM *num1, BIGNUM *num2);

/*	Returns the highest value
 *
 *  Input: two integers
 *  Output: the largest among the integers
 * 
 */
int max(int x, int y);

/*  Free a big number of memory
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void free_bn(BIGNUM *x);

/*  Free a big number matrix from memory
 *
 *  Input: a big number matrix pointer
 *  Output:
 * 
 */
void free_matrix_bn(BIGNUM *matrix, int size);

/*  Prints a big number
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void print_bn(BIGNUM *num);

/*  Prints a big number with line break
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void println_bn(BIGNUM *num);

/*  Generates a large random number between 0 and the specified value,
 *	[0, maximum value[.
 *
 *  Input: maximum value, a big number pointer
 *  Output:
 * 
 */
void random_bn(uintmax_t max_random_size, BIGNUM *result);

/*  Generates a large random number between the first and the second 
 *  large number specified, [lower limit, upper limit[.
 *
 *  Input: lower limit, upper limit, a big number pointer
 *  Output:
 * 
 */
void random_range_bn(BIGNUM *start, BIGNUM *end, BIGNUM *result);

/*  Adds two big numbers
 *
 *  Input: big number to be added, big number to be added, a big number pointer
 *  Output:
 * 
 */
void sum_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Subtracts two large numbers
 *
 *  Input: minuend in big number format, subtrahend in big number format, 
 *         a big number pointer
 *  Output:
 * 
 */
void sub_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Add zeros to the left to make the large number the specified size
 *
 *  Input: a big number pointer, integer number specifying the size that the big number will be
 *  Output:
 * 
 */
void fill(BIGNUM *x, int n);

/*  Split a big number between two positions
 *
 *  Input: a big number pointer, integer containing the starting position value, 
 *	       integer containing the final position value, a big number pointer
 *  Output:
 * 
 */
void split(BIGNUM *x, int start, int end, BIGNUM *result);

/*  Performs base 10 exponentiation quickly
 *
 *  Input: integer containing the exponent value, a big number pointer
 *  Output:
 * 
 */
void fastpow_base10_bn(int e, BIGNUM *result);

/*  Performs a multiplication of big numbers using the karatsuba algorithm
 *
 *  Input: two big numbers that will be multiplied, a big number pointer
 *  Output:
 * 
 */
void karatsuba(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Multiplies two big numbers
 *
 *  Input: two big numbers that will be multiplied, a big number pointer
 *  Output:
 * 
 */
void mul_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Divides two big numbers
 *
 *  Input: dividend in big number format, divisor in big number 
 *         format, a big number pointer
 *  Output:
 * 
 */
void div_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Performs the module operation between two large numbers
 *
 *  Input: dividend in big number format, divisor in big number 
 *         format, a big number pointer
 *  Output:
 * 
 */
void mod_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Calculates the inverse multiplicative module of two big numbers
 *
 *  Input: dividend in big number format, divisor in big number 
 *         format, a big number pointer
 *  Output:
 * 
 */
void mod_inverse_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

/*  Calculates the exponentiation of a big number
 *
 *  Input: base in large number format, exponent in 
 *         big number format, a big number pointer
 *  Output:
 * 
 */
void pow_bn(BIGNUM *bb, BIGNUM *ee, BIGNUM *result);

/*  Calculates the exponentiation of a big number
 *
 *  Input: base in large number format, exponent in 
 *         big number format, a big number pointer
 *  Output:
 * 
 */
void pow_mod_bn(BIGNUM *bb, BIGNUM *ee, BIGNUM *mm, BIGNUM *result);

/*  Calculates the greatest common divisor between two large 
 *  numbers
 *
 *  Input: two big number pointers to calculate the mdc between 
 *         them, a big number pointer
 *  Output:
 * 
 */
void mdc_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

#endif
