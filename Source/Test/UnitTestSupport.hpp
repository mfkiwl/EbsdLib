/* ============================================================================
 * Copyright (c) 2009-2016 BlueQuartz Software, LLC
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
 * contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The code contained herein was partially funded by the following contracts:
 *    United States Air Force Prime Contract FA8650-07-D-5800
 *    United States Air Force Prime Contract FA8650-10-D-5210
 *    United States Prime Contract Navy N00173-07-C-2068
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#pragma once

//-- C Includes
#include <assert.h>

//-- C++ Includes
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>

#define NUM_COLS 120

#include <sstream>
#include <string>

#define EBSD_GET_NAME_OF_CLASS_DECL(CLASS)                                                                                                                                                             \
  std::string getNameOfClass()                                                                                                                                                                         \
  {                                                                                                                                                                                                    \
    return {#CLASS};                                                                                                                                                                                   \
  }

namespace Ebsd
{
namespace unittest
{
static std::string CurrentMethod("");
static int numTestsPass = 0;
static int numTestFailed = 0;
static int numTests = 0;

static char TestMessage[NUM_COLS + 1];
static const char Passed[6] = {'P', 'A', 'S', 'S', 'E', 'D'};
static const char Failed[6] = {'F', 'A', 'I', 'L', 'E', 'D'};
static int SizeOfPassed = 6;
static int SizeOfFailed = 6;
} // namespace unittest
} // namespace Ebsd

#if 0
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
std::stringstream& operator<<(std::stringstream& out, const DataArrayPath& v)
{
  out << v.getDataContainerName() << "|" << v.getAttributeMatrixName() << "|" << v.getDataArrayName();
  return out;
}
#endif

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
class TestException : public std::exception
{
public:
  /**
   * @brief
   * @param what
   * @param file
   * @param lineNumber
   */
  TestException(const std::string& what, const std::string& filename, int lineNumber)
  : m_Message(what)
  , m_FileName(filename)
  , m_LineNumber(lineNumber)
  {
    updateWhat();
  }

  /**
   * @brief Copy Constructor
   */
  TestException(const TestException& te)
  {
    m_Message = (&te)->getMessage();
    m_FileName = te.getFileName();
    m_LineNumber = te.getLineNumber();
    updateWhat();
  }

  virtual ~TestException() throw()
  {
  }

  /**
   * @brief Over ride from base class
   */
  virtual const char* what() const throw()
  {
    return m_What;
  }

  void setMessage(const std::string& m)
  {
    m_Message = m;
    updateWhat();
  }
  std::string getMessage()
  {
    return m_Message;
  }
  std::string getMessage() const
  {
    return m_Message;
  }

  void setFileName(const std::string& fn)
  {
    m_FileName = fn;
    updateWhat();
  }
  std::string getFileName()
  {
    return m_FileName;
  }
  std::string getFileName() const
  {
    return m_FileName;
  }

  void setLineNumber(int ln)
  {
    m_LineNumber = ln;
    updateWhat();
  }
  int getLineNumber()
  {
    return m_LineNumber;
  }
  int getLineNumber() const
  {
    return m_LineNumber;
  }

protected:
  TestException()
  {
    updateWhat();
  }

  void updateWhat()
  {
    std::stringstream ss;
    ss << "    Reason: " << m_Message << std::endl;
    ss << "    File:   " << m_FileName << std::endl;
    ss << "    Line:   " << m_LineNumber;

    ::memset(m_What, 0, 2048);
    ::memcpy(m_What, ss.str().c_str(), ss.str().size());
    m_What[2047] = 0; // Make sure we nullptr terminate no matter what.
  }

