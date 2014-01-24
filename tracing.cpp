/*
QUAD v2.0
final revision January 24th, 2014

This file is part of QUAD Toolset available @:
http://sourceforge.net/projects/quadtoolset

Copyright © 2008-2014 Arash Ostadzadeh (ostadzadeh@gmail.com)
http://www.linkedin.com/in/ostadzadeh

This file is part of QUAD toolset.


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
/* tracing.cpp: 
 * This file is part of QUAD.
 *
 *  Author: Arash Ostadzadeh
 *  Lastly revised on 24-1-2014
*/
//==============================================================================


#include "tracing.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))


FILE* gfp,*ufa;
bool First_Rec_in_XML = true;
TiXmlNode* Put_QUAD_here=NULL;

UINT64 MaxLabel=0;

struct trieNode *graphRoot=NULL,*uflist=NULL;


//==============================================================================
void Put_Binding_in_XML_file(string producer, string consumer, UINT64 bytes, UINT64 UnMA, UINT64 UnDV)
{
  if (First_Rec_in_XML)  // check to make sure <PROFILE> exists and create the <QUAD> element...
  {	  
        First_Rec_in_XML = false;
  	
        TiXmlElement* root = xmldoc.RootElement();
        if (!root) 
	  {
		   cerr<<"Error writing <BINDING> elements in XML file...\n";
		   return;
	  }
  	
        TiXmlNode* Profile_element=root->FirstChildElement( "PROFILE" );
        if (!Profile_element)
        {
    	    TiXmlElement profile_tag("PROFILE");
    	    Profile_element=root->InsertEndChild(profile_tag);
        }

        TiXmlElement QUAD_tag("QUAD");
        Put_QUAD_here=Profile_element->InsertEndChild(QUAD_tag);
  }

  char buffer1[20], buffer2[20], buffer3[20];
  sprintf(buffer1,"%" PRIu64 "", bytes);
  sprintf(buffer2,"%" PRIu64 "", UnMA);
  sprintf(buffer3,"%" PRIu64 "", UnDV);
  
  	  
  TiXmlElement BINDING_tag("BINDING"),PRODUCER_tag("PRODUCER"),CONSUMER_tag("CONSUMER"),DATA_TRANSFER_tag("DATA_TRANSFER"),UnMA_tag("UnMA"),UnDV_tag("UnDV");
  TiXmlText pro_text(producer),con_text(consumer),data_transfer_text(buffer1),unma_text(buffer2),undv_text(buffer3);

  TiXmlNode* Current_binding; 
  
  Current_binding=Put_QUAD_here->InsertEndChild(BINDING_tag);
  (Current_binding->InsertEndChild(PRODUCER_tag))->InsertEndChild(pro_text);
  (Current_binding->InsertEndChild(CONSUMER_tag))->InsertEndChild(con_text);
  (Current_binding->InsertEndChild(DATA_TRANSFER_tag))->InsertEndChild(data_transfer_text);
  (Current_binding->InsertEndChild(UnMA_tag))->InsertEndChild(unma_text);
  (Current_binding->InsertEndChild(UnDV_tag))->InsertEndChild(undv_text);
  
  if (xmldoc.Error())	
  	cerr << xmldoc.ErrorDesc() << endl ;
}

//==============================================================================
void Update_total_statistics(string producer,string consumer,UINT64 bytes,UINT64 UnMA,bool p_f,bool c_f)
{
	if(p_f)
	{
		ML_OUTPUT[producer]->total_OUT_ALL+=bytes;
		ML_OUTPUT[producer]->total_OUT_ALL_UnMA+=UnMA;	
		ML_OUTPUT[producer]->consumers.push_back(consumer);	 // update the list of consumers for the particular producer in the ML
	}
	
	if(c_f)
	{
		ML_OUTPUT[consumer]->total_IN_ALL+=bytes;
		ML_OUTPUT[consumer]->total_IN_ALL_UnMA+=UnMA;
		ML_OUTPUT[consumer]->producers.push_back(producer);	 // update the list of producers for the particular consumer in the ML
	}
	
	if(p_f && c_f)
	{
		ML_OUTPUT[producer]->total_OUT_ML+=bytes;
		ML_OUTPUT[producer]->total_OUT_ML_UnMA+=UnMA;
		ML_OUTPUT[consumer]->total_IN_ML+=bytes;
		ML_OUTPUT[consumer]->total_IN_ML_UnMA+=UnMA;
	}
}

