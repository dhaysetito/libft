#include "libft.h"
#include <stdio.h>
#include <bsd/string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define YELLOW  "\033[33m"
#define CYAN "\033[36m"

/* ===========================================================
 * === CONFIGURAÇÃO DE TESTES ===
 * =========================================================== */

/* Coloque 1 para ativar o teste, 0 para pular */
#define TEST_PART1 1
#define TEST_PART2 1

/* Subtestes Parte 1 */
#define TEST_CTYPE 1
#define TEST_STRING_MEM 1
#define TEST_ATOI_CALLOC 1

/* Subtestes Parte 2 */
#define TEST_SUBSTR 1
#define TEST_STRJOIN 1
#define TEST_STRTRIM 1
#define TEST_SPLIT 1
#define TEST_ITOA 1
#define TEST_STRMAPI 1
#define TEST_STRITERI 1
#define TEST_FD_FUNCS 1

/* =========================================================== */

static void print_result(const char *func, const char *desc, int ok)
{
	if (ok)
		printf(BLUE "[OK]   %-12s | %-25s\n" RESET, func, desc);
	else
		printf(RED "[FAIL] %-12s | %-25s\n" RESET, func, desc);
}

static void print_value(const char *func, const size_t result, const char *value)
{
	printf(GREEN "[VAL]  %-12s | %-25zu -> [%s]\n" RESET, func, result, value);
}

/* ===========================================================
 * === TESTES PARTE 1
 * =========================================================== */

#if TEST_PART1 && TEST_CTYPE
void test_isalpha(void)
{
	print_result("ft_isalpha", "letra minúscula", (!!ft_isalpha('a') == !!isalpha('a')));
	print_result("ft_isalpha", "letra maiúscula", (!!ft_isalpha('Z') == !!isalpha('Z')));
	print_result("ft_isalpha", "número", (!!ft_isalpha('9') == !!isalpha('9')));
	print_result("ft_isalpha", "símbolo", (!!ft_isalpha('$') == !!isalpha('$')));
	print_result("ft_isalpha", "nao alfanumerico", (!!ft_isalpha('\r') == !!isalpha('\r')));
}
void test_isdigit(void)
{
	print_result("ft_isdigit", "número válido", (!!ft_isdigit('7') == !!isdigit('7')));
	print_result("ft_isdigit", "letra", (!!ft_isdigit('A') == !!isdigit('A')));
}
void test_isalnum(void)
{
	print_result("ft_isalnum", "letra", (!!ft_isalnum('A') == !!isalnum('A')));
	print_result("ft_isalnum", "número", (!!ft_isalnum('3') == !!isalnum('3')));
}
void test_isascii(void)
{
	print_result("ft_isascii", "máximo (127)", (!!ft_isascii(127) == !!isascii(127)));
	print_result("ft_isascii", "mínimo (0)", (!!ft_isascii(0) == !!isascii(0)));
}
void test_isprint(void)
{
	print_result("ft_isprint", "letra visível", (!!ft_isprint('A') == !!isprint('A')));
	print_result("ft_isprint", "tab vertical", (!!ft_isprint('\v') == !!isprint('\v')));
	print_result("ft_isprint", "empty", (!!ft_isprint(' ') == !!isprint(' ')));
	print_result("ft_isprint", "32", (!!ft_isprint(32) == !!isprint(32)));
	print_result("ft_isprint", "127", (!!ft_isprint(127) == !!isprint(127)));
}
void test_case_conversion(void)
{
	/* Lowercase to uppercase */
	print_result("ft_toupper", "lowercase -> uppercase", ft_toupper('a') == toupper('a'));

	/* Uppercase to lowercase */
	print_result("ft_tolower", "uppercase -> lowercase", ft_tolower('Z') == tolower('Z'));

	/* Already uppercase (should remain the same) */
	print_result("ft_toupper", "uppercase unchanged", ft_toupper('M') == toupper('M'));

	/* Already lowercase (should remain the same) */
	print_result("ft_tolower", "lowercase unchanged", ft_tolower('m') == tolower('m'));

	/* Non-alphabetic: digits should stay the same */
	print_result("ft_toupper", "digit unchanged", ft_toupper('5') == toupper('5'));
	print_result("ft_tolower", "digit unchanged", ft_tolower('5') == tolower('5'));

	/* Non-alphabetic: symbols should stay the same */
	print_result("ft_toupper", "symbol unchanged", ft_toupper('@') == toupper('@'));
	print_result("ft_tolower", "symbol unchanged", ft_tolower('@') == tolower('@'));

	/* Edge cases: extended ASCII characters */
	print_result("ft_toupper", "extended char (128)", ft_toupper(128) == toupper(128));
	print_result("ft_tolower", "extended char (130)", ft_tolower(130) == tolower(130));
}

#endif

#if TEST_PART1 && TEST_STRING_MEM

void test_strlen(void)
{
	print_result("ft_strlen", "string vazia", ft_strlen("") == strlen(""));
	print_result("ft_strlen", "string curta", ft_strlen("42") == strlen("42"));
	print_result("ft_strlen", "string longa", ft_strlen("42 Rio, melhor base da 42!") == strlen("42 Rio, melhor base da 42!"));
}

void test_memset(void)
{
	char a[10] = "123456789", b[10] = "123456789";
	ft_memset(a, 'X', 5);
	memset(b, 'X', 5);
	print_result("ft_memset", "partial fill", memcmp(a, b, 10) == 0);

	/* Fill the entire buffer */
	char full1[10] = "abcdefghi", full2[10] = "abcdefghi";
	ft_memset(full1, 'Z', 9);
	memset(full2, 'Z', 9);
	print_result("ft_memset", "full fill", memcmp(full1, full2, 10) == 0);

	/* Fill with null bytes */
	char null1[10] = "abcdefgh", null2[10] = "abcdefgh";
	ft_memset(null1, '\0', 5);
	memset(null2, '\0', 5);
	print_result("ft_memset", "fill with nulls", memcmp(null1, null2, 10) == 0);

	/* Check return value (should point to the same address as input) */
	char ret1[10] = "XXXXXXXX";
	char *p1 = ft_memset(ret1, 'A', 3);
	char *p2 = memset(ret1, 'A', 3);
	print_result("ft_memset", "return pointer", p1 == p2);
}

