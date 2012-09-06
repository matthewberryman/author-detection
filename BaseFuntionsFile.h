/* Extended base functions
 
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
  Last modification : 1/07/2010
*/

#ifndef BASEFUNTIONSFILE_H_INCLUDED
#define BASEFUNTIONSFILE_H_INCLUDED

#include "Base2.h"
#include "Word.h"
#include <math.h>



//seeking the number of characters in the text and returns the result
int NbChar(char* SourceFile)
{
    FILE *file;
    char tmp;
    int Compteur = 0;

    if((file = fopen(SourceFile, "r")) != NULL) //try to open file
    {
        //if it's ok and while we are not to Enf Of File
        while (!feof(file))
        {
            fread(&tmp, 1, 1, file); //get caracter in tmp
            Compteur += 1;
        }
    }
    fclose(file);
    return(Compteur-1);
}


//seeking the number of strings in the text and returns the result
int NbStr(char* SourceFile)
{
    FILE *file;
    char tmp;
    int Compteur = 0;
    int test = 0;

    if((file = fopen(SourceFile, "r")) != NULL) //try to open file
    {
        while (!feof(file))
        {
            fread(&tmp, 1, 1, file);
            if ((tmp == ' ') | (tmp == '\n') | (tmp == '.') |
                (tmp == ',') | (tmp == ';') | (tmp == '?') |
                (tmp == '!') | (tmp == ':') | (tmp == '[') |
                (tmp == ']') | (tmp == '{') | (tmp == '}') |
                (tmp == '/') | (tmp == '\'') | (tmp == '@') |
                (tmp == '\"') | (tmp == '_') | (tmp == '-') |
                (tmp == '#') | (tmp == '$') | (tmp == '%') |
                (tmp == '&') | (tmp == '*') | (tmp == '+') |
                (tmp == '='))
            {
                if (test == 1)
                {
                    test = 0;
                    Compteur += 1;
                }
            }
            else
                test = 1;
        }
    }
    fclose(file);
    return(Compteur+1);
}

// seeking the number of strings - set in parameter - in the text and returns the result
int NumberOfString(char *SourceFile, char *Chaine)
{
    FILE *file;
    char tmp;
    int NbFois = 0;
    int Compteur;
    int TailleChaine;
    long posi;
    bool test = false;

    TailleChaine = strlen(Chaine);

    if((file = fopen(SourceFile, "rw")) != NULL) //try to open the file
    {
        fread(&tmp, 1, 1, file);
        posi = ftell(file);
        while (!feof(file))
        {
            Compteur = 0;

            if (test == true)
            {
                    fseek ( file , (posi-2) , SEEK_SET );
                    test = false;
            }

            while ((tmp != Chaine[Compteur]) && (!feof(file)))
            {
                Compteur = 0;
                fread(&tmp, 1, 1, file);
                posi = ftell(file);
            }

            while ((tmp == Chaine[Compteur]) && (!feof(file)))
            {
                if (Compteur<TailleChaine)
                {
                    Compteur++;
                    fread(&tmp, 1, 1, file);
                    posi = ftell(file);
                }
            }

            if (Compteur == TailleChaine)
            {
                NbFois++;
                posi = ftell(file);
                test = true;
            }
        }
    }
    fclose(file);
    return (NbFois);
}

//function to know how many seek we need to do the concatenation
int SeekPosi(char *SourceFile)
{
    int size = 0;
    FILE *file;

    if((file = fopen(SourceFile, "rw")) != NULL)
    {
        fseek (file, 0, SEEK_END);
        size=ftell (file);
        fclose (file);
    }
    else
    {
        cout << "problem to open the file in function named : SeekPosi" << endl;
    }
    return (size);
}

//to test the first word of the file
int FirstWord(char *SourceFile, char *Chaine)
{
    FILE *file;
    char tmp;
    int NbFois = 0;
    int Compteur = 0;
    int TailleChaine;

    TailleChaine = strlen(Chaine);

    if((file = fopen(SourceFile, "r")) != NULL) //try to open the file in read only mode
    {
        fread(&tmp, 1, 1, file);

        while ((tmp == Chaine[Compteur]) && (!feof(file)))
        {
            if (Compteur<TailleChaine)
            {
                Compteur++;
                fread(&tmp, 1, 1, file);
            }
        }

        if (Compteur == TailleChaine)
        {
            NbFois = 1;
        }
    }
    fclose(file);
    return (NbFois);
}


//to count the string give in parameter in a file (first parameter)
int CountAllString(char *SourceFile, char *str)
{
    int total = 0;
    char *strN;

//declaration of tab : array of string for the ponctuation
    char *tab[24] = {"\n", " ", ",", ".", ";", ":", " :", " ?",
                    " !", "( ", "(", ")", " )", "\"", "_", "-",
                    "#", "@", "%", "$", "&", "*", "+", "="};

    //joint the string to every ponctuation sign
    for (int i=0; i<23; i++)
    {
        strN = str_join(str, tab[i]);
        total = total + NumberOfString(SourceFile,strN);
    }

    return (total);
}


