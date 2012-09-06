/*
 
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
 
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "stdafx.h"
#include "Base2.h"



//to lower a string


char *str_tolower (const char *ct)
{
  char *s = NULL;

  if (ct != NULL)
  {
    int i;

    s = (char*) malloc (sizeof (*s) * (strlen (ct) + 1));
    if (s != NULL)
    {
      for (i = 0; ct[i]; i++)
      {
        s[i] = tolower (ct[i]);
      }
      s[i] = '\0';
    }
  }
  return s;
}

// to upper string's charaters
char *str_toupper (const char *ct)
{
  char *s = NULL;

  if (ct != NULL)
  {
    int i;

    s = (char*) malloc (sizeof (*s) * (strlen (ct) + 1));
    if (s != NULL)
    {
      for (i = 0; ct[i]; i++)
      {
        s[i] = toupper (ct[i]);
      }
      s[i] = '\0';
    }
  }
  return s;
}


/*
To Know the substring index number
*/

int str_istr ( char *cs,  char *ct)
{
  int index = -1;

  if (cs != NULL && ct != NULL)
  {
    char *ptr_pos = NULL;

    ptr_pos = strstr (cs, ct);
    if (ptr_pos != NULL)
    {
      index = ptr_pos - cs;
    }
  }
  return index;
}

/*
extract a substring of s between the start and end index.
*/

char *str_sub (const char *s, unsigned int start, unsigned int end)
{
  char *new_s = NULL;

  if (s != NULL && start < end)
  {
    // calculate how many characters in the string called "s"
    new_s = (char*) malloc (sizeof (*new_s) * (end - start + 2));
    if (new_s != NULL)
    {
      unsigned int i;
      // assign to new_s the string between start and end
      for (i = start; i <= end; i++)
      {
        new_s[i-start] = s[i];
      }
      //we must finish with '\0'
      new_s[i-start] = '\0';
    }
    else
    {
      cout << "not enough memory " << endl;
      exit (EXIT_FAILURE);
    }
  }
  return new_s;
}

/*
join multiple strings, through a separator (cs)
*/

char *str_join (char *cs, char* ct)
{
    char *s = NULL;
    size_t size = 0;

    char *tmp = NULL ;
    //for each argument, we calculate the new size of the final string
    //without forgetting to add the size of the separator
    size += strlen (ct) + strlen (cs);
    tmp = (char*) realloc (s, sizeof (*s) * (size + 1));
    if (tmp != NULL)
    {
          if (s == NULL)
          {
            //we just copy this in memory space
            s = tmp;
            strcpy (s, cs);
            strcat (s, ct);
          }
    }
    else
    {
      cout << "not enough memory to do that"<<endl;
      free (s);
      s = NULL;
      exit (EXIT_FAILURE);
    }
  return s;
}


/*
This feature allows you to replace length characters of string s from
the index start by a new string ct. A new string is created, don't forget to free memory.
*/

char *str_remplace (const char *s, unsigned int start, unsigned int lenght, const char *ct)
{
  char *new_s = NULL;

  if (s != NULL && ct != NULL && start >= 0 && lenght > 0)
  {
    size_t size = strlen (s);

    //new memory space to store the modified string
    new_s = (char*) malloc (sizeof (*new_s) * (size - lenght + strlen (ct) + 1));
    if (new_s != NULL)
    {
          //The new channel is created by copy & paste the beginning of s
          memcpy (new_s, s, start);

          //At the start index, we add the replacement string
          memcpy (&new_s[start], ct, strlen (ct));

          //To end with the end of the string s starting
          memcpy (&new_s[start + strlen (ct)], &s[start + lenght], size - lenght - start + 1);
    }
  }
  else
  {
    cout << "not enough memory" << endl;
    exit (EXIT_FAILURE);
  }
  return new_s;
}


/*To remove the spaces, just copy the original string and when we encounter a space,
we will see if this is the first (if one has already met with a space, the variable tmp equals 1)
If so, it copies it as any other character and it tmp is 1, if not first, you do not copy.
Of course, if you copy anything other than space, do not forget to put tmp to
zero for the next space is copied. */

char *str_strip (const char *string)
{
  char *strip = NULL;

  if (string != NULL)
  {
    strip = (char*) malloc (sizeof (*strip) * (strlen (string) + 1));
    if (strip != NULL)
    {
      int i, j;
      int tmp = 0;

      for (i = 0, j = 0; string[i]; i++)
      {
            if (string[i] == ' ')
            {
              if (tmp == 0)
              {
                strip[j] = string[i];
                tmp = 1;
                j++;
              }
            }
            else
            {
              strip[j] = string[i];
              tmp = 0;
              j++;
            }
        }
        strip[j] = '\0';
    }
    else
    {
        cout << "not enough memory" << endl;
        exit (EXIT_FAILURE);
    }
  }
  return strip;
}

bool ValidFile(char **tab, int nbFichier)
{
    int j = 0;
    bool test;

    for (int i=0; i<nbFichier; i++)
    {
       j = 0;
        while (tab[i][j] != '.')
        {
            if (tab[i][j]=='\0')
            {
                cout << "File : " << tab[i] << " isn't valid";
                return false;
            }
            j++;
        }
        cout << tab[i][j] << endl;
        j++;
        if (tab[i][j] == 't')
        {
            //cout << tab[i][j] << endl;
            j++;
            if (tab[i][j] == 'x')
            {
                //cout << tab[i][j] << endl;
                j++;
                if (tab[i][j] == 't')
                {
                    //cout << tab[i][j] << endl;
                    j++;
                    if (tab[i][j]=='\0')
                    {
                        test = true;
                    }
                    else{test = false;}
                }
                else{test = false;}
            }
            else{test = false;}
        }
        else{test = false;}
    }

    return test;
}
