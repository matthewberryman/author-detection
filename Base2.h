/*  Text treatment functions

Copyright (C) 2010 François-Pierre Huchet

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

  Creation date : 28/06/2010
  Last modification : 05/07/2010

*/

#ifndef BASE2_H_INCLUDED
#define BASE2_H_INCLUDED

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h> // for realloc
#include <string.h>

/* Redefinition of standard functions for future use, such check
   the validity of arguments. */
#define str_cpy  strcpy
#define str_ncpy strncpy
#define str_cat  strcat
#define str_ncat strncat
#define str_cmp  strcmp
#define str_ncmp strncmp
#define str_len  strlen
#define str_chr  strchr
#define str_rchr strrchr
#define str_str  strstr
#define str_spn  strspn
#define str_pbrk strpbrk
#define str_tok  strtok


using namespace std;

char *str_tolower (const char *);
char *str_toupper (const char *);

int str_istr (const char *, const char *);
char *str_sub (const char *, unsigned int, unsigned int);
char **str_split (char *, const char *);
char *str_join (char *, char*);
char *str_remplace (const char *, unsigned int, unsigned int, const char *);
char *str_strip (const char *);

bool ValidFile(char **tab, int nbFichier);

#endif // BASE2_H_INCLUDED
