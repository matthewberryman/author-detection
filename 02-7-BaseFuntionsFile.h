/* Provides base functions for working with text files.
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
 
  Text treatment :
      1) seeking the number of characters in the text and returns the result
      2) seeking the number of strings - set in parameter - in the text and returns the result
 
  Creation date : 28/06/2010
  Last modification : 1/07/2010
 */



#ifndef BASEFUNTIONSFILE_H_INCLUDED
#define BASEFUNTIONSFILE_H_INCLUDED

#include "Base2.h"

using namespace std;

//seeking the number of characters in the text and returns the result
int NbChar(char* SourceFile)
{
    FILE *file;
    char tmp;
    int Compteur = 0;

    if((file = fopen(SourceFile, "r")) != NULL) //on ouvre le fichier et verifie si on y arrive:it opens the file and checked if there happens
    {
        //si on arrive a ouvrire le fichier tant que l'on est pas a la fin:if you get a file opens as it is not the end
        while (!feof(file))
        {
            fread(&tmp, 1, 1, file); //on range les caracteres dans le buffer:The one arranges characters in The Buff
            Compteur += 1;
        }
    }
    fclose(file);
    return(Compteur-1);
}



// seeking the number of strings - set in parameter - in the text and returns the result
int ResearchChar(char *SourceFile, char *Chaine)
{
    FILE *file;
    char tmp, tmp2;

    int NbFois = 0;
    int Compteur;
    int TailleChaine;
 //   char* Concat;

//    Concat = cat_chaine(Chaine);

    TailleChaine = strlen(Chaine);
    cout << "input's string length : " << TailleChaine << endl;


    if((file = fopen(SourceFile, "r")) != NULL) //on ouvre le fichier et verifie si on y arrive
    {
        while (!feof(file))
        {
            Compteur = 0;
            if ((tmp == ' ') | (tmp == '\n') | (tmp == '?') | (tmp == ';') | (tmp == '.') |
                (tmp == ',') | (tmp == ':') | (tmp == '!')| (tmp == '\'') | (tmp == '/'))
                {

                }
            fread(&tmp, 1, 1, file); //on range les caracteres dans le buffer:one arranges the characters in the buffer
            while (((tmp == ' ') | (tmp == '\n') | (tmp == '?') | (tmp == ';') | (tmp == '.') |
                   (tmp == ',') | (tmp == ':') | (tmp == '!')| (tmp == '\'') | (tmp == '/')) && (!feof(file)))
                   {
                       fread(&tmp, 1, 1, file);
                   }

            while ((tmp == Chaine[Compteur]) && (!feof(file)) /*&& ((tmp2 == '\n') | (tmp2 == ' '))*/)
            {
                if (Compteur<TailleChaine)
                {
                    Compteur++;
                    fread(&tmp, 1, 1, file);
                }
            }
            if (Compteur == TailleChaine)//Chain Size
            {
                if ((tmp == ' ') | (tmp == '\n') |
                   (tmp == '.') | (feof(file)) |
                   (tmp == '?') | (tmp == ';') |
                   (tmp == ',') | (tmp == ':') | (tmp == '!'))
                   {
                       NbFois++;
                   }
            }
        }

    }
    fclose(file);

    return(NbFois);
}



void Newfile(char *SourceFile)
{
    FILE *fileSource, *fileDest;
    char tmp;

    if((fileSource = fopen(SourceFile, "r")) != NULL) //on ouvre le fichier et verifie si on y arrive
    {
        if((fileDest = fopen("FichierDest.txt", "w")) != NULL)
        {

        }
    }
    fclose(fileSource);
    fclose(fileDest);
}

#endif // BASEFUNTIONSFILE_H_INCLUDED
