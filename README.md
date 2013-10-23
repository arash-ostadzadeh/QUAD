QUADcore

This tool is part of the QUAD Toolset project, developed by Arash Ostadzadeh.

QUAD is open source and provided under the GNU Lesser General Public License (LGPL), particularly for academic (non-commercial) purposes.

QUADcore has been deliberately maintained separately with the aim to offer simplicity and ease of use for experimental academic purposes, meanwhile, to provide the primary functionality of the QUAD toolset.

To use the complete QUAD toolset refer to the 'QUAD' project on sourceforge.

QUAD Toolset is available @
http://sourceforge.net/projects/quadtoolset

Copyright © 2008-2013 Arash Ostadzadeh 
http://www.linkedin.com/in/ostadzadeh


Description
===========

QUAD (Quantitative Usage Analysis of Data) provides useful information regarding the data transfered between any pair of co-operating functions in an application. The data transfer is calculated in the sense of Producer-Consumer binding. QUADcore reports precisely which function is reading data produced by which function. The exact quantities, showing the amount of data transferred (in bytes), as well as the number of unique memory addresses used in the transfer, are reported. The tool has been developed based on 'Pin'. Pin is a toolkit for Dynamic Binary Instrumentation (DBI) of programs. It supports Linux binary executables for Intel (R) Xscale (R), IA-32, Intel64 (64 bit x86), and Itanium (R) processors; Windows executables for IA-32 and Intel64; MacOS  executables for IA-32 and Intel64; and Android executables for IA-32. Pin does not instrument an executable statically by rewriting it, but rather adds the code dynamically while the executable is running.


What QUADcore does
==================

At the moment, the QUADcore tool is able to track every single access (read/write) to a memory location. By monitoring the memory access behaviour of the application, processed information is provided to the user in the form of easily interpretable data, i.e. XML text and '.dot' files.


How to build the QUADcore tool
==============================

The Pin toolkit should be installed on the target machine as a prerequisite. You can download the latest appropriate Pin toolkit from the following URL:
http://www.pintool.org/downloads.html

After installing the Pin toolkit, copy the QUADcore files to a place of your choosing. In that location, make a corresponding directory for the object files ("obj-intel64" if you are using a 64-bit platform or "obj-ia32" for a 32-bit one).

To build QUADcore.so (from QUADcore.cpp) use:

make PIN_ROOT=<path to your Pin kit> obj-intel64/YourTool.so

For the IA-32 architecture, use "obj-ia32" instead of "obj-intel64". For changing the directory where the tool will be created, override the OBJDIR variable from the command line:

make PIN_ROOT=<path to Pin kit> OBJDIR=<path to output dir> <path to output dir>/QUADcore.so

We have tested QUADcore with Pin 2.13-61206 in Linux for IA32 and intel64. If you are using older versions of Pin, you may need to use the old makefile provided here in order to build QUADcore. Rename "makefile.old" to "makefile" and try to build the tool. For more details and problems related to building tools with Pin, please consult the available information on the Pin website @ http://software.intel.com/en-us/articles/pintool#GettingStarted

How to use
==========

Using Pin, an application and a tool are invoked as follows.

pin [pin-options] -t [toolname] [tool-options] -- [application] [application-options]

QUADcore can be invoked as follows.

[Linux]
pin -t [QUADcore-path] QUADcore.so [QUADcore-options] -- [application-name] [application-options]

If the operating system configuration prevents Pin from using the default (parent) injection mode, try this:

pin -injection child -t [QUADcore-path] QUADcore.so [QUADcore-options] -- [application-name] [application-options]

[Windows]
pin -t [QUADcore-path] QUADcore.dll [QUADcore-options] -- [application-name] [application-options]


----------------------------------
*Important Note for Windows users*
----------------------------------