void test_bzero(void)
{
	char s1[6] = "42Rio", s2[6] = "42Rio";
	ft_bzero(s1, 3);
	bzero(s2, 3);
	print_result("ft_bzero", "zero 3 bytes", memcmp(s1, s2, 6) == 0);

	/* Zero entire buffer */
	char full1[6] = "12345", full2[6] = "12345";
	ft_bzero(full1, 5);
	bzero(full2, 5);
	print_result("ft_bzero", "zero entire buffer", memcmp(full1, full2, 6) == 0);

	/* Zero all but one character */
	char almost1[6] = "HELLO", almost2[6] = "HELLO";
	ft_bzero(almost1, 4);
	bzero(almost2, 4);
	print_result("ft_bzero", "zero all but one", memcmp(almost1, almost2, 6) == 0);

	/* Ensure remaining character stays intact */
	print_result("ft_bzero", "last char intact", almost1[4] == almost2[4] && almost1[4] == 'O');
}

void test_memcpy(void)
{
	char d1[10] = "abcdefghi", d2[10] = "abcdefghi";
	ft_memcpy(d1, "12345", 5);
	memcpy(d2, "12345", 5);
	print_result("ft_memcpy", "simple copy", memcmp(d1, d2, 10) == 0);

	/* Copy entire buffer */
	char full1[10] = "AAAAAAAAA", full2[10] = "AAAAAAAAA";
	ft_memcpy(full1, "123456789", 9);
	memcpy(full2, "123456789", 9);
	print_result("ft_memcpy", "full buffer copy", memcmp(full1, full2, 9) == 0);

	/* Zero-length copy (should not modify anything) */
	char zero1[10] = "abcdefghi", zero2[10] = "abcdefghi";
	ft_memcpy(zero1, "ZZZZZ", 0);
	memcpy(zero2, "ZZZZZ", 0);
	print_result("ft_memcpy", "zero length copy", memcmp(zero1, zero2, 10) == 0);

	/* Return pointer should be same as destination */
	char ret1[10] = "XXXXXXXXX";
	char *r1 = ft_memcpy(ret1, "12345", 5);
	char *r2 = memcpy(ret1, "12345", 5);
	print_result("ft_memcpy", "return pointer", r1 == ret1 && r2 == ret1);
}

void test_memmove(void)
{
	char s1[20] = "123456789", s2[20] = "123456789";
	ft_memmove(s1 + 2, s1, 5);
	memmove(s2 + 2, s2, 5);
	print_result("ft_memmove", "forward overlap", memcmp(s1, s2, 10) == 0);

	/* Backward overlap (destination before source) */
	char b1[20] = "ABCDEFGHIJ", b2[20] = "ABCDEFGHIJ";
	ft_memmove(b1, b1 + 2, 5);
	memmove(b2, b2 + 2, 5);
	print_result("ft_memmove", "backward overlap", memcmp(b1, b2, 10) == 0);

	/* Regular non-overlapping copy */
	char reg1[10] = "abcdefghi", reg2[10] = "abcdefghi";
	ft_memmove(reg1, "12345", 5);
	memmove(reg2, "12345", 5);
	print_result("ft_memmove", "non-overlapping copy", memcmp(reg1, reg2, 10) == 0);

	/* Zero-length copy (should not modify anything) */
	char zero1[10] = "abcdefghi", zero2[10] = "abcdefghi";
	ft_memmove(zero1, "ZZZZZ", 0);
	memmove(zero2, "ZZZZZ", 0);
	print_result("ft_memmove", "zero length", memcmp(zero1, zero2, 10) == 0);

	/* Full buffer move */
	char full1[10] = "123456789", full2[10] = "123456789";
	ft_memmove(full1, "987654321", 9);
	memmove(full2, "987654321", 9);
	print_result("ft_memmove", "full buffer", memcmp(full1, full2, 9) == 0);

	/* Move to itself (should be a no-op) */
	char same1[10] = "abcdefghi", same2[10] = "abcdefghi";
	ft_memmove(same1, same1, 9);
	memmove(same2, same2, 9);
	print_result("ft_memmove", "self move", memcmp(same1, same2, 9) == 0);

	/* Return value check */
	char ret1[10] = "XXXXXXXXX";
	char *p1 = ft_memmove(ret1, "12345", 5);
	char *p2 = memmove(ret1, "12345", 5);
	print_result("ft_memmove", "return pointer", p1 == ret1 && p2 == ret1);
}

void test_strlcpy(void)
{
	char d1[10], d2[10];
	size_t r1, r2;

	/* Basic case: normal copy within buffer size */
	r1 = ft_strlcpy(d1, "42 Rio", sizeof(d1));
	r2 = strlcpy(d2, "42 Rio", sizeof(d2));
	print_result("ft_strlcpy", "safe copy", r1 == r2 && strcmp(d1, d2) == 0);

	/* Truncation case: source is larger than destination */
	char small1[5], small2[5];
	r1 = ft_strlcpy(small1, "42 Rio de Janeiro", sizeof(small1));
	r2 = strlcpy(small2, "42 Rio de Janeiro", sizeof(small2));
	print_result("ft_strlcpy", "truncation handled",
				 r1 == r2 && strcmp(small1, small2) == 0 && small1[sizeof(small1) - 1] == '\0');
	print_value("ft_strlcpy", r1, small1);
	print_value("strlcpy", r2, small2);

	/* Size = 0: should not copy anything, only return length of src */
	char zero1[5] = "AAAA", zero2[5] = "AAAA";
	r1 = ft_strlcpy(zero1, "42", 0);
	r2 = strlcpy(zero2, "42", 0);
	print_result("ft_strlcpy", "zero size buffer", r1 == r2 && strcmp(zero1, zero2) == 0);

	/* Empty source string */
	char empty1[10] = "XXXXXXXXX", empty2[10] = "XXXXXXXXX";
	r1 = ft_strlcpy(empty1, "", sizeof(empty1));
	r2 = strlcpy(empty2, "", sizeof(empty2));
	print_result("ft_strlcpy", "empty source", r1 == r2 && strcmp(empty1, empty2) == 0);

	/* Destination buffer of size 1 (only room for '\0') */
	char one1[1], one2[1];
	r1 = ft_strlcpy(one1, "42 Rio", sizeof(one1));
	r2 = strlcpy(one2, "42 Rio", sizeof(one2));
	print_result("ft_strlcpy", "1-byte destination",
				 r1 == r2 && one1[0] == '\0');
}