//function to write a new file from the begining (size) of an another file
void WriteNewFile(char *DestinationFile, int size, char *tab[])
{
    FILE *FS;
    FILE *FD;
    char tmp;
    char retour = '\n';
    int compteur = 0;
    int test = 0;

    if((FD = fopen(DestinationFile, "w+")) != NULL)
    {
        for (int i = 0; i<13 ; i++)
        {
            compteur = 0;
            if((FS = fopen(tab[i], "r")) != NULL)
            {
                 while ((!feof(FS)) & (compteur<size))
                {
                    fread(&tmp, 1, 1, FS);
                    fwrite(&tmp , 1 , sizeof(tmp) , FD );
                    if ((tmp == ' ')|(tmp == '\n'))
                    {
                        if (test==0)
                        {
                            test = 1;
                            compteur++;
                        }
                    }
                    else
                        test = 0;
                }
                fwrite (&retour , 1 , sizeof(retour) , FD );
                fwrite (&retour , 1 , sizeof(retour) , FD );
                fclose(FS);
            }
            else
            {
                cout << "problem to open the file" << i <<"in function named : WriteNewFile" << endl;
            }
        }
    }
    else
    {
        cout << "problem to open the destination file in function named : WriteNewFile" << endl;
    }
    fclose(FD);
}


//count the number of recurrence of a string in parameter in the file FileOut.txt
int CountRecurrence(char *chaine)
{
    char *chaine2 = NULL;
    char *str2 = NULL;
    int NombreDeRecurences = 0;

    chaine2 = str_tolower(chaine);
    str2 = str_join(chaine2," ");
    NombreDeRecurences = FirstWord("FileOut.txt", str2);

    str2 = str_join(" ", chaine2);
    NombreDeRecurences += CountAllString("FileOut.txt", str2);

    str2 = str_join(chaine2, "\n");
    NombreDeRecurences += CountAllString("FileOut.txt", str2);

    str2 = str_join("\n", chaine2);
    NombreDeRecurences += CountAllString("FileOut.txt", str2);

    cout << endl << "Number of string recurrences de " << chaine2 <<
                    " est: " << NombreDeRecurences << endl;

    chaine2 = str_toupper(chaine);
    NombreDeRecurences = 0;
    str2 = str_join(" ", chaine2);
    NombreDeRecurences += CountAllString("FileOut.txt", str2);

    str2 = str_join(chaine2, "\n");
    NombreDeRecurences += CountAllString("FileOut.txt", str2);

    str2 = str_join("\n", chaine2);
    NombreDeRecurences += CountAllString("FileOut.txt", str2);

    cout << endl << "Number of string recurrences de " << chaine2 <<
                    " est: " << NombreDeRecurences << endl;

    free (str2);
    return (NombreDeRecurences);
}

//use for a concatenation of a list of texts.
//we looking for the most useful words after in this file
Word* FillArrayStr1(char* SourceFile, char **tableau, int* taille, int *nbFich)
{
    int size = *taille;
    int nbFichier = *nbFich;
    FILE *file;
    char tmp;
    int i = 0, j = 0, test = 0;
    char tampon[20]; //buffer to stock on word

    Word *OnlyOneTime; // array with each word only time to compare.
    OnlyOneTime = (Word*) calloc ((size*nbFichier), sizeof(Word));

    for (int k=0; k<(size*nbFichier) ; k++)
    {
        Word *p_Word = new Word(" ",0);
        OnlyOneTime[k] = *p_Word;
    }

    for (int p = 0; p<20; p++)
    {
        tampon[p] = '\0';
    }

    if((file = fopen(SourceFile, "r")) != NULL) //on ouvre le fichier et verifie si on y arrive
    {
        while (!feof(file))
        {
            fread(&tmp, 1, 1, file);
            if ((tmp == ' ') | (tmp == '\n') | (tmp == '.') |
                (tmp == ',') | (tmp == ';') | (tmp == '?') |
                (tmp == '!') | (tmp == ':') | (tmp == '[') |
                (tmp == ']') | (tmp == '{') | (tmp == '}') |
                (tmp == '/') | (tmp == '\'') | (tmp == '@') |
                (tmp == '\"')| (tmp == '-') | (tmp == '_') |
                (tmp == '#') | (tmp == '$') | (tmp == '%') |
                (tmp == '&') | (tmp == '*') | (tmp == '+') |
                (tmp == '='))
            {
                if (test == 1)
                {
                    test = 0;
                    strcpy(tableau[j], tampon);
                    j++;
                    i = 0;
                    for (int c = 0; c<20; c++)
                    {
                        tampon[c] = '\0';
                    }
                }
            }
            else
            {
                tampon[i] = tmp;
                i++;
                test = 1;
            }
        }
    }
    fclose(file);

    int IndiceTabFinal = 0;
    Word *p_wd = new Word(tableau[IndiceTabFinal], 0);
    OnlyOneTime[IndiceTabFinal] = *p_wd;
    IndiceTabFinal++;

    for (int IndiceA = 0; IndiceA<(size*nbFichier); IndiceA++)
    {
        bool test = false;
        int nb = 0;

        for (int IndiceB = 0; IndiceB<(size*nbFichier); IndiceB++)
        {
            if (strcmp(tableau[IndiceA], tableau[IndiceB]) == 0)
            {
                nb++;
            }
        }

        for (int IndiceC = 0; IndiceC<(size*nbFichier); IndiceC++)
        {
            if (strcmp(OnlyOneTime[IndiceC].m_Nom, tableau[IndiceA]) == 0)
            {
                test = true;
                OnlyOneTime[IndiceC].m_nbRecurrence = nb;
            }
        }

        if (test == false)
        {
            OnlyOneTime[IndiceTabFinal].m_Nom = tableau[IndiceA];
            OnlyOneTime[IndiceTabFinal].m_nbRecurrence = nb;
            IndiceTabFinal++;
        }
    }
    return(OnlyOneTime);
}


