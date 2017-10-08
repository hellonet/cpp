#include <stdio.h>
#include <iostream>
#include <limits>

// http://en.cppreference.com/w/cpp/language/integer_literal
// https://msdn.microsoft.com/en-us/library/00a1awxf.aspx
// http://en.cppreference.com/w/cpp/io/c/fprintf

//
// The type of the integer literal is the first type in which the value can fit, 
// from the list of types which depends on which numeric base and which integer-suffix was used.
//
// A decimal literal has the smallest type of int, long, or long long (i.e., the first type in this list)
// in which the literal’s value fits. Octal and hexadecimal literals have the smallest type of int, 
// unsigned int, long, unsigned long, long long, or unsigned long long in which the literal’s value fits. 
// It is an error to use a literal that is too large to fit in the largest related type. 
// There are no literals of type short.
//
// int -> unsigned int -> long -> unsigned long -> long long -> unsigned long long
// !!!注意，两个int类型的进行四则运算的时候，结果是更大范围的int类型。
// 例如:
// int a = 1
// unsigned int b = 0xffff0000
// a+b是unsigned int
//
// Floating-point literals include either a decimal point or an exponent specified using scientific notation.
// 3.14159 3.14159E0 0. 0e0 .001
// By default, floating - point literals have type double.We can override the default using a suffix
//
// !!!注意，int literal的suffix, l与L都指long，但是在printf函数里面，指定int的格式的时候，只有l用于long
// printf_s("in f1(__int64): %lld\n", value); ok
// printf_s("in f1(__int64): %LLd\n", value); error
//

enum MyEnum {
	IntType,
	Int64Type
};

MyEnum f1(int value) {
	printf("in f1(int): %d\n", value);
	return IntType;
}

MyEnum f1(unsigned int value) {
	printf("in f1(unsigned int): %u\n", value);
	return IntType;
}

MyEnum f1(__int64 value) {
	printf_s("in f1(__int64): %lld\n", value);
	return Int64Type;
}

void test1()
{
	MyEnum t1 = f1(0x1234), t2 = f1(0x1234567891234i64), t3 = f1(0xffffffff);
	auto var = 0x1234567891234;
}

void test2()
{
	// Since C++14
	// Optional single quotes(') may be inserted between the digits as a separator. 
	// They are ignored by the compiler.
	unsigned long long l1 = 18446744073709550592ull; // C++11
	unsigned long long l2 = 18'446'744'073'709'550'592llu; // C++14
	unsigned long long l3 = 1844'6744'0737'0955'0592uLL; // C++14
	unsigned long long l4 = 184467'440737'0'95505'92LLU; // C++14

	printf("in f1(__int64): %llu\n", l1);
	printf("in f1(__int64): %llu\n", l2);
	printf("in f1(__int64): %llu\n", l3);
	printf("in f1(__int64): %llu\n", l4);
}

void test3()
{
	std::cout << 123 << '\n'
		<< 0123 << '\n'
		<< 0x123 << '\n'
		<< 0b10 << '\n'
		<< 12345678901234567890ull << '\n'
		<< 12345678901234567890u << '\n'; // the type is unsigned long long even
										  // without a long long suffix

										  //   std::cout << -9223372036854775808 << '\n'; // error: the value
										  // 9223372036854775808 cannot fit in signed long long, which is the
										  // biggest type allowed for unsuffixed decimal integer literal
	std::cout << -9223372036854775808u << '\n'; // unary minus applied to unsigned
												// value subtracts it from 2^64, this gives 9223372036854775808
	std::cout << -9223372036854775807 - 1 << '\n'; // correct way to calculate
												   // the value -9223372036854775808
}

void show_int_type(int value)
{
	printf("int: %d\n", value);
}

void show_int_type(unsigned int value)
{
	printf("unsigned int: %u\n", value);
}

void show_int_type(long int value)
{
	printf("long int: %ld\n", value);
}

void show_int_type(unsigned long int value)
{
	printf("unsigned long int: %lu\n", value);
}

void show_int_type(long long int value)
{
	printf("long long int: %lld\n", value);
}

void show_int_type(unsigned long long int value)
{
	printf("unsigned long long int: %llu\n", value);
}

void test5()
{
	// test for decimal literals
	//  int: 2147483648
	//	long long int: 9223372036854775808

	//unsigned long long a = (unsigned long long)(128) * 256 * 256 * 256;
	//printf("int: %llu\n", a);

	//a = (unsigned long long)(128) * 256 * 256 * 256 * 256 * 256 * 256 * 256;
	//printf("int: %llu\n", a);

	show_int_type(2147483647);
	show_int_type(2147483648);
	show_int_type(9223372036854775807);
	show_int_type(9223372036854775808);
}

void check(int i)
{
	// unary minus operator applied to unsigned type, result still unsigned
	// 1. The number 2147483648 is evaluated. Because it is greater than the maximum integer value of 2147483647, 
	// the type of 2147483648 is not int, but unsigned int.
	// 2. Unary minus is applied to the value, with an unsigned result, which also happens to be 2147483648.

	// C4146: unary minus operator applied to unsigned type, result still unsigned
	// You can avoid C4146 by using INT_MIN from limits.h, which has the type signed int.

	9947483648234234234;
	if (i > -2147483648)   // C4146  
		printf_s("%d is greater than the most negative int\n", i);

	// 2147483648应该就是
}

void test4()
{
	check(-100);
	check(1);
}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}