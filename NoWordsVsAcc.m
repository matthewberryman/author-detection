
ine Greek Texts	Word.h
mberryma@guanshiyin:~/Documents/author-detection$ vi LooCV.m 

%{

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
for i=1:100
 Model2(i)=svmtrain(data2000words(:,1),data2000words(:,2:i+1),'-r 2000, -g 0.0005, -v 168, -t 1'); 

 end
