#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bn.h"

/*	Initializes the number values ​​and returns a big number pointer	
 *
 *  Input:
 *  Output: a big number pointer
 * 
 */
BIGNUM* init_bn(){
	
	BIGNUM *num = malloc(sizeof(BIGNUM));
	num->digits = NULL;
	num->size   = 0;
	num->sign   = 1;

	return num;

}

/*	Converts a big number to an integer	
 *
 *  Input: a big number pointer
 *  Output: an integer
 * 
 */
int bn_to_int(BIGNUM *nnum){
	
	int result = 0;
	
	BIGNUM *num = init_bn();
	copy_bn(num, nnum);
	
	rev_bn(num);
	for(int i = 0, e = 1; i < num->size; i++, e*=10){
		result += num->digits[i] * e;
	}
	
	if(num->sign == 0){
		result *= -1;
	}

	return result;
}

/*	Converts an integer to a big number
 *
 *  Input: an integer
 *  Output: a big number pointer
 * 
 */
BIGNUM* int_to_bn(uintmax_t num){
	
	BIGNUM *bignum = init_bn();

	if(num < 0){
		bignum->sign = 0;
		num *= -1;
	}else {
		bignum->sign = 1;
	}
	
	do{
		bignum->digits = realloc(bignum->digits, ++bignum->size);
		bignum->digits[bignum->size - 1] = num % 10;
		num /= 10;
	
	}while(num != 0);

	rev_bn(bignum);
	return bignum;
	
}

/*	Calculates the bit size of a large number
 *
 *  Input: a big number
 *  Output: an integer containing the length in bits
 * 
 */
int bit_length_bn(BIGNUM *xx){

	int result = 0;

	BIGNUM *zero = int_to_bn(0);
	BIGNUM *two  = int_to_bn(2);

	BIGNUM *x = init_bn();
	copy_bn(x , xx);

	while(comp_bn(x, zero) != 0){
		BIGNUM *div = init_bn();
		div_bn(x, two, div);

		result++;
		copy_bn(x, div);

		free_bn(div);
	}

	return result;
}

/*	Copy a big number to another big number
 *
 *  Input: two big numbers pointer
 *  Output:
 * 
 */
void copy_bn(BIGNUM *a, BIGNUM *b){
	a->size = b->size;
	a->sign = b->sign;
	
	free(a->digits);
	a->digits = malloc(a->size);
	for(int i = 0; i < a->size; i++){
		a->digits[i] = b->digits[i];
	}
}

/*	Reverse the order of the digits of the large number
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void rev_bn(BIGNUM *num){
	for(int i = 0, j = num->size - 1; i < num->size/2-0.5; i++, j--){
		int aux = num->digits[i];
		num->digits[i] = num->digits[j];
		num->digits[j] = aux;
	}
}

/*	Removes zeros to the left of the large number
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void rmzero_bn(BIGNUM *num){
	while(num->digits[0] == 0 && num->size > 1){
		for(int i = 0; i < num->size - 1; i++){
			num->digits[i] = num->digits[i+1];
		}

		num->digits = realloc(num->digits, --num->size);
	}
}

/*  Compares two large numbers
 *
 *  Input: two big numbers pointer
 *  Output:
 *			1 - if the first number is greater than the second
 *    		0 - if the two numbers are equal
 *   	   -1 - if the first number is less than the second
 * 
 */
int comp_bn(BIGNUM *num1, BIGNUM *num2){
	if(num1->size > num2->size){
		return 1;
	}else if(num2->size > num1->size){
		return -1;
	}else {

		for(int i = 0; i < num1->size; i++){
			if(num1->digits[i] > num2->digits[i]){
				return 1;
				break;
		
			}else if(num1->digits[i] < num2->digits[i]){
				return -1;
				break;
			}
		}	

		return 0;	
	}
}

/*	Returns the highest value
 *
 *  Input: two integers
 *  Output: the largest among the integers
 * 
 */
int max(int x, int y){
	if(x >= y){
		return x;
	}

	return y;
}

/*  Free a big number of memory
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void free_bn(BIGNUM *x){
	free(x->digits);
	free(x);
}

/*  Free a big number matrix from memory
 *
 *  Input: a big number matrix pointer
 *  Output:
 * 
 */