//Like fileArrayStr1 but use for the teatment of all words in each files
Word* FillArrayStr2(char* SourceFile, int NbString)
{
    //NbString = NbString+1;
    FILE *file;
    char tmp;
    int i = 0;
    int test = 0;
    char tampon[20];
    int IndiceA = 0,IndiceB = 0,IndiceC = 0 ;

    char **tableau = (char**) malloc ((NbString)* sizeof(char*));

    for (int j=0; j<(NbString) ; j++)
    {
        tableau[j] = (char*) malloc ((20)* sizeof(char));
        if (tableau==NULL) exit (1);
    }

    Word *OnlyOneTime; // array with each word only time to compare.
    OnlyOneTime = (Word*) calloc ((NbString), sizeof(Word*));
    if (OnlyOneTime==NULL) exit (1);
    for (int k=0; k<(NbString) ; k++)
    {
       Word *p_Word = new Word(" ",0);
        if (p_Word==NULL) exit (1);
        OnlyOneTime[k] = *p_Word;
    }

    for (int p = 0; p<20; p++)
    {
        tampon[p] = '\0';
    }

    int j=0;
    if((file = fopen(SourceFile, "r")) != NULL) //on ouvre le fichier et verifie si on y arrive
    {
        while (!feof(file) & (j<NbString))
        {
            fread(&tmp, 1, 1, file);
            if ((tmp == ' ') | (tmp == '\n') | (tmp == '.') |
                (tmp == ',') | (tmp == ';') | (tmp == '?') |
                (tmp == '!') | (tmp == ':') | (tmp == '[') |
                (tmp == ']') | (tmp == '{') | (tmp == '}') |
                (tmp == '/') | (tmp == '\'') | (tmp == '@') |
                (tmp == '\"')| (tmp == '-') | (tmp == '_') |
                (tmp == '#') | (tmp == '$') | (tmp == '%') |
                (tmp == '&') | (tmp == '*') | (tmp == '+') |
                (tmp == '='))
            {
                if (test == 1)
                {
                    test = 0;
                    strcpy(tableau[j], tampon);
                    //cout << tableau[j] << "  ,  ";
                    j++;
                    i = 0;
                    for (int c = 0; c<20; c++)
                    {
                        tampon[c] = '\0';
                    }
                }
            }
            else
            {
                tmp = tolower(tmp);
                tampon[i] = tmp;
                i++;
                test = 1;
            }
        }
		//cout << "end" << endl;
    }
    fclose(file);

    int IndiceTabFinal = 0;
    Word *p_wd = new Word(tableau[IndiceTabFinal], 0);
    OnlyOneTime[IndiceTabFinal] = *p_wd;
    IndiceTabFinal++;

    for ( IndiceA = 0; IndiceA<(NbString); IndiceA++)
    {
        bool test = false;
        int nb = 0;
        char *qq = tableau[IndiceA];

        for ( IndiceB = 0; IndiceB<(NbString); IndiceB++)
        {
            char *ss = tableau[IndiceB];

            if (strcmp(tableau[IndiceA], tableau[IndiceB]) == 0)
            {
                nb++;
            }
        }

        for ( IndiceC = 0; IndiceC<(NbString); IndiceC++)
        {
            char *pp = OnlyOneTime[IndiceC].m_Nom;

                if (strcmp(OnlyOneTime[IndiceC].m_Nom, tableau[IndiceA]) == 0)
                {
                    test = true;
                    OnlyOneTime[IndiceC].m_nbRecurrence = nb;
                    OnlyOneTime[IndiceC].m_Fichier = SourceFile;
                }
        }

        if (test == false)
        {
            char *tt = tableau[IndiceA];
            OnlyOneTime[IndiceTabFinal].m_Nom = tableau[IndiceA];
            OnlyOneTime[IndiceTabFinal].m_nbRecurrence = nb;
            OnlyOneTime[IndiceTabFinal].m_Fichier = SourceFile;
            IndiceTabFinal++;
        }
    }
    //	for ( IndiceC = 0; IndiceC<30; IndiceC++)
   	//{    
	//         cout << OnlyOneTime[IndiceC].m_nbRecurrence << endl;
    //         cout << OnlyOneTime[IndiceC].m_Fichier << endl;
    //         cout << OnlyOneTime[IndiceC].m_Nom << endl;
	//
    //}
    return(OnlyOneTime);
}


Word* SortArrayByNbRecurrence(Word *OnlyOneTime, int NombreDeString)
{
    int IndiceTabFinal = NombreDeString;
	//int maryam;
    for (int final1=0; final1<(IndiceTabFinal-1); final1++)
    {
        for (int final2=0; final2<(IndiceTabFinal-1); final2++)
        {
            if ((OnlyOneTime[final2].m_nbRecurrence)<(OnlyOneTime[final2+1].m_nbRecurrence))
            {
                Word *tempo = new Word(" ",0);
                *tempo = OnlyOneTime[final2];
                OnlyOneTime[final2] = OnlyOneTime[final2+1];
                OnlyOneTime[final2+1] = *tempo;
                delete tempo;
            }
        }
    }
	//	for ( maryam = 0; maryam<10; maryam++)
   	//{    
    //         cout << OnlyOneTime[maryam].m_Nom << endl;
    //}
    return(OnlyOneTime);
}

