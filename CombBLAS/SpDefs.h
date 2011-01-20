/****************************************************************/
/* Sequential and Parallel Sparse Matrix Multiplication Library  /
/  version 2.3 --------------------------------------------------/
/  date: 01/18/2009 ---------------------------------------------/
/  author: Aydin Buluc (aydin@cs.ucsb.edu) ----------------------/
\****************************************************************/


#ifndef _SP_DEFS_H_
#define _SP_DEFS_H_

#include <cmath>
#include <limits.h>
#include "SequenceHeaps/knheap.C"
#include "psort-1.0/src/psort.h"
#include "psort-1.0/src/psort_samplesort.h"
#include "psort-1.0/driver/MersenneTwister.h"
#include "CommGrid.h"

#define EPSILON 0.01
#define FLOPSPERLOC 0	// always use SPA based merger inside the sequential code
#define HEAPMERGE 1
#define MEM_EFFICIENT_STAGES 8

#define GRIDMISMATCH 3001
#define DIMMISMATCH 3002
#define NOTSQUARE 3003
#define NOFILE 3004


// MPI Message tags 
// Prefixes denote functions
//	TR: Transpose
//	RD: ReadDistribute
//	RF: Sparse matrix indexing
#define TRTAGNZ 121
#define TRTAGM 122
#define TRTAGN 123
#define TRTAGROWS 124
#define TRTAGCOLS 125
#define TRTAGVALS 126
#define RDTAGINDS 127
#define RDTAGVALS 128
#define RDTAGNNZ 129
#define RFROWIDS 130
#define RFCOLIDS 131
#define TRROWX 132
#define TRCOLX 133
#define TRX 134	
#define TRI 135
#define TRNNZ 136
#define TROST 137
#define TRLUT 138
#define SWAPTAG 139

enum Dim
{
Column,
Row
};


// force 8-bytes alignment in heap allocated memory
#ifndef ALIGN
#define ALIGN 8
#endif

#ifndef THRESHOLD
#define THRESHOLD 4	// if range1.size() / range2.size() < threshold, use scanning based indexing
#endif

#ifndef MEMORYINBYTES
#define MEMORYINBYTES  1048576	// 1 MB, it is advised to define MEMORYINBYTES to be "at most" (1/4)th of available memory per core
#endif

#endif
