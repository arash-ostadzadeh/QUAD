/*
QUAD v2.0
final revision December 6th, 2013

This file is part of QUAD Toolset available @:
http://sourceforge.net/projects/quadtoolset

Copyright © 2008-2013 Arash Ostadzadeh (ostadzadeh@gmail.com)
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
/* callpath.h: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 6-12-2013
*/
//==============================================================================

#ifndef __callpath__H__
#define __callpath__H__

/*
#include <iostream>
#include <fstream>    
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <tr1/unordered_set>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>


#ifndef NULL
#define NULL 0L
#endif


// To use a generic address type to suit 32- as well as 64-bit platforms "ADDRINT" is defined as "uintptr_t" in terms of <stdint.h>


using namespace std;
using std::tr1::unordered_set;

*/

// The CallPath class is used to track and save the chain of function calls and provide relevant statistics for each individual function as requested by the user

class CallPath
{
        typedef struct
        {
            string func;
            UINT64 call_num;
            unordered_set<ADDRINT>* write_UnMA;
            map <string,unordered_set<ADDRINT>*>* read_UnMA;
        } CallPathStackElem;    // to keep the summary of memory access statistics for each function call

    public:
        CallPath( );
        bool CallPathTrackOn( ) { return CP_TRACK_ON_flag; }
        void BuildFuncList( string fname );     // put the function names listed in the input text file into the "callcounter" map container
        void FuncEnter( string func );      // a function is called in the application, check and update the internal data if necessary
        void FuncReturn( string func );      // a called function returns control to the caller, check and update the internal data
        bool RecordWrite( ADDRINT addr, UINT8 size );   // a write access needs to be recorded
        bool RecordRead( string producer, ADDRINT addr, UINT8 size );   // a read access needs to be recorded

        void FlushOutput( ) { cpf.close(); }
        
    private:
        
        stack<CallPathStackElem> cp_stack;
        BOOL CP_TRACK_ON_flag;  // if true means that currently there is a function 
        map <string,UINT64> callcounter;    // how many times the function has been called so far
        ADDRINT temp_adds[8];   //  this array is used to add memory addresses to the UnMA sets via the "range" strategy of the set's insert method 
        ofstream cpf;   // the text file to store in the call path data
        
};

#endif //__callpath__H__
