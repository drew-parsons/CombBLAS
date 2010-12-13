#ifndef PY_DENSE_PAR_VEC_H
#define PY_DENSE_PAR_VEC_H

#include "../../CombBLAS/SpParVec.h"
#include "../../CombBLAS/SpTuples.h"
#include "../../CombBLAS/SpDCCols.h"
#include "../../CombBLAS/SpParMat.h"
#include "../../CombBLAS/SpParVec.h"
#include "../../CombBLAS/DenseParMat.h"
#include "../../CombBLAS/DenseParVec.h"
#include "../../CombBLAS/SpParVec.h"
#include "../../CombBLAS/ParFriends.h"

#include "pyCombBLAS.h"
class pySpParMat;
class pySpParVec;
class pyDenseParVec;

class pyDenseParVec {
protected:

	DenseParVec<int64_t, int64_t> v;
	
	friend class pySpParVec;
	friend class pySpParMat;
	friend pySpParVec* EWiseMult(const pySpParVec& a, const pyDenseParVec& b, bool exclude, int64_t zero);
	friend void EWiseMult_inplacefirst(pySpParVec& a, const pyDenseParVec& b, bool exclude, int64_t zero);

	pyDenseParVec();
/////////////// everything below this appears in python interface:
public:
	pyDenseParVec(int64_t size, int64_t init);
	pyDenseParVec(int64_t size, int64_t init, int64_t zero);
	
	pySpParVec* sparse() const;
	pySpParVec* sparse(int64_t zero) const;
	
public:
	int64_t len() const;
	
	void add(const pyDenseParVec& other);
	void add(const pySpParVec& other);
	pyDenseParVec& operator+=(const pyDenseParVec & rhs);
	pyDenseParVec& operator-=(const pyDenseParVec & rhs);
	pyDenseParVec& operator+=(const pySpParVec & rhs);
	pyDenseParVec& operator-=(const pySpParVec & rhs);
	//pyDenseParVec& operator=(const pyDenseParVec & rhs); // SWIG doesn't allow operator=
	
	pyDenseParVec* operator+(const pyDenseParVec & rhs);
	pyDenseParVec* operator-(const pyDenseParVec & rhs);
	pyDenseParVec* operator+(const pySpParVec & rhs);
	pyDenseParVec* operator-(const pySpParVec & rhs);
	
	pyDenseParVec* copy();
	
	void SetElement (int64_t indx, int64_t numx);	// element-wise assignment
	int64_t GetElement (int64_t indx);	// element-wise fetch
	
	void RandPerm();

	void printall();
	
public:
	void invert(); // "~";  almost equal to logical_not
	void abs();
	void negate();
	
	int64_t getnnz() const;
	int64_t getnz() const;

	
public:	
	void load(const char* filename);
	
public:
	int64_t Count_GreaterThan(int64_t value);
	pySpParVec* Find_totality();
	pySpParVec* Find_GreaterThan(int64_t value);
	pySpParVec* Find_NotEqual(int64_t value);
	pyDenseParVec* FindInds_GreaterThan(int64_t value);
	pyDenseParVec* FindInds_NotEqual(int64_t value);
	
	pyDenseParVec* SubsRef(const pyDenseParVec& ri);
	void ApplyMasked_SetTo(const pySpParVec& mask, int64_t value);

public:
	static pyDenseParVec* range(int64_t howmany, int64_t start);

};

#endif
