/* Define a Word class for keeping track of seen words
 
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
 
 */

#ifndef WORD_H
#define WORD_H


class Word
{
    public:
        Word(char *name, int nbFois)
        {
            m_nbRecurrence = nbFois;
            m_Nom = name;
            m_Fichier = "";
            m_nbTotal = 0;
            m_IsCounted = 0;
        }

        void IncreRec()
        {
            m_nbRecurrence++;
        }

        virtual ~Word() {}

        int m_nbRecurrence;
        int m_nbTotal;
        char *m_Nom;
        char *m_Fichier;
        int m_IsCounted;
    protected:
    private:

};

#endif // WORD_H