void free_matrix_bn(BIGNUM *matrix, int size){
	for(int i = 0; i < size; i++){
		free(matrix[i].digits);
	}

	free(matrix);
}

/*  Prints a big number
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void print_bn(BIGNUM *num){
	if(num->sign){
		printf("+");
	
	}else {
		printf("-");
	
	}

	for(int i = 0; i < num->size; i++){
		printf("%i", num->digits[i]);
	}
}

/*  Prints a big number with line break
 *
 *  Input: a big number pointer
 *  Output:
 * 
 */
void println_bn(BIGNUM *num){
	if(num->sign){
		printf("+");
	
	}else {
		printf("-");
	
	}

	for(int i = 0; i < num->size; i++){
		printf("%i", num->digits[i]);
	}

	printf("\n");
}

/*  Generates a large random number between 0 and the specified value,
 *	[0, maximum value[.
 *
 *  Input: maximum value, a big number pointer
 *  Output:
 * 
 */
void random_bn(uintmax_t max_random_size, BIGNUM *result){
	
	int size = rand() % max_random_size + 1;
	
	BIGNUM *result_temp = malloc(sizeof(BIGNUM));
	result_temp->digits = malloc(size);
	result_temp->size = size;
	result_temp->sign = 1;

	for(int i = 0; i < size; i++){
		result_temp->digits[i] = rand() % 10;
	}

	copy_bn(result, result_temp);
	free_bn(result_temp);
}

/*  Generates a large random number between the first and the second 
 *  large number specified, [lower limit, upper limit[.
 *
 *  Input: lower limit, upper limit, a big number pointer
 *  Output:
 * 
 */
void random_range_bn(BIGNUM *start, BIGNUM *end, BIGNUM *result){
	BIGNUM *sub = init_bn();
	sub_bn(end, start, sub);
	
	BIGNUM *rand = init_bn();
	random_bn(sub->size + 1, rand);

	BIGNUM *mod  = init_bn();
	mod_bn(rand, sub, mod);
	
	BIGNUM *result_temp = init_bn();
	sum_bn(mod, start, result_temp);

	copy_bn(result, result_temp);

	free_bn(sub);
	free_bn(rand);
	free_bn(mod);
	free_bn(result_temp);
}

/*  Adds two big numbers
 *
 *  Input: big number to be added, big number to be added, a big number pointer
 *  Output:
 * 
 */
void sum_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	BIGNUM *x = init_bn();
	BIGNUM *y = init_bn();

	copy_bn(x, xx);
	copy_bn(y, yy);

	if(x->sign != y->sign){
		if(x->sign == 1){
			y->sign = 1;
			sub_bn(x, y, result);
		
		}else {
			x->sign = 1;
			sub_bn(y, x, result);
		}
	

	}else if(comp_bn(y, x) == 1){
		
		sum_bn(y, x, result);

	}else{
	
		BIGNUM *aux = init_bn();
		aux->sign = x->sign;
		
		int r = 0;

		for(int i = x->size - 1, j = y->size - 1; i >= 0; i--, j--){
			aux->digits = realloc(aux->digits, ++aux->size);

			if(j < 0){
				r += x->digits[i];
			}else {
				r += x->digits[i] + y->digits[j];
			}

			aux->digits[aux->size - 1] = r % 10;
			r /= 10;

		}
		
		if(r != 0){
			aux->digits = realloc(aux->digits, ++aux->size);
			aux->digits[aux->size - 1] = r;
		}

		rev_bn(aux);
		rmzero_bn(aux);

		copy_bn(result, aux);
		
		free_bn(aux);
	}

	free_bn(x);
	free_bn(y);
}

/*  Subtracts two large numbers
 *
 *  Input: minuend in big number format, subtrahend in big number format, 
 *         a big number pointer
 *  Output:
 * 
 */