Word** SortArrayByNbTotal(Word **OnlyOneTime, int nbFichier, int nbString)
{
    for (int final1=0; final1<nbFichier; final1++)
    {
        for (int final2=0; final2<nbString; final2++)
        {
            for (int final3=0; final3<nbFichier; final3++)
            {
                for (int final4=0; final4<nbString-1; final4++)
                {
                    if ((OnlyOneTime[final3][final4].m_nbTotal)<(OnlyOneTime[final3][final4+1].m_nbTotal))
                    {
                        Word *tempo = new Word(" ",0);
                        *tempo = OnlyOneTime[final3][final4+1];
                        OnlyOneTime[final3][final4+1] = OnlyOneTime[final3][final4];
                        OnlyOneTime[final3][final4] = *tempo;
                        delete tempo;
                    }
                }
            }
        }
    }
	cout<< " here ";
    cout << OnlyOneTime[1][1].m_Nom << endl << OnlyOneTime[1][1].m_nbRecurrence;
    return(OnlyOneTime);
}





//void WriteReccurence2(Word **FinalDblArray, int NbSort, int NbString, int NbFichier)
//{
//    cout << endl;
//
//    int compteur = 0;
//    FILE *FD;
//    char retour = '\n';
//    char space = ' ';
//
//    while (compteur<NbSort)
//    {
//        int indiceASup1 = 0;
//        int indiceASup2 = 0;
//        Word tmp = FinalDblArray[0][0];
//
//        for (int indiceFichier = 0; indiceFichier<NbFichier; indiceFichier++)
//        {
//            for (int indiceString = 0; indiceString<(NbString-1); indiceString++)
//            {
//                char *test = tmp.m_Nom;
//                char *test3 = tmp.m_Fichier;
//                int test2 = tmp.m_nbRecurrence;
//
//                if (tmp.m_nbRecurrence<FinalDblArray[indiceFichier][indiceString+1].m_nbRecurrence)
//                {
//                    tmp = FinalDblArray[indiceFichier][indiceString+1];
//                    indiceASup1 = indiceFichier;
//                    indiceASup2 = indiceString+1;
//                }
//            }
//        }
//        if((FD = fopen("Result.txt", "a+")) != NULL)
//        {
//            fprintf(FD, "\t%s\t\t", tmp.m_Nom);
//            for (int indiceFichier = 0; indiceFichier<NbFichier; indiceFichier++)
//            {
//                int test = 0; //initialise "test" to 0 for each file
//                for (int indiceString = 0; indiceString<NbString; indiceString++)
//                {
//                    if (test == 0)
//                    {
//                        char* t = FinalDblArray[indiceFichier][indiceString].m_Nom;
//                        char* y = tmp.m_Nom;
//                        int u = FinalDblArray[indiceFichier][indiceString].m_nbRecurrence;
//                        if (strcmp(FinalDblArray[indiceFichier][indiceString].m_Nom,tmp.m_Nom)==0)
//                        {
//                            fprintf(FD, "\t%d", FinalDblArray[indiceFichier][indiceString].m_nbRecurrence);
//                            FinalDblArray[indiceFichier][indiceString].m_nbRecurrence = 0;
//                            test = 1;
//                        }
//                    }
//                }
//                if (test == 0)
//                {
//                    fprintf(FD, "\t%d", 0);
//                }
//            }
//        }
//        fprintf(FD, "%s", "\n");
//        fclose(FD);
//        compteur++;
//        //delete of the most useful word
//        FinalDblArray[indiceASup1][indiceASup2].m_nbRecurrence = 0;
//        FinalDblArray[indiceASup1][indiceASup2].m_Nom = " ";
//    } // end of while
//}



