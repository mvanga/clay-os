#include <clay/ctype.h>

int isdigit(int c)
{
	return c >= '0' && c <= '9';
}

int isxdigit(int c)
{
	return isdigit(c)
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}

int isalpha(int c)
{
	return islower(c) || isupper(c);
}

int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

int islower(int c)
{
	return c >= 'a' && c <= 'z';
}

int isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}

int toupper(int c)
{
	if (!islower(c))
		return c;
	return c - 'a' + 'A';
}

int tolower(int c)
{
	if (!isupper(c))
		return c;
	return c - 'A' + 'a';
}
