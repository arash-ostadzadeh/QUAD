/*
QUAD v2.0
final revision October 21st, 2013

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
/* MAT.cpp: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 21-10-2013
*/
//==============================================================================



#include "MAT.h"

//////////////////////////////////////////////////////////////////////
//  Definitions of the "MemPool" member functions  //
//////////////////////////////////////////////////////////////////////

/*

MemPool::MemPool ( size_t ReservedSize )
{
         CurrentPoolSize=0;     // ***  to be revised once an advanced MemPool implementation is carried out
         CurrentlyUsed=0;
}

//==============================================================================
void * MemPool::Alloc ( size_t size )
{
    void * temp;
    temp=new char [size];
    if (temp) CurrentlyUsed+=size;
    
    return temp;
}

//==============================================================================
void MemPool::Dealloc ( void * ptr, size_t size )   // size not needed for de-allocation, just to update the currently used space in the MemPool
{
    CurrentlyUsed-=size;
    delete [] ptr;
}

*/
        
/////////////////////////////////////////////////////////////////
//  Definitions of the "MAT" member functions   //
/////////////////////////////////////////////////////////////////

MAT::MAT ( const char* QDUG_filename="QDUG.dot", const char* Binding_XML_filename="QUAD.xml" )
{

// *****  to be uncommented later ...
/*
    MAT::QDUG_filename=QDUG_filename;
    MAT::Binding_XML_filename=Binding_XML_filename;

    
    QDUG_file.open(QDU_filename);
    if (! QDUG_file.is_open() ) 
    {
        cerr<<"\nCannot create the QDU graph file... aborting!\n";
        exit(1);
    }


    XML_file.open(Binding_XML_filename);
    if (! XML_file.is_open() ) 
    {
        cerr<<"\nCannot create the XML file for the bindings info... aborting!\n";
        exit(1);
    }

*/
    
    // Initialize the xml processing for QDUG file
    // Write the preamble text for the QDUG file
    // ***********************************
    
    TrieDepth=( sizeof(ADDRINT)==4? 8 : 16 );  // 32-bit  addresses -> 8 levels, 64-bit addresses -> 16 levels
    // Create the first level in the trie

    // if( !(root=(struct trieNode*) mp.Alloc(sizeof(struct trieNode)) ) ) 
    if( !(root=(struct trieNode*) malloc(sizeof(struct trieNode)) ) ) 
        
    {   // memory allocation failed
        cerr<<"\nCannot create the initial directory in MAT. Memory allocation failed... aborting!\n";
        exit(1);
    }
    else    // initialize all the 16 directory links to zero
        for ( UINT8 i=0; i<16 ; i++ )   
                  root->list[i]=NULL;
    
    DCC_flat_profile_flag=false;
    
    // Reserve space up to 5 entries for DCC bindings
    // *************************************
    // if (MAT::DCC_flat_profile_flag) { }
}

//==============================================================================

/*

MAT_ERR_TYPE  MAT::Add_DCC_Binding ( string producer, string consumer )
{
    DCC_binding temp;
    ofstream out;
    vector<DCC_binding>::size_type sz=DCC_Binding_Size ( );
    
    if (! DCC_flat_profile_flag )   DCC_flat_profile_flag=true;
    
    temp.producer=producer;
    temp.consumer=consumer;
    Binding_list.push_back(temp);
    
    if ( DCC_Binding_Size ( )!=(sz+1) )
    {
        cerr<<"\nError in adding <"<<producer<<","<<consumer<<"> pair to the DCC binding list... \n";
        return BINDING_ADD_FAIL;
    }
    
    // revise the name of the flat profiles from the (id->name) map
    // ************************************************************
    string temp_name=producer+"_"+consumer+".txt";
    
    out.open( temp_name.c_str() );
    if (! out.is_open() ) 
    {
        cerr<<"\nCannot create the DCC flat profile for <"<<producer<<","<<consumer<<">... aborting!\n";
        return DCC_PROFILE_CREATE_FAIL;
    }

    DCC_flat_profiles.push_back(out);
    
    if ( static_cast<unsigned int>(DCC_flat_profiles.size() ) != static_cast<unsigned  int>(sz+1) )
    {
        cerr<<"\nError in adding <"<<producer<<","<<consumer<<"> pair to the DCC binding list... \n";
        return BINDING_ADD_FAIL;
    }
    
    // probably make new empty entires for <p,c> pair in the binding trie to record the place the corresponding ofstream can be found and used...
    // *******************************************************************
    
    return SUCCESS;
}

//==============================================================================
vector<DCC_binding>::size_type  MAT::DCC_Binding_Size ( )
{
    return Binding_list.size();
}

*/

