/****************************************************************/
/* Sequential and Parallel Sparse Matrix Multiplication Library */
/* version 2.3 --------------------------------------------------/
/* date: 01/18/2009 ---------------------------------------------/
/* author: Aydin Buluc (aydin@cs.ucsb.edu) ----------------------/
/****************************************************************/

#ifndef _SP_PAR_MPI2_H_
#define _SP_PAR_MPI2_H_

#include <iostream>
#include <fstream>
#include <cmath>
#include <mpi.h>
#include <vector>
#include <iterator>
#ifdef NOTR1
	#include <boost/tr1/memory.hpp>
	#include <boost/tr1/tuple.hpp>
#else
	#include <tr1/memory>	// for shared_ptr
	#include <tr1/tuple>
#endif
#include "SpMat.h"
#include "SpTuples.h"
#include "SpDCCols.h"
#include "CommGrid.h"
#include "MPIType.h"
#include "LocArr.h"
#include "SpDefs.h"
#include "Deleter.h"
#include "SpHelper.h"
#include "SpParHelper.h"
#include "DenseParMat.h"
#include "Friends.h"

using namespace std;
using namespace std::tr1;


/**
  * This class implements an asynchronous 2D algorithm, in the sense that there is no notion of stages.
  * \n The process that completes its submatrix update, requests subsequent matrices from their owners w/out waiting to sychronize with other processors
  * \n This partially remedies the severe load balancing problem in sparse matrices. 
  * \n The class uses MPI-2 to achieve one-sided asynchronous communication
  * \n The algorithm treats each submatrix as a single block
  * \n Local data structure can be any SpMat that has a constructor with array sizes and getarrs() member 
  */
template <class IT, class NT, class DER>
class SpParMPI2
{
public:
	// Constructors
	SpParMPI2 ();
	SpParMPI2 (DER * myseq, shared_ptr<CommGrid> grid);
		
	SpParMPI2 (ifstream & input, MPI::Intracomm & world);
	SpParMPI2 (DER * myseq, MPI::Intracomm & world);	

	SpParMPI2 (const SpParMPI2< IT,NT,DER > & rhs);				// copy constructor
	SpParMPI2< IT,NT,DER > & operator=(const SpParMPI2< IT,NT,DER > & rhs);	// assignment operator
	SpParMPI2< IT,NT,DER > & operator+=(const SpParMPI2< IT,NT,DER > & rhs);
	~SpParMPI2 ();

	void Transpose();

	template <typename SR, typename IU, typename NU1, typename NU2, typename UDER1, typename UDER2> 
	friend SpParMPI2<IU,typename promote_trait<NU1,NU2>::T_promote,typename promote_trait<UDER1,UDER2>::T_promote> 
	Mult_AnXBn (const SpParMPI2<IU,NU1,UDER1> & A, const SpParMPI2<IU,NU2,UDER2> & B );

	void ElementWiseMult (const SpParMPI2< IT,NT,DER >  & rhs, bool exclude);
	void ElementWiseScale(DenseParMat<IT, NT> & rhs);

	template <typename _UnaryOperation>
	void Apply(_UnaryOperation __unary_op)
	{
		spSeq->Apply(__unary_op);	
	}

	template <typename _BinaryOperation>
	void UpdateDense(DenseParMat<IT, NT> & rhs, _BinaryOperation __binary_op) const;

	void PrintInfo() const;

	template <typename IU, typename NU1, typename NU2, typename UDER1, typename UDER2> 
	friend SpParMPI2<IU,typename promote_trait<NU1,NU2>::T_promote,typename promote_trait<UDER1,UDER2>::T_promote> 
	EWiseMult (const SpParMPI2<IU,NU1,UDER1> & A, const SpParMPI2<IU,NU2,UDER2> & B , bool exclude);

	template <typename NNT, typename NDER>
	SpParMPI2< IT,NNT,NDER > ConvertNumericType ();

	IT getnrow() const;
	IT getncol() const;
	IT getnnz() const;

	SpParMPI2<IT,NT,DER> SubsRefCol (const vector<IT> & ci) const;				// Column indexing with special parallel semantics
	SpParMPI2<IT,NT,DER> operator() (const vector<IT> & ri, const vector<IT> & ci) const;	// General indexing with serial semantics

	ifstream& ReadDistribute (ifstream& infile, int master);
	ofstream& put(ofstream& outfile) const;

	shared_ptr<CommGrid> getcommgrid () { return commGrid; }	
	IT getlocalrows() const { return spSeq->getnrow(); }
	IT getlocalcols() const { return spSeq->getncol();} 
	IT getlocalnnz() const { return spSeq->getnnz(); }
	DER seq() { return (*spSeq); }
private:
	const static IT zero = static_cast<IT>(0);
	shared_ptr<CommGrid> commGrid; 
	DER * spSeq;
	
	template <class IU, class NU>
	friend class DenseParMat;

	template <typename IU, typename NU, typename UDER> 	
	friend ofstream& operator<< (ofstream& outfile, const SpParMPI2<IU,NU,UDER> & s);	
};

#include "SpParMPI2.cpp"
#endif