void test_strlcat(void)
{
	char d1[20] = "Ola ";
	char d2[20] = "Ola ";
	size_t r1 = ft_strlcat(d1, "42 Rio", sizeof(d1));
	size_t r2 = strlcat(d2, "42 Rio", sizeof(d2));
	print_result("ft_strlcat", "safe concatenation", r1 == r2 && strcmp(d1, d2) == 0);

	/* Source fits exactly into destination */
	char exact1[10] = "Hi";
	char exact2[10] = "Hi";
	r1 = ft_strlcat(exact1, " There", sizeof(exact1));
	r2 = strlcat(exact2, " There", sizeof(exact2));
	print_result("ft_strlcat", "exact fit", r1 == r2 && strcmp(exact1, exact2) == 0);
	print_value("ft_strlcat", r1, exact1);
	print_value("strlcat", r2, exact2);

	/* Truncation: source larger than available space */
	char small1[10] = "Hello";
	char small2[10] = "Hello";
	r1 = ft_strlcat(small1, " 42RioSchool", sizeof(small1));
	r2 = strlcat(small2, " 42RioSchool", sizeof(small2));
	print_result("ft_strlcat", "truncation handled",
				 r1 == r2 && strcmp(small1, small2) == 0 && small1[sizeof(small1) - 1] == '\0');

	/* Empty destination string */
	char empty1[10] = "";
	char empty2[10] = "";
	r1 = ft_strlcat(empty1, "42 Rio", sizeof(empty1));
	r2 = strlcat(empty2, "42 Rio", sizeof(empty2));
	print_result("ft_strlcat", "empty destination", r1 == r2 && strcmp(empty1, empty2) == 0);

	/* Empty source string */
	char src_empty1[20] = "Hello";
	char src_empty2[20] = "Hello";
	r1 = ft_strlcat(src_empty1, "", sizeof(src_empty1));
	r2 = strlcat(src_empty2, "", sizeof(src_empty2));
	print_result("ft_strlcat", "empty source", r1 == r2 && strcmp(src_empty1, src_empty2) == 0);

	/* Zero-size destination (should not copy, just return length of src) */
	char zero1[5] = "AAA";
	char zero2[5] = "AAA";
	r1 = ft_strlcat(zero1, "BBB", 0);
	r2 = strlcat(zero2, "BBB", 0);
	print_result("ft_strlcat", "zero-size buffer", r1 == r2 && strcmp(zero1, zero2) == 0);

	/* Destination already full (no room to append) */
	char full1[10] = "ABCDEFGHI";
	char full2[10] = "ABCDEFGHI";
	r1 = ft_strlcat(full1, "Z", sizeof(full1));
	r2 = strlcat(full2, "Z", sizeof(full2));
	print_result("ft_strlcat", "destination full", r1 == r2 && strcmp(full1, full2) == 0);
}

void test_strchr(void)
{
	/* Find first occurrence of 'R' */
	print_result("ft_strchr", "find 'R'", strcmp(ft_strchr("42 Rio", 'R'), strchr("42 Rio", 'R')) == 0);

	/* Character not found */
	print_result("ft_strchr", "not found 'Z'", ft_strchr("42 Rio", 'Z') == strchr("42 Rio", 'Z'));

	/* Find first occurrence when multiple exist */
	print_result("ft_strchr", "multiple matches (first only)",
				 ft_strchr("banana", 'a') == strchr("banana", 'a'));

	/* Search for the terminating null character '\0' */
	print_result("ft_strchr", "find null terminator",
				 ft_strchr("42 Rio", '\0') == strchr("42 Rio", '\0'));

	/* Search for the first character of the string */
	print_result("ft_strchr", "find first char",
				 ft_strchr("42 Rio", '4') == strchr("42 Rio", '4'));

	/* Search in an empty string */
	print_result("ft_strchr", "empty string (no match)",
				 ft_strchr("", 'A') == strchr("", 'A'));

	/* Search for null terminator in empty string */
	print_result("ft_strchr", "empty string (find \\0)",
				 ft_strchr("", '\0') == strchr("", '\0'));
}

void test_strrchr(void)
{
	/* Find the last occurrence of 'i' */
	print_result("ft_strrchr", "find last 'i'", strcmp(ft_strrchr("42 Rio", 'i'), strrchr("42 Rio", 'i')) == 0);

	/* Character not found */
	print_result("ft_strrchr", "not found 'z'", ft_strrchr("42 Rio", 'z') == strrchr("42 Rio", 'z'));

	/* Multiple matches — should return pointer to last occurrence */
	print_result("ft_strrchr", "multiple matches (last only)",
				 ft_strrchr("banana", 'a') == strrchr("banana", 'a'));

	/* Search for the terminating null character '\0' */
	print_result("ft_strrchr", "find null terminator",
				 ft_strrchr("42 Rio", '\0') == strrchr("42 Rio", '\0'));

	/* Search for the first character of the string */
	print_result("ft_strrchr", "find first char (only one occurrence)",
				 ft_strrchr("42 Rio", '4') == strrchr("42 Rio", '4'));

	/* Search in an empty string (no match) */
	print_result("ft_strrchr", "empty string (no match)",
				 ft_strrchr("", 'A') == strrchr("", 'A'));

	/* Search for null terminator in empty string */
	print_result("ft_strrchr", "empty string (find \\0)",
				 ft_strrchr("", '\0') == strrchr("", '\0'));
}