private:
  std::string m_Message;
  std::string m_FileName;
  int m_LineNumber;

  char m_What[2048];
  void operator=(const TestException&); // Move assignment Not Implemented
};

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TestPassed(const std::string& test)
{
  ::memset(Ebsd::unittest::TestMessage, ' ', NUM_COLS); // Splat Spaces across the entire message
  Ebsd::unittest::TestMessage[NUM_COLS] = 0;            // Make sure it is null terminated

  std::string::size_type size = NUM_COLS - Ebsd::unittest::SizeOfPassed;
  ::strncpy(&(Ebsd::unittest::TestMessage[size]), Ebsd::unittest::Passed, Ebsd::unittest::SizeOfPassed);
  if(test.length() < size)
  {
    ::strncpy(Ebsd::unittest::TestMessage, test.c_str(), test.length());
  }
  else
  {
    ::strncpy(Ebsd::unittest::TestMessage, test.substr(0, size).c_str(), size);
  }
  Ebsd::unittest::TestMessage[NUM_COLS] = 0; // Make sure it is null terminated
  std::cout << Ebsd::unittest::TestMessage << std::endl;
  Ebsd::unittest::numTestsPass++;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TestFailed(const std::string& test)
{
  ::memset(Ebsd::unittest::TestMessage, ' ', NUM_COLS); // Splat Spaces across the entire message
  Ebsd::unittest::TestMessage[NUM_COLS] = 0;            // Make sure it is null terminated

  std::string::size_type size = NUM_COLS - Ebsd::unittest::SizeOfFailed;
  ::strncpy(&(Ebsd::unittest::TestMessage[size]), Ebsd::unittest::Failed, Ebsd::unittest::SizeOfFailed);
  if(test.length() < size)
  {
    ::strncpy(Ebsd::unittest::TestMessage, test.c_str(), test.length());
  }
  else
  {
    ::strncpy(Ebsd::unittest::TestMessage, test.substr(0, size).c_str(), size);
  }
  Ebsd::unittest::TestMessage[NUM_COLS] = 0; // Make sure it is null terminated
  std::cout << Ebsd::unittest::TestMessage << std::endl;
  Ebsd::unittest::numTestFailed++;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
#define INFINITYCHECK 1
#define SIGNCHECK 1
#ifdef INFINITYCHECK
inline bool IsInfinite(float* A)
{
  const int kInfAsInt = 0x7F800000;
  int* comp = reinterpret_cast<int*>(A);

  // An infinity has an exponent of 255 (shift left 23 positions) and
  // a zero mantissa. There are two infinities - positive and negative.
  if((*comp & 0x7FFFFFFF) == kInfAsInt)
  {
    return true;
  }
  return false;
}
#endif

#ifdef NANCHECK
inline bool IsNan(float A)
{
  // A NAN has an exponent of 255 (shifted left 23 positions) and
  // a non-zero mantissa.
  int exp = *(int*)&A & 0x7F800000;
  int mantissa = *(int*)&A & 0x007FFFFF;
  if(exp == 0x7F800000 && mantissa != 0)
  {
    return true;
  }
  return false;
}
#endif

#ifdef SIGNCHECK
inline int Sign(float* A)
{
  int* comp = reinterpret_cast<int*>(A);

  // The sign bit of a number is the high bit.
  return *comp & 0x80000000;
}
#endif

bool AlmostEqualUlpsFinal(float* A, float* B, int maxUlps)
{
  // There are several optional checks that you can do, depending
  // on what behavior you want from your floating point comparisons.
  // These checks should not be necessary and they are included
  // mainly for completeness.

#ifdef INFINITYCHECK
  // If A or B are infinity (positive or negative) then
  // only return true if they are exactly equal to each other -
  // that is, if they are both infinities of the same sign.
  // This check is only needed if you will be generating
  // infinities and you don't want them 'close' to numbers
  // near FLT_MAX.
  if(IsInfinite(A) || IsInfinite(B))
  {
    return *A == *B;
  }
#endif

#ifdef NANCHECK
  // If A or B are a NAN, return false. NANs are equal to nothing,
  // not even themselves.
  // This check is only needed if you will be generating NANs
  // and you use a maxUlps greater than 4 million or you want to
  // ensure that a NAN does not equal itself.
  if(IsNan(A) || IsNan(B))
  {
    return false;
  }
#endif

#ifdef SIGNCHECK
  // After adjusting floats so their representations are lexicographically
  // ordered as twos-complement integers a very small positive number
  // will compare as 'close' to a very small negative number. If this is
  // not desireable, and if you are on a platform that supports
  // subnormals (which is the only place the problem can show up) then
  // you need this check.
  // The check for A == B is because zero and negative zero have different
  // signs but are equal to each other.
  if(Sign(A) != Sign(B))
  {
    return *A == *B;
  }
#endif

  int* aInt = reinterpret_cast<int*>(A);
  // Make aInt lexicographically ordered as a twos-complement int
  if(*aInt < 0)
  {
    *aInt = 0x80000000 - *aInt;
  }
  // Make bInt lexicographically ordered as a twos-complement int
  int* bInt = reinterpret_cast<int*>(B);
  if(*bInt < 0)
  {
    *bInt = 0x80000000 - *bInt;
  }

  // Now we can compare aInt and bInt to find out how far apart A and B
  // are.
  int intDiff = abs(*aInt - *bInt);
  if(intDiff <= maxUlps)
  {
    return true;
  }
  return false;
}

// -----------------------------------------------------------------------------
// Developer Used Macros
// -----------------------------------------------------------------------------
#define DREAM3D_TEST_FAILED(P)                                                                                                                                                                         \
  {                                                                                                                                                                                                    \
    DREAM3D_TEST_THROW_EXCEPTION(s)                                                                                                                                                                    \
  }

#define DREAM3D_REQUIRE(P)                                                                                                                                                                             \
  {                                                                                                                                                                                                    \
    bool b = (P);                                                                                                                                                                                      \
    if((b) == (false))                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
      std::string s("Your test required the following\n            '");                                                                                                                                \
      s = s.append(#P).append("'\n             but this condition was not met.");                                                                                                                      \
      DREAM3D_TEST_THROW_EXCEPTION(s)                                                                                                                                                                  \
    }                                                                                                                                                                                                  \
  }

#define DREAM3D_REQUIRED(L, Q, R)                                                                                                                                                                      \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    bool b = (L Q R);                                                                                                                                                                                  \
    if((b) == (false))                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
      ss << "Your test required the following\n            '";                                                                                                                                         \
      ss << #L << " " << #Q << " " << #R << "' but this condition was not met.\n";                                                                                                                     \
      ss << "            " << #L << " = " << L << "\n";                                                                                                                                                \
      ss << "            " << #R << " = " << R << "\n";                                                                                                                                                \
      DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

#define DREAM3D_REQUIRED_PTR(L, Q, P)                                                                                                                                                                  \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    bool b = (L Q P);                                                                                                                                                                                  \
    if((b) == (false))                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
      ss << "Your test required the following\n            '";                                                                                                                                         \
      ss << #L << " " << #Q << " " << #P << "' but this condition was not met.\n";                                                                                                                     \
      ss << "            " << #L << " = " << L << "\n";                                                                                                                                                \
      ss << "            " << #P << " = \n";                                                                                                                                                           \
      DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

#define DREAM3D_REQUIRE_NE(L, R)                                                                                                                                                                       \
  if((L) == (R))                                                                                                                                                                                       \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    ss << "Your test required the following\n            '";                                                                                                                                           \
    ss << #L << " != " << #R << "'\n             but this condition was not met.\n";                                                                                                                   \
    ss << "             " << L << "==" << R;                                                                                                                                                           \
    DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                  \
  }

#define DREAM3D_REQUIRE_EQUAL(L, R)                                                                                                                                                                    \
  if((L) != (R))                                                                                                                                                                                       \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    ss << "Your test required the following\n            '";                                                                                                                                           \
    ss << #L << " == " << #R << "'\n             but this condition was not met.\n";                                                                                                                   \
    ss << "             " << L << "==" << R;                                                                                                                                                           \
    DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                  \
  }

