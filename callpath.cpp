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
/* callpath.cpp: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 6-12-2013
*/
//==============================================================================
#include "callpath.h"
//======================CallPath function definitions===================================
CallPath::CallPath( )
{
    CP_TRACK_ON_flag=false;

    cpf.open("callpath.txt");
     if (!cpf)
     {
	  cerr<<"\nCannot create the call path summary file (\"callpath.txt\")... Aborting!\n";
	  exit(1);
     }

}

//==============================================================================
void CallPath::BuildFuncList( string fname)
{
	ifstream ilistf;
	ilistf.open(fname.c_str());
         if (!ilistf)
	{
	  cerr<<"\nCannot open the call path list file ("<<fname.c_str()<<")... Aborting!\n";
	  exit(1);
	}

	string item;
         do
         {
	    ilistf>>item;	// get the next function name in the call path list
             // getline( ilistf, item );
	    if (ilistf.eof()) break;	// oops we are finished!
	    callcounter[item]=0;        // add the function name to be monitored in the call path, and initialize the number of times called to zero
         } while(1);	
	
	ilistf.close();	    
}

//==============================================================================
void CallPath::FuncEnter( string func )
{
    CallPathStackElem El;
    map<string,UINT64>::iterator it=callcounter.find(func);

    El.func=func;

    if ( it==callcounter.end( ) )     // entering a function which we do not want to track in the call path... pause the current data recording if recording is activated
    {
        CP_TRACK_ON_flag=false;
        El.call_num=0;      // 0 is signaling that we are not interested in tracking this function. Anyhow, we have to add the dummy record to the call path stack 
                                      //  because when the function returns we should be able to update the call path accordingly
        El.write_UnMA=NULL;    // dummy values, not used anyway
        El.read_UnMA=NULL;
    }
    else
    {           // a function of interest is called, activate a new tracking element
    
        CP_TRACK_ON_flag=true;
        it->second++;   // adjust the number of calling times for the corresponding function
        El.call_num=it->second;
        try
        {
            El.write_UnMA= new unordered_set<ADDRINT>;
        } catch (bad_alloc& ba)
            {
                cerr<<"\nMemory allocation failed in adding a new element to the call path stack... Aborting!\n";
                exit(1);
            }
        
        try
        {
            El.read_UnMA= new map <string,unordered_set<ADDRINT>*>;
        } catch (bad_alloc& ba)
            {
                cerr<<"\nMemory allocation failed in adding a new element to the call path stack... Aborting!\n";
                exit(1);
            }
        // report the incident in the call path output file
        cpf<<El.func<<"("<<El.call_num<<") call"<<endl;
    }
    
    cp_stack.push( El );
}

//==============================================================================
void CallPath::FuncReturn( string func )
{
    if ( !(cp_stack.empty()) && ( cp_stack.top( ).func==func ) )    // the returning function has been previously pushed to call path stack
    {
        if ( CP_TRACK_ON_flag )     // CP_TRACK_ON_flag is true, which means that we have been tracking this particular function in the call path
        {
            // dump the summary of tracking statistics to the call path output file
            cpf << "W\t" << ( cp_stack.top().write_UnMA )->size( ) << endl;

            delete cp_stack.top().write_UnMA; // release the memory allocated for the set of "write" UnMAs 
            
            for ( map<string,unordered_set<ADDRINT>*>::iterator it= ( cp_stack.top().read_UnMA )->begin(); it != ( cp_stack.top().read_UnMA )->end(); ++it )
            {
                 cpf <<  "R\t" << it->first << " " << (it->second)->size( ) << endl;
                 delete it->second;     // release the memory allocated for individual sets
            }

            cpf << func << "(" << cp_stack.top( ).call_num << ") return" << endl;
            delete cp_stack.top().read_UnMA;    // release the memory allocated for the map of all "read" UnMAs
        } // end of "CP_TRACK_ON_flag is true"
        // else cpf<<func<<" return"<<endl;
        
        cp_stack.pop( );    // remove the top element in the call path stack
            
         // adjust the CP_TRACK_ON_flag
         // if call_num for the current top function is non-zero, it means that we have been tracking this particular function in the call path
         if ( cp_stack.top( ).call_num ) CP_TRACK_ON_flag=true;
         else CP_TRACK_ON_flag=false;
    }
}

//==============================================================================
bool CallPath::RecordWrite( ADDRINT addr, UINT8 size )
{
    UINT8 i;

    for ( i=0;i<size;i++) temp_adds[i]=addr+i;      // put all the individual addresses in order in the temp array
    unordered_set<ADDRINT>* ptr= ( cp_stack.top( ) ).write_UnMA;
    
    try
    {
        ptr->insert( temp_adds, temp_adds+size );   // range insert for numbers in the range [ temp_adds[0]...temp_adds[size-1] ] 
    } catch ( bad_alloc& ba )  { return false; }
    
    return true;
}

//==============================================================================
bool CallPath::RecordRead( string producer, ADDRINT addr, UINT8 size )
{
    UINT8 i;

    for ( i=0;i<size;i++) temp_adds[i]=addr+i;      // put all the individual addresses in order in the temp array
    
    unordered_set<ADDRINT>* set_ptr;
    map <string,unordered_set<ADDRINT>*>* map_ptr= ( cp_stack.top( ) ).read_UnMA;
    
    if ( ! map_ptr->count(producer) ) // the producer is new, create a new set for this producer and add the link to the map
    {
        try
        {
           set_ptr=new unordered_set<ADDRINT>;
        } catch ( bad_alloc& ba )  { return false; }
        
        (*map_ptr)[producer]=set_ptr;     // add the new producer and the link to the corresponding set to the map
    }
    else set_ptr=map_ptr->at(producer);     // the producer is seen before!
    
    try
    {
        set_ptr->insert( temp_adds, temp_adds+size );   // range insert for numbers in the range [ temp_adds[0]...temp_adds[size-1] ] 
    } catch ( bad_alloc& ba )  { return false; }
    
    return true;
}
//==============================================================================
void CallPath::FlushOutput( ) 
{ 
    cpf.close(); 
}
//==============================================================================