void WriteReccurence2(Word **FinalDblArray, int NbSort, int NbString, int NbFichier)
{
    //cout << endl;
    int compteur = 0;
    FILE *FD;
    char retour = '\n';
    char space = ' ';
    int total ;
	//int maryam1, maryam2;

    while (compteur<NbSort)
    {
        int indiceASup1 = 0;
        int indiceASup2 = 0;
        Word tmp = FinalDblArray[0][0];

        for (int indiceFichier = 0; indiceFichier<NbFichier; indiceFichier++)
        {
            for (int indiceString = 0; indiceString<(NbString); indiceString++)
            {
                char *test = tmp.m_Nom;
                char *test3 = tmp.m_Fichier;
                int test2 = tmp.m_nbRecurrence;
                int a = tmp.m_nbTotal;
                char *aa = FinalDblArray[indiceFichier][indiceString].m_Nom;

                if (tmp.m_nbTotal<FinalDblArray[indiceFichier][indiceString].m_nbTotal)
                {
                    tmp = FinalDblArray[indiceFichier][indiceString];
                    indiceASup1 = indiceFichier;
                    indiceASup2 = indiceString;
                }
            }
        }

        if((FD = fopen("Result.txt", "a+")) != NULL)
        {
            total = tmp.m_nbTotal;
            fprintf(FD, "%s\t", tmp.m_Nom);
            for (int indiceFichier = 0; indiceFichier<NbFichier; indiceFichier++)
            {
                int test = 0; //initialise "test" to 0 for each file
                for (int indiceString = 0; indiceString<NbString; indiceString++)
                {
                    if (test == 0)
                    {
                        char* t = FinalDblArray[indiceFichier][indiceString].m_Nom;
                        char* y = tmp.m_Nom;
                        int u = FinalDblArray[indiceFichier][indiceString].m_nbRecurrence;
                        if (strcmp(FinalDblArray[indiceFichier][indiceString].m_Nom,tmp.m_Nom)==0)
                        {
                            fprintf(FD, "\t%d", FinalDblArray[indiceFichier][indiceString].m_nbRecurrence);
							//
							//cout<<FinalDblArray[indiceFichier][indiceString].m_nbRecurrence<<"  ";
						    //
                            FinalDblArray[indiceFichier][indiceString].m_nbRecurrence = 0;
                            FinalDblArray[indiceFichier][indiceString].m_nbTotal = 0;
                            test = 1;
                        }
                    }
                }
                if (test == 0)
                {
                    fprintf(FD, "\t%d", 0);
                }
            }
        }
        fprintf(FD, "\t total : %d", total);
        fprintf(FD, "%s", "\n");
        fclose(FD);
        compteur++;
        //delete of the most useful word
        FinalDblArray[indiceASup1][indiceASup2].m_nbTotal = 0;
        FinalDblArray[indiceASup1][indiceASup2].m_nbRecurrence = 0;
        FinalDblArray[indiceASup1][indiceASup2].m_Nom = " ";
    } // end of while

	//just for test, delete it
	//for(maryam1=0; maryam1<10; maryam1++)
	//{	for(maryam2=0; maryam2<10; maryam2++)

	//{
	//	cout<<FinalDblArray[maryam1][maryam2].m_Nom<<"  ";
	//	cout<<FinalDblArray[maryam1][maryam2].m_Fichier<<"  ";
	//}
	//cout<<endl;
	//cout<<endl;
	//}

}

Word **FillNbTotal(Word **FinalDblArray, int nbFichier, int nbString, int nb)
{
    for (int indiceFichierBase=0; indiceFichierBase<nbFichier; indiceFichierBase++)
    {
        for (int indiceStringBase=0; indiceStringBase<(nbString); indiceStringBase++)
        {
            //the words aren't yet counted
            if (FinalDblArray[indiceFichierBase][indiceStringBase].m_IsCounted == 0);
            {
                Word tmp = FinalDblArray[indiceFichierBase][indiceStringBase];

                //sort by word : str1
                char *str1 = tmp.m_Nom;
                int compteur = /*tmp.m_nbRecurrence*/0;
                tmp.m_IsCounted = 1;
                FinalDblArray[indiceFichierBase][indiceStringBase].m_IsCounted = 1;

                for (int indiceFichier=0; indiceFichier<nbFichier; indiceFichier++)
                {
                    for (int indiceString=0; indiceString<(nbString); indiceString++)
                    {
                        char *str2 = FinalDblArray[indiceFichier][indiceString].m_Nom;
                        if (strcmp(str2, str1) == 0)
                        {
                            compteur += FinalDblArray[indiceFichier][indiceString].m_nbRecurrence;
                            FinalDblArray[indiceFichier][indiceString].m_IsCounted = 1;
                        }
                    }
                }

                for (int indiceFichier=0; indiceFichier<nbFichier; indiceFichier++)
                {
                    for (int indiceString=0; indiceString<(nbString); indiceString++)
                    {
                        char *str2 = FinalDblArray[indiceFichier][indiceString].m_Nom;
                        if (strcmp(str2, str1) == 0)
                        {
                            FinalDblArray[indiceFichier][indiceString].m_nbTotal = compteur;
                            FinalDblArray[indiceFichier][indiceString].m_IsCounted = 1;
                        }
                    }
                }
            }
        }
    }
	
    cout << endl ;
  // FinalDblArray = SortArrayByNbTotal(FinalDblArray, nbFichier, nbString );
  //  for (int indiceFichier=0; indiceFichier<nbFichier; indiceFichier++)
  // {
  //   for (int indiceString=0; indiceString<(nbString); indiceString++)
  //      {
   //         cout << FinalDblArray[indiceFichier][indiceString].m_Nom << " ";
   //         cout << FinalDblArray[indiceFichier][indiceString].m_nbTotal << " ";
   //         cout << FinalDblArray[indiceFichier][indiceString].m_nbRecurrence << " ";
   //         cout << FinalDblArray[indiceFichier][indiceString].m_Fichier << endl;
   //    }
   // }
    return (FinalDblArray);
}