//==============================================================================
UINT8  MAT::Seek_Real_Producer ( ADDRINT add, UINT16 & producer )
{

    UINT8  currentLevel=0;
    struct trieNode* currentLP=root;
    AddressSplitter* ASP= (AddressSplitter *) &add;
    
    // Reserve space for the worst case: 64-bit address needs a 16-level trie
    //  **** Further extension: can sizeof be determined during the compilation? if so use conditional macro instead for optimization, no need for the extra reservation, etc.
    UINT8 addressArray[16];

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

    // **** performance gain: try to write the following loop in the straightforward manner and as soon as reaching a null path in trie conclude for unknown producer!
    // **** extra note: the same strategy may be beneficial in other functions, "Check_Prev_7_Addresses" and "Nullify_Old_Producer"
    while( (currentLevel<TrieDepth-1) && (currentLP=currentLP->list[addressArray[currentLevel++]]) );  // proceed as far as possible in the trie 

    if ( ! currentLP ) return 0;    // this particular address not been written to previously
    
    trieBucket* tempptr=  (trieBucket*) (currentLP->list[addressArray[currentLevel]]) ;
    if ( ! tempptr )  return 0;    // this particular address not been written to previously
    
    //  report the size of data object and the producer ID
    producer=tempptr->last_producer;
    return tempptr->data_size;
}

//==============================================================================
MAT_ERR_TYPE  MAT::ReadAccess ( UINT16 func, ADDRINT add, UINT8 size )
{

    UINT8  currentLevel=0;
    struct trieNode* currentLP=root;
    AddressSplitter* ASP= (AddressSplitter *) &add;
    
    // Reserve space for the worst case: 64-bit address needs a 16-level trie
    //  **** Further extension: can sizeof be determined during the compilation? if so use conditional macro instead for optimization, no need for the extra reservation, etc.
    UINT8 addressArray[16];

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

    // **** performance gain: try to write the following loop in the straightforward manner and as soon as reaching a null path in trie conclude for unknown producer!
    // **** extra note: the same strategy may be beneficial in other functions, "Check_Prev_7_Addresses" and "Nullify_Old_Producer"
    while( (currentLevel<TrieDepth-1) && (currentLP=currentLP->list[addressArray[currentLevel++]]) );  // proceed as far as possible in the trie 

    if ( currentLP ) 
    {
      trieBucket* tempptr=  (trieBucket*) (currentLP->list[addressArray[currentLevel]]) ;

      if ( tempptr )   // there is a bucket for this address
      {
        if (size <= tempptr->data_size ) return RecordBinding ( tempptr->last_producer, func, add, size );

        // the consumer function is reading data with a size exceeding the recorded data size for the current producer of that specific address.
        if ( RecordBinding ( tempptr->last_producer, func, add, tempptr->data_size ) != SUCCESS ) return BINDING_RECORD_FAIL;
        return MAT::ReadAccess ( func, add+tempptr->data_size, size - tempptr->data_size );      // issue another virtual read access for the uncovered portion (this is for memory accesses with sizes more that what is currently recorded at that particular address)
      }
    }
    
    //  apparently we are reading from a location  which was not previously written to! however, before drawing any conclusion, we have to check to ensure that the read instruction is not indeed landing in the middle of a data object!

    // some local variables to keep track of the real producer, if any.
    ADDRINT add_prod=add-1;     // start the probe from the previous address, as soon as detecting a recorded production, no need to check the addresses which come in prior.
    UINT16 ID_prod;
    UINT8 size_prod=0;      // was forced by gcc to initialize this!!!!!! though it will never be used uninitialized in line# 335
    
    // do the following check for at most 7 addresses before the current "add" or until Seek_Real_Producer return a non-zero value
    while (  (add_prod+8 > add)  &&  ( ! (size_prod = Seek_Real_Producer ( add_prod, ID_prod ) ) )   )  add_prod--;     // "ID_prod" contains the ID of the producer, if any, after returning
    
    if ( size_prod ) // a potential producer has been found, go for further check to see if "add" really falls in the range of the produced data
    {
        if ( add_prod + size_prod >= add + size ) // the current read access falls entirely in the range of the data object produced by ID_prod, record the binding
                                return RecordBinding ( ID_prod, func, add, size );
                                
        if ( add_prod + size_prod >= add  ) // the current read access falls partially in the range of the data object produced by ID_prod, record the binding for the first part, and then continue to the next phase to record the binding for the second part as UNKNOWN PRODUCER
        {
            if ( RecordBinding ( ID_prod, func, add, add_prod + size_prod - add  ) != SUCCESS ) return BINDING_RECORD_FAIL;
            
            // adjust "add" and "size" for subsequent processing in the last phase of the MAT::ReadAccess, see *** important section below
            size=size - ( add_prod + size_prod - add );
            add=add_prod + size_prod;
        }
    }
    // last phase of MAT::ReadAccess  (for unknown producer)
    // if we are here, then the "func" is trying to read from a memory which was not previously written to by any user defined function in the application (UNKOWN PRODUCER / CONSTANT DATA)
    if ( RecordBinding ( 0, func, add, 1 ) != SUCCESS ) return BINDING_RECORD_FAIL;     // function ID# 0 is reserved for UNKOWN PRODUCER / CONSTANT DATA, Note that for just the current address we are sure that we are reading a value from unknown producer, thus the size is 1, for other addresses, if any, the check is repeated!
    
    // **** important: (performance degradation) calling "ReadAccess" in the following is unnecessarily slow, there is no need to check again the previous addresses in case of "UNKNOWN PRODUCER" as these were checked before!!!
    // try to define a new function with the knowledge that most probably subsequent addresses would be intact as well.
    if ( size >1 ) return  MAT::ReadAccess ( func, add+1, size-1 );      // repeat the check for memory accesses with sizes more than 1 byte

    return SUCCESS;
}