void sub_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	BIGNUM *x = init_bn();
	BIGNUM *y = init_bn();

	copy_bn(x, xx);
	copy_bn(y, yy);

	if(x->sign != y->sign){
		if(x->sign == 1){
			y->sign = 1;
			sum_bn(x, y, result);
		
		}else {
			y->sign = 0;
			sum_bn(x, y, result);
		
		}

	}else if(comp_bn(y, x) == 1){
	
		sub_bn(y, x, result);
		
		if(result->sign == 1){
			result->sign = 0;
		
		}else {
			result->sign = 1;
		
		}

	}else {

		BIGNUM *aux = init_bn();
		aux->sign   = x->sign;

		for(int i = x->size - 1, j = y->size - 1; i >= 0; i--, j--){
			aux->digits = realloc(aux->digits, ++aux->size);	
			
			if(j < 0){
			
				aux->digits[aux->size - 1] = x->digits[i];

			}else {
			
				if(x->digits[i] - y->digits[j] < 0){
					aux->digits[aux->size - 1] = (x->digits[i]+10) - y->digits[j];

					for(int k = i - 1; k >= 0; k--){
						if(x->digits[k] == 0){
							x->digits[k] = 9;
						}else {
							x->digits[k]--;
							break;
						}
					}		
				}else {
					aux->digits[aux->size - 1] = x->digits[i] - y->digits[j];
				}
			}
		}
	

		rev_bn(aux);
		rmzero_bn(aux);

		copy_bn(result, aux);
		
		free_bn(aux);
	}

	free_bn(x);
	free_bn(y);
}

/*  Add zeros to the left to make the large number the specified size
 *
 *  Input: a big number pointer, integer number specifying the size that the big number will be
 *  Output:
 * 
 */
void fill(BIGNUM *x, int n){
	if (x->size < n){
		BIGNUM *result = init_bn();

		for (int i = 0; i < (n - x->size); i++){
			result->digits = realloc(result->digits, ++result->size);
			result->digits[result->size - 1] = 0;
		}

		for (int i = 0; i < x->size; i++){
			result->digits = realloc(result->digits, ++result->size);
			result->digits[result->size - 1] = x->digits[i];
		}

		copy_bn(x, result);
		free_bn(result);

	}

}

/*  Split a big number between two positions
 *
 *  Input: a big number pointer, integer containing the starting position value, 
 *	       integer containing the final position value, a big number pointer
 *  Output:
 * 
 */
void split(BIGNUM *x, int start, int end, BIGNUM *result){

	BIGNUM *result_temp = init_bn();

	for (int i = start; i < end; i++){
		result_temp->digits = realloc(result_temp->digits, ++result_temp->size);
		result_temp->digits[result_temp->size - 1] = x->digits[i];
	}

	copy_bn(result, result_temp);
	free_bn(result_temp);
}

/*  Performs base 10 exponentiation quickly
 *
 *  Input: integer containing the exponent value, a big number pointer
 *  Output:
 * 
 */
void fastpow_base10_bn(int e, BIGNUM *result){

	BIGNUM *one  = int_to_bn(1);
	BIGNUM *result_temp = int_to_bn(1);

	for (int i = 0; i < e; i++){
		result_temp->digits = realloc(result_temp->digits, ++result_temp->size);
		result_temp->digits[result_temp->size - 1] = 0;
	}

	copy_bn(result, result_temp);

	free_bn(one);
	free_bn(result_temp);
}

/*  Performs a multiplication of big numbers using the karatsuba algorithm
 *
 *  Input: two big numbers that will be multiplied, a big number pointer
 *  Output:
 * 
 */
void karatsuba(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){

	if(xx->size < 130 && yy->size < 130){

		mul_bn(xx, yy, result);

	}else{

		BIGNUM *x = init_bn();
		BIGNUM *y = init_bn();

		copy_bn(x, xx);
		copy_bn(y, yy);

		int n = max(x->size, y->size);
		int m = (float)(n + 1) / 2;

		BIGNUM *xH = init_bn();
		BIGNUM *xL = init_bn();
		BIGNUM *yH = init_bn();
		BIGNUM *yL = init_bn();

		fill(x, n);
		fill(y, n);

		split(x, 0, m, xH);
		split(x, m, n, xL);
		split(y, 0, m, yH);
		split(y, m, n, yL);

		BIGNUM *S1 = init_bn();
		BIGNUM *S2 = init_bn();
		BIGNUM *S3 = init_bn();
		BIGNUM *S4 = init_bn();

		karatsuba(xH, yH, S1);
		karatsuba(xL, yL, S2);

		BIGNUM *sum1 = init_bn();
		BIGNUM *sum2 = init_bn();

		sum_bn(xH, xL, sum1);
		sum_bn(yH, yL, sum2);

		karatsuba(sum1, sum2, S3);

		sub_bn(S3, S2, S4);
		sub_bn(S4, S1, S4);

		/*return*/
			BIGNUM *pow1 = init_bn();
			BIGNUM *pow2 = init_bn();

			fastpow_base10_bn(n, pow1);
			fastpow_base10_bn(m, pow2);

			BIGNUM *mul1 = init_bn();
			BIGNUM *mul2 = init_bn();

			mul_bn(S1, pow1, mul1);
			mul_bn(S4, pow2, mul2);

			BIGNUM *sum3 = init_bn();

			sum_bn(mul1, mul2, sum3);
			sum_bn(S2, sum3, sum3);

			copy_bn(result, sum3);

	}
}

