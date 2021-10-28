#include <stdio.h>
#include <math.h>
#define Word16 short int
#define Word32 int 
#define m1 8
#define m2 10
#define m3 12
#define m4 14 
#define length 100

Word16 tmp_Q[4] = { 0 };
Word16 z1_Q[m1] = { 0 };
Word16 z2_Q[m2] = { 0 };
Word16 z3_Q[m3] = { 0 };
Word16 z4_Q[m4] = { 0 };
Word16 x_Q[length] = { 0 };
Word16 y_Q[length] = { 0 };
Word16 add(Word16 var1, Word16 var2);
Word16 mult(Word16 var1, Word16 var2);

// Q16.15 * Q16.15 = Q32.30
Word16 mult(Word16 var1, Word16 var2)
{
	Word16 var_out;
	Word32 L_product;
	L_product = (Word32)var1 * (Word32)var2;
	
	//overflow 방지
	if (L_product >= 1073741824) //2^30 2^15*2^15 보다 작으면 Q32.31로 바꿨을때 overflow 발생 x
		L_product = 2147483647;//2^31 - 1
	else if (L_product <= -1073741824)//-2^30
		L_product = 2147483648;//-2^31
	else
		L_product = L_product << 1;//Q32.30 --> Q32.31
	var_out = L_product >> 16;// Q32.31 --> 16.15
	return var_out;
}


Word16 add(Word16 var1, Word16 var2)
{
	Word16 var_out;
	Word32 L_sum;
	L_sum = (Word32)var1 + (Word32)var2; // Q16.15 + Q 16.15
	if (L_sum > 32767)
		L_sum = 32767;
	else if (L_sum<-32768)
		L_sum = -32768;
	else
		L_sum = L_sum;
	var_out = (Word16)L_sum;
	return(var_out);
}
Word16 matrix_multiply(Word16 *A, Word16 *B){
	Word16 output;
	output = add(add(add(mult(A[0], B[0]), mult(A[1], B[1])), mult(A[2], B[2])), mult(A[3], B[3]));
	return output;
}

int main()
{
	//PARAMETERS
	int i;
	float g, gain;
	int cnt1,cnt2,cnt3,cnt4;
	//lossless matrix
	Word16 a1[4] = { 0, 32767, 32767, 0 };
	Word16 a2[4] = { -32768, 0, 0, -32768 };
	Word16 a3[4] = { 32767, 0, 0, -32768 };
	Word16 a4[4] = { 0, 32767, -32768, 0 };
	Word16 g_Q;
	Word16 gain_Q;
	g = 0.70710678;
	g_Q = g * 32767;
	gain = 0.5;
	gain_Q =gain * 32767;
	x_Q[0] = 32767;

	//Delay
	cnt1 = 0;
	cnt2 = 0;
	cnt3 = 0;
	cnt4 = 0;

	for (i = 0; i < length; i++)
	{
		tmp_Q[0] = z1_Q[cnt1];
		tmp_Q[1] = z2_Q[cnt2];
		tmp_Q[2] = z3_Q[cnt3];
		tmp_Q[3] = z4_Q[cnt4];
		
		//tmp--> Q16.15 
		//y-->Q16.15

		y_Q[i] = add(x_Q[i],add(add(tmp_Q[2], add(tmp_Q[0], tmp_Q[1])), tmp_Q[3]));
		z1_Q[cnt1] = add(mult(mult(matrix_multiply(tmp_Q, a1), g_Q), gain_Q) , x_Q[i]);
		z2_Q[cnt2] = add(mult(mult(matrix_multiply(tmp_Q, a2), g_Q), gain_Q), x_Q[i]);
		z3_Q[cnt3] = add(mult(mult(matrix_multiply(tmp_Q, a3), g_Q), gain_Q), x_Q[i]);
		z4_Q[cnt4] = add(mult(mult(matrix_multiply(tmp_Q, a4), g_Q), gain_Q), x_Q[i]);
		cnt1++;
		cnt2++;
		cnt3++;
		cnt4++;

		if (cnt1 >= m1)
			cnt1 = 0;
		if (cnt2 >= m2)
			cnt2 = 0;
		if (cnt3 >= m3)
			cnt3 = 0;
		if (cnt4 >= m4)
			cnt4 = 0;

		
	}
	//Fixed point 계산 후 floating으로 변환
	for (i = 0; i < length; i++)
	{
		printf("%f ", (float)y_Q[i]/32767);
	}
}
