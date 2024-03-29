//=================================================================================================
/*!
//  \file src/mathtest/uniuppermatrix/SparseTest.cpp
//  \brief Source file for the UniUpperMatrix sparse test
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


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <cstdlib>
#include <iostream>
#include <blaze/math/SparseColumn.h>
#include <blaze/math/SparseRow.h>
#include <blaze/math/SparseSubmatrix.h>
#include <blaze/math/StaticMatrix.h>
#include <blaze/math/StaticVector.h>
#include <blaze/util/Complex.h>
#include <blazetest/mathtest/uniuppermatrix/SparseTest.h>


namespace blazetest {

namespace mathtest {

namespace uniuppermatrix {

//=================================================================================================
//
//  CONSTRUCTORS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Constructor for the UniUpperMatrix sparse test.
//
// \exception std::runtime_error Operation error detected.
*/
SparseTest::SparseTest()
{
   testConstructors();
   testAssignment();
   testAddAssign();
   testSubAssign();
   testMultAssign();
   testFunctionCall();
   testIterator();
   testNonZeros();
   testReset();
   testClear();
   testSet();
   testInsert();
   testAppend();
   testErase();
   testResize();
   testReserve();
   testTrim();
   testSwap();
   testFind();
   testLowerBound();
   testUpperBound();
   testIsDefault();
   testSubmatrix();
   testRow();
   testColumn();
}
//*************************************************************************************************