void WriteReccurence(Word *OnlyOneTime, int NbSort, int NombreDeString)
{
    char *aa = " on : ";
    char *bb = "\t";
    char *cc = " words or ";
    cout << endl;

    FILE *FD;
    char retour = '\n';
    char space = ' ';

    if((FD = fopen("Result.txt", "a+")) != NULL)
    {
        char FDW;
        for (int LesPlusGrd = 0; LesPlusGrd<NbSort; LesPlusGrd++)
        {
            fprintf(FD, "%s", "               ");
            fprintf(FD, "%s", bb);
            for (int i = 0; i<20; i++)
            {
                FDW = OnlyOneTime[LesPlusGrd].m_Nom[i];
                if (FDW != '\0')
                {
                    fwrite(&FDW, 1, sizeof(char), FD);
                }
                else
                {
                    i=20;
                    fwrite(&space,1,sizeof(char),FD);
                    fprintf(FD, "%s", "               ");
                    fprintf(FD, "%s", bb);
                    fprintf(FD, "%i", OnlyOneTime[LesPlusGrd].m_nbRecurrence); //Will write the integer as a string (ASCII)
                    fprintf(FD, "%s", "               ");
                    fprintf(FD, "%s", bb);
                    float calcul = (((float)(OnlyOneTime[LesPlusGrd].m_nbRecurrence))/((float)NombreDeString));
                    fprintf(FD, "%f", calcul);
                    fwrite(&retour,1,sizeof(char),FD);
                }
            }
       }
    }
    fclose(FD);
}


int Nbstring1(int nbFichier, char **tab)
{
    int NbString2 = 0, NbString=0; 
	NbString= 10000;
   // for (int i=0; i<nbFichier; i++)
  //  {
        //count the number of word in each file of tab[]
      //  NbString2 = NbStr(tab[i]);
       // if (NbString2<=NbString)
      //  {
         //   NbString = (NbString2-1);
      //  }
      //  cout <<  "Number of string in the text "<< i << " : " << (NbString2-1) << endl;
  //  }
    return NbString;
}


void TraitementTotaliteFichier(char **tab, int nbFichier)
{
    int NbString = 0, nb;
    FILE *FD;
    cout << "how many words you want? (the Results will be in Result.txt...)" << endl;
    cin >> nb;

    NbString = Nbstring1(nbFichier,tab);

    cout << "please wait ............ " << endl;
    Word *FinalTab;
    Word *temp;
    Word **FinalDblArray = (Word**) malloc ((nbFichier)* sizeof(Word*));

    for (int j=0; j<(nbFichier) ; j++)
    {
        FinalDblArray[j] = (Word*) malloc ((nb)* sizeof(Word));
        if (FinalDblArray==NULL) exit (1);
    }

    if((FD = fopen("Result.txt", "w")) != NULL)
    {
        fprintf (FD, "  Number of Strings use in each files : %d \n\n",NbString);
        fprintf (FD, "%s","  \t");
    }
    fclose(FD);
    char retour = '\n';
    for (int i=0; i<nbFichier; i++)
    {
        cout << "File Treatment : " << tab[i] << endl;
        temp = FillArrayStr2(tab[i], NbString);

        if((FD = fopen("Result.txt", "a+")) != NULL)
        {
            int oo = 0;
            char Titre = tab[i][oo];
            fprintf(FD, "%s","   \t");
            while (Titre!='\0')
            {
                fwrite(&Titre, 1, sizeof(char), FD);
                oo++;
                Titre = tab[i][oo];
            }
        }
        fclose(FD);
        FinalDblArray[i] = SortArrayByNbRecurrence(temp, NbString);
    }

    cout << "Wait... treatment in progress" << endl;
    FinalDblArray = FillNbTotal(FinalDblArray, nbFichier, NbString, nb);

    if((FD = fopen("Result.txt", "a+")) != NULL)
    {
        fwrite(&retour,1,sizeof(char),FD);
        fwrite(&retour,1,sizeof(char),FD);
    }
    fclose(FD);
    WriteReccurence2(FinalDblArray, nb, NbString, nbFichier);
}


void CountNumberOfSpacesFather(char *SourceFile,
                               /*int i,*/ /*indice du tableau des fichiers*/
                               unsigned int* tableauResultat)
{
    FILE *FD;
    FILE *fp;
    fp = fopen("Result2.txt", "rb");
    if (fp == NULL)
    {
        /* L'ouverture du fichier "Result2.txt" a echoue => le fichier "Result2.txt" n'existe pas. */
        FD = fopen("Result2.txt", "w");
    }
    else
    {
        fclose(fp);
        /* Le fichier a pu etre ouvert => le fichier existe. */
        FD = fopen("Result2.txt", "a+");
    }

    if(FD != NULL)
        {
            char retour = '\n';
            char tabulation = '\t';
            fwrite(&retour,1,sizeof(char),FD);
            fprintf(FD, "texte %s", SourceFile);
            fwrite(&retour,1,sizeof(char),FD);
            fwrite(&tabulation,1,sizeof(char),FD);
            fwrite(&tabulation,1,sizeof(char),FD);
            for (unsigned int z = 1; z<(tableauResultat[0]); z++)
            {
                unsigned int a = tableauResultat[z];
                fprintf(FD, "%d ", tableauResultat[z]);
                if (z%20 == 0) //retour a la ligne toutes les 10 iterations
                {
                    fwrite(&retour,1,sizeof(char),FD);
                    fwrite(&tabulation,1,sizeof(char),FD);
                    fwrite(&tabulation,1,sizeof(char),FD);
                }
            }
        }
        else
        {
            cout << "problem to open the result file" << endl;
            exit(0);
        }
        fclose(FD);
}