/*  Multiplies two big numbers
 *
 *  Input: two big numbers that will be multiplied, a big number pointer
 *  Output:
 * 
 */
void mul_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	BIGNUM *x = init_bn();
	BIGNUM *y = init_bn();

	copy_bn(x, xx);
	copy_bn(y, yy);

	if(y->size > x->size){
		mul_bn(y, x, result);

	}else {

		BIGNUM *results = NULL;
		int num_results = 0;
		
		BIGNUM *zero = int_to_bn(0);
		copy_bn(result, zero);

		for(int i = y->size - 1, k = 0; i >= 0; i--, k++){
			results = realloc(results, ++num_results * sizeof(BIGNUM));
			results[num_results-1].digits = NULL;
			results[num_results-1].size = 0;
			results[num_results-1].sign = 1;
		
			for(int j = 0; j < k; j++){
				results[num_results-1].digits = realloc(results[num_results-1].digits, ++results[num_results-1].size);
				results[num_results-1].digits[results[num_results-1].size-1] = 0;
			}
		
			int aux = 0;

			for(int j = x->size - 1; j >= 0; j--){
				results[num_results-1].digits = realloc(results[num_results-1].digits, ++results[num_results-1].size);
				aux += y->digits[i] * x->digits[j];
				results[num_results-1].digits[results[num_results-1].size-1] = aux%10;
				aux /= 10;
			}
		
			if(aux != 0){
				results[num_results-1].digits = realloc(results[num_results-1].digits, ++results[num_results-1].size);
				results[num_results-1].digits[results[num_results-1].size-1] = aux;
			}
		
			rev_bn(&results[num_results - 1]);	
			sum_bn(result, &results[num_results - 1], result);
		}
		
		if(x->sign == y->sign){
			result->sign = 1;
		}else {
			result->sign = 0;
		}
			
		rmzero_bn(result);

		free_bn(zero);
		free_matrix_bn(results, num_results);
	}

	free_bn(x);
	free_bn(y);
}

/*  Divides two big numbers
 *
 *  Input: dividend in big number format, divisor in big number 
 *         format, a big number pointer
 *  Output:
 * 
 */
void div_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	BIGNUM *x = init_bn();
	BIGNUM *y = init_bn();

	copy_bn(x, xx);
	copy_bn(y, yy);

	BIGNUM *result_temp = init_bn();

	if(comp_bn(y, x) == 1){
		BIGNUM *zero = int_to_bn(0);
		copy_bn(result, zero);
		
		free_bn(zero);
	
	}else {
		
		if(x->sign == y->sign){
	
			result_temp->sign = 1;
		}else {
	
			result_temp->sign = 0;
	
		}

		BIGNUM *aux = int_to_bn(0);

		for(int i = 0; i < x->size; i++){
		
			aux->digits = realloc(aux->digits, ++aux->size);
			aux->digits[aux->size - 1] = x->digits[i];
			rmzero_bn(aux);

			if(comp_bn(aux, y) != -1){		
				int qaux = 0;
				while(comp_bn(aux, y) != -1){
					qaux++;
				
					BIGNUM *sub = init_bn();
					sub_bn(aux, y, sub);
					copy_bn(aux, sub);
					
					free_bn(sub);
				}	
		
				result_temp->digits = realloc(result_temp->digits, ++result_temp->size);
				result_temp->digits[result_temp->size - 1] = qaux;
                             
			}else {
				
				result_temp->digits = realloc(result_temp->digits, ++result_temp->size);
				result_temp->digits[result_temp->size - 1] = 0;

			}
		}	
	
		rmzero_bn(result_temp);
		copy_bn(result, result_temp);
		
		free_bn(aux);
	}

	free_bn(x);
	free_bn(y);
	free_bn(result_temp);
}