Pin on Windows uses 'dbghelp.dll' by Microsoft to provide symbolic information. This DLL is not distributed with the kit. In order to get support for symbolic information in Pin, you have to download the "Debugging Tools For Windows" package, version 6.8.4.0 from http://www.microsoft.com/whdc/devtools/debugging/default.mspx. Use "Debugging Tools For Windows 32-bit Version" for IA-32 architectures and "Debugging Tools For Windows - Native X64" for Intel(R) 64 architectures. Distribution of the debugging tools is provided in .msi format which must be installed to extract a single file. Copy dbghelp.dll from the package into "ia32\bin" or "intel64\bin" directory of the Pin kit. This directory should already contain pin.exe and pinvm.dll files.

QUADcore Command line Options
=============================

Beside the common built-in options for Pin-developed tools, there are some specific command line options available to customize QUADcore. Here is the list:

-filter_uncommon_functions
        Filter out uncommon function names which are unlikely to be defined by user
        (beginning with question mark, underscore(s), etc.)
	
* this is useful if you do not want to see strange function names (usually library functions) appearing in the report file(s). The default value for this flag is set to 'true', so use '-filter_uncommon_functions 0' if you want to see all the function names in the main image file of the application, or there are some functions that are filtered out mistakenly by QUADcore!

-include_external_images
	Trace functions that are contained in external image file(s)

* This option enables tracing the functions that are contained in external image file(s). By default, only the functions in the main image file are traced and reported. This option together with '-filter_uncommon_functions' provides more flexibility to include/exclude required/unwanted functions in the report files. This option also has considerable impact on the reported quantitative bindings data and the corresponding producers/consumers.

-ignore_stack_access
        Ignore memory accesses within application's stack region

* By default, QUADcore tracks ALL memory accesses to produce binding information. This means, a function extensively using local variable(s) on the stack results in reporting self-bindings in the form of 'x->x' data transfers, which sometimes makes the reports polluted or we get some biased statistics due to a function's formal input parameter that is referenced many times in the stack region after call. To avoid this, there is a possibility to specify '-ignore_stack_access' in the command line, which tends to provide a clear and straightforward information to the user.

-use_monitor_list [file name]
        Create output report files only for certain function(s) in the application
        and filter out the rest (the functions are listed in a text file whose name
        follows)

* This option is helpful if there is a need to have the output report files only for specific function(s) and not all. The function names to monitor should be specified in a normal text file, whose path/name should be provided as the following argument.

-xmlfile  
        Specify file name for output data in XML format

* The main output report file is in XML format and named 'dek_arch.xml' by default. This can be changed by using this option.

-verbose
	No silence! print the number of instruction currently being executed on the console
* By default, QUADcore is silent.


Output Files
============

1. After instrumenting the application, all the producer/consumer bindings data is stored in an XML file named 'dek_arch.xml' in the current directory by default (previous <QUAD> elements in the xml file are removed if any).

The elements that are written in the XML file are stored under the root element, <ORGANIZATION>, in the following form:

<?xml version="1.0" encoding="ISO-8859-1" ?>
<!DOCTYPE ORGANIZATION SYSTEM "architecture.dtd">
<ORGANIZATION>
    <PROFILE>
        <QUAD>
            <BINDING>
                <PRODUCER>x264_validate_parameters</PRODUCER>
                <CONSUMER>x264_ratecontrol_new</CONSUMER>
                <DATA_TRANSFER>72</DATA_TRANSFER>
                <UnMA>72</UnMA>
            </BINDING>
            <BINDING>
                <PRODUCER>x264_validate_parameters</PRODUCER>
                <CONSUMER>x264_macroblock_cache_load</CONSUMER>
                <DATA_TRANSFER>28800</DATA_TRANSFER>
                <UnMA>464</UnMA>
            </BINDING>
             .
             .
             .
        </QUAD>
         .
         .
         .
    </PROFILE>
      .
      .
      .
</ORGANIZATION>


Terms
-----

BINDING -> When a function (itself or someone this function is responsible for calling and we are simply not interested to monitor the callee; e.g. system library functions, etc.) writes to a memory location, and later the same memory location is read by another function, we say a binding is established.

PRODUCER -> The name of the function who is responsible for the most recent write to a memory address.