//==============================================================================
int CreateTotalStatFile()
{
    ofstream out;
    ofstream out_list;
    unsigned int ii;
    
    map <string,TTL_ML_Data_Pack*> :: const_iterator pIter;

    
    out.open("ML_OV_Summary.txt");
    
    if(!out) 
    {

	    cerr<<"\nCannot create the summary report file containing information about the functions specified in the monitor list..."<<endl;

	    return 1;

    }

    cerr << "\nCreating summary report file (ML_OV_Summary.txt) containing information about the functions specified in the monitor list..." << endl;

    out<<setw(30)<<setiosflags(ios::left)<<"Function"<<setw(12)<<"   IN_ML"
    <<setw(12)<<" IN_ML_UnMA"
    <<setw(12)<<"  OUT_ML"
    <<setw(12)<<"OUT_ML_UnMA"
    <<setw(12)<<"  IN_ALL"
    <<setw(12)<<"IN_ALL_UnMA"
    <<setw(12)<<"  OUT_ALL"
    <<setw(12)<<"OUT_ALL_UnMA"
    <<endl;

    out<<setw(30)<<"-----------------------------"<<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<setw(12)<<"-----------"
    <<endl;

        
    for ( pIter = ML_OUTPUT.begin( ) ; pIter != ML_OUTPUT.end( ) ; pIter++ )
    {
     out << setw(30) << setiosflags(ios::left) << pIter -> first;
     
     out << setw(11) << setiosflags(ios::right) << pIter->second->total_IN_ML << " " <<
	    setw(11) << pIter->second->total_IN_ML_UnMA << " " <<
	    setw(11) << pIter->second->total_OUT_ML << " " << 
	    setw(11) << pIter->second->total_OUT_ML_UnMA << " " <<
	    setw(11) << pIter->second->total_IN_ALL << " " <<
	    setw(11) << pIter->second->total_IN_ALL_UnMA << " " <<
	    setw(11) << pIter->second->total_OUT_ALL << " " <<
	    setw(11) << pIter->second->total_OUT_ALL_UnMA << endl ;
	    
     
     out.unsetf(ios::right);
     
     // store the list of communicating functions for each kernel in ML
     // consumers
     out_list.open((pIter -> first+"_(p).txt").c_str());
	 if(!out_list) 
     {
	    cerr<<"\nCannot create the report file containing the list of communicating functions for kernels ..."<<endl;
	    return 1;
     }
     
	 for(ii=0; ii < pIter->second->consumers.size(); ii++)  	  
	 		out_list << pIter->second->consumers[ii] << endl;
	 
	 out_list.close();

     // producers
     out_list.open((pIter -> first+"_(c).txt").c_str());
	 if(!out_list) 
     {
	    cerr<<"\nCannot create the report file containing the list of communicating functions for kernels ..."<<endl;
	    return 1;
     }
     
	 for(ii=0; ii < pIter->second->producers.size(); ii++)  	  
	 		out_list << pIter->second->producers[ii] << endl;
	 
	 out_list.close();
    
   }//end of for
   
    out << endl << "--" << endl;
    out << "IN_ML -> Total number of bytes read by this function that a function in the monitor list is responsible for producing the value(s) of the byte(s)" << endl;
    out << "IN_ML_UnMA -> Total number of unique memory addresses used corresponding to 'IN_ML'" << endl;
    out << "OUT_ML -> Total number of bytes read by a function in the monitor list that this function is responsible for producing the value(s) of the byte(s)" << endl;
    out << "OUT_ML_UnMA -> Total number of unique memory addresses used corresponding to 'OUT_ML'" << endl;
    
    out << "IN_ALL -> Total number of bytes read by this function that a function in the application is responsible for producing the value(s) of the byte(s)" << endl;
    out << "IN_ALL_UnMA -> Total number of unique memory addresses used corresponding to 'IN_ALL'" << endl;
    out << "OUT_ALL -> Total number of bytes read by a function in the application that this function is responsible for producing the value(s) of the byte(s)" << endl;
    out << "OUT_ALL_UnMA -> Total number of unique memory addresses used corresponding to 'OUT_ALL'" << endl;
    
    
    out.close();
    return 0;
}	