/*  Performs the module operation between two large numbers
 *
 *  Input: dividend in big number format, divisor in big number 
 *         format, a big number pointer
 *  Output:
 * 
 */
void mod_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	BIGNUM *x = init_bn();
	BIGNUM *y = init_bn();

	copy_bn(x, xx);
	copy_bn(y, yy);

	if(comp_bn(y, x) == 1){
		copy_bn(result, x);

	}else {
		BIGNUM *aux = init_bn();

		for(int i = 0; i < x->size; i++){
			aux->digits = realloc(aux->digits, ++aux->size);
			aux->digits[aux->size - 1] = x->digits[i];
			
			rmzero_bn(aux);
	
			if(comp_bn(aux, y) != -1){
			
				int qaux = 0;
				while(comp_bn(aux, y) != -1){
					qaux++;
	
					BIGNUM *sub = init_bn();
					sub_bn(aux, y, sub);

					copy_bn(aux, sub);
					free_bn(sub);	
				}
			}
		}

		copy_bn(result, aux);
		
		free_bn(aux);
	}

	free_bn(x);
	free_bn(y);
}

/*  Calculates the inverse multiplicative module of two big numbers 
 *	with the extended euclidean algorithm
 *
 *  Input: dividend in big number format, divisor in big number 
 *         format, a big number pointer
 *  Output:
 * 
 *	Pseudocode:
 *
 */
void mod_inverse_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	
	BIGNUM *s     = int_to_bn(0);
	BIGNUM *old_s = int_to_bn(1);

	BIGNUM *t     = int_to_bn(1);
	BIGNUM *old_t = int_to_bn(0);

	BIGNUM *r     = init_bn();
	BIGNUM *old_r = init_bn();

	copy_bn(r, yy);
	copy_bn(old_r, xx);
	
	BIGNUM *zero = int_to_bn(0);

	while(comp_bn(r, zero) != 0){
	
		BIGNUM *quotient = init_bn();
		div_bn(old_r, r, quotient);

		BIGNUM *temp = init_bn();
		copy_bn(temp, r);
		
		BIGNUM *m1 = init_bn();
		mul_bn(quotient, r, m1);

		sub_bn(old_r, m1, r);
		copy_bn(old_r, temp);

		copy_bn(temp, s);
	
		mul_bn(quotient, s, m1);
		sub_bn(old_s, m1, s);
		copy_bn(old_s, temp);

		copy_bn(temp, t);
		mul_bn(quotient, t, m1);
		sub_bn(old_t, m1, t);
		copy_bn(t, temp);

		free_bn(quotient);
		free_bn(temp);
		free_bn(m1);
	}

	if(old_s->sign == 0){
		BIGNUM *s1 = init_bn(); 
		sum_bn(old_s, yy, s1);

		copy_bn(result, s1);
		free_bn(s1);

	}else {
		copy_bn(result, old_s);

	}

	free_bn(s);
	free_bn(old_s);
	free_bn(t);
	free_bn(old_t);
	free_bn(r);
	free_bn(old_r);
	free_bn(zero);
}

/*  Calculates the exponentiation of a big number
 *
 *  Input: base in large number format, exponent in 
 *         big number format, a big number pointer
 *  Output:
 * 
 *	Pseudocode:
 *			if expoent = 0: 
 *				return  1;
 *
 *			else if expoent = 1: 
 *				return base;
 *
 *			else if expoent is even: 
 *				return pow(base * base,  expoent / 2);
 *
 *			else if expoent is odd: 
 *				return base * pow(base * base, (expoent - 1) / 2);
 *
 */