#define DREAM3D_COMPARE_FLOATS(L, R, Ulps)                                                                                                                                                             \
  if(false == AlmostEqualUlpsFinal((L), (R), Ulps))                                                                                                                                                    \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    ss << "Your test required the following\n            '";                                                                                                                                           \
    ss << "AlmostEqualUlpsFinal(" << #L << ", " << #R << ", " << #Ulps << "'\n             but this condition was not met with MaxUlps=" << Ulps << "\n";                                              \
    ss << "             " << L << "==" << R;                                                                                                                                                           \
    DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                  \
  }

#define DREAM3D_TEST_POINTER(L, Q, R)                                                                                                                                                                  \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    bool b = (L Q R);                                                                                                                                                                                  \
    if((b) == (false))                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
      ss << "Your test required the following\n            '";                                                                                                                                         \
      ss << #L << " " << #Q << " " << #R << "' but this condition was not met.\n";                                                                                                                     \
      ss << "            " << #L << " = ";                                                                                                                                                             \
      if(L)                                                                                                                                                                                            \
      {                                                                                                                                                                                                \
        ss << reinterpret_cast<void*>(L);                                                                                                                                                              \
      }                                                                                                                                                                                                \
      else                                                                                                                                                                                             \
      {                                                                                                                                                                                                \
        ss << "Left side was nullptr";                                                                                                                                                                 \
      }                                                                                                                                                                                                \
      ss << "\n";                                                                                                                                                                                      \
      ss << "            " << #R << " = ";                                                                                                                                                             \
      if(R)                                                                                                                                                                                            \
      {                                                                                                                                                                                                \
        ss << reinterpret_cast<void*>(R);                                                                                                                                                              \
      }                                                                                                                                                                                                \
      else                                                                                                                                                                                             \
      {                                                                                                                                                                                                \
        ss << "Right Side was nullptr";                                                                                                                                                                \
      }                                                                                                                                                                                                \
      ss << "\n";                                                                                                                                                                                      \
      DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