/* Função auxiliar para comparar sinais */
int same_sign(int a, int b)
{
	if (a == 0 && b == 0)
		return (1);
	if (a < 0 && b < 0)
		return (1);
	if (a > 0 && b > 0)
		return (1);
	return (0);
}

void test_strncmp(void)
{
	/* Identical strings */
	print_result("ft_strncmp", "equal strings",
		same_sign(ft_strncmp("42", "42", 2), strncmp("42", "42", 2)));

	/* Different strings (first char different) */
	print_result("ft_strncmp", "different first char",
		same_sign(ft_strncmp("42", "45", 2), strncmp("42", "45", 2)));

	/* Different strings (later difference) */
	print_result("ft_strncmp", "different later",
		same_sign(ft_strncmp("42Rio", "42Rxo", 4), strncmp("42Rio", "42Rxo", 4)));
	
	/* Limit smaller than string length */
	print_result("ft_strncmp", "shorter limit",
		same_sign(ft_strncmp("42 Rio", "42 R", 4), strncmp("42 Rio", "42 R", 4)));

	/* n = 0 (should always return 0) */
	print_result("ft_strncmp", "zero length compare",
		same_sign(ft_strncmp("ABC", "XYZ", 0), strncmp("ABC", "XYZ", 0)));

	/* One string is prefix of the other */
	print_result("ft_strncmp", "prefix compare",
		same_sign(ft_strncmp("42", "42Rio", 5), strncmp("42", "42Rio", 5)));

	/* Completely different strings */
	print_result("ft_strncmp", "completely different",
		same_sign(ft_strncmp("ABC", "XYZ", 3), strncmp("ABC", "XYZ", 3)));

	/* Case sensitivity test */
	print_result("ft_strncmp", "case sensitivity",
		same_sign(ft_strncmp("Rio", "rio", 3), strncmp("Rio", "rio", 3)));
}


void test_memchr(void)
{
	const char *str = "42 Rio";
	char *out;
	char *out2;

	/* Character found in the middle */
	print_result("ft_memchr", "find 'R'", ft_memchr(str, 'R', 6) == memchr(str, 'R', 6));

	/* Character not found */
	print_result("ft_memchr", "not found 'Z'", ft_memchr(str, 'Z', 6) == memchr(str, 'Z', 6));

	/* Character at the beginning */
	print_result("ft_memchr", "find first char", ft_memchr(str, '4', 6) == memchr(str, '4', 6));

	/* Character at the end (before null) */
	print_result("ft_memchr", "find last char before \\0", ft_memchr(str, 'o', 6) == memchr(str, 'o', 6));

	/* Search limited range (character exists but outside range) */
	print_result("ft_memchr", "limit too short", ft_memchr(str, 'o', 3) == memchr(str, 'o', 3));

	/* Search for null terminator */
	out = ft_memchr(str, '\0', 10);
	out2 = memchr(str, '\0', 10);
	print_result("ft_memchr", "find null terminator", out == out2);
	print_value("ft_memchr", 0, out);
	print_value("memchr", 0, out2);

	/* Empty string */
	print_result("ft_memchr", "empty string", ft_memchr("", 'A', 1) == memchr("", 'A', 1));
}

