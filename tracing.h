/*
QUAD v2.0
final revision January 24th, 2014

This file is part of QUAD Toolset available @:
http://sourceforge.net/projects/quadtoolset

Copyright © 2008-2014 Arash Ostadzadeh (ostadzadeh@gmail.com)
http://www.linkedin.com/in/ostadzadeh


QUAD is free software: you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of 
the License, or (at your option) any later version.

QUAD is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU Lesser General Public License for more details. You should have 
received a copy of the GNU Lesser General Public License along with QUAD.
If not, see <http://www.gnu.org/licenses/>.

--------------
<LEGAL NOTICE>
--------------
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution. The names of the contributors 
must be retained to endorse or promote products derived from this software.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ITS CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.
*/


//==============================================================================
/* tracing.h: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 24-1-2014
*/
//==============================================================================


#ifndef __TRACING__H__
#define __TRACING__H__

#include <pin.H>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <map>

#ifndef NULL
#define NULL 0L
#endif


void Put_Binding_in_XML_file(string producer,string consumer,UINT64 bytes,UINT64 UnMA, UINT64 UnDV);
void Update_total_statistics(string producer,string consumer,UINT64 bytes,UINT64 UnMA,bool p_f,bool c_f);
int CreateTotalStatFile();
int IsNewFunc(UINT16 funcID);
void recTrieTraverse(struct trieNode* current,int level);
int CreateDSGraphFile();
MAT_ERR_TYPE  RecordBinding(UINT16 producer, UINT16 consumer, ADDRINT add, UINT8 size, bool fresh);

#endif //__TRACING__H__
