#ifndef BN_H_INCLUDED
#define BN_H_INCLUDED

typedef struct {

	int *digits;
	int size;
	int sign;
	
} BIGNUM;

BIGNUM* init_bn();
int bn_to_int(BIGNUM *num);
BIGNUM* int_to_bn(int num);
void copy_bn(BIGNUM *a, BIGNUM *b);
void rev_bn(BIGNUM *num);
void rmzero_bn(BIGNUM *num);
int comp_bn(BIGNUM *num1, BIGNUM *num2);
int max(int x, int y);
void fill(BIGNUM *x, int n);

void free_bn(BIGNUM *x);
void free_matrix_bn(BIGNUM *matrix, int size);

void print_bn_file(FILE *file, BIGNUM *x);
void println_bn_file(FILE *file, BIGNUM *x);
void print_bn(BIGNUM *num);
void println_bn(BIGNUM *num);

void random_bn(BIGNUM *result);
void random_range_bn(BIGNUM *start, BIGNUM *end, BIGNUM *result);

void sum_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void sub_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void mul_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void karatsuba(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void div_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void mod_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void mod_inverse_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);
void pow_bn(BIGNUM *bb, BIGNUM *ee, BIGNUM *result);
void pow_mod_bn(BIGNUM *bb, BIGNUM *ee, BIGNUM *mm, BIGNUM *result);
void mdc_bn(BIGNUM *xx, BIGNUM *yy, BIGNUM *result);

#endif
