//=================================================================================================
/*!
//  \file blaze/math/adaptors/UniLowerMatrix.h
//  \brief Header file for the implementation of a lower unitriangular matrix adaptor
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_ADAPTORS_UNILOWERMATRIX_H_
#define _BLAZE_MATH_ADAPTORS_UNILOWERMATRIX_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/adaptors/unilowermatrix/BaseTemplate.h>
#include <blaze/math/adaptors/unilowermatrix/Dense.h>
#include <blaze/math/adaptors/unilowermatrix/Sparse.h>
#include <blaze/math/Forward.h>
#include <blaze/math/traits/AddTrait.h>
#include <blaze/math/traits/ColumnTrait.h>
#include <blaze/math/traits/DerestrictTrait.h>
#include <blaze/math/traits/DivTrait.h>
#include <blaze/math/traits/MathTrait.h>
#include <blaze/math/traits/MultTrait.h>
#include <blaze/math/traits/RowTrait.h>
#include <blaze/math/traits/SubmatrixTrait.h>
#include <blaze/math/traits/SubTrait.h>
#include <blaze/math/typetraits/Columns.h>
#include <blaze/math/typetraits/IsAdaptor.h>
#include <blaze/math/typetraits/IsResizable.h>
#include <blaze/math/typetraits/IsRestricted.h>
#include <blaze/math/typetraits/IsSquare.h>
#include <blaze/math/typetraits/IsUniLower.h>
#include <blaze/math/typetraits/RemoveAdaptor.h>
#include <blaze/math/typetraits/Rows.h>
#include <blaze/util/constraints/Numeric.h>


namespace blaze {

//=================================================================================================
//
//  UNILOWERMATRIX OPERATORS
//
//=================================================================================================

//*************************************************************************************************
/*!\name UniLowerMatrix operators */
//@{
template< typename MT, bool SO, bool DF >
inline void reset( UniLowerMatrix<MT,SO,DF>& m );

template< typename MT, bool SO, bool DF >
inline void reset( UniLowerMatrix<MT,SO,DF>& m, size_t i );

template< typename MT, bool SO, bool DF >
inline void clear( UniLowerMatrix<MT,SO,DF>& m );

template< typename MT, bool SO, bool DF >
inline bool isDefault( const UniLowerMatrix<MT,SO,DF>& m );

