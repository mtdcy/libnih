/* libnih
 *
 * test_strutil.c - test suite for nih/strutil.c
 *
 * Copyright © 2006 Scott James Remnant <scott@netsplit.com>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */


#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include <nih/alloc.h>
#include <nih/strutil.h>


int
test_sprintf (void)
{
	char *str1, *str2;
	int   ret = 0;

	printf ("Testing nih_sprintf()\n");

	printf ("...with no parent\n");
	str1 = nih_sprintf (NULL, "this %s a test %d", "is", 54321);

	/* Returned value should be correct */
	if (strcmp (str1, "this is a test 54321")) {
		printf ("BAD: return value wasn't what we expected.\n");
		ret = 1;
	}

	/* Size should be correct */
	if (nih_alloc_size (str1) != strlen ("this is a test 54321") + 1) {
		printf ("BAD: size incorrect.\n");
		ret = 1;
	}

	/* Parent should be none */
	if (nih_alloc_parent (str1) != NULL) {
		printf ("BAD: parent incorrect.\n");
		ret = 1;
	}


	printf ("...with a parent\n");
	str2 = nih_sprintf (str1, "another %d test %s", 12345, "string");

	/* Returned value should be correct */
	if (strcmp (str2, "another 12345 test string")) {
		printf ("BAD: return value wasn't what we expected.\n");
		ret = 1;
	}

	/* Size should be correct */
	if (nih_alloc_size (str2)
	    != strlen ("another 12345 test string") + 1) {
		printf ("BAD: size incorrect.\n");
		ret = 1;
	}

	/* Parent should be first string */
	if (nih_alloc_parent (str2) != str1) {
		printf ("BAD: parent incorrect.\n");
		ret = 1;
	}

	return ret;
}

static char *
my_vsprintf (void *parent,
	     const char *format,
	     ...)
{
	char    *str;
	va_list  args;

	va_start (args, format);
	str = nih_vsprintf (parent, format, args);
	va_end (args);

	return str;
}

int
test_vsprintf (void)
{
	char *str1, *str2;
	int   ret = 0;

	printf ("Testing nih_vsprintf()\n");

	printf ("...with no parent\n");
	str1 = my_vsprintf (NULL, "this %s a test %d", "is", 54321);

	/* Returned value should be correct */
	if (strcmp (str1, "this is a test 54321")) {
		printf ("BAD: return value wasn't what we expected.\n");
		ret = 1;
	}

	/* Size should be correct */
	if (nih_alloc_size (str1) != strlen ("this is a test 54321") + 1) {
		printf ("BAD: size incorrect.\n");
		ret = 1;
	}

	/* Parent should be none */
	if (nih_alloc_parent (str1) != NULL) {
		printf ("BAD: parent incorrect.\n");
		ret = 1;
	}


	printf ("...with a parent\n");
	str2 = my_vsprintf (str1, "another %d test %s", 12345, "string");

	/* Returned value should be correct */
	if (strcmp (str2, "another 12345 test string")) {
		printf ("BAD: return value wasn't what we expected.\n");
		ret = 1;
	}

	/* Size should be correct */
	if (nih_alloc_size (str2)
	    != strlen ("another 12345 test string") + 1) {
		printf ("BAD: size incorrect.\n");
		ret = 1;
	}

	/* Parent should be first string */
	if (nih_alloc_parent (str2) != str1) {
		printf ("BAD: parent incorrect.\n");
		ret = 1;
	}

	return ret;
}


int
main (int   argc,
      char *argv[])
{
	int ret = 0;

	ret |= test_sprintf ();
	ret |= test_vsprintf ();

	return ret;
}