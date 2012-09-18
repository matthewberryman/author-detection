%{

Matlab code for generating an SVM model, predicting, and evaluating using
leave one out cross-validation.

(c) Maryam Ebrahim, 2012

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

%}


NofCorrect=0;
for i=1:168 
   data=data2000words;
   data(i,:)=[];
   Model=svmtrain(data(1:167,1),data(1:167,2:95),'-r 2000, -g 0.0005, -t 1');
   accu(i)=svmpredict(data2000words(i,1),data2000words(i,2:95),Model);
   if accu(i)==data2000words(i,1)
       NofCorrect=NofCorrect+1;
   end
end
accuracy=(NofCorrect/168)*100

