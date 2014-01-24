/*
QUAD v2.0
final revision January 20th, 2014

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
/* MAT.h: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 20-1-2014
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConsumptionStatusFlags;   // forward declaration

// Errors encountered using functions related to MAT
typedef enum {
         SUCCESS,
         MEM_ALLOC_FAIL,
	BINDING_ADD_FAIL,
	DCC_PROFILE_CREATE_FAIL,
         BINDING_RECORD_FAIL,       // a memory read access was unsuccessful to update the (p->c) binding data (memory problem!)
} MAT_ERR_TYPE;


typedef struct
{
	UINT16 last_producer;     // for now each (prodocer) function is assigned a unique id number (0..65535). Can be replaced with a link to a data block that contains info about the function
	UINT8 data_size;	// for now the only legitimate values are 1,2,4, and 8
         ConsumptionStatusFlags * UnDV_flags;   // for each data value once read by a particular consumer we keep a record to determine the freshness of values later for subsequent reads
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
	// if the producer and consumer are some kind of entry point (directory) to the data records, they may be left out of the actual data fields in the record... *** to be checked later
	UINT16 producer;  
	UINT16 consumer;

	UINT64 bytes;   // number of bytes read by the consumer, whose data was produced by the producer
	unordered_set<ADDRINT>* UnMA;     // **** a customized set implementation to replace STL set
	UINT64 UnDV;    // // number of fresh bytes read by the consumer (data that has not been read before-first time reads- by the consumer), whose data was produced by the producer
	
	// UINT8 DCC_file_ptr_idx;	// (0) is reserved for no monitoring flag, (idx-1) points to the corresponding ofstream to dump the DCC flat profile, maximum DCCs that can be monitored is 255
} Binding;


// Define the "trie" data structure for tracing adresses
struct trieNode 
{
    struct trieNode* list[16];   // Each cell corresponds to a hexadecimal digit in the memory address 
};

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// forward declaration for RecordBinding ****  should be integrated inside MAT after revising the data structure used for implementation!!!
MAT_ERR_TYPE  RecordBinding(UINT16 producer, UINT16 consumer, ADDRINT add, UINT8 size, bool fresh);


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
        
        //   MemPool mp;     // The main memory pool used for storing all the tracing info

        string QDUG_filename;    // The file name of the output QDU graph
        ofstream QDUG_file;

        string Binding_XML_filename;    // The name of the XML file containing the bindings info
        ofstream XML_file;
		
		
        bool DCC_flat_profile_flag;     // DCC monitored or not?  *** seems redundant but keep it for now ***
        vector<DCC_binding> Binding_list;  // The list of DCCs currently being monitored
        vector<ofstream> DCC_flat_profiles;
		
        MAT_ERR_TYPE  Nullify_Old_Producer ( ADDRINT add, int8_t size );	// Recursively nullify old producers already present in the trie in case the size of the current write is larger than the size of a previous write
        MAT_ERR_TYPE  Check_Prev_7_Addresses ( ADDRINT add, int8_t size );	// Check and correct, if necessary, the "size" field of the previous 7 addresses, to make sure that the current write access does not land amid an already existing data object
        trieBucket*  Seek_Real_Producer ( ADDRINT add );      // Check "add" and return the trieBucket address of that location, if any.
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  To keep and track the status of data read by consumers from a particular location with regard to its freshness
enum ConStatusFlagVal { OLD, FRESH };

class ConsumptionStatusFlags
{
    struct ConsFlagEntity;  // forward declaration
        
    public:
        ConsumptionStatusFlags ( ) 
        { 
                size=0;         // initially no consumer is seen
                capacity=3;     // initial size of the array ( I am not expecting that many concurrent consumers of a particular location! ) adjust if necessary
                if (! (flags_array = (ConsFlagEntity *) malloc( sizeof (ConsFlagEntity) * capacity ) ) )
                {
                    cerr<<"\nCannot create the initial array of consumption status flags in MAT. Memory allocation failed... aborting!\n";
                    exit(1);  // Memory allocation failed
                }
        }
        
        // a read is issued by consumer, check and report the current status of the data at the corresponding location, and then mark it as OLD for this consumer
        ConStatusFlagVal CheckAndClearFlag ( UINT16 consumer )
        {
                 UINT16 i=0;
                
                 for ( ; i<size ; i++ ) 
                    if ( flags_array[i].consID==consumer )      // the consumer is already in the list
                    {
                        if ( flags_array[i].flag==OLD ) return OLD;
                        else { flags_array[i].flag=OLD; return FRESH; }
                    }
                 
                 // the consumer is a new consumer (the first time seen)
                 
                 if ( size < capacity )     // still space left in the reserved array
                 {
                     flags_array[size].consID=consumer;
                     flags_array[size].flag=OLD;
                     size++;
                 }
                 else    // do realloc, no space left in the reserved array
                 {
                     capacity+=3;   // adjust the incremental value if needed
                     
                     if (capacity<size)     // can be removed, somehow redundant check!
                     {
                            cerr<<"\nOverflow in extending the array of consumption status flags in MAT... aborting!\n";
                            exit(2);  // the size and capacity variables should be adjusted
                     }

                     if (! (flags_array = (ConsFlagEntity *) realloc ( flags_array, sizeof (ConsFlagEntity) * capacity ) ) )
                     {
                            cerr<<"\nCannot extend the array of consumption status flags in MAT. Memory allocation failed... aborting!\n";
                            exit(1);  // Memory allocation failed
                     }
                     flags_array[size].consID=consumer;
                     flags_array[size].flag=OLD;
                     size++;
                 }
                 
                 return FRESH;
        }
        
        MAT_ERR_TYPE  CopyStatusFlags ( ADDRINT destination, struct trieNode* root, UINT8 TrieDepth )   // Copy the status flags from this object to the object found at the destination address.
        // The object at the destination is guaranteed to be an empty just created one, so no already existing list will be preserved! This rountine is expected to be rarely used.
        // Only in MAT::Check_Prev_7_Addresses, when a new write access in fully enclosed in a previous write access, hence a new record should be added for the extra end portion
        {
            AddressSplitter* ASP= (AddressSplitter *) &destination;
            ConsumptionStatusFlags * des_flag_obj_ptr;
            UINT8  currentLevel=0;
            struct trieNode* currentLP=root;
            // Reserve space for the worst case: 64-bit address needs a 16-level trie
            //  **** Further extension: can sizeof be determined during the compilation? if so use conditional macro instead for optimization, no need for the extra reservation, etc.
            UINT8 addressArray[16];
            
            
            // first find the ConsumptionStatusFlags object at the destination address
            if (TrieDepth==16)  // for 64-bit addresses
            {
                addressArray[0]=ASP->h15;
                addressArray[1]=ASP->h14;
                addressArray[2]=ASP->h13;
                addressArray[3]=ASP->h12;
                addressArray[4]=ASP->h11;
                addressArray[5]=ASP->h10;
                addressArray[6]=ASP->h9;
                addressArray[7]=ASP->h8;
                addressArray[8]=ASP->h7;
                addressArray[9]=ASP->h6;
                addressArray[10]=ASP->h5;
                addressArray[11]=ASP->h4;
                addressArray[12]=ASP->h3;
                addressArray[13]=ASP->h2;
                addressArray[14]=ASP->h1;
                addressArray[15]=ASP->h0;
            }
            else    // for 32-bit addresses
            {
                addressArray[0]=ASP->h7;
                addressArray[1]=ASP->h6;
                addressArray[2]=ASP->h5;
                addressArray[3]=ASP->h4;
                addressArray[4]=ASP->h3;
                addressArray[5]=ASP->h2;
                addressArray[6]=ASP->h1;
                addressArray[7]=ASP->h0;
            }    

           while( (currentLevel<TrieDepth-1) && (currentLP=currentLP->list[addressArray[currentLevel++]]) );  // proceed as far as possible in the trie 
           
           // ****** I am expecting a trieBucket be definitely present at the destination address (we just added one!!!) so no checking is necessary for the pointers
           des_flag_obj_ptr=( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->UnDV_flags;
           
           if ( des_flag_obj_ptr->capacity != capacity )  // do a reallocation for the destination object
           {
               des_flag_obj_ptr->capacity=capacity;
                if (! (des_flag_obj_ptr->flags_array = (ConsFlagEntity *) realloc ( des_flag_obj_ptr->flags_array, sizeof (ConsFlagEntity) * capacity ) ) )
                {
                      cerr<<"\nCannot extend the array of consumption status flags in MAT. Memory allocation failed... aborting!\n";
                      return MEM_ALLOC_FAIL;
                }
           }
           
           for (UINT16 i=0; i<size; i++)  // copy the flags array
           {
                des_flag_obj_ptr->flags_array[i].consID=flags_array[i].consID;
                des_flag_obj_ptr->flags_array[i].flag=flags_array[i].flag;
           }
           
           des_flag_obj_ptr->size=size;     // adjust the size for the destination object
            return SUCCESS;
        }
        
        // a new write is issued for the corresponding location, reset the flags for all
        void ResetAllFlags ( void )   {    for ( UINT16 i=0; i<size ;i++ )   flags_array[i].flag=FRESH;   }
        
        // Destructor needed to free the dynamically allocated memory
        ~ConsumptionStatusFlags ( )   {   free ( flags_array );  }
        
     private:
        struct ConsFlagEntity
        {
            UINT16 consID;
            ConStatusFlagVal flag;
        } * flags_array;
        
        UINT16 size, capacity;      // size shows the current number of consumer functions for the corresponding location, capacity indicates the maximum number of entities reserved in the flags_array
                                                   // note that in the current implementation 65535 concurrent consumer functions may be tracked for each location
};

#endif //__MAT__H__