//==============================================================================
// Start from the current "add" and nullify the old producers (if any) up to and including the subsequent "size" addresses
MAT_ERR_TYPE  MAT::Nullify_Old_Producer ( ADDRINT add, int8_t size )
{
    if ( size<=0 )  return  SUCCESS; // base condition: no more nullification required
    
    UINT8  currentLevel=0;
    struct trieNode* currentLP=root;
    AddressSplitter* ASP= (AddressSplitter *) &add;
    
    // Reserve space for the worst case: 64-bit address needs a 16-level trie
    //  **** Further extension: can sizeof be determined during the compilation? if so use conditional macro instead for optimization, no need for the extra reservation, etc.
    UINT8 addressArray[16];

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

    if ( currentLP ) 
    {
      if (currentLP->list[addressArray[currentLevel]]  )   // there is a bucket for this address, inspect the size of the data written previously
      {
        UINT8  cur_data_sz= ( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->data_size;   // make a copy of the size of the current data object
        size=size - cur_data_sz;     // size may go negative
        
        if ( size<0 )   // The nullification does not hold for the whole size of the data object, issue a new (virtual) write access for the intact part of the data object to be added in the trie
            // *****  be aware of the extra parameters needed to record a write access, such as PTS, PSN, etc.
            if ( WriteAccess ( ( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->last_producer, 
                                         add+cur_data_sz+size, 
                                         -size ) != SUCCESS ) return MEM_ALLOC_FAIL;    // Adding the new record failed. inform the caller
         
        //  delete the record for the nullified address(es) and release the allocated memory
        //  **** if trieBucket contains any link to dynamically allocated memory, it should be deallocated first
        //  mp.Dealloc ( currentLP->list[addressArray[currentLevel]], sizeof(trieBucket) );
        free ( currentLP->list[addressArray[currentLevel]]  );
        currentLP->list[addressArray[currentLevel]]=NULL;
        
        return Nullify_Old_Producer ( add+cur_data_sz, size );     // proceed to the next entry in the trie for nullification, note that the "size" is already decremented for the whole "cur_data_sz" not just one byte
      }
    }
    return Nullify_Old_Producer ( add+1, size-1 );     // current address is not written to until now, skip it and check the next address. viola, at least we are done checking for one byte!
}

//==============================================================================
// Check and correct, if necessary, the 7 addresses proior to the current "add". "size" indicates the size of the current write access
MAT_ERR_TYPE  MAT::Check_Prev_7_Addresses ( ADDRINT add, int8_t size )
{
    ADDRINT check_add=add-7;
    AddressSplitter* ASP= (AddressSplitter *) &check_add;

    UINT8  currentLevel;
    struct trieNode* currentLP;

    // Reserve space for the worst case: 64-bit address needs a 16-level trie
    //  **** Further extension: can sizeof be determined during the compilation? if so use conditional macro instead for optimization, no need for the extra reservation, etc.
    UINT8 addressArray[16];

    while ( check_add < add ) // check, at most, 'til the previous address of the current write access
    {   
        // initialize the trie tracing
        currentLP=root;
        currentLevel=0;

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

        if ( currentLP ) 
        {
          if ( currentLP->list[addressArray[currentLevel]]  )   // there is a bucket for this address, inspect the size of the data written previously
          {
            UINT8  check_add_sz= ( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->data_size;   // make a copy of the size of the record at check_add
        
            if (  (check_add+check_add_sz) == add )  return SUCCESS;  // the record at the check_add strictly precedes the current write access (no overlap)... everything is fine! no more checking is necessary
            
            if (  (check_add+check_add_sz) < add )  
            //  the record at the check_add does not overlap with the current write access... everything is fine 'til now, determine the next check address and jump to the beginning of the loop
            {
                check_add+=check_add_sz;
                continue;
            }
            
            if (  (check_add+check_add_sz) > (add+size) )   
            //  the record at the check_add fully encloses and exceeds the current write access... correct the "size" field for the check_add record and add a new record for the portion beyond the crrent write
            {
                ( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->data_size = add - check_add;
                
                // *****  be aware of the extra parameters needed to record a write access, such as PTS, PSN, etc.
                if ( WriteAccess ( ( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->last_producer, 
                                         add+size,      // new starting address
                                         check_add+check_add_sz-add-size ) != SUCCESS ) return MEM_ALLOC_FAIL;    // Adding the new record failed. inform the caller
                 
                return SUCCESS;
            }
            
            //  the last possibility -> the last effective address belonging to the write access at "check_add" lands somewhere in the range of the current write access, just correct the corresponding "size" field
            ( (trieBucket*) (currentLP->list[addressArray[currentLevel]]) )->data_size = add - check_add;
            return SUCCESS;
          }
        }   // end of -> if a valid record exists at the check_add
        
        check_add++;    // check the next address ...
    } // end of while (check_add < add)

    return SUCCESS;
}

//==============================================================================
MAT_ERR_TYPE  MAT::WriteAccess ( UINT16 func, ADDRINT add, UINT8 size )
{
    UINT8  currentLevel=0;
    UINT8  i;
    trieBucket* BucketAdd;
    struct trieNode* currentLP=root;
    AddressSplitter* ASP= (AddressSplitter *) &add;
    
    // Reserve space for the worst case: 64-bit address needs a 16-level trie
    //  **** Further extension: can sizeof be determined during the compilation? if so use conditional macro instead for optimization, no need for the extra reservation, etc.
    UINT8 addressArray[16];

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

	// **** performance improvment: define a new (or reuse BucketAdd as a placeholder for "currentLP->list[addressArray[currentLevel]]"
    while(currentLevel<TrieDepth-1)  // proceed to the last level of the trie 
    {
        if(! (currentLP->list[addressArray[currentLevel]]) ) // Create new level on demand
        {
                // if(!(currentLP->list[addressArray[currentLevel]]=(struct trieNode*)mp.Alloc(sizeof(struct trieNode))) ) 
                if(!(currentLP->list[addressArray[currentLevel]]=(struct trieNode*)malloc(sizeof(struct trieNode))) ) 
                {
                    // *** Further extension: maybe a sophisticated routine to release or dump some already allocated blocks in the MemPool class?!
                    cerr<<"\nCannot create the required trie levels in MAT. Memory allocation failed in tracing a memory write access... \n";
                    return MEM_ALLOC_FAIL;  // Memory allocation failed
                }
                else
                       for (i=0;i<16;i++) 
                              (currentLP->list[addressArray[currentLevel]])->list[i]=NULL;
        }
        
        currentLP=currentLP->list[addressArray[currentLevel]];
        currentLevel++;
    }
    
    // Reached the last level of the trie; time to check whether or not this particular address has been visited before
    // CurrentLP points to the last level in the trie
    // CurrentLevel ->7 or 15

    // **** performance improvement: redefine theBucketAdd to hold the address of the last pointer to the bucket instead of the bucket itself, the following statements can be shortened
    
    if( currentLP->list[addressArray[currentLevel]] == NULL ) // Create a new bucket to record the last write access details
    {
        // if(!(  currentLP->list[addressArray[currentLevel]] = (struct trieNode*) mp.Alloc(sizeof(trieBucket)) ) )  
        if(!(  currentLP->list[addressArray[currentLevel]] = (struct trieNode*) malloc(sizeof(trieBucket)) ) )  
        {
                // **** Further extension: maybe a sophisticated routine to release or dump some already allocated blocks in the MemPool class?!
                cerr<<"\nCannot create the required trie bucket in MAT to record access profiling info. Memory allocation failed in tracing a memory write access... \n";
                return MEM_ALLOC_FAIL; // Memory allocation failed
        
        }
        else     // Record the last write access details
        {
                BucketAdd=(trieBucket*) (currentLP->list[addressArray[currentLevel]]);	// record the address of the destination bucket for subsequent accesses
                BucketAdd->last_producer = func;
                BucketAdd->data_size = size;
                // *** more to be added later
                
                // check up to the previous 7 addresses to make sure that the current write access does not land amid an already existing data object. 
                // do the adjustments for the "size" field of previous write accesses when necessary.
                
                // **** Further extension: the check for the previous 7 addresses may be avoided if we keep track of the previous write access in the function (or the MAT class)  with the help of some extra variables to record the address, size and timing...
                // **** Further extension: size remains unchanged during the function call, try to optimize by removing from the formal parameters, any performance gain?!
                if ( Check_Prev_7_Addresses ( add, size ) != SUCCESS )  // new record may be added as the result of a correction
                {
                    cerr<<"\nMemory allocation failed during the checkup process for the previous write access. A record was supposed to be added to the trie because the current write access partially overrode a previous write access  ... \n";
                    return MEM_ALLOC_FAIL;  // Memory allocation failed
                }
        }
    }
    else    // The trie bucket already exists. first do the ckeck for data size incompatibility, rare but could happen 
    {

        BucketAdd= (trieBucket*) (currentLP->list[addressArray[currentLevel]]);	// record the address of the destination bucket for subsequent accesses
        UINT8 old_size= BucketAdd->data_size;   // save the current size of data object
        
        if ( old_size != size )
        {
        	if ( old_size < size  )   // Surpassing already recorded data size. check the subsequent address(es) as required to nullify the affected old producers
        	{
                if( Nullify_Old_Producer ( add+old_size, static_cast<int8_t>(size - old_size) ) != SUCCESS ) 
                {
                    cerr<<"\nMemory allocation failed during the nullification process. A record was supposed to be added to the trie due to incompatibility of the old and new data sizes ... \n";
                    return MEM_ALLOC_FAIL;  // Memory allocation failed
                }
        	}
        	else	// the new size is less than the old size -> a new record has to be added to the trie to cover the intact portion of the previous entry
        	{
                if( WriteAccess ( BucketAdd->last_producer, add+size, old_size-size  ) != SUCCESS ) // *** be aware of the extra data to be recorded with write access, such as PTS or PSN, as these should be retained with the same values for the original record (probably a separate write routine should be called) !!!
                {
                    cerr<<"\nMemory allocation failed during size correction. A record was supposed to be added to the trie due to incompatibility of the old and new data sizes ... \n";
                    return MEM_ALLOC_FAIL;  // Memory allocation failed
                }
        	}
        	BucketAdd->data_size=size;	// update the old size in the bucket, producer update will be carried out later
    	}
        
        // if we are here either the current size of data matches the size of the new write access or we have already corrected the size of the entry 
        
        // **** you may want to check if this is the same producer skip the assignment! performance gain?! check ...
        BucketAdd->last_producer = func;  // update the last producer
        
        // **** more updates are needed for extra data (PTS, PSN, etc.)
    }   // end of the trie bucket already exists

return  SUCCESS;    // The write access was successfully recorded in the trie
}

//==============================================================================
MAT::~MAT (  )
{
  //  QDUG_file.close( );
  //  XML_file.close( );
    // **** more housekeeping to come later...
}
//==============================================================================