//count the number of space between 2 occurences of a string in parameter
void CountNumberOfSpaces(char* SourceFile, char *str)
{
    FILE *file = NULL;
    char tmp;
    unsigned int i = 0, j=0;
    int Compteur = 0, indice = 1; // l'indice 0 sert a poser la taille du tableau de retour
    int test = 0;
    char tampon[20];
    char** tableau;

    unsigned int NbString = (unsigned int)(NbStr(SourceFile)-1);
    cout <<  "Number of string in the text " << SourceFile << " : " << NbString << endl;

    tableau = (char**) malloc ((NbString)* sizeof(char*));

    for (unsigned int k=0; k<(NbString+1) ; k++)
    {
        tableau[k] = (char*) malloc ((20)* sizeof(char));
        if (tableau==NULL) exit (1);
    }

    unsigned int *tabResult = (unsigned int*) calloc ( NbString, sizeof(unsigned int));
    if (tabResult==NULL) exit (1);

    for (int p = 0; p<20; p++)
        tampon[p] = '\0';

    if((file = fopen(SourceFile, "r")) != NULL) //try to open file
    {
        while ((!feof(file)) & (i<NbString))
        {
            fread(&tmp, 1, 1, file);
            if ((tmp == ' ') | (tmp == '\n') | (tmp == '.') |
                (tmp == ',') | (tmp == ';') | (tmp == '?') |
                (tmp == '!') | (tmp == ':') | (tmp == '[') |
                (tmp == ']') | (tmp == '{') | (tmp == '}') |
                (tmp == '/') | (tmp == '\'') | (tmp == '@') |
                (tmp == '\"')| (tmp == '-') | (tmp == '_') |
                (tmp == '#') | (tmp == '$') | (tmp == '%') |
                (tmp == '&') | (tmp == '*') | (tmp == '+') |(tmp == '``')|
                (tmp == '='))
            {
                if (test == 1)
                {
                    test = 0;
                    strcpy(tableau[j], tampon);
                    j++;
                    i = 0;
                    for (int c = 0; c<20; c++)
                        tampon[c] = '\0';
                }
            }
            else
            {
                tampon[i] = tmp;
                i++;
                test = 1;
            }
        }
    }
    fclose(file);
    j = 0;
    while ( j <NbString)
    {
        while ((strcmp(tableau[i], str)!=0) & (i<NbString))
            i++;
        if (strcmp(tableau[i], str)==0)
        {
            Compteur = 0;
            i++;
            //while we havn't the same word
            while ((strcmp(tableau[i], str)!=0) & (i<NbString))
            {
                Compteur++;
                i++;
            }
            tabResult[indice] = Compteur;
            indice++;
        }
        j=i;
        tabResult[0] = indice-1;
    }
    CountNumberOfSpacesFather(SourceFile,tabResult);
}


Word* FillArrayStr3(char* tab[])
//
//FillArrayStr2(tab[i], NbString);
{
	//
    //NbString = NbString+1;
    FILE *file;
    char tmp,tmp2;
    int i,m = 0;
    int test = 0;
    char tampon[20],tampon2[20];
    int IndiceA = 0,IndiceB = 0,IndiceC = 0 ;
	double sigma[40];//nbfichier=40
	int IndiceText,IndiceDistance,j,NoText2;
	float mu;
	char* SourceFile;
	int NbString=4000;
	const int NoWord=10;
	
    const int NoText=40;
	double AverageSigma[100];
	
	//char functionword[20][NoWord];
	int distance[1000];
    

    char **tableau = (char**) malloc ((NbString)* sizeof(char*));
	 char **tableau2 = (char**) malloc ((NbString)* sizeof(char*));
	 char **functionword = (char**) malloc ((NoWord)* sizeof(char*));
   
	for (int n=0; n<40; n++)
         sigma[n] = 0;

    
    for (int j=0; j<(NbString) ; j++)
   {
       tableau[j] = (char*) malloc ((20)* sizeof(char));
      if (tableau==NULL) exit (1);
 }

	 for (int j=0; j<(NbString) ; j++)
  {
       tableau2[j] = (char*) malloc ((20)* sizeof(char));
       if (tableau2==NULL) exit (1);
 }



	for (int j=0; j<(100) ; j++)
    {
       functionword[j] = (char*) malloc ((20)* sizeof(char));
        if (functionword==NULL) exit (1);
    }
cout<<"here";
	//geting all function word
	i=0;
	j=0;
     if((file = fopen("words.txt", "r")) != NULL) //try to open file
    {
     while ((!feof(file)) & (j<100))
      {
            fread(&tmp2, 1, 1, file);
            if ((tmp2 == ' ') | (tmp2 == '\n') | (tmp2 == '.') |
               (tmp2 == ',') | (tmp2 == ';') | (tmp2 == '?') |
              (tmp2 == '!') | (tmp2 == ':') | (tmp2 == '[') |
               (tmp2 == ']') | (tmp2 == '{') | (tmp2 == '}') |
               (tmp2 == '/') | (tmp2 == '\'') | (tmp2 == '@') |
               (tmp2 == '\"')| (tmp2 == '-') | (tmp2 == '_') |
               (tmp2 == '#') | (tmp2 == '$') | (tmp2 == '%') |
                (tmp2 == '&') | (tmp2 == '*') | (tmp2 == '+') |(tmp == '``')|
              (tmp2 == '='))
            {
                if (test == 1)
                {
                   test = 0;
                   strcpy(tableau2[j], tampon2);
					
                  j++;
                    i = 0;
                  for (int c = 0; c<20; c++)
                       tampon2[c] = '\0';
            }
           }
          else
            {
                tampon2[i] = tmp2;
                i++;
                test = 1;
            }
       }
	 }
   fclose(file);
   
//	for(int m=1; m<(NoWord+1); m++)
//	{
	//cout<<m;	
	//strcpy(functionword[m-1],tableau2[m+92]);
	//cout<<functionword[m-1]<<endl;
	//	
//	}
	// cout<<"****end****"<<endl;

    //
   Word *OnlyOneTime; // array with each word only time to compare.
   OnlyOneTime = (Word*) calloc ((NbString), sizeof(Word*));
    if (OnlyOneTime==NULL) exit (1);
    for (int k=0; k<(NbString) ; k++)
    {
       Word *p_Word = new Word(" ",0);
        if (p_Word==NULL) exit (1);
        OnlyOneTime[k] = *p_Word;
    }

    for (int p = 0; p<20; p++)
    {
        tampon[p] = '\0';
    }

     j=0;
	 i=0;

	 for (int m=0; m<NoWord; m++)//for each function word
	 {

	for (int IndiceText=0; IndiceText<NoText; IndiceText++) //in each text
	{
		
      j=0;
	  SourceFile=tab[IndiceText];

      if((file = fopen(SourceFile, "r")) != NULL) 
       {
       
		
		int counter=0;
		IndiceDistance=0;
        while (!feof(file) & (j<NbString))
			 
          {
            fread(&tmp, 1, 1, file);
            if ((tmp == ' ') | (tmp == '\n')| (tmp == '.') |
                (tmp == ',') | (tmp == ';') | (tmp == '?') |
                (tmp == '!') | (tmp == ':') | (tmp == '[') |
                (tmp == ']') | (tmp == '{') | (tmp == '}') |
                (tmp == '/') | (tmp == '\'')| (tmp == '@') |
                (tmp == '\"')| (tmp == '-') | (tmp == '_') |
                (tmp == '#') | (tmp == '$') | (tmp == '%') |
                (tmp == '&') | (tmp == '*') | (tmp == '+') |(tmp == '`')|
                (tmp == '='))
            {
                if (test == 1)
                {
                    test = 0;
                    strcpy(tableau[j], tampon);
                    //cout<<j<<tableau[j]<<"  ****  ";
					if (strcmp(functionword[m],tableau[j]) == 0)
					{

						//cout<<" "<<functionword[m]<<" and ";//test
						//cout<<tableau[j]<<" is same"<<endl;//test

						//cout<<" j="<<j<<",";//test

						//cout<<"counter="<<counter<<":";//test

						distance[IndiceDistance]=j-counter;
					    counter=j;
						cout<<distance[IndiceDistance]<<",";//test
						cout<<",j is"<<j<<",";
                        IndiceDistance++;
						
					 }
					
                    j++;
                    i = 0;
                    for (int c = 0; c<20; c++)
                    {
                        tampon[c] = '\0';
                    }
				}
            }
            else
            {
                tmp = tolower(tmp);
                tampon[i] = tmp;
                i++;
                test = 1;
			}
		}
          
		  
		//mu=0;
        //for (int n=0; n<IndiceDistance; n++)
		//	if (distance[n]>0)
	    //   mu = mu + distance[n];
		 
		
		// mu=(mu/IndiceDistance);
		// if (mu>0)
		//cout<<"mu for "<<functionword[m]<<" in text "<<IndiceText<<":"<<mu<<endl;

       // for (int n=0; n<IndiceDistance; n++)
       //    sigma[IndiceText]=0;

		//for (int n=0; n<IndiceDistance; n++)
		//	sigma[IndiceText] = sigma[IndiceText] + ((distance[n]-mu)*(distance[n]-mu));
			


   // cout<<"sigma for "<<functionword[m]<<" in text "<<IndiceText<<" : "<<sigma[IndiceText]<<endl;	
	//	if (IndiceDistance!=0)
	//	{
	 //     sigma[IndiceText]= (sigma[IndiceText]/IndiceDistance);//this is for one function word and one text
     //     sigma[IndiceText]= sqrt(sigma[IndiceText]); //this is for one function word and one text 
	//	}
	//	else
      //    sigma[IndiceText]=0;

 }
		
	  }
      fclose(file);

//	  AverageSigma[m]=0;
   //    NoText2=NoText;
  //    for (IndiceText=0; IndiceText<NoText; IndiceText++)
	//	  if (sigma[IndiceText]>0)
    //        AverageSigma[m] = AverageSigma[m] + sigma[IndiceText];
	//	  else
	//		NoText2=NoText2-1;


	//  AverageSigma[m]=AverageSigma[m]/NoText2;
	  
	}
//
	// for (int j=0; j<NoWord; j++)
	//	 cout<<"avareage sigma "<<functionword[j]<<":"<< AverageSigma[j]<<endl;
          

   
	  }
	 
#endif 
	  
	  
	  BASEFUNTIONSFILE_H_INCLUDED