#define DREAM3D_REQUIRE_VALID_POINTER(L)                                                                                                                                                               \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    if(L == nullptr)                                                                                                                                                                                   \
    {                                                                                                                                                                                                  \
      ss << "Your test requires\n            '";                                                                                                                                                       \
      ss << #L << "' != nullptr' but this condition was not met.\n";                                                                                                                                   \
      ss << "\n";                                                                                                                                                                                      \
      DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

#define DREAM3D_REQUIRE_NULL_POINTER(L)                                                                                                                                                                \
  {                                                                                                                                                                                                    \
    std::string buf;                                                                                                                                                                                   \
    std::stringstream ss(buf);                                                                                                                                                                         \
    if(L != nullptr)                                                                                                                                                                                   \
    {                                                                                                                                                                                                  \
      ss << "Your test requires\n            '";                                                                                                                                                       \
      ss << #L << " == nullptr' but this condition was not met.\n";                                                                                                                                    \
      ss << "\n";                                                                                                                                                                                      \
      DREAM3D_TEST_THROW_EXCEPTION(buf)                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

// -----------------------------------------------------------------------------
// Private Macros. The Normal developer should NOT be using these.
// -----------------------------------------------------------------------------
#define DREAM3D_TEST_THROW_EXCEPTION(P) throw TestException(P, __FILE__, __LINE__);

#define DREAM3D_ASSERT(P) assert((P));

#define DREAM3D_ENTER_TEST(test)                                                                                                                                                                       \
  Ebsd::unittest::CurrentMethod = #test;                                                                                                                                                               \
  Ebsd::unittest::numTests++;

#define DREAM3D_LEAVE_TEST(test)                                                                                                                                                                       \
  TestPassed(#test);                                                                                                                                                                                   \
  Ebsd::unittest::CurrentMethod = "";

#define DREAM3D_REGISTER_TEST(test)                                                                                                                                                                    \
  try                                                                                                                                                                                                  \
  {                                                                                                                                                                                                    \
    DREAM3D_ENTER_TEST(test);                                                                                                                                                                          \
    test;                                                                                                                                                                                              \
    DREAM3D_LEAVE_TEST(test)                                                                                                                                                                           \
  } catch(TestException & e)                                                                                                                                                                           \
  {                                                                                                                                                                                                    \
    TestFailed(Ebsd::unittest::CurrentMethod);                                                                                                                                                         \
    std::cout << e.what() << std::endl;                                                                                                                                                                \
    err = EXIT_FAILURE;                                                                                                                                                                                \
  }

#define PRINT_TEST_SUMMARY()                                                                                                                                                                           \
  std::cout << "Test Summary:" << std::endl;                                                                                                                                                           \
  std::cout << "  Tests Passed: " << Ebsd::unittest::numTestsPass << std::endl;                                                                                                                        \
  std::cout << "  Tests Failed: " << Ebsd::unittest::numTestFailed << std::endl;                                                                                                                       \
  std::cout << "  Total Tests:  " << Ebsd::unittest::numTests << std::endl;                                                                                                                            \
  if(Ebsd::unittest::numTestFailed > 0)                                                                                                                                                                \
  {                                                                                                                                                                                                    \
    err = EXIT_FAILURE;                                                                                                                                                                                \
  }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
template <typename T, typename K>
void require_equal(T l, const std::string& L, K r, const std::string& R, const std::string file = "", int line = 0)
{
  if(l != r)
  {
    std::string buf;
    std::stringstream ss(buf);
    ss << "Your test required the following\n            '";
    ss << L << " == " << R << "'\n             but this condition was not met.\n";
    ss << "             " << l << "==" << r;
    // DREAM3D_TEST_THROW_EXCEPTION( buf )
    throw TestException(buf, file, line);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
template <typename T, typename K>
void require_less_than(T l, const std::string& L, K r, const std::string& R, const std::string file = "", int line = 0)
{
  if(l >= r)
  {
    std::string buf;
    std::stringstream ss(buf);
    ss << "Your test required the following\n            '";
    ss << L << " < " << R << "'\n             but this condition was not met.\n";
    ss << "             " << l << "==" << r;
    throw TestException(buf, file, line);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
template <typename T, typename K>
void require_greater_than(T l, const std::string& L, K r, const std::string& R, const std::string file = "", int line = 0)
{
  if(l <= r)
  {
    std::string buf;
    std::stringstream ss(buf);
    ss << "Your test required the following\n            '";
    ss << L << " < " << R << "'\n             but this condition was not met.\n";
    ss << "             " << l << "==" << r;
    throw TestException(buf, file, line);
  }
}