void pow_bn(BIGNUM *bb, BIGNUM *ee, BIGNUM *result){
	BIGNUM *b = init_bn();
	BIGNUM *e = init_bn();

	copy_bn(b, bb);
	copy_bn(e, ee);

	BIGNUM *zero = int_to_bn(0);
	BIGNUM *one  = int_to_bn(1);
	BIGNUM *two  = int_to_bn(2);
	
	BIGNUM *mod = init_bn();
	mod_bn(e, two, mod);

	if(comp_bn(e, zero) == 0){
		
		copy_bn(result, one);
	
	}else if(comp_bn(e, one) == 0){

		copy_bn(result, b);
	
	}else if(comp_bn(mod, zero) == 0){
		
		BIGNUM *div = init_bn();
		div_bn(e, two, div);
		
		BIGNUM *mul = init_bn();
		mul_bn(b, b, mul);

		pow_bn(mul, div, result);

		free_bn(div);
		free_bn(mul);

	}else {
		
		BIGNUM *sub = init_bn();
		sub_bn(e, one, sub);

		BIGNUM *div = init_bn();
		div_bn(sub, two, div);

		BIGNUM *mul = init_bn();
		mul_bn(b, b, mul);

		BIGNUM *pow = init_bn();
		pow_bn(mul, div, pow);

		mul_bn(b, pow, result);

		free_bn(sub);
		free_bn(div);
		free_bn(mul);
		free_bn(pow);
	}

	free_bn(b);
	free_bn(e);
	free_bn(zero);
	free_bn(one);
	free_bn(two);
	free_bn(mod);
}

/*  Calculates the exponentiation of a big number
 *
 *  Input: base in large number format, exponent in 
 *         big number format, a big number pointer
 *  Output:
 *
 *	Pseudocode: 
 *		 	result = 1    
 *
 * 			base %= m 
 *			      
 *			if (base == 0): 
 *			    return 0
 * 			  
 *			while (expoent > 0): 
 *			    if ((expoent & 1) == 1): 
 *			    	result = (result * base) % module
 *			      
 *			    expoent /= 2  
 *			    base = (base * base) % module
 *			          
 *			return result
 * 
 */
void pow_mod_bn(BIGNUM *bb, BIGNUM *ee, BIGNUM *mm, BIGNUM *result){
	BIGNUM *b = init_bn();
	BIGNUM *e = init_bn();
	BIGNUM *m = init_bn();

	copy_bn(b, bb);
	copy_bn(e, ee);
	copy_bn(m, mm);

	BIGNUM *r = int_to_bn(1);

	BIGNUM *zero = int_to_bn(0);
	BIGNUM *one  = int_to_bn(1);
	BIGNUM *two  = int_to_bn(2);

	BIGNUM *mod = init_bn();
	mod_bn(b, m, mod);
	copy_bn(b, mod);
	free_bn(mod);

	while(comp_bn(e, zero) == 1){
		if(e->digits[e->size - 1] & 1 == 1){
			
			BIGNUM *mul = init_bn(); 
			mul_bn(r, b, mul);
			
			BIGNUM *mod = init_bn();
			mod_bn(mul, m, mod);
			copy_bn(r, mod);

			free_bn(mul);
			free_bn(mod);
			
		}
		
		BIGNUM *div = init_bn();
		div_bn(e, two, div);
		copy_bn(e, div);
		
		BIGNUM *mul = init_bn();
		mul_bn(b, b, mul);

		BIGNUM *mod = init_bn();
		mod_bn(mul, m, mod);
	    copy_bn(b, mod);

		free_bn(div);
		free_bn(mul);
		free_bn(mod);
	}
	
	free_bn(b);
	free_bn(e);
	free_bn(m);
	free_bn(zero);
	free_bn(one);
	free_bn(two);
	
	copy_bn(result, r);

	free_bn(r);
}

/*  calculates the greatest common divisor between two big numbers 
 *	with the euclidean algorithm
 *
 *  Input: two big number pointers to calculate the mdc between 
 *         them, a big number pointer
 *  Output:
 *
 *	Pseudocode:  
 * 				while (y != 0)
 *	       			r = x % y
 *	       			x = y
 *	       			y = r
 *				return x;
 * 
 */
void mdc_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result){
	BIGNUM *zero = int_to_bn(0);
	BIGNUM *x = init_bn();
	BIGNUM *y = init_bn();

	copy_bn(x, xx);
	copy_bn(y, yy);

	while(comp_bn(y, zero) != 0){

		BIGNUM *r = init_bn();
		mod_bn(x, y, r);

		copy_bn(x, y);
		copy_bn(y, r);

		free_bn(r);
	}

	copy_bn(result, x);
	free_bn(zero);
	free_bn(x);
	free_bn(y);
}