template< typename MT, bool SO, bool DF >
inline void swap( UniLowerMatrix<MT,SO,DF>& a, UniLowerMatrix<MT,SO,DF>& b ) /* throw() */;
//@}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Resetting the given unilower matrix.
// \ingroup unilower_matrix
//
// \param m The unilower matrix to be resetted.
// \return void
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline void reset( UniLowerMatrix<MT,SO,DF>& m )
{
   m.reset();
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Resetting the specified row/column of the given unilower matrix.
// \ingroup unilower_matrix
//
// \param m The unilower matrix to be resetted.
// \param i The index of the row/column to be resetted.
// \return void
//
// This function resets the values in the specified row/column of the given unilower matrix to
// their default value. In case the given matrix is a \a rowMajor matrix the function resets the
// values in row \a i, if it is a \a columnMajor matrix the function resets the values in column
// \a i. Note that the capacity of the row/column remains unchanged.
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline void reset( UniLowerMatrix<MT,SO,DF>& m, size_t i )
{
   m.reset( i );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Clearing the given unilower matrix.
// \ingroup unilower_matrix
//
// \param m The unilower matrix to be cleared.
// \return void
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline void clear( UniLowerMatrix<MT,SO,DF>& m )
{
   m.clear();
}
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns whether the given resizable unilower matrix is in default state.
// \ingroup unilower_matrix
//
// \param m The unilower matrix to be tested for its default state.
// \return \a true in case the given matrix is in default state, \a false otherwise.
//
// This function checks whether the resizable lower unitriangular matrix is in default state.
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline bool isDefault_backend( const UniLowerMatrix<MT,SO,DF>& m, TrueType )
{
   return ( m.rows() == 0UL );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns whether the given fixed-size unilower matrix is in default state.
// \ingroup unilower_matrix
//
// \param m The unilower matrix to be tested for its default state.
// \return \a true in case the given matrix is in default state, \a false otherwise.
//
// This function checks whether the fixed-size lower unitriangular matrix is in default state.
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline bool isDefault_backend( const UniLowerMatrix<MT,SO,DF>& m, FalseType )
{
   return isIdentity( m );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Returns whether the given unilower matrix is in default state.
// \ingroup unilower_matrix
//
// \param m The unilower matrix to be tested for its default state.
// \return \a true in case the given matrix is in default state, \a false otherwise.
//
// This function checks whether the lower unitriangular matrix is in default state. The following
// example demonstrates the use of the \a isDefault function:

   \code
   using blaze::DynamicMatrix;
   using blaze::UniLowerMatrix;
   using blaze::rowMajor;

   UniLowerMatrix< DynamicMatrix<int,rowMajor> > A;
   // ... Resizing and initialization
   if( isDefault( A ) ) { ... }
   \endcode
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline bool isDefault( const UniLowerMatrix<MT,SO,DF>& m )
{
   return isDefault_backend( m, typename IsResizable<MT>::Type() );
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Swapping the contents of two matrices.
// \ingroup unilower_matrix
//
// \param a The first matrix to be swapped.
// \param b The second matrix to be swapped.
// \return void
// \exception no-throw guarantee.
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline void swap( UniLowerMatrix<MT,SO,DF>& a, UniLowerMatrix<MT,SO,DF>& b ) /* throw() */
{
   a.swap( b );
}
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Returns a reference to the instance without the access restrictions to the upper part.
// \ingroup math_shims
//
// \param m The unilower matrix to be derestricted.
// \return Reference to the matrix without access restrictions.
//
// This function returns a reference to the given unilower matrix instance that has no access
// restrictions to the upper part of the matrix.\n
// This function must \b NOT be called explicitly! It is used internally for the performance
// optimized evaluation of expression templates. Calling this function explicitly might result
// in the violation of invariants, erroneous results and/or in compilation errors.
*/
template< typename MT  // Type of the adapted matrix
        , bool SO      // Storage order of the adapted matrix
        , bool DF >    // Density flag
inline MT& derestrict( UniLowerMatrix<MT,SO,DF>& m )
{
   return m.matrix_;
}
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ROWS SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct Rows< UniLowerMatrix<MT,SO,DF> > : public Rows<MT>
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  COLUMNS SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct Columns< UniLowerMatrix<MT,SO,DF> > : public Columns<MT>
{};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISSQUARE SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct IsSquare< UniLowerMatrix<MT,SO,DF> > : public TrueType
{
   enum { value = 1 };
   typedef TrueType  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISUNILOWER SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct IsUniLower< UniLowerMatrix<MT,SO,DF> > : public TrueType
{
   enum { value = 1 };
   typedef TrueType  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISADAPTOR SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct IsAdaptor< UniLowerMatrix<MT,SO,DF> > : public TrueType
{
   enum { value = 1 };
   typedef TrueType  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISRESTRICTED SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct IsRestricted< UniLowerMatrix<MT,SO,DF> > : public TrueType
{
   enum { value = 1 };
   typedef TrueType  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ISRESIZABLE SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct IsResizable< UniLowerMatrix<MT,SO,DF> > : public IsResizable<MT>::Type
{
   enum { value = IsResizable<MT>::value };
   typedef typename IsResizable<MT>::Type  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  REMOVEADAPTOR SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct RemoveAdaptor< UniLowerMatrix<MT,SO,DF> >
{
   typedef MT  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  DERESTRICTTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct DerestrictTrait< UniLowerMatrix<MT,SO,DF> >
{
   typedef MT&  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ADDTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO1, bool DF, typename T, size_t M, size_t N, bool SO2 >
struct AddTrait< UniLowerMatrix<MT,SO1,DF>, StaticMatrix<T,M,N,SO2> >
{
   typedef typename AddTrait< MT, StaticMatrix<T,M,N,SO2> >::Type  Type;
};

template< typename T, size_t M, size_t N, bool SO1, typename MT, bool SO2, bool DF >
struct AddTrait< StaticMatrix<T,M,N,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename AddTrait< StaticMatrix<T,M,N,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, size_t M, size_t N, bool SO2 >
struct AddTrait< UniLowerMatrix<MT,SO1,DF>, HybridMatrix<T,M,N,SO2> >
{
   typedef typename AddTrait< MT, HybridMatrix<T,M,N,SO2> >::Type  Type;
};

template< typename T, size_t M, size_t N, bool SO1, typename MT, bool SO2, bool DF >
struct AddTrait< HybridMatrix<T,M,N,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename AddTrait< HybridMatrix<T,M,N,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, bool SO2 >
struct AddTrait< UniLowerMatrix<MT,SO1,DF>, DynamicMatrix<T,SO2> >
{
   typedef typename AddTrait< MT, DynamicMatrix<T,SO2> >::Type  Type;
};

template< typename T, bool SO1, typename MT, bool SO2, bool DF >
struct AddTrait< DynamicMatrix<T,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename AddTrait< DynamicMatrix<T,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, bool SO2 >
struct AddTrait< UniLowerMatrix<MT,SO1,DF>, CompressedMatrix<T,SO2> >
{
   typedef typename AddTrait< MT, CompressedMatrix<T,SO2> >::Type  Type;
};

template< typename T, bool SO1, typename MT, bool SO2, bool DF >
struct AddTrait< CompressedMatrix<T,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename AddTrait< CompressedMatrix<T,SO1>, MT >::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2, bool NF >
struct AddTrait< UniLowerMatrix<MT1,SO1,DF1>, SymmetricMatrix<MT2,SO2,DF2,NF> >
{
   typedef typename AddTrait<MT1,MT2>::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, bool NF, typename MT2, bool SO2, bool DF2 >
struct AddTrait< SymmetricMatrix<MT1,SO1,DF1,NF>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef typename AddTrait<MT1,MT2>::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct AddTrait< UniLowerMatrix<MT1,SO1,DF1>, LowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename AddTrait<MT1,MT2>::Type >  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct AddTrait< LowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename AddTrait<MT1,MT2>::Type >  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct AddTrait< UniLowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename AddTrait<MT1,MT2>::Type >  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  SUBTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO1, bool DF, typename T, size_t M, size_t N, bool SO2 >
struct SubTrait< UniLowerMatrix<MT,SO1,DF>, StaticMatrix<T,M,N,SO2> >
{
   typedef typename SubTrait< MT, StaticMatrix<T,M,N,SO2> >::Type  Type;
};

template< typename T, size_t M, size_t N, bool SO1, typename MT, bool SO2, bool DF >
struct SubTrait< StaticMatrix<T,M,N,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename SubTrait< StaticMatrix<T,M,N,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, size_t M, size_t N, bool SO2 >
struct SubTrait< UniLowerMatrix<MT,SO1,DF>, HybridMatrix<T,M,N,SO2> >
{
   typedef typename SubTrait< MT, HybridMatrix<T,M,N,SO2> >::Type  Type;
};

template< typename T, size_t M, size_t N, bool SO1, typename MT, bool SO2, bool DF >
struct SubTrait< HybridMatrix<T,M,N,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename SubTrait< HybridMatrix<T,M,N,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, bool SO2 >
struct SubTrait< UniLowerMatrix<MT,SO1,DF>, DynamicMatrix<T,SO2> >
{
   typedef typename SubTrait< MT, DynamicMatrix<T,SO2> >::Type  Type;
};

template< typename T, bool SO1, typename MT, bool SO2, bool DF >
struct SubTrait< DynamicMatrix<T,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename SubTrait< DynamicMatrix<T,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, bool SO2 >
struct SubTrait< UniLowerMatrix<MT,SO1,DF>, CompressedMatrix<T,SO2> >
{
   typedef typename SubTrait< MT, CompressedMatrix<T,SO2> >::Type  Type;
};

template< typename T, bool SO1, typename MT, bool SO2, bool DF >
struct SubTrait< CompressedMatrix<T,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename SubTrait< CompressedMatrix<T,SO1>, MT >::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2, bool NF >
struct SubTrait< UniLowerMatrix<MT1,SO1,DF1>, SymmetricMatrix<MT2,SO2,DF2,NF> >
{
   typedef typename SubTrait<MT1,MT2>::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, bool NF, typename MT2, bool SO2, bool DF2 >
struct SubTrait< SymmetricMatrix<MT1,SO1,DF1,NF>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef typename SubTrait<MT1,MT2>::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct SubTrait< UniLowerMatrix<MT1,SO1,DF1>, LowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename SubTrait<MT1,MT2>::Type >  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct SubTrait< LowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename SubTrait<MT1,MT2>::Type >  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct SubTrait< UniLowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename SubTrait<MT1,MT2>::Type >  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  MULTTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF, typename T >
struct MultTrait< UniLowerMatrix<MT,SO,DF>, T >
{
   typedef LowerMatrix< typename MultTrait<MT,T>::Type >  Type;
   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( T );
};

template< typename T, typename MT, bool SO, bool DF >
struct MultTrait< T, UniLowerMatrix<MT,SO,DF> >
{
   typedef LowerMatrix< typename MultTrait<T,MT>::Type >  Type;
   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( T );
};

template< typename MT, bool SO, bool DF, typename T, size_t N >
struct MultTrait< UniLowerMatrix<MT,SO,DF>, StaticVector<T,N,false> >
{
   typedef typename MultTrait< MT, StaticVector<T,N,false> >::Type  Type;
};

template< typename T, size_t N, typename MT, bool SO, bool DF >
struct MultTrait< StaticVector<T,N,true>, UniLowerMatrix<MT,SO,DF> >
{
   typedef typename MultTrait< StaticVector<T,N,true>, MT >::Type  Type;
};

template< typename MT, bool SO, bool DF, typename T, size_t N >
struct MultTrait< UniLowerMatrix<MT,SO,DF>, HybridVector<T,N,false> >
{
   typedef typename MultTrait< MT, HybridVector<T,N,false> >::Type  Type;
};

template< typename T, size_t N, typename MT, bool SO, bool DF >
struct MultTrait< HybridVector<T,N,true>, UniLowerMatrix<MT,SO,DF> >
{
   typedef typename MultTrait< HybridVector<T,N,true>, MT >::Type  Type;
};

template< typename MT, bool SO, bool DF, typename T >
struct MultTrait< UniLowerMatrix<MT,SO,DF>, DynamicVector<T,false> >
{
   typedef typename MultTrait< MT, DynamicVector<T,false> >::Type  Type;
};

template< typename T, typename MT, bool SO, bool DF >
struct MultTrait< DynamicVector<T,true>, UniLowerMatrix<MT,SO,DF> >
{
   typedef typename MultTrait< DynamicVector<T,true>, MT >::Type  Type;
};

template< typename MT, bool SO, bool DF, typename T >
struct MultTrait< UniLowerMatrix<MT,SO,DF>, CompressedVector<T,false> >
{
   typedef typename MultTrait< MT, CompressedVector<T,false> >::Type  Type;
};

template< typename T, typename MT, bool SO, bool DF >
struct MultTrait< CompressedVector<T,true>, UniLowerMatrix<MT,SO,DF> >
{
   typedef typename MultTrait< CompressedVector<T,true>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, size_t M, size_t N, bool SO2 >
struct MultTrait< UniLowerMatrix<MT,SO1,DF>, StaticMatrix<T,M,N,SO2> >
{
   typedef typename MultTrait< MT, StaticMatrix<T,M,N,SO2> >::Type  Type;
};

template< typename T, size_t M, size_t N, bool SO1, typename MT, bool SO2, bool DF >
struct MultTrait< StaticMatrix<T,M,N,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename MultTrait< StaticMatrix<T,M,N,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, size_t M, size_t N, bool SO2 >
struct MultTrait< UniLowerMatrix<MT,SO1,DF>, HybridMatrix<T,M,N,SO2> >
{
   typedef typename MultTrait< MT, HybridMatrix<T,M,N,SO2> >::Type  Type;
};

template< typename T, size_t M, size_t N, bool SO1, typename MT, bool SO2, bool DF >
struct MultTrait< HybridMatrix<T,M,N,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename MultTrait< HybridMatrix<T,M,N,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, bool SO2 >
struct MultTrait< UniLowerMatrix<MT,SO1,DF>, DynamicMatrix<T,SO2> >
{
   typedef typename MultTrait< MT, DynamicMatrix<T,SO2> >::Type  Type;
};

template< typename T, bool SO1, typename MT, bool SO2, bool DF >
struct MultTrait< DynamicMatrix<T,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename MultTrait< DynamicMatrix<T,SO1>, MT >::Type  Type;
};

template< typename MT, bool SO1, bool DF, typename T, bool SO2 >
struct MultTrait< UniLowerMatrix<MT,SO1,DF>, CompressedMatrix<T,SO2> >
{
   typedef typename MultTrait< MT, CompressedMatrix<T,SO2> >::Type  Type;
};

template< typename T, bool SO1, typename MT, bool SO2, bool DF >
struct MultTrait< CompressedMatrix<T,SO1>, UniLowerMatrix<MT,SO2,DF> >
{
   typedef typename MultTrait< CompressedMatrix<T,SO1>, MT >::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2, bool NF >
struct MultTrait< UniLowerMatrix<MT1,SO1,DF1>, SymmetricMatrix<MT2,SO2,DF2,NF> >
{
   typedef typename MultTrait<MT1,MT2>::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, bool NF, typename MT2, bool SO2, bool DF2 >
struct MultTrait< SymmetricMatrix<MT1,SO1,DF1,NF>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef typename MultTrait<MT1,MT2>::Type  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct MultTrait< UniLowerMatrix<MT1,SO1,DF1>, LowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename MultTrait<MT1,MT2>::Type >  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct MultTrait< LowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef LowerMatrix< typename MultTrait<MT1,MT2>::Type >  Type;
};

template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct MultTrait< UniLowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef UniLowerMatrix< typename MultTrait<MT1,MT2>::Type >  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  DIVTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF, typename T >
struct DivTrait< UniLowerMatrix<MT,SO,DF>, T >
{
   typedef LowerMatrix< typename DivTrait<MT,T>::Type >  Type;
   BLAZE_CONSTRAINT_MUST_BE_NUMERIC_TYPE( T );
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  MATHTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT1, bool SO1, bool DF1, typename MT2, bool SO2, bool DF2 >
struct MathTrait< UniLowerMatrix<MT1,SO1,DF1>, UniLowerMatrix<MT2,SO2,DF2> >
{
   typedef UniLowerMatrix< typename MathTrait<MT1,MT2>::HighType >  HighType;
   typedef UniLowerMatrix< typename MathTrait<MT1,MT2>::LowType  >  LowType;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  SUBMATRIXTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct SubmatrixTrait< UniLowerMatrix<MT,SO,DF> >
{
   typedef typename SubmatrixTrait<MT>::Type  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  ROWTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct RowTrait< UniLowerMatrix<MT,SO,DF> >
{
   typedef typename RowTrait<MT>::Type  Type;
};
/*! \endcond */
//*************************************************************************************************




//=================================================================================================
//
//  COLUMNTRAIT SPECIALIZATIONS
//
//=================================================================================================

//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
template< typename MT, bool SO, bool DF >
struct ColumnTrait< UniLowerMatrix<MT,SO,DF> >
{
   typedef typename ColumnTrait<MT>::Type  Type;
};
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif
