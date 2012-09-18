/* Generate lists of function words
 
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




//  Author FP Huchet
//  Text treatment
//      main.cpp
//  Creation date : 28/06/2010
//  Last modification : 05/07/2010

// #include "stdafx.h"
#include "BaseFuntionsFile.h"


#include <string.h>
#include <stdio.h>
#include <math.h>



using namespace std;
//char *tab[]={
	
//"AD_AB.txt","BB_CC.txt","CD_BH.txt","HJ_AA.txt","RD_BB.txt","ZG_BE.txt",
//"AD_AC.txt","BB_CF.txt","CD_BL.txt","HJ_AD.txt","RD_BT.txt","ZG_BL.txt",
//"AD_AD.txt","BB_CR.txt","CD_BR.txt","HJ_AM.txt","RD_CC.txt","ZG_BZ.txt",
//"AD_AG.txt","BB_CU.txt","CD_CC.txt","HJ_AP.txt","RD_CL.txt","ZG_CC.txt",
//"AD_BC.txt","BB_FU.txt","CD_CH.txt","HJ_BH.txt","RD_CM.txt","ZG_DB.txt",
//"AD_CP.txt","BB_GE.txt","CD_DC.txt","HJ_BJ.txt","RD_CO.txt","ZG_DG.txt",
//"AD_DD.txt","BB_GI.txt","CD_DM.txt","HJ_BL.txt","RD_FU.txt","ZG_DW.txt",
//"AD_DL.txt","BB_HF.txt","CD_DS.txt","HJ_CF.txt","RD_GO.txt","ZG_HD.txt",
//"AD_DR.txt","BB_HS.txt","CD_GE.txt","HJ_CO.txt","RD_IF.txt","ZG_LE.txt",
//"AD_DU.txt","BB_IE.txt","CD_GI.txt","HJ_DL.txt","RD_JP.txt","ZG_LM.txt",
//"AD_EB.txt","BB_JL.txt","CD_GS.txt","HJ_DM.txt","RD_KJ.txt","ZG_LP.txt",
//"AD_FG.txt","BB_LD.txt","CD_HD.txt","HJ_EP.txt","RD_LH.txt","ZG_LS.txt",
//"AD_GF.txt","BB_LL.txt","CD_HL.txt","HJ_FC.txt","RD_LR.txt","ZG_LT.txt",
//"AD_HB.txt","BB_LM.txt","CD_HM.txt","HJ_GF.txt","RD_LU.txt","ZG_LW.txt",
//"AD_LB.txt","BB_LO.txt","CD_HO.txt","HJ_GL.txt","RD_MB.txt","ZG_ME.txt",
//"AD_LW.txt","BB_LS.txt","CD_HR.txt","HJ_IC.txt","RD_MC.txt","ZG_MF.txt",
//"AD_MC.txt","BB_LT.txt","CD_HT.txt","HJ_IE.txt","RD_NF.txt","ZG_MR.txt",
//"AD_MD.txt","BB_PH.txt","CD_LD.txt","HJ_JC.txt","RD_PA.txt","ZG_PC.txt",
//"AD_PB.txt","BB_PK.txt","CD_LL.txt","HJ_LH.txt","RD_PM.txt","ZG_RO.txt",
//"AD_RC.txt","BB_RC.txt","CD_LT.txt","HJ_LM.txt","RD_QL.txt","ZG_RP.txt",
//"AD_RL.txt","BB_RD.txt","CD_MC.txt","HJ_MA.txt","RD_RC.txt","ZG_RT.txt",
//"AD_SF.txt","BB_SD.txt","CD_MH.txt","HJ_MD.txt","RD_RF.txt","ZG_SB.txt",
//"AD_SH.txt","BB_TB.txt","CD_ML.txt","HJ_MF.txt","RD_TA.txt","ZG_TL.txt",
//"AD_TP.txt","BB_TG.txt","CD_MS.txt","HJ_TA.txt","RD_TC.txt","ZG_UP.txt",
//"AD_VF.txt","BB_UC.txt","CD_OT.txt","HJ_TC.txt","RD_TD.txt","ZG_WF.txt",
//"AD_WL.txt","BB_WM.txt","CD_TC.txt","HJ_TE.txt","RD_TM.txt","ZG_YF.txt"};


char*tab[]={
"LU01.txt","LU02.txt","LU03.txt","LU04.txt","MK01.txt","MK02.txt","MK03.txt","MK04.txt",
"MT01.txt","MT02.txt","MT03.txt","MT04.txt","JO01.txt","JO02.txt","JO03.txt","JO04.txt",
"HEBR.txt","PA01.txt","PA02.txt","PA03.txt","PA04.txt","CL01.txt","CL02.txt","CL03.txt",
"CL04.txt","IG01.txt","IG02.txt","IG03.txt","IG04.txt","BA01.txt","BA02.txt","BA03.txt","BA04.txt"
};
//33 texts

//char *tab[]={"1.txt"};

//char *tab[]={
//"PE01.txt","JA01.txt","JO01.txt","JO02.txt","JO03.txt","JO04.txt","JO05.txt","JO06.txt","JO07.txt","JO08.txt","JO09.txt",
//"LU01.txt","LU02.txt","LU03.txt","LU04.txt","LU05.txt","LU06.txt","LU07.txt","LU08.txt","LU09.txt","LU10.txt","LU11.txt",
//"MK01.txt","MK02.txt","MK03.txt","MK04.txt","MT05.txt","MT06.txt","MT01.txt","MT02.txt","MT03.txt","MT04.txt","MT05.txt",
//"MT06.txt","MT07.txt","MT08.txt","MT09.txt","MT10.txt","PA01.txt","PA02.txt","PA03.txt","PA04.txt","PA05.txt","PA06.txt",
//"PA07.txt","PA08.txt","PA08.txt","PA09.txt","PA10.txt","PA11.txt","PA12.txt","PA13.txt","PA14.txt","CL01.txt","CL02.txt",
//"CL03.txt","CL04.txt","CL05.txt","IG01.txt","IG02.txt","IG03.txt","IG04.txt","BR01.txt","BR02.txt","BR03.txt","BR04.txt",
//"PL01.txt","HE01.txt"
//};

//char *tab[]={"FederalistNo1.txt","FederalistNo2.txt","FederalistNo3.txt","FederalistNo4.txt","FederalistNo5.txt",
//             "FederalistNo6.txt","FederalistNo7.txt","FederalistNo8.txt","FederalistNo9.txt","FederalistNo10.txt",
//			 "FederalistNo11.txt","FederalistNo12.txt","FederalistNo13.txt","FederalistNo14.txt","FederalistNo15.txt",
 //            "FederalistNo16.txt","FederalistNo17.txt","FederalistNo18.txt","FederalistNo19.txt","FederalistNo20.txt",
//			 "FederalistNo21.txt","FederalistNo22.txt","FederalistNo23.txt","FederalistNo24.txt","FederalistNo25.txt",
 //            "FederalistNo26.txt","FederalistNo27.txt","FederalistNo28.txt","FederalistNo29.txt","FederalistNo30.txt",
//			 "FederalistNo31.txt","FederalistNo32.txt","FederalistNo33.txt","FederalistNo34.txt","FederalistNo35.txt",
 //            "FederalistNo36.txt","FederalistNo37.txt","FederalistNo38.txt","FederalistNo39.txt","FederalistNo40.txt",
//			 "FederalistNo41.txt","FederalistNo42.txt","FederalistNo43.txt","FederalistNo44.txt","FederalistNo45.txt",
 //            "FederalistNo46.txt","FederalistNo47.txt","FederalistNo48.txt","FederalistNo49.txt","FederalistNo50.txt",
//			 "FederalistNo51.txt","FederalistNo52.txt","FederalistNo53.txt","FederalistNo54.txt","FederalistNo55.txt",
//             "FederalistNo56.txt","FederalistNo57.txt","FederalistNo58.txt","FederalistNo59.txt","FederalistNo60.txt",
//			 "FederalistNo61.txt","FederalistNo62.txt","FederalistNo63.txt","FederalistNo64.txt","FederalistNo65.txt",
//             "FederalistNo66.txt","FederalistNo67.txt","FederalistNo68.txt","FederalistNo69.txt","FederalistNo70.txt",
//			 "FederalistNo71.txt","FederalistNo72.txt","FederalistNo73.txt","FederalistNo74.txt","FederalistNo75.txt",
//             "FederalistNo76.txt","FederalistNo77.txt","FederalistNo78.txt","FederalistNo79.txt","FederalistNo80.txt",
//			 "FederalistNo81.txt","FederalistNo82.txt","FederalistNo83.txt","FederalistNo84.txt","FederalistNo85.txt"
//};


int main()
{
//nb file
   int nbFichier = 33, NbString;
    char str[100];
    char *str1;
    char chaine[1000];
    char **tableau;
  //  int NbString, indiceBase=0,indiceHaut = 0;



/*nb word you want to see*/
    int nb = 0;