void test_memcmp(void)
{
	/* Equal memory blocks */
	char s1a[] = "abc";
	char s2a[] = "abc";
	print_result("ft_memcmp", "equal blocks", ft_memcmp(s1a, s2a, 3) == memcmp(s1a, s2a, 3));

	/* Equal memory blocks */
	char s1z[] = "Hello";
	char s2z[] = "Hellz";
	print_result("ft_memcmp", "err 5 ", ft_memcmp(s1z, s2z, 5) == memcmp(s1z, s2z, 5));

	/* Different memory blocks */
	char s1b[] = "abc";
	char s2b[] = "abd";
	print_result("ft_memcmp", "different bytes", ft_memcmp(s1b, s2b, 3) == memcmp(s1b, s2b, 3));

	/* Difference in the middle (explicit bytes) */
	char bin1[5] = {'a', 'b', 'c', 'd', 'e'};
	char bin2[5] = {'a', 'b', 'X', 'd', 'e'};
	print_result("ft_memcmp", "third middle difference", ft_memcmp(bin2, bin1, 5) == memcmp(bin2, bin1, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "ft_memcmp", ft_memcmp(bin2, bin1, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "memcmp", memcmp(bin2, bin1, 5));

	/* Simple test */
	char s1c[] = "aBcdef";
	char s2c[] = "abcdef";
	print_result("ft_memcmp", "second middle difference", ft_memcmp(s1c, s2c, 5) == memcmp(s1c, s2c, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "ft_memcmp", ft_memcmp(s1c, s2c, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "memcmp", memcmp(s1c, s2c, 5));

	/* n smaller than first difference (should be equal up to n) */
	char s1d[] = "abc";
	char s2d[] = "abd";
	print_result("ft_memcmp", "short limit (no diff in range)", ft_memcmp(s1d, s2d, 2) == memcmp(s1d, s2d, 2));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "ft_memcmp", ft_memcmp(s1d, s2d, 2));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "memcmp", memcmp(s1d, s2d, 2));

	/* Completely different data */
	char s1e[] = "12345";
	char s2e[] = "ZZZZZ";
	print_result("ft_memcmp", "completely different", ft_memcmp(s1e, s2e, 5) == memcmp(s1e, s2e, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "ft_memcmp", ft_memcmp(s1e, s2e, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "memcmp", memcmp(s1e, s2e, 5));

	/* Zero-length comparison (should return 0) */
	char s1f[] = "abc";
	char s2f[] = "xyz";
	print_result("ft_memcmp", "zero length compare", ft_memcmp(s1f, s2f, 0) == memcmp(s1f, s2f, 0));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "ft_memcmp", ft_memcmp(s1f, s2f, 0));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "memcmp", memcmp(s1f, s2f, 0));

	/* Compare binary data with null bytes */
	char bin3[5] = {'a', '\0', 'b', 'c', 'd'};
	char bin4[5] = {'a', '\0', 'b', 'x', 'd'};
	print_result("ft_memcmp", "binary data with nulls", !!ft_memcmp(bin3, bin4, 5) == !!memcmp(bin3, bin4, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "ft_memcmp", ft_memcmp(bin3, bin4, 5));
	printf(GREEN "[VAL]  %-12s | %-25d\n" RESET, "memcmp", memcmp(bin3, bin4, 5));
}

void test_strnstr(void)
{
	const char *big = "aaabcabcd";
	const char *lit = "aabc";
	char *r1, *r2;

	/* Normal match within range */
	r1 = ft_strnstr(big, lit, 10);
	r2 = strnstr(big, lit, 10);
	print_result("ft_strnstr", "found inside limit", (!r1 && !r2) || (r1 && r2 && strcmp(r1, r2) == 0));

	/* Match outside range */
	r1 = ft_strnstr(big, "abcd", 4);
	r2 = strnstr(big, "abcd", 4);
	print_result("ft_strnstr", "outside limit", (!r1 && !r2));

	/* Literal not found at all */
	r1 = ft_strnstr(big, "XYZ", 10);
	r2 = strnstr(big, "XYZ", 10);
	print_result("ft_strnstr", "no occurrence", r1 == r2);

	/* Empty needle: should return big */
	r1 = ft_strnstr(big, "", 10);
	r2 = strnstr(big, "", 10);
	print_result("ft_strnstr", "empty needle", r1 == r2 && r1 == big);

	/* Zero-length search (should return NULL even if found) */
	r1 = ft_strnstr(big, "aa", 0);
	r2 = strnstr(big, "aa", 0);
	print_result("ft_strnstr", "zero-length search", r1 == r2);

	/* Needle longer than haystack */
	r1 = ft_strnstr("42", "42 Rio", 10);
	r2 = strnstr("42", "42 Rio", 10);
	print_result("ft_strnstr", "needle longer than haystack", r1 == r2);

	/* Match right at the end of limit */
	r1 = ft_strnstr("Hello42Rio", "42", 7);
	r2 = strnstr("Hello42Rio", "42", 7);
	print_result("ft_strnstr", "match at limit end", (!r1 && !r2) || (r1 && r2 && strcmp(r1, r2) == 0));
}

void test_strdup(void)
{
	/* Basic duplication */
	char *a = ft_strdup("42 Rio"), *b = strdup("42 Rio");
	print_result("ft_strdup", "basic duplication", strcmp(a, b) == 0);
	free(a);
	free(b);

	/* Empty string */
	a = ft_strdup("");
	b = strdup("");
	print_result("ft_strdup", "empty string", strcmp(a, b) == 0);
	free(a);
	free(b);

	/* String with spaces and punctuation */
	a = ft_strdup("Hello, World!");
	b = strdup("Hello, World!");
	print_result("ft_strdup", "string with punctuation", strcmp(a, b) == 0);
	free(a);
	free(b);

	/* Long string */
	const char *long_str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	a = ft_strdup(long_str);
	b = strdup(long_str);
	print_result("ft_strdup", "long string", strcmp(a, b) == 0);
	free(a);
	free(b);

	/* Verify independence of the copy (modifying one should not affect the other) */
	a = ft_strdup("42Rio");
	b = strdup("42Rio");
	a[0] = 'X';
	print_result("ft_strdup", "independent copy", b[0] == '4' && a[0] == 'X');
	free(a);
	free(b);
}

#endif

#if TEST_PART1 && TEST_ATOI_CALLOC
void test_atoi(void)
{
	/* Basic positive number */
	print_result("ft_atoi", "positive number", ft_atoi("42") == atoi("42"));

	/* Basic negative number */
	print_result("ft_atoi", "negative number", ft_atoi("-42") == atoi("-42"));

	/* Signal play +-*/
	print_result("ft_atoi", "signal play +-", ft_atoi("+-42") == atoi("+-42"));

	/* Signal play -+*/
	print_result("ft_atoi", "signal play -+", ft_atoi("-+42") == atoi("-+42"));

	/* Multiples +*/
	print_result("ft_atoi", "multiples +", ft_atoi("+++42") == atoi("+++42"));

	/* Multiples -*/
	print_result("ft_atoi", "multiples -", ft_atoi("---42") == atoi("---42"));

	/* Leading spaces */
	print_result("ft_atoi", "leading spaces", ft_atoi("   123") == atoi("   123"));

	/* With plus sign */
	print_result("ft_atoi", "explicit + sign", ft_atoi("+99") == atoi("+99"));

	/* With multiple spaces and sign */
	print_result("ft_atoi", "spaces + sign", ft_atoi("   -123") == atoi("   -123"));

	/* Zero */
	print_result("ft_atoi", "zero", ft_atoi("0") == atoi("0"));

	/* Mixed numbers and letters */
	print_result("ft_atoi", "stops before letters", ft_atoi("42abc") == atoi("42abc"));

	/* Only letters (invalid number) */
	print_result("ft_atoi", "no digits", ft_atoi("abc") == atoi("abc"));
}

void test_calloc(void)
{
	/* Basic zero-initialized memory */
	char *a = ft_calloc(5, sizeof(char)), *b = calloc(5, sizeof(char));
	print_result("ft_calloc", "zeroed memory", memcmp(a, b, 5) == 0);
	free(a);
	free(b);

	/* Allocate integer array */
	int *ia = ft_calloc(4, sizeof(int));
	int *ib = calloc(4, sizeof(int));
	print_result("ft_calloc", "integer array zeroed", memcmp(ia, ib, sizeof(int) * 4) == 0);

	printf(GREEN "[VAL]  %-12s | ", "ft_calloc");
	for (int i = 0; i < 4; i++)
		printf("%d ", ia[i]);
	printf("\n");

	printf(GREEN "[VAL]  %-12s | ", "calloc");
	for (int i = 0; i < 4; i++)
		printf("%d ", ib[i]);
	printf("\n");
	free(ia);
	free(ib);

	/* Zero elements (should still return valid pointer) */
	char *z1 = ft_calloc(0, sizeof(char));
	char *z2 = calloc(0, sizeof(char));
	print_result("ft_calloc", "zero elements", (!!z1) == (!!z2));
	printf(GREEN "[VAL]  %-12s | %-25p\n" RESET, "ft_calloc", &z1);
	printf(GREEN "[VAL]  %-12s | %-25p\n" RESET, "calloc", &z2);
	free(z1);
	free(z2);

	/* Large allocation (within reasonable limits) */
	size_t n = 10000;
	char *l1 = ft_calloc(n, sizeof(char));
	char *l2 = calloc(n, sizeof(char));
	print_result("ft_calloc", "large allocation", l1 && l2 && memcmp(l1, l2, n) == 0);
	free(l1);
	free(l2);

	/* Check independent memory regions */
	char *c1 = ft_calloc(5, sizeof(char));
	char *c2 = ft_calloc(5, sizeof(char));
	strcpy(c1, "123");
	print_result("ft_calloc", "independent blocks", strcmp(c1, c2) != 0);
	free(c1);
	free(c2);
}

#endif

/* ===========================================================
 * === PART 2 TESTS (ADDITIONAL FUNCTIONS)
 * =========================================================== */

#if TEST_PART2 && TEST_SUBSTR
void test_substr(void)
{
	char *res;

	/* Basic valid slice */
	res = ft_substr("42 Rio de Janeiro", 3, 6);
	print_result("ft_substr", "valid slice (Rio de)", strcmp(res, "Rio de") == 0);
	free(res);

	/* Start inside string, but length bigger than remaining */
	res = ft_substr("42 Rio de Janeiro", 13, 6);
	print_result("ft_substr", "half-valid slice (eiro)", strcmp(res, "eiro") == 0);
	free(res);

	/* Start at zero */
	res = ft_substr("Hello World", 0, 5);
	print_result("ft_substr", "start at zero", strcmp(res, "Hello") == 0);
	free(res);

	/* Zero length */
	res = ft_substr("Hello World", 2, 0);
	print_result("ft_substr", "zero length", strcmp(res, "") == 0);
	free(res);

	/* Length bigger than string */
	res = ft_substr("Hi", 0, 50);
	print_result("ft_substr", "length > size", strcmp(res, "Hi") == 0);
	free(res);

	/* Start at end → should return empty string */
	res = ft_substr("Testing", 7, 5);
	print_result("ft_substr", "start == length (empty)", strcmp(res, "") == 0);
	free(res);

	/* Start beyond end → must return empty string */
	res = ft_substr("Testing", 50, 10);
	print_result("ft_substr", "start > length (empty)", strcmp(res, "") == 0);
	free(res);

	/* Empty input */
	res = ft_substr("", 0, 5);
	print_result("ft_substr", "empty input string", strcmp(res, "") == 0);
	free(res);

	/* Full extract */
	res = ft_substr("ABCDE", 0, 5);
	print_result("ft_substr", "full extract", strcmp(res, "ABCDE") == 0);
	free(res);

	/* Middle slice */
	res = ft_substr("ABCDE", 1, 3);
	print_result("ft_substr", "middle slice (BCD)", strcmp(res, "BCD") == 0);
	free(res);
}
#endif


#if TEST_PART2 && TEST_STRJOIN
void test_strjoin(void)
{
	char *res;

	/* Basic join */
	res = ft_strjoin("42 ", "Rio");
	print_result("ft_strjoin", "simple concatenation", strcmp(res, "42 Rio") == 0);
	print_value("ft_strjoin", 0, res);
	free(res);

	/* Join with empty left */
	res = ft_strjoin("", "Hello");
	print_result("ft_strjoin", "left empty", strcmp(res, "Hello") == 0);
	free(res);

	/* Join with empty right */
	res = ft_strjoin("Hello", "");
	print_result("ft_strjoin", "right empty", strcmp(res, "Hello") == 0);
	free(res);

	/* Join both empty */
	res = ft_strjoin("", "");
	print_result("ft_strjoin", "both empty", strcmp(res, "") == 0);
	free(res);

	/* Join multi-word */
	res = ft_strjoin("Rio de ", "Janeiro");
	print_result("ft_strjoin", "multi-word", strcmp(res, "Rio de Janeiro") == 0);
	free(res);

	/* Join symbols */
	res = ft_strjoin("<<", ">>");
	print_result("ft_strjoin", "symbols", strcmp(res, "<<>>") == 0);
	free(res);

	/* Join long strings */
	res = ft_strjoin("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "1234567890");
	print_result("ft_strjoin", "long strings",
		strcmp(res, "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890") == 0);
	free(res);

	/* Join with spaces preserved */
	res = ft_strjoin("Hello ", "World");
	print_result("ft_strjoin", "preserve spaces", strcmp(res, "Hello World") == 0);
	free(res);

	/* Edge case: pointer to empty string inside static memory */
	const char *a = "";
	const char *b = "OK";
	res = ft_strjoin(a, b);
	print_result("ft_strjoin", "const empty left", strcmp(res, "OK") == 0);
	free(res);

	/* More weird join */
	res = ft_strjoin("foo", "\nbar");
	print_result("ft_strjoin", "newline join", strcmp(res, "foo\nbar") == 0);
	free(res);
}
#endif


#if TEST_PART2 && TEST_STRTRIM
void test_strtrim(void)
{
	char *res = ft_strtrim(".42.Rio.", ".");
	print_result("ft_strtrim", "remove dot", strcmp(res, "42.Rio") == 0);
	printf(GREEN "[VAL]  %-12s | %-25s\n" RESET, "ft_strtrim", res);
	free(res);

	res = ft_strtrim("423Rio423", "234");
	print_result("ft_strtrim", "remove 3 chars", strcmp(res, "Rio") == 0);
	printf(GREEN "[VAL]  %-12s | %-25s\n" RESET, "ft_strtrim", res);
	free(res);

	res = ft_strtrim("42 Rio", "f");
	print_result("ft_strtrim", "remove no chars", strcmp(res, "42 Rio") == 0);
	printf(GREEN "[VAL]  %-12s | %-25s\n" RESET, "ft_strtrim", res);
	free(res);
}
#endif

#if TEST_PART2 && TEST_SPLIT
void	print_split(char **tab)
{
	int	i = 0;
	while (tab && tab[i])
	{
		printf("[%d] \"%s\"\n", i, tab[i]);
		i++;
	}
}

void	test_split(void)
{
	char	**res;

	// Basic test
	res = ft_split("42 Rio de Janeiro", ' ');
	print_result("ft_split", "last word", strcmp(res[3], "Janeiro") == 0);
	print_split(res);
	for (int i = 0; res[i]; i++)
		free(res[i]);
	free(res);

	// Empty string test
	res = ft_split("", ' ');
	print_result("ft_split", "empty string", res && res[0] == NULL);
	free(res);

	// Delimiter at beginning and end
	res = ft_split("  42  Rio  ", ' ');
	print_result("ft_split", "ignore extra delimiters",
		strcmp(res[0], "42") == 0 && strcmp(res[1], "Rio") == 0 && res[2] == NULL);
	print_split(res);
	for (int i = 0; res[i]; i++)
		free(res[i]);
	free(res);

	// Only delimiters
	res = ft_split("     ", ' ');
	print_result("ft_split", "only delimiters", res && res[0] == NULL);
	print_split(res);
	free(res);

	// Single character
	res = ft_split("a", ' ');
	print_result("ft_split", "single char string", strcmp(res[0], "a") == 0 && res[1] == NULL);
	for (int i = 0; res[i]; i++)
		free(res[i]);
	free(res);

	// Different delimiter
	res = ft_split("um,dois,tres", ',');
	print_result("ft_split", "comma delimiter", strcmp(res[0], "um") == 0 && strcmp(res[1], "dois") == 0 && strcmp(res[2], "tres") == 0 && res[3] == NULL);
	for (int i = 0; res[i]; i++)
		free(res[i]);
	free(res);
}
#endif

#if TEST_PART2 && TEST_ITOA
void	test_itoa(void)
{
	char	*res;

	// Test: simple negative number
	res = ft_itoa(-42);
	print_result("ft_itoa", "negative number", strcmp(res, "-42") == 0);
	free(res);

	// Test: simple positive number
	res = ft_itoa(42);
	print_result("ft_itoa", "positive number", strcmp(res, "42") == 0);
	free(res);

	// Test: zero
	res = ft_itoa(0);
	print_result("ft_itoa", "zero", strcmp(res, "0") == 0);
	free(res);

	// Test: INT_MIN (-2147483648)
	res = ft_itoa(-2147483648);
	print_result("ft_itoa", "INT_MIN", strcmp(res, "-2147483648") == 0);
	free(res);

	// Test: INT_MAX (2147483647)
	res = ft_itoa(2147483647);
	print_result("ft_itoa", "INT_MAX", strcmp(res, "2147483647") == 0);
	free(res);

	// Test: multiple digits with zeros in the middle
	res = ft_itoa(1002);
	print_result("ft_itoa", "zeros in the middle", strcmp(res, "1002") == 0);
	free(res);

	// Test: single digit number
	res = ft_itoa(7);
	print_result("ft_itoa", "small number", strcmp(res, "7") == 0);
	free(res);

	// Test: rapid sign alternation (should not crash)
	res = ft_itoa(-1);
	print_result("ft_itoa", "minus one", strcmp(res, "-1") == 0);
	free(res);
}
#endif

#if TEST_PART2 && TEST_STRMAPI
static char	map_toggle(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (ft_toupper(c));
	else
		return (ft_tolower(c));
}

static char	map_plus_index(unsigned int i, char c)
{
	return (c + (i % 3));
}

void	test_strmapi(void)
{
	char	*res;

	// Basic test with alternation
	res = ft_strmapi("42 Rio de Janeiro", map_toggle);
	print_result("ft_strmapi", "toggle upper/lower",
		strcmp(res, "42 rIo dE JaNeIrO") == 0);
	free(res);

	// Empty string test
	res = ft_strmapi("", map_toggle);
	print_result("ft_strmapi", "empty string returns empty string",
		res && strcmp(res, "") == 0);
	free(res);

	// Function uses index to alter character
	res = ft_strmapi("aaa", map_plus_index);
	print_result("ft_strmapi", "uses index in calculation", strcmp(res, "abc") == 0);
	printf("res: %s\n", res);
	free(res);

	// NULL pointer test
	res = ft_strmapi(NULL, map_toggle);
	print_result("ft_strmapi", "NULL input returns NULL", res == NULL);

	// NULL function test
	res = ft_strmapi("abc", NULL);
	print_result("ft_strmapi", "NULL function returns NULL", res == NULL);
}
#endif

#if TEST_PART2 && TEST_STRITERI

#include <string.h>
#include <stdio.h>
#include "libft.h"

// Test 1 function: convert to uppercase
static void iter_up(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

// Test 2 function: increment char based on index
static void iter_index(unsigned int i, char *c)
{
	*c = *c + i;
}

// Test 3 function: replace all with '*'
static void iter_replace(unsigned int i, char *c)
{
	(void)i;
	*c = '*';
}

void test_striteri(void)
{
	// Test 1: lowercase letters become uppercase
	char str1[] = "rio";
	ft_striteri(str1, iter_up);
	print_result("ft_striteri", "convert to uppercase", strcmp(str1, "RIO") == 0);

	// Test 2: mixed characters
	char str2[] = "42Rio";
	ft_striteri(str2, iter_up);
	print_result("ft_striteri", "only lowercase letters change", strcmp(str2, "42RIO") == 0);

	// Test 3: function uses index — each char adds its index
	char str3[] = "abcd";
	ft_striteri(str3, iter_index);
	print_result("ft_striteri", "uses index correctly", strcmp(str3, "aceg") == 0);

	// Test 4: empty string — should remain unchanged
	char str4[] = "";
	ft_striteri(str4, iter_up);
	print_result("ft_striteri", "empty string unchanged", strcmp(str4, "") == 0);

	// Test 5: NULL function — should not modify or crash
	char str5[] = "test";
	ft_striteri(str5, NULL);
	print_result("ft_striteri", "NULL function does not modify", strcmp(str5, "test") == 0);

	// Test 6: NULL string — should not crash
	ft_striteri(NULL, iter_up);
	print_result("ft_striteri", "NULL string does not crash", 1);

	// Test 7: long string — ensure full iteration
	char str6[] = "abcdefghij";
	ft_striteri(str6, iter_replace);
	print_result("ft_striteri", "modify all characters", strcmp(str6, "**********") == 0);
}

#endif

#if TEST_PART2 && TEST_FD_FUNCS
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "libft.h"

void test_msg(const char *msg)
{
	printf(CYAN "\n[TEST] %s\n" RESET, msg);
	printf(YELLOW "Output: \n" RESET);
}

void test_fd_functions(void)
{
	int fd = 1;
	int fd_err = 2;

	printf(BLUE "\n========== Tests for *_fd functions ==========\n" RESET);

	/* --- STDOUT --- */
	printf(YELLOW "\n[STDOUT tests]\n" RESET);

	test_msg("ft_putchar_fd('A')");
	ft_putchar_fd('A', fd);
	ft_putchar_fd('\n', fd);

	test_msg("ft_putstr_fd(\"Hello \")");
	ft_putstr_fd("Hello ", fd);
	printf("\n");

	test_msg("ft_putendl_fd(\"World\")");
	ft_putendl_fd("World", fd);

	test_msg("ft_putendl_fd(\"new line\")");
	ft_putendl_fd("new line", fd);

	test_msg("ft_putnbr_fd(42)");
	ft_putnbr_fd(42, fd);
	ft_putchar_fd('\n', fd);

	/* --- STDERR --- */
	printf(YELLOW "\n[STDERR tests]\n" RESET);

	test_msg("ft_putstr_fd(\"Error message -> \")");
	ft_putstr_fd("Error message -> ", fd_err);
	printf("\n");

	test_msg("ft_putnbr_fd(-999)");
	ft_putnbr_fd(-999, fd_err);
	ft_putchar_fd('\n', fd_err);

	/* --- NEGATIVE NUMBERS --- */
	printf(YELLOW "\n[Negative number tests]\n" RESET);

	test_msg("ft_putnbr_fd(-42)");
	ft_putnbr_fd(-42, fd);
	ft_putchar_fd('\n', fd);

	test_msg("ft_putnbr_fd(INT_MIN)");
	ft_putnbr_fd(INT_MIN, fd);
	ft_putchar_fd('\n', fd);

	/* --- EMPTY STRINGS --- */
	printf(YELLOW "\n[Empty string tests]\n" RESET);

	test_msg("ft_putstr_fd(\"\")");
	ft_putstr_fd("", fd);
	printf("\n");

	test_msg("ft_putendl_fd(\"\")");
	ft_putendl_fd("", fd);

	/* --- TEMP FILE --- */
	printf(YELLOW "\n[Temp file test]\n" RESET);

	int file = open("test_fd_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
	{
		perror("Error opening file");
		return;
	}

	test_msg("Writing to test_fd_output.txt");

	ft_putstr_fd("Saving...\n", file);
	ft_putnbr_fd(123456, file);
	ft_putendl_fd("\nEnd of test!", file);
	close(file);

	printf(GREEN "\nSaved output in test_fd_output.txt\n" RESET);
}

#endif



/* ===========================================================
 * === MAIN ===
 * =========================================================== */

int main(void)
{
	printf("\n===== TESTES UNITÁRIOS LIBFT - 42 RIO =====\n\n");

#if TEST_PART1 && TEST_CTYPE
	test_isalpha();
	printf("\n");
	test_isdigit();
	printf("\n");
	test_isalnum();
	printf("\n");
	test_isascii();
	printf("\n");
	test_isprint();
	printf("\n");
	test_case_conversion();
	printf("\n");
#endif

#if TEST_PART1 && TEST_STRING_MEM
	test_strlen();
	printf("\n");
	test_memset();
	printf("\n");
	test_bzero();
	printf("\n");
	test_memcpy();
	printf("\n");
	test_memmove();
	printf("\n");
	test_strlcpy();
	printf("\n");
	test_strlcat();
	printf("\n");
	test_strchr();
	printf("\n");
	test_strrchr();
	printf("\n");
	test_strncmp();
	printf("\n");
	test_memchr();
	printf("\n");
	test_memcmp();
	printf("\n");
	test_strnstr();
	printf("\n");
	test_strdup();
	printf("\n");
#endif

#if TEST_PART1 && TEST_ATOI_CALLOC
	test_atoi();
	printf("\n");
	test_calloc();
	printf("\n");
#endif

#if TEST_PART2 && TEST_SUBSTR
	test_substr();
	printf("\n");
#endif
#if TEST_PART2 && TEST_STRJOIN
	test_strjoin();
	printf("\n");
#endif
#if TEST_PART2 && TEST_STRTRIM
	test_strtrim();
	printf("\n");
#endif
#if TEST_PART2 && TEST_SPLIT
	test_split();
	printf("\n");
#endif
#if TEST_PART2 && TEST_ITOA
	test_itoa();
	printf("\n");
#endif
#if TEST_PART2 && TEST_STRMAPI
	test_strmapi();
	printf("\n");
#endif
#if TEST_PART2 && TEST_STRITERI
	test_striteri();
	printf("\n");
#endif
#if TEST_PART2 && TEST_FD_FUNCS
	test_fd_functions();
	printf("\n");
#endif

	printf("\n===== FIM DOS TESTES =====\n");
	return (0);
}