CONSUMER -> The name of the function who is responsible for reading from that memory location.

DATA_TRANSFER -> The total amount of data being read in this fashion (note that if the same memory location is read 100 times, it is regarded as 100 bytes binding).

UnMA -> This value shows the number of unique memory addresses used for this transfer, it could be regarded as the actual size of memory buffer needed for the data transfer.

2. 'QDUGraph.dot' is output for visualization and contains all the binding information which is contained in the main XML file. For further details, refer to 'Output Visualization' section in the following.

3. Summary report file ('ML_OV_Summary.txt') is also created containing information about the functions specified in a monitor list, only in case the user has specified the relevant option in the command line. This text file basically provides statistics on total bytes/UnMA for selected functions. There are eight different values that are explained in the following.

IN_ML -> Total number of bytes read by this function that a function in the monitor list is responsible for producing the value(s) of the byte(s)

IN_ML_UnMA -> Total number of unique memory addresses used corresponding to 'IN_ML'

OUT_ML -> Total number of bytes read by a function in the monitor list that this function is responsible for producing the value(s) of the byte(s)

OUT_ML_UnMA -> Total number of unique memory addresses used corresponding to 'OUT_ML'

IN_ALL -> Total number of bytes read by this function that a function in the application is responsible for producing the value(s) of the byte(s)

IN_ALL_UnMA -> Total number of unique memory addresses used corresponding to 'IN_ALL'

OUT_ALL -> Total number of bytes read by a function in the application that this function is responsible for producing the value(s) of the byte(s)

OUT_ALL_UnMA -> Total number of unique memory addresses used corresponding to 'OUT_ALL'


Output Visualization
====================

The Quantitative Data Usage Graph (QDUG) created by QUADcore can also be visualized with any package capable of interpreting standard '.dot' files. For example, Graphviz - Graph Visualization Software, which is available for download from http://www.graphviz.org/Download.php

QUADcore will output a file named 'QDUGraph.dot' in the current directory. This file can be converted to the pdf format using the following command:

dot -Tpdf QDUGraph.dot -O


QUADcore revision history
=========================

v2.0
------
The initial version of the QUAD v2.0 core module, which is responsible for the critical task of Memory Access Tracing (MAT) during the instrumentation, is implemented and is currently being tested for performance and accuracy of extracted profiling data. In comparison with the primary implementation of QUAD, two main causes of performance issues are addressed to improve both the instrumentation time and the required memory footprint to trace accesses.


v0.4.3
------
-> a list of communicating functions with each kernel is extracted from the profile data and stored separately for each function in the monitor list in two modes (In one the kernel is acting as a producer, in the other, as a consumer. The names of the output text files are <kernel_(p).txt> and <kernel_(c).txt>


v0.4.2
------
-> Verbose option revised to print something only at the intervals of 1 million instructions
-> QDUGraph.dot header modified to make the final graph more readable

v0.4.1
------
-> Added the option to run the tool in the verbose ON/OFF mode

v0.4
----
-> Added command line option to include/exclude functions that are not contained in the main image file of an application.

v0.3
----
-> Added the command line option for a filter list specification (functions we are interested to monitor) and overall accumulative statistics regarding the total bytes in/out for each function as well as UMA info.

-> Added the command line option to filter out uncommon functions in the application (should prevent the tracer from diving into system related modules, libraries, etc.) 

v0.2.1
------
-> Uses 'Pintools' built-in constructs to monitor the changes to the esp (Extended Stack Pointer) register. Higher level of portability compared to the inline assembly version (v0.2)

v0.2
----
-> Added command line option to exclude/include stack region memory accesses
-> Added command line option for XML file name specification

v0.1
----
This is the very first version of QUADcore

-> Has basic capabilities
-> Includes UMA
-> Traces all memory accesses including Stack region


Bug Report
==========

Please use the bug report facility on sourceforge. Alternatively, you may direct your bug reports to "Arash Ostadzadeh" (ostadzadeh@gmail.com). It will be helpful if you have a clear description of what went wrong.