//    NombreDeCarateres = NbChar("fichier2.txt");
//    cout << "Number of characters in the file : " << NombreDeCarateres << endl;

//    NbString1 = NbStr("fichier1.txt");
//    cout << endl << "Number of string in the text : " << NbString1 << endl;
//    NbString2 = NbStr("fichier2.txt");
//    cout << endl << "Number of string in the text : " << NbString2 << endl;

    Nbstring1(nbFichier, tab);


/******************************
//test sans concatenation,
//traitement de chaque fichiers independament.
//UTILISATION DE FILLARRAYSTR2
**********************************/
	
bool test = ValidFile(tab, nbFichier);
    if (test == true)
    {
        cout << "No problem in files names." << endl;
        TraitementTotaliteFichier(tab, nbFichier);
		FillArrayStr3(tab);
    }
    else
    {
        cout << "Problem in a file name. you must check them...." << endl;
    }


/*******************************************
//  for the array of files
//  Traitement d'un ensemble de fichiers
//  representant tout la concatenation des fichiers passes en parametre (tab[])
//  UTILISATION DE FILLARRAYSTR1
*******************************************/
   NbString = Nbstring1(nbFichier,tab);
// cout <<  "Number of string in the text : " << NbString << endl;

       tableau = (char**) malloc ((NbString*nbFichier) * sizeof(char*));
     for (int j=0; j<(NbString*nbFichier); j++)
        {
            tableau[j] = (char*) malloc ((15) * sizeof(char));
       }
   WriteNewFile("FileOut.txt", NbString, tab);
    Word *FinalTab = FillArrayStr1("FileOut.txt", tableau, &NbString, &nbFichier);
    cout << "how many words you want? (the Result will be in Result.txt...)" << endl;
   cin >> nb;

   WriteReccurence(FinalTab, nb, NbString);

   cout << "give the string (to know how many there are)" << endl;

  scanf("%s", chaine);

   CountRecurrence(chaine);


/**************************
Plusieurs tests pour tester les fonctions
ecrites de base: Several tests to demonstrate the capabilities
written basic
**************************/
   // to test the upper qnd lower functions
  //  char *chain="This IS A StrinG";
  //  chain = str_tolower(chain);
  //  cout << "Lowercase : "<< chain << endl;
  //  chain = str_toupper(chain);
  //  cout << "Lowercase : "<< chain << endl;

  //  to test the str_istr function
   // char *petiteChaine = "A";
   // int a = str_istr(chain, petiteChaine);
   // cout << "number of substring index : "<< a << endl;

  // to test the jonction function :
  //  str = str_join(str, " w");
  //  cout<< str << endl;
  //  NombreDeRecurences = CountAllString("fichier.txt", str);


/***********************
reflect the number of words between every
occurrence of the word given in parameter.
***********************/
//    cout << "enter your word" << endl;
//    scanf ("%s",str);
//    for (int t=0; t<nbFichier; t++)
//        {CountNumberOfSpaces(tab[t], str);}
  //  return (0);

}