//==============================================================================
int IsNewFunc(UINT16 funcID)
{
    int currentLevel=0;
    int i;
    struct trieNode* currentLP;
    AddressSplitter* ASP= (AddressSplitter *)&funcID;
    
    unsigned int addressArray[4];
    
    addressArray[0]=ASP->h3;
    addressArray[1]=ASP->h2;
    addressArray[2]=ASP->h1;
    addressArray[3]=ASP->h0;
    
    currentLP=uflist;                
    while(currentLevel<3)  /* proceed to the last level */
    {
        if(! (currentLP->list[addressArray[currentLevel]]) ) /* create new level on demand */
        {
                if(!(currentLP->list[addressArray[currentLevel]]=(struct trieNode*)malloc(sizeof(struct trieNode))) ) 
        		{
        			fprintf(stderr,"Memory allocation failed in \'IsNewFunc()\'...");
        			return 2; /* memory allocation failed*/
        		}
                else
                       for (i=0;i<16;i++) 
                              (currentLP->list[addressArray[currentLevel]])->list[i]=NULL;
        }
        
        currentLP=currentLP->list[addressArray[currentLevel]];
        currentLevel++;
    }            
    
    if( !currentLP->list[addressArray[currentLevel]] )
    {
    	currentLP->list[addressArray[currentLevel]] = currentLP; /* a dummy value to show the cell has been filled before!! */
    	return 1; /* this function address is new */
    }
    	
    return 0; /* function address exists in the list */
}

//==============================================================================
void recTrieTraverse(struct trieNode* current,int level)
{
    int i;
	if (level==7)
	{   
		Binding *temp;
		bool producer_in_ML=false,consumer_in_ML=false;
		for (i=0; i<16; i++)
		{
		   temp=(Binding*)(current->list[i]);
		   if (temp) 
		   {
                	        string name2,name3;
                	        int color;
                	        name2 = ADDtoName[temp->producer];
		        name3 = ADDtoName[temp->consumer];
		
		        // If monitor list is specified, lets see we like the current functions' names or not!!
		        // if we do not like the names skip to the next binding!
			
			if (Monitor_ON)
			{
			    producer_in_ML = ( ML_OUTPUT.find(name2) != ML_OUTPUT.end() );
			    consumer_in_ML = ( ML_OUTPUT.find(name3) != ML_OUTPUT.end() );
			    if( ! (producer_in_ML || consumer_in_ML) ) break;
			}	

			if( IsNewFunc( temp->producer ) )
                	         {
			    fprintf(gfp,"\"%08x\" [label=\"%s\"];\n", (unsigned int)temp->producer , name2.c_str());
                	         }

			if( IsNewFunc( temp->consumer ) )
                	         {
			    fprintf(gfp,"\"%08x\" [label=\"%s\"];\n", (unsigned int)temp->consumer , name3.c_str());
               		}

			color = (int) (  1023 *  log((double)(temp->bytes)) / log((double)MaxLabel)  ); 
			fprintf( gfp,
                                    "\"%08x\" -> \"%08x\"  [label=\" %" PRIu64 " bytes \\n %" PRIu64 " UnMA \\n %" PRIu64 " UnDV \" color=\"#%02x%02x%02x\"]\n",
                                    (unsigned int) temp->producer,
                                    (unsigned int) temp->consumer,
                                    temp->bytes, 
                                    (UINT64) ( temp->UnMA->size() ),
                                    temp->UnDV,
                                    max(0,color-768),
                                    min(255,512-abs(color-512)),
                                    max(0,min(255,512-color)) 
                                    );
			
			Put_Binding_in_XML_file(name2, name3, temp->bytes, (UINT64) temp->UnMA->size(), temp->UnDV );
			
			if (Monitor_ON)  // do we need the total statistics file always or not? ... should be modified if we need this in any case... do not forget to make also the relevant modifications in the monitor list input file processing ... this can also be moved up in the previous condition if we need output file only when monitor list is specified!
			
			Update_total_statistics(
						name2,name3,temp->bytes,
					        (UINT64) ( temp->UnMA->size() ),
					        producer_in_ML,consumer_in_ML
					       );
		   
		   } // end of this item in the last level of the trie has a binding we need to check!   
		} // end of for which goes thru all the items in the last level of the trie...
	 return;
	} // end of if ...(we reached the last level of the trie, time to check binding items!)
  
	for (i=0;i<16;i++)   // we have not reached the last level of trie, we are in the middle somewhere! DO spawn further searches deep in the trie, covering everywhere!
    	  if (current->list[i]) 
	    recTrieTraverse(current->list[i],level+1);

  return;
}
		  
