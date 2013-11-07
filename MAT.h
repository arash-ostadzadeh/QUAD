/*
QUAD v2.0
final revision November 7th, 2013

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
/* MAT.h: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 7-11-2013
*/
//==============================================================================

#ifndef __MAT__H__
#define __MAT__H__

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


// Errors encountered using functions related to MAT
typedef enum {
         SUCCESS,
         MEM_ALLOC_FAIL,
	BINDING_ADD_FAIL,
	DCC_PROFILE_CREATE_FAIL,
         BINDING_RECORD_FAIL,       // a memory read access was unsuccessful to update the (p->c) binding data (memory problem!)
} MAT_ERR_TYPE;


// Define the "trie" data structure for tracing adresses
struct trieNode 
{
    struct trieNode* list[16];   // Each cell corresponds to a hexadecimal digit in the memory address 
};

typedef struct
{
	UINT16 last_producer;     // for now each (prodocer) function is assigned a unique id number (0..65535). Can be replaced with a link to a data block that contains info about the function
	UINT8 data_size;	// for now the only legitimate values are 1,2,4, and 8
	// *** other members should be added later, at least PTS and PSN from the cQUAD profiling data
} trieBucket;


// Structure for keeping track of pairs of <producer,consumer> for which we want to monitor the DCCs .... *** may be revised later
typedef struct 
{
    string producer;
    string consumer;
} DCC_binding;


// Structure definition to record producer->consumer Binding info 
typedef struct 
 {
	UINT64 bytes;
	
	// if the producer and consumer are some kind of entry point (directory) to the data records, they may be left out of the actual data fields in the record... *** to be checked later
	UINT16 producer;  
	UINT16 consumer;
	
	unordered_set<ADDRINT>* UnMA;     // **** a customized set implementation to replace STL set
	// set UnDV;  not sure if this is the place to keep it, *** check later!
	
	// UINT8 DCC_file_ptr_idx;	// (0) is reserved for no monitoring flag, (idx-1) points to the corresponding ofstream to dump the DCC flat profile, maximum DCCs that can be monitored is 255
} Binding;


// For easy access to individual hexadecimal digits in memory addresses (supports up to 64-bit addresses)
typedef struct 
{
    unsigned int h0:4;
    unsigned int h1:4;
    unsigned int h2:4;
    unsigned int h3:4;
    unsigned int h4:4;
    unsigned int h5:4;
    unsigned int h6:4;
    unsigned int h7:4;
    unsigned int h8:4;
    unsigned int h9:4;
    unsigned int h10:4;
    unsigned int h11:4;
    unsigned int h12:4;
    unsigned int h13:4;
    unsigned int h14:4;
    unsigned int h15:4;
} AddressSplitter;


class NonDeallocatableMemPool
{
    public:
        NonDeallocatableMemPool ( UINT16 InitSize=256, UINT16 IncSize=128 );    // the sizes are in MBs
        // void SetIncSize( UINT16 );
        void * Alloc ( UINT8 size );
        ~NonDeallocatableMemPool( );
        
     private:
         UINT16 InitSize_MB;    // The initial size of the pool to be allocated in MBs
         UINT16 IncSize_MB;     // The size of incremental blocks to be appended to the pool in MBs
         UINT64 TotalPoolSize;    // in bytes
         UINT64 TotalUsedSize;    // in bytes
         UINT32 TotalFragWasteSize;     // in bytes
         UINT16 NoAllocBlocks;      // Total number of allocated blocks so far
         UINT64 CurActiveBlockSize;     // The number of bytes for the most recent block allocated
         UINT64 CurActiveBlockUsedSize;     // how many bytes are already used in the current active block: this is the base for the decision to allocate a new block in the pool
         char * CurPoolPointer;     // Points to the current free memory block where allocations are made
};


// forward declaration for RecordBinding ****  should be integrated inside MAT after revising the data structure used for implementation!!!
MAT_ERR_TYPE  RecordBinding(UINT16 producer, UINT16 consumer, ADDRINT add, UINT8 size);


class MAT
{
    public:
        MAT ( const char* QDUG_filename, const char* Binding_XML_filename );
        
	// MAT_ERR_TYPE  Add_DCC_Binding ( string producer, string consumer );  // Add a new producer->consumer binding to be monitored regarding its Data Communication Channel (DCC)
	// vector<DCC_binding>::size_type  DCC_Binding_Size ( );	// Current number of DCC bindings
		
        MAT_ERR_TYPE  ReadAccess ( UINT16 func, ADDRINT add, UINT8 size ); // Record a memroy read access
        MAT_ERR_TYPE  WriteAccess ( UINT16 func, ADDRINT add, UINT8 size ); // Record a memroy write access
        ~MAT( );
    
    private:
        trieNode* root;   // The entry point for the trie tracing data structure
        
        // trieNode* graphRoot;    // The entry point for bindings records: producerID->consumerID-> [Binding Record]
        
        UINT8 TrieDepth;     // The depth of the trie based on the size of memory addresses (32-bit  -> 8 levels, 64-bit -> 16 levels)
        
         NonDeallocatableMemPool mp;     // The memory pool used for storing the main tracing trie nodes

        string QDUG_filename;    // The file name of the output QDU graph
        ofstream QDUG_file;

        string Binding_XML_filename;    // The name of the XML file containing the bindings info
        ofstream XML_file;
		
		
        bool DCC_flat_profile_flag;     // DCC monitored or not?  *** seems redundant but keep it for now ***
        vector<DCC_binding> Binding_list;  // The list of DCCs currently being monitored
        vector<ofstream> DCC_flat_profiles;
		
        MAT_ERR_TYPE  Nullify_Old_Producer ( ADDRINT add, int8_t size );	// Recursively nullify old producers already present in the trie in case the size of the current write is larger than the size of a previous write
        MAT_ERR_TYPE  Check_Prev_7_Addresses ( ADDRINT add, int8_t size );	// Check and correct, if necessary, the "size" field of the previous 7 addresses, to make sure that the current write access does not land amid an already existing data object
        UINT8  Seek_Real_Producer ( ADDRINT add, UINT16 & producer );      // Check "add" and return the size of the last production in that particular address and the producer function ID, if any. The second argument is treated as output.
};

#endif //__MAT__H__