//=================================================================================================
//
//  TEST FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix constructors.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all constructors of the Matrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testConstructors()
{
   //=====================================================================================
   // Row-major default constructor
   //=====================================================================================

   // Default constructor (CompressedMatrix)
   {
      test_ = "Row-major UniUpperMatrix default constructor (CompressedMatrix)";

      const UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Row-major size constructor
   //=====================================================================================

   // Size constructor (CompressedMatrix)
   {
      test_ = "Row-major UniUpperMatrix size constructor (CompressedMatrix)";

      const UT upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkNonZeros( upper, 2UL );
   }


   //=====================================================================================
   // Row-major copy constructor
   //=====================================================================================

   // Copy constructor (0x0)
   {
      test_ = "Row-major UniUpperMatrix copy constructor (0x0)";

      const UT upper1;
      const UT upper2( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy constructor (3x3)
   {
      test_ = "Row-major UniUpperMatrix copy constructor (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const UT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 5UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major conversion constructor
   //=====================================================================================

   // Conversion constructor (0x0)
   {
      test_ = "Row-major UniUpperMatrix conversion constructor (0x0)";

      const blaze::DynamicMatrix<int,blaze::rowMajor> mat;
      const UT upper( mat );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Conversion constructor (uniupper)
   {
      test_ = "Row-major UniUpperMatrix conversion constructor (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      const UT upper( mat );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Conversion constructor (non-uniupper)
   {
      test_ = "Row-major UniUpperMatrix conversion constructor (non-upper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         const UT upper( mat );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of non-uniupper UniUpperMatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Conversion constructor (UniUpperMatrix)
   {
      test_ = "Row-major UniUpperMatrix conversion constructor (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const UT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 5UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major default constructor
   //=====================================================================================

   // Default constructor (CompressedMatrix)
   {
      test_ = "Column-major UniUpperMatrix default constructor (CompressedMatrix)";

      const OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major size constructor
   //=====================================================================================

   // Size constructor (CompressedMatrix)
   {
      test_ = "Column-major UniUpperMatrix size constructor (CompressedMatrix)";

      const OUT upper( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkNonZeros( upper, 2UL );
   }


   //=====================================================================================
   // Column-major copy constructor
   //=====================================================================================

   // Copy constructor (0x0)
   {
      test_ = "Column-major UniUpperMatrix copy constructor (0x0)";

      const OUT upper1;
      const OUT upper2( upper1 );

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy constructor (3x3)
   {
      test_ = "Column-major UniUpperMatrix copy constructor (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const OUT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 5UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major conversion constructor
   //=====================================================================================

   // Conversion constructor (0x0)
   {
      test_ = "Column-major UniUpperMatrix conversion constructor (0x0)";

      const blaze::DynamicMatrix<int,blaze::columnMajor> mat;
      const OUT upper( mat );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Conversion constructor (uniupper)
   {
      test_ = "Column-major UniUpperMatrix conversion constructor (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      const OUT upper( mat );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Conversion constructor (non-uniupper)
   {
      test_ = "Column-major UniUpperMatrix conversion constructor (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         const OUT upper( mat );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Setup of non-uniupper UniUpperMatrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Conversion constructor (UniUpperMatrix)
   {
      test_ = "Column-major UniUpperMatrix conversion constructor (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      const OUT upper2( upper1 );

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 5UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Construction failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of all assignment operators of the UniUpperMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testAssignment()
{
   //=====================================================================================
   // Row-major copy assignment
   //=====================================================================================

   // Copy assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix copy assignment (0x0)";

      UT upper1, upper2;

      upper2 = upper1;

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy assignment (3x3)
   {
      test_ = "Row-major UniUpperMatrix copy assignment (3x3)";

      UT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix dense matrix assignment (0x0)";

      const blaze::DynamicMatrix<int,blaze::rowMajor> mat;

      UT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Row-major/row-major dense matrix assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Row-major UniUpperMatrix sparse matrix assignment (0x0)";

      const blaze::CompressedMatrix<int,blaze::rowMajor> mat;

      UT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Row-major/row-major sparse matrix assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      UT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         UT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      UT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 1UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major copy assignment
   //=====================================================================================

   // Copy assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix copy assignment (0x0)";

      OUT upper1, upper2;

      upper2 = upper1;

      checkRows    ( upper2, 0UL );
      checkColumns ( upper2, 0UL );
      checkNonZeros( upper2, 0UL );
   }

   // Copy assignment (3x3)
   {
      test_ = "Column-major UniUpperMatrix copy assignment (3x3)";

      OUT upper1( 3UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;
      upper1(1,2) =  0;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix dense matrix assignment (0x0)";

      const blaze::DynamicMatrix<int,blaze::columnMajor> mat;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Column-major/row-major dense matrix assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix assignment (uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix assignment (non-uniupper)";

      blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> mat;
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::rowMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::StaticMatrix<int,3UL,3UL,blaze::columnMajor> > upper1;
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   // Conversion assignment (0x0)
   {
      test_ = "Column-major UniUpperMatrix sparse matrix assignment (0x0)";

      const blaze::CompressedMatrix<int,blaze::rowMajor> mat;

      OUT upper;
      upper = mat;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }

   // Column-major/row-major sparse matrix assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,2) =  1;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper;
      upper = mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix assignment (non-uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,1) = -4;
      mat(0,2) =  7;
      mat(1,1) =  1;
      mat(2,0) =  5;
      mat(2,2) =  1;

      try {
         OUT upper;
         upper = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,1) = -4;
      upper1(0,2) =  7;

      OUT upper2;
      upper2 = upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkNonZeros( upper2, 5UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != 7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) != 0 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix addition assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the addition assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testAddAssign()
{
   //=====================================================================================
   // Row-major dense matrix addition assignment
   //=====================================================================================

   // Row-major/row-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix addition assignment (not strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix addition assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix addition assignment (not strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix addition assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix addition assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix addition assignment (not strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix addition assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix addition assignment (not strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix addition assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major dense matrix addition assignment
   //=====================================================================================

   // Column-major/row-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix addition assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix addition assignment (not strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix addition assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix addition assignment (not strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix addition assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix addition assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix addition assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix addition assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) =  2;
      mat(0,2) = -7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper += mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1  5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix addition assignment (not strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix addition assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix addition assignment (not strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix addition assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper += mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Addition assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix subtraction assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the subtraction assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testSubAssign()
{
   //=====================================================================================
   // Row-major dense matrix subtraction assignment
   //=====================================================================================

   // Row-major/row-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix subtraction assignment (not strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix subtraction assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix subtraction assignment (not strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix subtraction assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix subtraction assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix subtraction assignment (not strictly upper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix subtraction assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix subtraction assignment (not strictly upper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix subtraction assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major dense matrix subtraction assignment
   //=====================================================================================

   // Column-major/row-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix subtraction assignment (strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix subtraction assignment (not strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix subtraction assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix subtraction assignment (not strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix subtraction assignment (not strictly upper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix subtraction assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix subtraction assignment (strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix subtraction assignment (strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 4UL );
      mat(0,1) = -2;
      mat(0,2) =  7;
      mat(1,2) =  5;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper -= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  0 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  0 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix subtraction assignment (not strictly upper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix subtraction assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix subtraction assignment (not strictly upper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix subtraction assignment (not strictly upper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 1UL );
      mat(2,0) = 6;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper -= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Subtraction assignment of not strictly upper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix multiplication assignment operators.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the multiplication assignment operators of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testMultAssign()
{
   //=====================================================================================
   // Row-major dense matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major sparse matrix multiplication assignment
   //=====================================================================================

   // Row-major/row-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/row-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 5UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/column-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Row-major/row-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/row-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Row-major/column-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Row-major/column-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      UT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 3UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix multiplication assignment (uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major dense matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      UT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major dense matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix dense matrix multiplication assignment (UniUpperMatrix)";

      OUT upper1( 3UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major sparse matrix multiplication assignment
   //=====================================================================================

   // Column-major/row-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix multiplication assignment (uniupper)";

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 6UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  1;
      mat(1,2) =  3;
      mat(2,2) =  1;
      mat.insert( 2UL, 1UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      upper *= mat;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != -7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=  3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/row-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 3UL, 3UL, 5UL );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper row-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/column-major sparse matrix multiplication assignment (non-uniupper)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix multiplication assignment (non-uniupper)";

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 3UL, 3UL, 0 );
      mat(0,0) =  1;
      mat(0,2) = -2;
      mat(1,1) =  4;
      mat(1,2) =  3;
      mat(2,2) =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      try {
         upper *= mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment of non-uniupper column-major matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // Column-major/row-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/row-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::rowMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // Column-major/column-major sparse matrix multiplication assignment (UniUpperMatrix)
   {
      test_ = "Column-major/column-major UniUpperMatrix sparse matrix multiplication assignment (UniUpperMatrix)";

      blaze::UniUpperMatrix< blaze::CompressedMatrix<int,blaze::columnMajor> > upper1( 3UL, 5UL );
      upper1(0,2) = -2;
      upper1(1,2) =  3;

      OUT upper2( 3UL );
      upper2(0,1) = -4;
      upper2(0,2) =  7;

      upper2 *= upper1;

      checkRows    ( upper2, 3UL );
      checkColumns ( upper2, 3UL );
      checkCapacity( upper2, 6UL );
      checkNonZeros( upper2, 6UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );
      checkNonZeros( upper2, 2UL, 3UL );

      if( upper2(0,0) != 1 || upper2(0,1) != -4 || upper2(0,2) != -7 ||
          upper2(1,0) != 0 || upper2(1,1) !=  1 || upper2(1,2) !=  3 ||
          upper2(2,0) != 0 || upper2(2,1) !=  0 || upper2(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Multiplication assignment failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 -4 -7 )\n( 0  1  3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix function call operator.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of adding and accessing elements via the function call operator
// of the UniUpperMatrix specialization. In case an error is detected, a \a std::runtime_error
// exception is thrown.
*/
void SparseTest::testFunctionCall()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::operator()";

      UT upper( 3UL );

      // Writing the element (1,2)
      upper(1,2) = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the element (0,1)
      upper(0,1) = upper(1,2);

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Adding to the element (0,2)
      upper(0,2) += 3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtracting from the element (0,1)
      upper(0,1) -= 4;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  3 )\n( 0  1  2 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplying the element (1,2)
      upper(1,2) *= -3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -6 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  3 )\n( 0  1 -6 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Dividing the element (1,2)
      upper(1,2) /= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  3 )\n( 0  1 -3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to write the element (1,1)
      try {
         upper(1,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to diagonal matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      // Trying to write the element (2,1)
      try {
         upper(2,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to lower matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::operator()";

      OUT upper( 3UL );

      // Writing the element (1,2)
      upper(1,2) = 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Writing the element (0,1)
      upper(0,1) = upper(1,2);

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Adding to the element (0,2)
      upper(0,2) += 3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 2 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Subtracting from the element (0,1)
      upper(0,1) -= 4;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  3 )\n( 0  1  2 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Multiplying the element (1,2)
      upper(1,2) *= -3;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -6 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  3 )\n( 0  1 -6 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Dividing the element (1,2)
      upper(1,2) /= 2;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) !=  3 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -3 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  3 )\n( 0  1 -3 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to write the element (1,1)
      try {
         upper(1,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to diagonal matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}

      // Trying to write the element (2,1)
      try {
         upper(2,1) = 5;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to lower matrix element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the UniUpperMatrix iterator implementation.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the iterator implementation of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testIterator()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      typedef UT::Iterator       Iterator;
      typedef UT::ConstIterator  ConstIterator;

      UT upper( 3UL );
      upper(0,2) = 2;
      upper(1,2) = 3;

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Row-major Iterator/ConstIterator conversion";

         ConstIterator it( begin( upper, 1UL ) );

         if( it == end( upper, 1UL ) || it->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th row via Iterator
      {
         test_ = "Row-major Iterator subtraction";

         const size_t number( end( upper, 0UL ) - begin( upper, 0UL ) );

         if( number != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st row via ConstIterator
      {
         test_ = "Row-major ConstIterator subtraction";

         const size_t number( cend( upper, 1UL ) - cbegin( upper, 1UL ) );

         if( number != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Row-major read-only access via ConstIterator";

         ConstIterator it ( cbegin( upper, 0UL ) );
         ConstIterator end( cend( upper, 0UL ) );

         if( it == end || it->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || it->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to upper elements via Iterator
      {
         test_ = "Row-major assignment to upper elements via Iterator";

         Iterator it1 = upper.find( 0UL, 2UL );
         Iterator it2 = upper.find( 1UL, 2UL );
         *it1 = 5;
         it2->value() = 7;

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 5 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 7 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 5 )\n( 0 1 7 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to diagonal elements via Iterator
      {
         test_ = "Row-major assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing addition assignment to upper elements via Iterator
      {
         test_ = "Row-major addition assignment to upper elements via Iterator";

         Iterator it1 = upper.find( 0UL, 2UL );
         Iterator it2 = upper.find( 1UL, 2UL );
         *it1 += 2;
         it2->value() += -2;

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 7 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 7 )\n( 0 1 5 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment to diagonal elements via Iterator
      {
         test_ = "Row-major addition assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing subtraction assignment to upper elements via Iterator
      {
         test_ = "Row-major subtraction assignment to upper elements via Iterator";

         Iterator it1 = upper.find( 0UL, 2UL );
         Iterator it2 = upper.find( 1UL, 2UL );
         *it1 -= 2;
         it2->value() -= -2;

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 5 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 7 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 5 )\n( 0 1 7 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment to diagonal elements via Iterator
      {
         test_ = "Row-major subtraction assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing multiplication assignment to upper elements via Iterator
      {
         test_ = "Row-major multiplication assignment to upper elements via Iterator";

         Iterator it1 = upper.find( 0UL, 2UL );
         Iterator it2 = upper.find( 1UL, 2UL );
         *it1 *= 2;
         it2->value() *= -2;

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) !=  10 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != -14 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=   1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1  0  10 )\n( 0  1 -14 )\n( 0  0   1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment to diagonal elements via Iterator
      {
         test_ = "Row-major multiplication assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing division assignment to upper elements via Iterator
      {
         test_ = "Row-major division assignment to upper elements via Iterator";

         Iterator it1 = upper.find( 0UL, 2UL );
         Iterator it2 = upper.find( 1UL, 2UL );
         *it1 /= 2;
         it2->value() /= -2;

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 5 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 7 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 5 )\n( 0 1 7 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment to diagonal elements via Iterator
      {
         test_ = "Row-major division assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      typedef OUT::Iterator       Iterator;
      typedef OUT::ConstIterator  ConstIterator;

      OUT upper( 3UL );
      upper(0,1) = 3;
      upper(0,2) = 2;

      // Testing conversion from Iterator to ConstIterator
      {
         test_ = "Column-major Iterator/ConstIterator conversion";

         ConstIterator it( begin( upper, 1UL ) );

         if( it == end( upper, 1UL ) || it->value() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Failed iterator conversion detected\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 0th column via Iterator
      {
         test_ = "Column-major Iterator subtraction";

         const size_t number( end( upper, 0UL ) - begin( upper, 0UL ) );

         if( number != 1UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 1\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Counting the number of elements in 1st column via ConstIterator
      {
         test_ = "Column-major ConstIterator subtraction";

         const size_t number( cend( upper, 1UL ) - cbegin( upper, 1UL ) );

         if( number != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid number of elements detected\n"
                << " Details:\n"
                << "   Number of elements         : " << number << "\n"
                << "   Expected number of elements: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing read-only access via ConstIterator
      {
         test_ = "Column-major read-only access via ConstIterator";

         ConstIterator it ( cbegin( upper, 2UL ) );
         ConstIterator end( cend( upper, 2UL ) );

         if( it == end || it->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid initial iterator detected\n";
            throw std::runtime_error( oss.str() );
         }

         ++it;

         if( it == end || it->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator pre-increment failed\n";
            throw std::runtime_error( oss.str() );
         }

         it++;

         if( it != end ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Iterator post-increment failed\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to upper elements via Iterator
      {
         test_ = "Column-major assignment to upper elements via Iterator";

         Iterator it1 = begin( upper, 1UL );
         Iterator it2 = begin( upper, 2UL );
         *it1 = 5;
         it2->value() = 7;

         if( upper(0,0) != 1 || upper(0,1) != 5 || upper(0,2) != 7 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 5 7 )\n( 0 1 0 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing assignment to diagonal elements via Iterator
      {
         test_ = "Column-major assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() = 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing addition assignment to upper elements via Iterator
      {
         test_ = "Column-major addition assignment to upper elements via Iterator";

         Iterator it1 = begin( upper, 1UL );
         Iterator it2 = begin( upper, 2UL );
         *it1 += 2;
         it2->value() += -2;

         if( upper(0,0) != 1 || upper(0,1) != 7 || upper(0,2) != 5 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 7 5 )\n( 0 1 0 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing addition assignment to diagonal elements via Iterator
      {
         test_ = "Column-major addition assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() += 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing subtraction assignment to upper elements via Iterator
      {
         test_ = "Column-major subtraction assignment to upper elements via Iterator";

         Iterator it1 = begin( upper, 1UL );
         Iterator it2 = begin( upper, 2UL );
         *it1 -= 2;
         it2->value() -= -2;

         if( upper(0,0) != 1 || upper(0,1) != 5 || upper(0,2) != 7 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 5 7 )\n( 0 1 0 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing subtraction assignment to diagonal elements via Iterator
      {
         test_ = "Column-major subtraction assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() -= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing multiplication assignment to upper elements via Iterator
      {
         test_ = "Column-major multiplication assignment to upper elements via Iterator";

         Iterator it1 = begin( upper, 1UL );
         Iterator it2 = begin( upper, 2UL );
         *it1 *= 2;
         it2->value() *= -2;

         if( upper(0,0) != 1 || upper(0,1) != 10 || upper(0,2) != -14 ||
             upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) !=   0 ||
             upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=   1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1  10 -14 )\n( 0   1   0 )\n( 0   0   1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing multiplication assignment to diagonal elements via Iterator
      {
         test_ = "Column-major multiplication assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() *= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }

      // Testing division assignment to upper elements via Iterator
      {
         test_ = "Column-major division assignment to upper elements via Iterator";

         Iterator it1 = begin( upper, 1UL );
         Iterator it2 = begin( upper, 2UL );
         *it1 /= 2;
         it2->value() /= -2;

         if( upper(0,0) != 1 || upper(0,1) != 5 || upper(0,2) != 7 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment via iterator failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 5 7 )\n( 0 1 0 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Testing division assignment to diagonal elements via Iterator
      {
         test_ = "Column-major division assignment to diagonal elements via Iterator";

         try {
            const Iterator it = begin( upper, 0UL );
            *it /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}

         try {
            const Iterator it = begin( upper, 0UL );
            it->value() /= 5;

            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Assignment to diagonal matrix element succeeded\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         catch( std::invalid_argument& ) {}
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c nonZeros() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c nonZeros() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testNonZeros()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::nonZeros()";

      // Default matrix
      {
         UT upper( 3UL );

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 3UL );
         checkNonZeros( upper, 3UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Fully filled matrix
      {
         UT upper( 3UL );
         upper(0,1) =  2;
         upper(0,2) =  3;
         upper(1,2) = -5;

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 3UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) !=  3 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != -5 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1  2  3 )\n( 0  1 -5 )\n( 0  0  1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::nonZeros()";

      // Default matrix
      {
         OUT upper( 3UL );

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 3UL );
         checkNonZeros( upper, 3UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Fully filled matrix
      {
         OUT upper( 3UL );
         upper(0,1) =  2;
         upper(0,2) =  3;
         upper(1,2) = -5;

         checkRows    ( upper, 3UL );
         checkColumns ( upper, 3UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 3UL );

         if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) !=  3 ||
             upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != -5 ||
             upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) !=  1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Initialization failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1  2  3 )\n( 0  1 -5 )\n( 0  0  1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reset() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reset() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testReset()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::reset()";

      // Initialization check
      UT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting an upper element
      reset( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a diagonal element
      reset( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a lower element
      reset( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting row 1
      reset( upper, 1UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting the entire matrix
      reset( upper );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::reset()";

      // Initialization check
      OUT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting an upper element
      reset( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a diagonal element
      reset( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting a lower element
      reset( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting column 1
      reset( upper, 1UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resetting the entire matrix
      reset( upper );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Reset operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c clear() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c clear() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testClear()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::clear()";

      // Initialization check
      UT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing an upper element
      clear( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 4 5 )\n( 0 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a diagonal element
      clear( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 4 5 )\n( 0 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a lower element
      clear( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 4 5 )\n( 0 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing the matrix
      clear( upper );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::clear()";

      // Initialization check
      OUT upper( 3UL );
      upper(0,1) = 2;
      upper(0,2) = 3;
      upper(1,2) = 5;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 6UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 3 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 3 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing an upper element
      clear( upper(0,2) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 4 5 )\n( 0 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a diagonal element
      clear( upper(1,1) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 4 5 )\n( 0 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing a lower element
      clear( upper(2,0) );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 || upper(0,2) != 0 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 5 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Clear operation failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 )\n( 0 4 5 )\n( 0 0 6 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Clearing the matrix
      clear( upper );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c set() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c set() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testSet()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::set()";

      typedef UT::Iterator  Iterator;

      // Initialization check
      UT upper( 4UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      // Setting a non-zero element
      {
         Iterator pos = upper.set( 1UL, 3UL, 2 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 2 || pos->index() != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 2\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,3) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 2 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Setting a second non-zero element
      {
         Iterator pos = upper.set( 1UL, 2UL, 3 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 3UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 3 || pos->index() != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 3\n"
                << "   Expected index: 2\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,2) != 3 || upper(1,3) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 3 2 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Setting an already existing element
      {
         Iterator pos = upper.set( 1UL, 3UL, 4 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 3UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 4 || pos->index() != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 4\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,2) != 3 || upper(1,3) != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 3 4 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::set()";

      typedef OUT::Iterator  Iterator;

      // Initialization check
      OUT upper( 4UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      // Setting a non-zero element
      {
         Iterator pos = upper.set( 1UL, 2UL, 2 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 2 || pos->index() != 1UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 2\n"
                << "   Expected index: 1\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,2) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 2 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Setting a second non-zero element
      {
         Iterator pos = upper.set( 0UL, 2UL, 3 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 3UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 3 || pos->index() != 0UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 3\n"
                << "   Expected index: 0\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(0,2) != 3 || upper(1,2) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 3 0 )\n( 0 1 2 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Setting an already existing element
      {
         Iterator pos = upper.set( 1UL, 2UL, 4 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 3UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 4 || pos->index() != 1UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 4\n"
                << "   Expected index: 1\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(0,2) != 3 || upper(1,2) != 4 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Setting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 3 0 )\n( 0 1 4 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c insert() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c insert() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testInsert()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::insert()";

      typedef UT::Iterator  Iterator;

      // Initialization check
      UT upper( 4UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      // Inserting a non-zero element
      {
         Iterator pos = upper.insert( 1UL, 3UL, 2 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 2 || pos->index() != 3UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 2\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,3) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Inserting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 2 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Inserting a second non-zero element
      {
         Iterator pos = upper.insert( 1UL, 2UL, 3 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 3UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 3 || pos->index() != 2UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 3\n"
                << "   Expected index: 2\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,2) != 3 || upper(1,3) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Inserting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 2 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to insert an already existing element
      try {
         upper.insert( 1UL, 3UL, 4 );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting an existing element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 2 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::insert()";

      typedef OUT::Iterator  Iterator;

      // Initialization check
      OUT upper( 4UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      // Inserting a non-zero element
      {
         Iterator pos = upper.insert( 1UL, 2UL, 2 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 2 || pos->index() != 1UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 2\n"
                << "   Expected index: 1\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(1,2) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Inserting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 2 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Inserting a second non-zero element
      {
         Iterator pos = upper.insert( 0UL, 2UL, 3 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 3UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( pos->value() != 3 || pos->index() != 0UL ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 3\n"
                << "   Expected index: 0\n";
            throw std::runtime_error( oss.str() );
         }

         if( upper(0,2) != 3 || upper(1,2) != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Inserting an element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 3 0 )\n( 0 1 2 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to insert an already existing element
      try {
         upper.insert( 1UL, 2UL, 4 );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Inserting an existing element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 3 0 )\n( 0 1 2 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c append() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c append() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testAppend()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::append()";

      // Appending with pre-allocation in each row
      {
         // Initialization check
         UT upper( 4UL, 9UL );
         upper.reserve( 0UL, 3UL );
         upper.reserve( 1UL, 2UL );
         upper.reserve( 2UL, 3UL );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 4UL );
         checkNonZeros( upper, 4UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         // Appending one non-zero element
         upper.append( 1UL, 2UL, 2 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 ||
             upper(1,1) != 1 || upper(1,2) != 2 ||
             upper(2,2) != 1 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Appending operation failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 2 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         upper.append( 0UL, 1UL, 3 );
         upper.append( 2UL, 3UL, 4 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 7UL );
         checkNonZeros( upper, 7UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 3 ||
             upper(1,1) != 1 || upper(1,2) != 2 ||
             upper(2,2) != 1 || upper(2,3) != 4 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 3 0 0 )\n( 0 1 2 0 )\n( 0 0 1 4 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         upper.append( 0UL, 3UL, 5 );
         upper.append( 1UL, 3UL, 6 );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 9UL );
         checkNonZeros( upper, 9UL );
         checkNonZeros( upper, 0UL, 3UL );
         checkNonZeros( upper, 1UL, 3UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 3 || upper(0,3) != 5 ||
             upper(1,1) != 1 || upper(1,2) != 2 || upper(1,3) != 6 ||
             upper(2,2) != 1 || upper(2,3) != 4 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 3 0 5 )\n( 0 1 2 6 )\n( 0 0 1 4 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Appending with row finalization
      {
         // Initialization check
         UT upper( 4UL, 8UL );
         upper.reserve( 0UL, 2UL );
         upper.reserve( 1UL, 3UL );
         upper.reserve( 2UL, 2UL );

         // Appending one non-zero element
         upper.append( 0UL, 1UL, 2 );
         upper.finalize( 0UL );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 2 ||
             upper(1,1) != 1 ||
             upper(2,2) != 1 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 2 0 0 )\n( 0 1 0 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         upper.append( 1UL, 2UL, 3 );
         upper.append( 1UL, 3UL, 4 );
         upper.finalize( 1UL );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 7UL );
         checkNonZeros( upper, 7UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 3UL );
         checkNonZeros( upper, 2UL, 1UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 2 ||
             upper(1,1) != 1 || upper(1,2) != 3 || upper(1,3) != 4 ||
             upper(2,2) != 1 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 2 0 0 )\n( 0 1 3 4 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         // Appending two more non-zero elements
         upper.append( 2UL, 3UL, 5 );
         upper.finalize( 2UL );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 8UL );
         checkNonZeros( upper, 8UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 3UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,1) != 2 ||
             upper(1,1) != 1 || upper(1,2) != 3 || upper(1,3) != 4 ||
             upper(2,2) != 1 || upper(2,3) != 5 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Append operation failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 2 0 0 )\n( 0 1 3 4 )\n( 0 0 1 5 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::append()";

      // Initialization check
      OUT upper( 4UL, 5UL );
      upper.reserve( 2UL, 2UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 4UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      // Trying to append an element
      try {
         upper.append( 3UL, 2UL, 2 );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Appending a lower element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c erase() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c erase() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testErase()
{
   //=====================================================================================
   // Row-major index-based erase function
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::erase( size_t, size_t )";

      // Initialization check
      UT upper( 4UL, 9UL );
      upper(0,2) = 2;
      upper(0,3) = 3;
      upper(1,2) = 4;
      upper(1,3) = 5;
      upper(2,3) = 6;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 3UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,2) != 4 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 4 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the element at (1,2)
      upper.erase( 1UL, 2UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 8UL );
      checkNonZeros( upper, 8UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the element at (0,3)
      upper.erase( 0UL, 3UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 ||
          upper(1,1) != 1 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase a zero element
      upper.erase( 0UL, 1UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 ||
          upper(1,1) != 1 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase a diagonal element
      try {
         upper.erase( 3UL, 3UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a diagonal element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major iterator-based erase function
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::erase( size_t, Iterator )";

      typedef UT::Iterator  Iterator;

      // Initialization check
      UT upper( 4UL, 9UL );
      upper(0,2) = 2;
      upper(0,3) = 3;
      upper(1,2) = 4;
      upper(1,3) = 5;
      upper(2,3) = 6;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 3UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,2) != 4 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 4 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the element at (1,2)
      {
         Iterator pos = upper.erase( 1UL, upper.find( 1UL, 2UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 8UL );
         checkNonZeros( upper, 8UL );
         checkNonZeros( upper, 0UL, 3UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 3 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 5 || pos->index() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 5\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the element at (0,3)
      {
         Iterator pos = upper.erase( 0UL, upper.find( 0UL, 3UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 7UL );
         checkNonZeros( upper, 7UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos != upper.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase a zero element
      {
         Iterator pos = upper.erase( 0UL, upper.find( 0UL, 1UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 7UL );
         checkNonZeros( upper, 7UL );
         checkNonZeros( upper, 0UL, 2UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos != upper.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase a diagonal element
      try {
         upper.erase( 3UL, upper.find( 3UL, 3UL ) );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a diagonal element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major iterator-range-based erase function
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::erase( size_t, Iterator, Iterator )";

      typedef UT::Iterator  Iterator;

      // Initialization check
      UT upper( 4UL, 9UL );
      upper(0,2) = 2;
      upper(0,3) = 3;
      upper(1,2) = 4;
      upper(1,3) = 5;
      upper(2,3) = 6;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 3UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,2) != 4 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 4 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the elements from (1,2) to (1,3)
      {
         Iterator pos = upper.erase( 1UL, upper.find( 1UL, 2UL ), upper.find( 1UL, 3UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 8UL );
         checkNonZeros( upper, 8UL );
         checkNonZeros( upper, 0UL, 3UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a single-element range failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 3 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 5 || pos->index() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 5\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the elements from (0,2) to the row end
      {
         Iterator pos = upper.erase( 0UL, upper.find( 0UL, 2UL ), upper.end( 0UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a multi-element range failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos != upper.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an empty range
      {
         Iterator pos = upper.erase( 3UL, upper.find( 3UL, 3UL ), upper.find( 3UL, 3UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 6UL );
         checkNonZeros( upper, 6UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 2UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing an empty range failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 1 || pos->index() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 1\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase a range including a diagonal element
      try {
         upper.erase( 2UL, upper.begin( 2UL ), upper.end( 2UL ) );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a range including a diagonal element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 0 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major index-based erase function
   //=====================================================================================

   {
      test_ = "Column-major UpperMatrix::erase( size_t, size_t )";

      // Initialization check
      OUT upper( 4UL, 9UL );
      upper(0,2) = 2;
      upper(0,3) = 3;
      upper(1,2) = 4;
      upper(1,3) = 5;
      upper(2,3) = 6;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 4UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,2) != 4 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 4 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the element at (1,2)
      upper.erase( 1UL, 2UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 8UL );
      checkNonZeros( upper, 8UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 4UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the element at (0,3)
      upper.erase( 0UL, 3UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 ||
          upper(1,1) != 1 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a non-zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase a zero element
      upper.erase( 0UL, 1UL );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 ||
          upper(1,1) != 1 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a zero element failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Trying to erase a diagonal element
      try {
         upper.erase( 0UL, 0UL );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a diagonal element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major iterator-based erase function
   //=====================================================================================

   {
      test_ = "Column-major UpperMatrix::erase( size_t, Iterator )";

      typedef OUT::Iterator  Iterator;

      // Initialization check
      OUT upper( 4UL, 9UL );
      upper(0,2) = 2;
      upper(0,3) = 3;
      upper(1,2) = 4;
      upper(1,3) = 5;
      upper(2,3) = 6;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 4UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,2) != 4 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 4 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the element at (1,2)
      {
         Iterator pos = upper.erase( 2UL, upper.find( 1UL, 2UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 8UL );
         checkNonZeros( upper, 8UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 4UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 3 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 1 || pos->index() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 1\n"
                << "   Expected index: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the element at (0,3)
      {
         Iterator pos = upper.erase( 3UL, upper.find( 0UL, 3UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 7UL );
         checkNonZeros( upper, 7UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 3UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a non-zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 5 || pos->index() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 5\n"
                << "   Expected index: 1\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase a zero element
      {
         Iterator pos = upper.erase( 1UL, upper.find( 0UL, 1UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 7UL );
         checkNonZeros( upper, 7UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 3UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a zero element failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos != upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Expected result: the end() iterator\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase a diagonal element
      try {
         upper.erase( 0UL, upper.find( 0UL, 0UL ) );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a diagonal element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major iterator-range-based erase function
   //=====================================================================================

   {
      test_ = "Column-major UpperMatrix::erase( size_t, Iterator, Iterator )";

      typedef OUT::Iterator  Iterator;

      // Initialization check
      OUT upper( 4UL, 9UL );
      upper(0,2) = 2;
      upper(0,3) = 3;
      upper(1,2) = 4;
      upper(1,3) = 5;
      upper(2,3) = 6;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 9UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 4UL );

      if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
          upper(1,1) != 1 || upper(1,2) != 4 || upper(1,3) != 5 ||
          upper(2,2) != 1 || upper(2,3) != 6 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Initialization failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 3 )\n( 0 1 4 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Erasing the elements from (1,2) to (2,2)
      {
         Iterator pos = upper.erase( 2UL, upper.find( 1UL, 2UL ), upper.find( 2UL, 2UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 8UL );
         checkNonZeros( upper, 8UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 4UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 || upper(0,3) != 3 ||
             upper(1,1) != 1 || upper(1,3) != 5 ||
             upper(2,2) != 1 || upper(2,3) != 6 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a single-element range failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 3 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 1 || pos->index() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 1\n"
                << "   Expected index: 2\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Erasing the elements from the beginning of column 3 to (3,3)
      {
         Iterator pos = upper.erase( 3UL, upper.begin( 3UL ), upper.find( 3UL, 3UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 ||
             upper(1,1) != 1 ||
             upper(2,2) != 1 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing a multi-element range failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 1 || pos->index() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 1\n"
                << "   Expected index: 3\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase an empty range
      {
         Iterator pos = upper.erase( 0UL, upper.begin( 0UL ), upper.find( 0UL, 0UL ) );

         checkRows    ( upper, 4UL );
         checkColumns ( upper, 4UL );
         checkCapacity( upper, 5UL );
         checkNonZeros( upper, 5UL );
         checkNonZeros( upper, 0UL, 1UL );
         checkNonZeros( upper, 1UL, 1UL );
         checkNonZeros( upper, 2UL, 2UL );
         checkNonZeros( upper, 3UL, 1UL );

         if( upper(0,0) != 1 || upper(0,2) != 2 ||
             upper(1,1) != 1 ||
             upper(2,2) != 1 ||
             upper(3,3) != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Erasing an empty range failed\n"
                << " Details:\n"
                << "   Result:\n" << upper << "\n"
                << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
            throw std::runtime_error( oss.str() );
         }

         if( pos->value() != 1 || pos->index() != 0 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid iterator returned\n"
                << " Details:\n"
                << "   Value: " << pos->value() << "\n"
                << "   Index: " << pos->index() << "\n"
                << "   Expected value: 1\n"
                << "   Expected index: 0\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Trying to erase a diagonal element
      try {
         upper.erase( 1UL, upper.begin( 1UL ), upper.end( 1UL ) );

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Erasing a diagonal element succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 2 0 )\n( 0 1 0 5 )\n( 0 0 1 6 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c resize() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c resize() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testResize()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::resize()";

      // Initialization check
      UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Resizing to 2x2
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 2UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 x )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 4x4 and preserving the elements
      upper(0,1) = 2;
      upper.resize( 4UL, true );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,1) != 1 ||
          upper(2,2) != 1 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 0 )\n( 0 1 0 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 2x2
      upper(1,2) = 4;
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 4UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 2UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 0x0
      upper.resize( 0UL );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::resize()";

      // Initialization check
      OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Resizing to 2x2
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 2UL );
      checkNonZeros( upper, 2UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );

      if( upper(0,0) != 1 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 4x4 and preserving the elements
      upper(0,1) = 2;
      upper.resize( 4UL, true );

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkCapacity( upper, 5UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,1) != 1 ||
          upper(2,2) != 1 ||
          upper(3,3) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 0 0 )\n( 0 1 0 0 )\n( 0 0 1 0 )\n( 0 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 2x2
      upper(1,2) = 4;
      upper.resize( 2UL );

      checkRows    ( upper, 2UL );
      checkColumns ( upper, 2UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );

      if( upper(0,0) != 1 || upper(0,1) != 2 ||
          upper(1,0) != 0 || upper(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Resizing the matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      // Resizing to 0x0
      upper.resize( 0UL );

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c reserve() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c reserve() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testReserve()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::reserve()";

      // Initialization check
      UT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Increasing the capacity of the matrix
      upper.reserve( 10UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 10UL );
      checkNonZeros( upper,  0UL );

      // Further increasing the capacity of the matrix
      upper.reserve( 20UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 20UL );
      checkNonZeros( upper,  0UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::reserve()";

      // Initialization check
      OUT upper;

      checkRows    ( upper, 0UL );
      checkColumns ( upper, 0UL );
      checkNonZeros( upper, 0UL );

      // Increasing the capacity of the matrix
      upper.reserve( 10UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 10UL );
      checkNonZeros( upper,  0UL );

      // Further increasing the capacity of the matrix
      upper.reserve( 20UL );

      checkRows    ( upper,  0UL );
      checkColumns ( upper,  0UL );
      checkCapacity( upper, 20UL );
      checkNonZeros( upper,  0UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c trim() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c trim() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testTrim()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::trim()";

      // Initialization check
      UT upper( 3UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      // Increasing the row capacity of the matrix
      upper.reserve( 0UL, 10UL );
      upper.reserve( 1UL, 15UL );
      upper.reserve( 2UL, 20UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 10UL );
      checkCapacity( upper,  1UL, 15UL );
      checkCapacity( upper,  2UL, 20UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the matrix
      upper.trim();

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 1UL );
      checkCapacity( upper,  1UL, 1UL );
      checkCapacity( upper,  2UL, 1UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );
   }

   {
      test_ = "Row-major UniUpperMatrix::trim( size_t )";

      // Initialization check
      UT upper( 3UL, 3UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      // Increasing the row capacity of the matrix
      upper.reserve( 0UL, 10UL );
      upper.reserve( 1UL, 15UL );
      upper.reserve( 2UL, 20UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 10UL );
      checkCapacity( upper,  1UL, 15UL );
      checkCapacity( upper,  2UL, 20UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the 0th row
      upper.trim( 0UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL,  1UL );
      checkCapacity( upper,  1UL, 24UL );
      checkCapacity( upper,  2UL, 20UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the 1st row
      upper.trim( 1UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL,  1UL );
      checkCapacity( upper,  1UL,  1UL );
      checkCapacity( upper,  2UL, 43UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the 2nd row
      upper.trim( 2UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 1UL );
      checkCapacity( upper,  1UL, 1UL );
      checkCapacity( upper,  2UL, 1UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::trim()";

      // Initialization check
      OUT upper( 3UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      // Increasing the row capacity of the matrix
      upper.reserve( 0UL, 10UL );
      upper.reserve( 1UL, 15UL );
      upper.reserve( 2UL, 20UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 10UL );
      checkCapacity( upper,  1UL, 15UL );
      checkCapacity( upper,  2UL, 20UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the matrix
      upper.trim();

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 1UL );
      checkCapacity( upper,  1UL, 1UL );
      checkCapacity( upper,  2UL, 1UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );
   }

   {
      test_ = "Column-major UniUpperMatrix::trim( size_t )";

      // Initialization check
      OUT upper( 3UL, 3UL );

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkCapacity( upper, 3UL );
      checkNonZeros( upper, 3UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      // Increasing the column capacity of the matrix
      upper.reserve( 0UL, 10UL );
      upper.reserve( 1UL, 15UL );
      upper.reserve( 2UL, 20UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 10UL );
      checkCapacity( upper,  1UL, 15UL );
      checkCapacity( upper,  2UL, 20UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the 0th column
      upper.trim( 0UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL,  1UL );
      checkCapacity( upper,  1UL, 24UL );
      checkCapacity( upper,  2UL, 20UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the 1st column
      upper.trim( 1UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL,  1UL );
      checkCapacity( upper,  1UL,  1UL );
      checkCapacity( upper,  2UL, 43UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );

      // Trimming the 2nd column
      upper.trim( 2UL );

      checkRows    ( upper,  3UL );
      checkColumns ( upper,  3UL );
      checkCapacity( upper, 45UL );
      checkCapacity( upper,  0UL, 1UL );
      checkCapacity( upper,  1UL, 1UL );
      checkCapacity( upper,  2UL, 1UL );
      checkNonZeros( upper,  3UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 1UL );
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c swap() functionality of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c swap() function of the UniUpperMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testSwap()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix swap";

      UT upper1( 2UL );
      upper1(0,1) = 2;

      UT upper2( 3UL );
      upper2(0,1) = 3;
      upper2(0,2) = 4;
      upper2(1,2) = 5;

      swap( upper1, upper2 );

      checkRows    ( upper1, 3UL );
      checkColumns ( upper1, 3UL );
      checkCapacity( upper1, 6UL );
      checkNonZeros( upper1, 6UL );
      checkNonZeros( upper1, 0UL, 3UL );
      checkNonZeros( upper1, 1UL, 2UL );
      checkNonZeros( upper1, 2UL, 1UL );

      if( upper1(0,0) != 1 || upper1(0,1) != 3 || upper1(0,2) != 4 ||
          upper1(1,0) != 0 || upper1(1,1) != 1 || upper1(1,2) != 5 ||
          upper1(2,0) != 0 || upper1(2,1) != 0 || upper1(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the first matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper1 << "\n"
             << "   Expected result:\n( 1 3 4 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      checkRows    ( upper2, 2UL );
      checkColumns ( upper2, 2UL );
      checkCapacity( upper2, 3UL );
      checkNonZeros( upper2, 3UL );
      checkNonZeros( upper2, 0UL, 2UL );
      checkNonZeros( upper2, 1UL, 1UL );

      if( upper2(0,0) != 1 || upper2(0,1) != 2 || upper2(1,0) != 0 || upper2(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the second matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix swap";

      OUT upper1( 2UL );
      upper1(0,1) = 2;

      OUT upper2( 3UL );
      upper2(0,1) = 3;
      upper2(0,2) = 4;
      upper2(1,2) = 5;

      swap( upper1, upper2 );

      checkRows    ( upper1, 3UL );
      checkColumns ( upper1, 3UL );
      checkCapacity( upper1, 6UL );
      checkNonZeros( upper1, 6UL );
      checkNonZeros( upper1, 0UL, 1UL );
      checkNonZeros( upper1, 1UL, 2UL );
      checkNonZeros( upper1, 2UL, 3UL );

      if( upper1(0,0) != 1 || upper1(0,1) != 3 || upper1(0,2) != 4 ||
          upper1(1,0) != 0 || upper1(1,1) != 1 || upper1(1,2) != 5 ||
          upper1(2,0) != 0 || upper1(2,1) != 0 || upper1(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the first matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper1 << "\n"
             << "   Expected result:\n( 1 3 4 )\n( 0 1 5 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      checkRows    ( upper2, 2UL );
      checkColumns ( upper2, 2UL );
      checkCapacity( upper2, 3UL );
      checkNonZeros( upper2, 3UL );
      checkNonZeros( upper2, 0UL, 1UL );
      checkNonZeros( upper2, 1UL, 2UL );

      if( upper2(0,0) != 1 || upper2(0,1) != 2 || upper2(1,0) != 0 || upper2(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Swapping the second matrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper2 << "\n"
             << "   Expected result:\n( 1 2 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c find() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c find() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testFind()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::find()";

      typedef UT::ConstIterator  ConstIterator;

      // Initialization check
      UT upper( 8UL, 10UL );
      upper(1,2) = 2;
      upper(2,4) = 3;

      checkRows    ( upper,  8UL );
      checkColumns ( upper,  8UL );
      checkCapacity( upper, 10UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 2UL );
      checkNonZeros( upper,  2UL, 2UL );
      checkNonZeros( upper,  3UL, 1UL );
      checkNonZeros( upper,  4UL, 1UL );
      checkNonZeros( upper,  5UL, 1UL );
      checkNonZeros( upper,  6UL, 1UL );
      checkNonZeros( upper,  7UL, 1UL );

      // Searching for the first element
      {
         ConstIterator pos( upper.find( 1UL, 2UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (1,2)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 2 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 2\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for the second element
      {
         ConstIterator pos( upper.find( 2UL, 4UL ) );

         if( pos == upper.end( 2UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (2,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 4 || pos->value() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 4\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 3\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for a diagonal element
      {
         ConstIterator pos( upper.find( 6UL, 6UL ) );

         if( pos == upper.end( 6UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (6,6)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 6 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 6\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for a non-existing non-zero element
      {
         ConstIterator pos( upper.find( 0UL, 4UL ) );

         if( pos != upper.end( 0UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Non-existing element could be found\n"
                << " Details:\n"
                << "   Required index = 4\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 0\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::find()";

      typedef OUT::ConstIterator  ConstIterator;

      // Initialization check
      OUT upper( 8UL, 10UL );
      upper(1,2) = 2;
      upper(2,4) = 3;

      checkRows    ( upper,  8UL );
      checkColumns ( upper,  8UL );
      checkCapacity( upper, 10UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 1UL );
      checkNonZeros( upper,  2UL, 2UL );
      checkNonZeros( upper,  3UL, 1UL );
      checkNonZeros( upper,  4UL, 2UL );
      checkNonZeros( upper,  5UL, 1UL );
      checkNonZeros( upper,  6UL, 1UL );
      checkNonZeros( upper,  7UL, 1UL );

      // Searching for the first element
      {
         ConstIterator pos( upper.find( 1UL, 2UL ) );

         if( pos == upper.end( 2UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (1,2)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for the second element
      {
         ConstIterator pos( upper.find( 2UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (2,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 2 || pos->value() != 3 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 2\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 3\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for a diagonal element
      {
         ConstIterator pos( upper.find( 6UL, 6UL ) );

         if( pos == upper.end( 6UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Element could not be found\n"
                << " Details:\n"
                << "   Required position = (6,6)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 6 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 6\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Searching for a non-existing non-zero element
      {
         ConstIterator pos( upper.find( 0UL, 4UL ) );

         if( pos != upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Non-existing element could be found\n"
                << " Details:\n"
                << "   Required index = 0\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 0\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c lowerBound() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c lowerBound() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testLowerBound()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::lowerBound()";

      typedef UT::ConstIterator  ConstIterator;

      // Initialization check
      UT upper( 6UL, 7UL );
      upper(1,3) = 2;

      checkRows    ( upper, 6UL );
      checkColumns ( upper, 6UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );
      checkNonZeros( upper, 4UL, 1UL );
      checkNonZeros( upper, 5UL, 1UL );

      // Determining the lower bound for position (1,0)
      {
         ConstIterator pos( upper.lowerBound( 1UL, 0UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,0)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (1,1)
      {
         ConstIterator pos( upper.lowerBound( 1UL, 1UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,1)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (1,2)
      {
         ConstIterator pos( upper.lowerBound( 1UL, 2UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,2)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 3 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 3\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (1,3)
      {
         ConstIterator pos( upper.lowerBound( 1UL, 3UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,3)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 3 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 3\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (1,4)
      {
         ConstIterator pos( upper.lowerBound( 1UL, 4UL ) );

         if( pos != upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::lowerBound()";

      typedef OUT::ConstIterator  ConstIterator;

      // Initialization check
      OUT upper( 6UL, 7UL );
      upper(2,4) = 2;

      checkRows    ( upper, 6UL );
      checkColumns ( upper, 6UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );
      checkNonZeros( upper, 4UL, 2UL );
      checkNonZeros( upper, 5UL, 1UL );

      // Determining the lower bound for position (1,4)
      {
         ConstIterator pos( upper.lowerBound( 1UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 2 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 2\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (2,4)
      {
         ConstIterator pos( upper.lowerBound( 2UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (2,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 2 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 2\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (3,4)
      {
         ConstIterator pos( upper.lowerBound( 3UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (3,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 4 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 4\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (4,4)
      {
         ConstIterator pos( upper.lowerBound( 4UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (4,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 4 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 4\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the lower bound for position (5,4)
      {
         ConstIterator pos( upper.lowerBound( 5UL, 4UL ) );

         if( pos != upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Lower bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (5,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c upperBound() member function of the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c upperBound() member function of the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testUpperBound()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major UniUpperMatrix::upperBound()";

      typedef UT::ConstIterator  ConstIterator;

      // Initialization check
      UT upper( 6UL, 7UL );
      upper(1,3) = 2;

      checkRows    ( upper, 6UL );
      checkColumns ( upper, 6UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );
      checkNonZeros( upper, 4UL, 1UL );
      checkNonZeros( upper, 5UL, 1UL );

      // Determining the upper bound for position (1,0)
      {
         ConstIterator pos( upper.upperBound( 1UL, 0UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,0)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 1 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 1\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (1,1)
      {
         ConstIterator pos( upper.upperBound( 1UL, 1UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,1)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 3 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 3\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (1,2)
      {
         ConstIterator pos( upper.upperBound( 1UL, 2UL ) );

         if( pos == upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,2)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 3 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 3\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (1,3)
      {
         ConstIterator pos( upper.upperBound( 1UL, 3UL ) );

         if( pos != upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,3)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (1,4)
      {
         ConstIterator pos( upper.upperBound( 1UL, 4UL ) );

         if( pos != upper.end( 1UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major UniUpperMatrix::upperBound()";

      typedef OUT::ConstIterator  ConstIterator;

      // Initialization check
      OUT upper( 6UL, 7UL );
      upper(2,4) = 2;

      checkRows    ( upper, 6UL );
      checkColumns ( upper, 6UL );
      checkCapacity( upper, 7UL );
      checkNonZeros( upper, 7UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );
      checkNonZeros( upper, 3UL, 1UL );
      checkNonZeros( upper, 4UL, 2UL );
      checkNonZeros( upper, 5UL, 1UL );

      // Determining the upper bound for position (1,4)
      {
         ConstIterator pos( upper.upperBound( 1UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (1,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 2 || pos->value() != 2 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 2\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 2\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (2,4)
      {
         ConstIterator pos( upper.upperBound( 2UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (2,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 4 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 4\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (3,4)
      {
         ConstIterator pos( upper.upperBound( 3UL, 4UL ) );

         if( pos == upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (3,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
         else if( pos->index() != 4 || pos->value() != 1 ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Wrong element found\n"
                << " Details:\n"
                << "   Required index = 4\n"
                << "   Found index    = " << pos->index() << "\n"
                << "   Expected value = 1\n"
                << "   Value at index = " << pos->value() << "\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (4,4)
      {
         ConstIterator pos( upper.upperBound( 4UL, 4UL ) );

         if( pos != upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (4,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // Determining the upper bound for position (5,4)
      {
         ConstIterator pos( upper.upperBound( 5UL, 4UL ) );

         if( pos != upper.end( 4UL ) ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Upper bound could not be determined\n"
                << " Details:\n"
                << "   Required position = (5,4)\n"
                << "   Current matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c isDefault() function with the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c isDefault() function with the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testIsDefault()
{
   //=====================================================================================
   // Row-major matrix tests
   //=====================================================================================

   {
      test_ = "Row-major isDefault() function";

      // isDefault with 0x0 matrix
      {
         UT upper;

         if( isDefault( upper ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with default matrix
      {
         UT upper( 3UL );

         if( isDefault( upper(0,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default matrix
      {
         UT upper( 3UL );
         upper(0,1) = 1;

         if( isDefault( upper(0,1) ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }


   //=====================================================================================
   // Column-major matrix tests
   //=====================================================================================

   {
      test_ = "Column-major isDefault() function";

      // isDefault with 0x0 matrix
      {
         OUT upper;

         if( isDefault( upper ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with default matrix
      {
         OUT upper( 3UL );

         if( isDefault( upper(0,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }

      // isDefault with non-default matrix
      {
         OUT upper( 3UL );
         upper(0,1) = 1;

         if( isDefault( upper(0,1) ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(0,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper(1,1) ) != true ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix element:\n" << upper(1,1) << "\n";
            throw std::runtime_error( oss.str() );
         }

         if( isDefault( upper ) != false ) {
            std::ostringstream oss;
            oss << " Test: " << test_ << "\n"
                << " Error: Invalid isDefault evaluation\n"
                << " Details:\n"
                << "   Matrix:\n" << upper << "\n";
            throw std::runtime_error( oss.str() );
         }
      }
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c submatrix() function with the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c submatrix() function with the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testSubmatrix()
{
   //=====================================================================================
   // Row-major general tests
   //=====================================================================================

   {
      test_ = "Row-major submatrix() function";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      if( sm(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << sm(1,1) << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      SMT::Iterator it = sm.begin(0UL);

      if( it == sm.end(0UL) || it->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << it->value() << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      sm(0,1) = -5;

      if( sm(0,0) != 1 || sm(0,1) != -5 ||
          sm(1,0) != 0 || sm(1,1) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 -5 )\n( 0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( sm );

      if( sm(0,0) != 1 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense matrix assignment
   //=====================================================================================

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 4UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 0 );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 4UL );
      checkNonZeros( upper,  1UL, 3UL );
      checkNonZeros( upper,  2UL, 2UL );
      checkNonZeros( upper,  3UL, 1UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (row-major dense matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 4UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 0 );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 4UL );
      checkNonZeros( upper,  1UL, 3UL );
      checkNonZeros( upper,  2UL, 2UL );
      checkNonZeros( upper,  3UL, 1UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (column-major dense matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse matrix assignment
   //=====================================================================================

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 6UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;
      mat.insert( 3UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 4UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 6UL );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 4UL );
      checkNonZeros( upper,  1UL, 3UL );
      checkNonZeros( upper,  2UL, 2UL );
      checkNonZeros( upper,  3UL, 1UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (row-major sparse matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 6UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;
      mat.insert( 3UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 4UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );
      checkNonZeros( upper, 3UL, 1UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 6UL );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 4UL );
      checkNonZeros( upper,  1UL, 3UL );
      checkNonZeros( upper,  2UL, 2UL );
      checkNonZeros( upper,  3UL, 1UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Row-major submatrix() function (column-major sparse matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<UT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      UT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major general tests
   //=====================================================================================

   {
      test_ = "Column-major submatrix() function";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      if( sm(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << sm(1,1) << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      SMT::Iterator it = sm.begin(0UL);

      if( it == sm.end(0UL) || it->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << it->value() << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      sm(0,1) = -5;

      if( sm(0,0) != 1 || sm(0,1) != -5 ||
          sm(1,0) != 0 || sm(1,1) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 -5 )\n( 0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( sm );

      if( sm(0,0) != 1 || sm(0,1) != 0 ||
          sm(1,0) != 0 || sm(1,1) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 1 0 )\n( 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Submatrix reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense matrix assignment
   //=====================================================================================

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 0 );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 2UL );
      checkNonZeros( upper,  2UL, 3UL );
      checkNonZeros( upper,  3UL, 4UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (row-major dense matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::rowMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 0 );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 0 );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 2UL );
      checkNonZeros( upper,  2UL, 3UL );
      checkNonZeros( upper,  3UL, 4UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) =  0;
      mat(1,1) =  0;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (column-major dense matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::DynamicMatrix<int,blaze::columnMajor> mat( 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse matrix assignment
   //=====================================================================================

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 4UL, 2UL, 6UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;
      mat.insert( 3UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 4UL, 6UL );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 2UL );
      checkNonZeros( upper,  2UL, 3UL );
      checkNonZeros( upper,  3UL, 4UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (row-major sparse matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::rowMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 12 15 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 17  0 )
   // ( 0  0  1  1 )      ( 0  0  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 1)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 4UL, 2UL, 6UL );
      mat(0,0) = 12;
      mat(0,1) = 15;
      mat(1,0) =  1;
      mat(1,1) = 17;
      mat(2,1) =  1;
      mat.insert( 3UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 0UL, 1UL, 4UL, 2UL );
      sm = mat;

      checkRows    ( upper, 4UL );
      checkColumns ( upper, 4UL );
      checkNonZeros( upper, 9UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );
      checkNonZeros( upper, 3UL, 3UL );

      if( sm(0,0) != 12 || sm(0,1) != 15 ||
          sm(1,0) !=  1 || sm(1,1) != 17 ||
          sm(2,0) !=  0 || sm(2,1) !=  1 ||
          sm(3,0) !=  0 || sm(3,1) !=  0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 12 15 )\n(  1 17 )\n(  0  1 )\n(  0  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 12 || upper(0,2) != 15 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 17 || upper(1,3) !=  0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) !=  1 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 12 15 -2 )\n"
                                     "( 0  1 17  0 )\n"
                                     "( 0  0  1  1 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 14 10 )
   // ( 0  0  1  1 )      ( 0  0  1 16 )
   // ( 0  0  0  1 )      ( 0  0  0  1 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 2)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 4UL, 6UL );
      mat(0,1) =  1;
      mat(0,2) = 14;
      mat(0,3) = 10;
      mat(1,2) =  1;
      mat(1,3) = 16;
      mat.insert( 1UL, 0UL, 0 );

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 0UL, 2UL, 4UL );
      sm = mat;

      checkRows    ( upper,  4UL );
      checkColumns ( upper,  4UL );
      checkNonZeros( upper, 10UL );
      checkNonZeros( upper,  0UL, 1UL );
      checkNonZeros( upper,  1UL, 2UL );
      checkNonZeros( upper,  2UL, 3UL );
      checkNonZeros( upper,  3UL, 4UL );

      if( sm(0,0) != 0 || sm(0,1) != 1 || sm(0,2) != 14 || sm(0,3) != 10 ||
          sm(1,0) != 0 || sm(1,1) != 0 || sm(1,2) !=  1 || sm(1,3) != 16 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << sm << "\n"
             << "   Expected result:\n( 0  1 14 10 )\n( 0  0  1 16 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 || upper(0,3) != -2 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 14 || upper(1,3) != 10 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 || upper(2,3) != 16 ||
          upper(3,0) != 0 || upper(3,1) !=  0 || upper(3,2) !=  0 || upper(3,3) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment to submatrix failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 -2 )\n"
                                     "( 0  1 14 10 )\n"
                                     "( 0  0  1 16 )\n"
                                     "( 0  0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0  0  0  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 3)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 2UL );
      mat(0,0) =  1;
      mat(0,1) = 12;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 -2 )      ( 1 -4  7 -2 )
   // ( 0  1  0  0 )  =>  ( 0  1 12  0 )
   // ( 0  0  1  1 )      ( 0 13  1  1 )
   // ( 0  0  0  1 )      ( 0  0  0  5 )
   {
      test_ = "Column-major submatrix() function (column-major sparse matrix assignment test 4)";

      typedef blaze::SparseSubmatrix<OUT>  SMT;

      blaze::CompressedMatrix<int,blaze::columnMajor> mat( 2UL, 2UL, 4UL );
      mat(0,0) =  1;
      mat(0,1) = 12;
      mat(1,0) = 13;
      mat(1,1) =  1;

      OUT upper( 4UL );
      upper(0,1) = -4;
      upper(0,2) =  7;
      upper(0,3) = -2;
      upper(2,3) =  1;

      SMT sm = submatrix( upper, 1UL, 1UL, 2UL, 2UL );

      try {
         sm = mat;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid matrix succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c row() function with the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c row() function with the UniUpperMatrix specialization.
// In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testRow()
{
   //=====================================================================================
   // Row-major general tests
   //=====================================================================================

   {
      test_ = "Row-major row() function";

      typedef blaze::SparseRow<UT>  RT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      if( row1[1] != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      RT::Iterator it = row1.begin();

      if( it == row1.end() || it->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << it->value() << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      row1[2] = -5;

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 -5  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( row1 );

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major row() function (dense vector assignment test 1)";

      typedef blaze::SparseRow<UT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[1] =  1;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  1 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -2 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  0 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major row() function (dense vector assignment test 2)";

      typedef blaze::SparseRow<UT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 9  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major row() function (dense vector assignment test 3)";

      typedef blaze::SparseRow<UT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL );
      vec[0] =  9;
      vec[0] =  1;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major row() function (sparse vector assignment test 1)";

      typedef blaze::SparseRow<UT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 3UL );
      vec[1] =  1;
      vec[2] = -2;
      vec.insert( 0UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  1 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -2 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  0 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major row() function (sparse vector assignment test 2)";

      typedef blaze::SparseRow<UT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 1UL );
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 9  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major row() function (sparse vector assignment test 3)";

      typedef blaze::SparseRow<UT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 3UL );
      vec[0] =  9;
      vec[0] =  1;
      vec[2] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major general tests
   //=====================================================================================

   {
      test_ = "Column-major row() function";

      typedef blaze::SparseRow<OUT>  RT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      if( row1[1] != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << row1[1] << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      RT::Iterator it = row1.begin();

      if( it == row1.end() || it->value() != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << it->value() << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      row1[2] = -5;

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != -5 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  1 -5 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -5 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -5 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( row1 );

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major row() function (dense vector assignment test 1)";

      typedef blaze::SparseRow<OUT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[1] =  1;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  1 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -2 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  0 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major row() function (dense vector assignment test 2)";

      typedef blaze::SparseRow<OUT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL, 0 );
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 9  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major row() function (dense vector assignment test 3)";

      typedef blaze::SparseRow<OUT>  RT;

      blaze::DynamicVector<int,blaze::rowVector> vec( 3UL );
      vec[0] =  9;
      vec[0] =  1;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major row() function (sparse vector assignment test 1)";

      typedef blaze::SparseRow<OUT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 3UL );
      vec[1] =  1;
      vec[2] = -2;
      vec.insert( 0UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );
      row1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 6UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 3UL );

      if( row1[0] != 0 || row1[1] != 1 || row1[2] != -2 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << row1 << "\n"
             << "   Expected result:\n( 0  1 -2 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -4 || upper(0,2) !=  7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != -2 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) !=  1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Row reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -4  7 )\n( 0  1 -2 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 0  0 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major row() function (sparse vector assignment test 2)";

      typedef blaze::SparseRow<OUT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 1UL );
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -4  7 )
   // ( 0  1  0 )  =>  ( 9  1 -2 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major row() function (sparse vector assignment test 3)";

      typedef blaze::SparseRow<OUT>  RT;

      blaze::CompressedVector<int,blaze::rowVector> vec( 3UL, 3UL );
      vec[0] =  9;
      vec[0] =  1;
      vec[2] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      RT row1 = row( upper, 1UL );

      try {
         row1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Test of the \c column() function with the UniUpperMatrix specialization.
//
// \return void
// \exception std::runtime_error Error detected.
//
// This function performs a test of the \c column() function with the UniUpperMatrix
// specialization. In case an error is detected, a \a std::runtime_error exception is thrown.
*/
void SparseTest::testColumn()
{
   //=====================================================================================
   // Row-major general tests
   //=====================================================================================

   {
      test_ = "Row-major column() function";

      typedef blaze::SparseColumn<UT>  CT;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      if( col1[1] != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      CT::Iterator it = col1.begin();

      if( it == col1.end() || it->value() != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << it->value() << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      col1[0] = -5;

      if( col1[0] != -5 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -5  1  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -5 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -5  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( col1 );

      if( col1[0] != 0 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 0 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 7 )\n( 0 1 0 )\n( 0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Row-major dense vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major column() function (dense vector assignment test 1)";

      typedef blaze::SparseColumn<UT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;
      vec[1] =  1;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( col1[0] != -2 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  0  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major column() function (dense vector assignment test 2)";

      typedef blaze::SparseColumn<UT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  9  1 )
   {
      test_ = "Row-major column() function (dense vector assignment test 3)";

      typedef blaze::SparseColumn<UT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL );
      vec[0] = -2;
      vec[1] =  1;
      vec[2] =  9;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Row-major sparse vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major column() function (sparse vector assignment test 1)";

      typedef blaze::SparseColumn<UT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 3UL );
      vec[0] = -2;
      vec[1] =  1;
      vec.insert( 2UL, 0 );

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 3UL );
      checkNonZeros( upper, 1UL, 1UL );
      checkNonZeros( upper, 2UL, 1UL );

      if( col1[0] != -2 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  0  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Row-major column() function (sparse vector assignment test 2)";

      typedef blaze::SparseColumn<UT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 1UL );
      vec[0] = -2;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  9  1 )
   {
      test_ = "Row-major column() function (sparse vector assignment test 3)";

      typedef blaze::SparseColumn<UT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 3UL );
      vec[0] = -2;
      vec[1] =  1;
      vec[2] =  9;

      UT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major general tests
   //=====================================================================================

   {
      test_ = "Column-major column() function";

      typedef blaze::SparseColumn<OUT>  CT;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      if( col1[1] != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Function call operator access failed\n"
             << " Details:\n"
             << "   Result: " << col1[1] << "\n"
             << "   Expected result: 1\n";
         throw std::runtime_error( oss.str() );
      }

      CT::Iterator it = col1.begin();

      if( it == col1.end() || it->value() != -4 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Iterator access failed\n"
             << " Details:\n"
             << "   Result: " << it->value() << "\n"
             << "   Expected result: -4\n";
         throw std::runtime_error( oss.str() );
      }

      col1[0] = -5;

      if( col1[0] != -5 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -5  1  0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -5 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column access failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1  -5  7 )\n( 0  1  0 )\n( 0  0  3 )\n";
         throw std::runtime_error( oss.str() );
      }

      reset( col1 );

      if( col1[0] != 0 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( 0 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != 0 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) != 1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) != 0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 0 7 )\n( 0 1 0 )\n(  0 0 1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }


   //=====================================================================================
   // Column-major dense vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major column() function (dense vector assignment test 1)";

      typedef blaze::SparseColumn<OUT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;
      vec[1] =  1;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( col1[0] != -2 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  0  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major column() function (dense vector assignment test 2)";

      typedef blaze::SparseColumn<OUT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL, 0 );
      vec[0] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  9  1 )
   {
      test_ = "Column-major column() function (dense vector assignment test 3)";

      typedef blaze::SparseColumn<OUT>  CT;

      blaze::DynamicVector<int,blaze::columnVector> vec( 3UL );
      vec[0] = -2;
      vec[1] =  1;
      vec[2] =  9;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }


   //=====================================================================================
   // Column-major sparse vector assignment
   //=====================================================================================

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major column() function (sparse vector assignment test 1)";

      typedef blaze::SparseColumn<OUT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 3UL );
      vec[0] = -2;
      vec[1] =  1;
      vec.insert( 2UL, 0 );

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );
      col1 = vec;

      checkRows    ( upper, 3UL );
      checkColumns ( upper, 3UL );
      checkNonZeros( upper, 5UL );
      checkNonZeros( upper, 0UL, 1UL );
      checkNonZeros( upper, 1UL, 2UL );
      checkNonZeros( upper, 2UL, 2UL );

      if( col1[0] != -2 || col1[1] != 1 || col1[2] != 0 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << col1 << "\n"
             << "   Expected result:\n( -2 1 0 )\n";
         throw std::runtime_error( oss.str() );
      }

      if( upper(0,0) != 1 || upper(0,1) != -2 || upper(0,2) != 7 ||
          upper(1,0) != 0 || upper(1,1) !=  1 || upper(1,2) != 0 ||
          upper(2,0) != 0 || upper(2,1) !=  0 || upper(2,2) != 1 ) {
         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Column reset failed\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n"
             << "   Expected result:\n( 1 -2  7 )\n( 0  1  0 )\n( 0  0  1 )\n";
         throw std::runtime_error( oss.str() );
      }
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  0  0 )
   // ( 0  0  1 )      ( 0  0  1 )
   {
      test_ = "Column-major column() function (sparse vector assignment test 2)";

      typedef blaze::SparseColumn<OUT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 1UL );
      vec[0] = -2;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }

   // ( 1 -4  7 )      ( 1 -2  7 )
   // ( 0  1  0 )  =>  ( 0  1  0 )
   // ( 0  0  1 )      ( 0  9  1 )
   {
      test_ = "Column-major column() function (sparse vector assignment test 3)";

      typedef blaze::SparseColumn<OUT>  CT;

      blaze::CompressedVector<int,blaze::columnVector> vec( 3UL, 3UL );
      vec[0] = -2;
      vec[1] =  1;
      vec[2] =  9;

      OUT upper( 3UL );
      upper(0,1) = -4;
      upper(0,2) =  7;

      CT col1 = column( upper, 1UL );

      try {
         col1 = vec;

         std::ostringstream oss;
         oss << " Test: " << test_ << "\n"
             << " Error: Assignment of invalid vector succeeded\n"
             << " Details:\n"
             << "   Result:\n" << upper << "\n";
         throw std::runtime_error( oss.str() );
      }
      catch( std::invalid_argument& ) {}
   }
}
//*************************************************************************************************

} // namespace uniuppermatrix

} // namespace mathtest

} // namespace blazetest




//=================================================================================================
//
//  MAIN FUNCTION
//
//=================================================================================================

//*************************************************************************************************
int main()
{
   std::cout << "   Running UniUpperMatrix sparse test..." << std::endl;

   try
   {
      RUN_UNIUPPERMATRIX_SPARSE_TEST;
   }
   catch( std::exception& ex ) {
      std::cerr << "\n\n ERROR DETECTED during UniUpperMatrix sparse test:\n"
                << ex.what() << "\n";
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
//*************************************************************************************************