//==============================================================================
int CreateDSGraphFile()
{
   int i;

   if (!(gfp=fopen("QDUGraph.dot","wt")) ) return 1; /*can't create the output file */
   
   if(!(uflist=(struct trieNode*)malloc(sizeof(struct trieNode)) ) ) return 2; /* memory allocation failed*/
   else
        for (i=0;i<16;i++) 
                    uflist->list[i]=NULL;
   

   cerr << "\nWriting QDU graph preamble..." << endl;
   /* write prologue */
   fprintf(gfp,"digraph {\ngraph [];\nnode [fontcolor=black, style=filled, fontsize=20];\nedge [fontsize=14, arrowhead=vee, arrowsize=0.5];\n");

   cerr << "Writing QDU graph..." << endl; 
   recTrieTraverse(graphRoot,0);

   /* write epilogue */

   cerr << "Writing QDU graph epilogue..." << endl; 
   fprintf(gfp,"}\n");
   
   //printf("max: %u bytes\n",MaxLabel);
   
   cerr << "Writing <QUAD> in the XML file ...\n";
   
   if(!xmldoc.SaveFile()) cerr << "Error occurred in XML file update... \n";
   
   fclose(gfp);	
   return 0;
}                                               

//==============================================================================
MAT_ERR_TYPE  RecordBinding(UINT16 producer, UINT16 consumer, ADDRINT add, UINT8 size, bool fresh)
{
    UINT8  currentLevel=0;
    Binding* tempptr;
    UINT8  i;
    struct trieNode* currentLP;
    AddressSplitter* ASP= (AddressSplitter *)&producer;
    
    unsigned int addressArray[8];
    
    addressArray[0]=ASP->h3;
    addressArray[1]=ASP->h2;
    addressArray[2]=ASP->h1;
    addressArray[3]=ASP->h0;

    ASP=(AddressSplitter *)&consumer;

    addressArray[4]=ASP->h3;
    addressArray[5]=ASP->h2;
    addressArray[6]=ASP->h1;
    addressArray[7]=ASP->h0;
    

    if(!graphRoot)  /* create the first level in graph trie */
	   {
		    if(!(graphRoot=(struct trieNode*)malloc(sizeof(struct trieNode)) ) ) 
				return BINDING_RECORD_FAIL; /* memory allocation failed*/
            else
		    for (i=0;i<16;i++)     graphRoot->list[i]=NULL;
    }                         
            
    currentLP=graphRoot;                
    while(currentLevel<7)  /* proceed to the last level */
    {
        if(! (currentLP->list[addressArray[currentLevel]]) ) /* create new level on demand */
        {
                if(!(currentLP->list[addressArray[currentLevel]]=(struct trieNode*)malloc(sizeof(struct trieNode))) ) return BINDING_RECORD_FAIL; /* memory allocation failed*/
                else
                       for (i=0;i<16;i++) 
                              (currentLP->list[addressArray[currentLevel]])->list[i]=NULL;
        }
        
        currentLP=currentLP->list[addressArray[currentLevel]];
        currentLevel++;
    }            
    
    
    if( currentLP->list[addressArray[currentLevel]] == NULL ) // create a new bucket to store binding information between the two functions
    {
        if(!(  currentLP->list[addressArray[currentLevel]] = (trieNode *)malloc(sizeof(Binding)) ) ) return BINDING_RECORD_FAIL; /* memory allocation failed*/
        else 
        {
            tempptr=(Binding*) ( currentLP->list[addressArray[currentLevel]] );

	    tempptr->bytes=0;
             tempptr->UnDV=0;
	    tempptr->producer=producer;
	    tempptr->consumer=consumer;
             //  tempptr->DCC_file_ptr_idx=0;     // the DCC is not monitored for now!! ****
             
	    tempptr->UnMA=new unordered_set<ADDRINT>;
	    if (!tempptr->UnMA) return BINDING_RECORD_FAIL; /* memory allocation failed*/
    	}	
    }
	
    tempptr=(Binding*) ( currentLP->list[addressArray[currentLevel]] );
    
    tempptr->bytes=tempptr->bytes+size;
    if ( fresh ) tempptr->UnDV=tempptr->UnDV+size;  // if the value read by the consumer is a fresh one (not previously read) adjust the UnDV field correspondingly

    if (tempptr->bytes > MaxLabel) MaxLabel=tempptr->bytes; // only needed for graph visualization coloring!
    for ( i=0;i<size;i++) tempptr->UnMA->insert(add+i); // all the memroy addresses corresponding to the read size should be checked to have an accurate UnMA
	//****   check for memory problems during insertion!!!!!!!!!!!!

    //================================Call Path==================================================================
    // check the CP_TRACK_ON_flag status to decide whether or not we need to track access data for individual functions
    if ( CP.CallPathTrackOn( ) ) 
           if ( ! CP.RecordRead( ADDtoName[producer], add, size ) )  
           {
               cerr<<"\nFailed to record a memory read access in the call path stack! \n";
               exit(1);
            }
	
    return SUCCESS; /* successful recording */
}
//==============================================================================
