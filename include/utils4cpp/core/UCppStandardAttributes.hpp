/************************************************************************************
**
**  BSD 3-Clause License
**
**  Copyright (c) 2019, shaoguang. All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this
**     list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice,
**     this list of conditions and the following disclaimer in the documentation
**     and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its
**     contributors may be used to endorse or promote products derived from
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
**  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
**  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
**  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
**  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
**  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
**  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
************************************************************************************/

#ifndef UTILS4CPP_CORE_UCPPSTANDARDATTRIBUTES_HPP
#define UTILS4CPP_CORE_UCPPSTANDARDATTRIBUTES_HPP

#include "utils4cpp/core/UCppStandardDetection.hpp"
#include "utils4cpp/core/UCompilerDetection.hpp"

/* atrribute [[deprecated]] and [[deprecated("reason")]] since C++14 */
#if UTILS4CPP_HAS_CPP17
#   if  ( defined(UTILS4CPP_CC_MSVC) && UTILS4CPP_CC_MSVC >= 1900 ) || \
        ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 409 )    || \
        ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 304 )
#       define UTILS4CPP_HAS_ATTR_DEPRECATED            1
#       define UTILS4CPP_HAS_ATTR_DEPRECATED_REASON     1
#   endif
#else
#   define UTILS4CPP_HAS_ATTR_DEPRECATED                0
#   define UTILS4CPP_HAS_ATTR_DEPRECATED_REASON         0
#endif

/* atrribute [[fallthrough]] since C++17 */
#if UTILS4CPP_HAS_CPP17
#   if  ( defined(UTILS4CPP_CC_MSVC) && UTILS4CPP_CC_MSVC >= 1910 ) || \
        ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 700 )    || \
        ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 309 )
#       define UTILS4CPP_HAS_ATTR_FALLTHROUGH           1
#   endif
#else
#   define UTILS4CPP_HAS_ATTR_FALLTHROUGH               0
#endif

/* atrribute [[nodiscard]] and [[maybe_unused]] since C++17 */
#if UTILS4CPP_HAS_CPP17
#   if  ( defined(UTILS4CPP_CC_MSVC) && UTILS4CPP_CC_MSVC >= 1911 ) || \
        ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 700 )    || \
        ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 309 )
#       define UTILS4CPP_HAS_ATTR_NODISCARD                 1
#       define UTILS4CPP_HAS_ATTR_MAYBE_UNUSED              1
#   endif
#else
#   define UTILS4CPP_HAS_ATTR_NODISCARD                 0
#   define UTILS4CPP_HAS_ATTR_MAYBE_UNUSED              0
#endif

/* atrribute [[nodiscard("reason")]] since C++20 */
#if UTILS4CPP_HAS_CPP2A
#   if defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 900
#       define UTILS4CPP_HAS_ATTR_NODISCARD_REASON      1
#   endif
#else
#   define UTILS4CPP_HAS_ATTR_NODISCARD_REASON          0
#endif

/* atrribute [[likely]] and [[unlikely]] since C++20 */
#if UTILS4CPP_HAS_CPP2A
#   if defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 900
#       define UTILS4CPP_HAS_ATTR_LIKELY                1
#       define UTILS4CPP_HAS_ATTR_UNLIKELY              1
#   endif
#else
#   define UTILS4CPP_HAS_ATTR_LIKELY                    0
#   define UTILS4CPP_HAS_ATTR_UNLIKELY                  0
#endif

/* atrribute [[no_unique_address]] since C++20 */
#if UTILS4CPP_HAS_CPP2A
#   if  ( defined(UTILS4CPP_CC_GNU) && UTILS4CPP_CC_GNU >= 900 ) || \
        ( defined(UTILS4CPP_CC_CLANG) && UTILS4CPP_CC_CLANG >= 900 )
#       define UTILS4CPP_HAS_ATTR_NO_UNIQUE_ADDRESS     1
#   endif
#else
#   define UTILS4CPP_HAS_ATTR_NO_UNIQUE_ADDRESS         0
#endif

/* atrribute [[optimize_for_synchronized]] (TM TS) */
#define UTILS4CPP_HAS_ATTR_OPTIMIZE_FOR_SYNCHRONIZED    0

// ============================================================================

/**
    \brief Indicates that the function does not return.
    \since C++11

    This attribute applies to the name of the function being declared in function
    declarations only. The behavior is undefined if the function with this attribute
    actually returns.

    The first declaration of the function must specify this attribute if any declaration
    specifies it. If a function is declared with <b> [[noreturn]] </b> in one translation unit,
    and the same function is declared without <b> [[noreturn]] </b> in another translation unit,
    the program is ill-formed; no diagnostic required.
*/
#define UTILS4CPP_ATTR_NORETURN                         [[noreturn]]

/**
    \brief Indicates that dependency chain in release-consume std::memory_order propagates
    in and out of the function.
    \since C++11.

    Indicates that dependency chain in release-consume \c std::memory_order propagates in and out
    of the function, which allows the compiler to skip unnecessary memory fence instructions.\n
    This attribute may appear in two situations:
    -# it may apply to the parameter declarations of a function or lambda-expressions, in which
    case it indicates that initialization of the parameter carries dependency into lvalue-to-rvalue
    conversion of that object.
    -# It may apply to the function declaration as a whole, in which case it indicates that the
    return value carries dependency to the evaluation of the function call expression.

    This attribute must appear on the first declaration of a function or one of its parameters
    in any translation unit. If it is not used on the first declaration of a function or one of
    its parameters in another translation unit, the program is ill-formed; no diagnostic required.
*/
#define UTILS4CPP_ATTR_CARRIES_DEPENDENCY               [[carries_dependency]]

/**
    \brief Indicates that the use of the name or entity declared with this attribute is allowed.
    \since C++14.

    The string-literal, if specified, is usually included in the warnings.\n
    This attribute is allowed in declarations of the following names or entities:
    \li class/struct/union: <code> struct [[deprecated]] S; </code>
    \li typedef-name, including those declared by alias declaration:
        <code> [[deprecated]] typedef S* PS;, using PS [[deprecated]] = S*; </code>
    \li variable, including static data member: <code> [[deprecated]] int x; </code>
    \li non-static data member: <code> union U { [[deprecated]] int n; }; </code>
    \li function: <code> [[deprecated]] void f(); </code>
    \li namespace: <code> namespace [[deprecated]] NS { int x; } </code>
    \li enumeration: <code> enum [[deprecated]] E {}; </code>
    \li enumerator: <code> enum { A [[deprecated]], B [[deprecated]] = 42 }; </code>
    \li template specialization: <code> template<> struct [[deprecated]] X<int> {}; </code>

    A name declared non-deprecated may be redeclared deprecated. A name declared deprecated
    cannot be un-deprecated by redeclaring it without this attribute.

    \sa UTILS4CPP_ATTR_DEPRECATED_REASON
*/
#if UTILS4CPP_HAS_ATTR_DEPRECATED
#   define UTILS4CPP_ATTR_DEPRECATED                    [[deprecated]]
#else
#   define UTILS4CPP_ATTR_DEPRECATED
#endif

/**
    \brief Indicates that the use of the name or entity declared with this attribute is allowed,
    but discouraged for some reason.
    \since C++14.

    \sa UTILS4CPP_ATTR_DEPRECATED
*/
#if UTILS4CPP_HAS_ATTR_DEPRECATED_REASON
#   define UTILS4CPP_ATTR_DEPRECATED_REASON(_reason_)   [[deprecated(_reason_)]]
#else
#   define UTILS4CPP_ATTR_DEPRECATED_REASON(_reason_)
#endif

/**
    \brief Indicates that the fall through from the previous case label is intentional and
    should not be diagnosed by a compiler that warns on fall-through.
    \since C++17.

    May only be applied to a null statement to create a fallthrough statement (<b>[[fallthrough]]</b>;). \n
    A fallthrough statement may only be used in a switch statement, where the next statement
    to be executed is a statement with a case or default label for that switch statement.
    If the fallthrough statement is inside a loop, the next (labeled) statement must be part
    of the same iteration of that loop. \n
    Indicates that the fall through from the previous case label is intentional and should not
    be diagnosed by a compiler that warns on fallthrough.
*/
#if UTILS4CPP_HAS_ATTR_FALLTHROUGH
#   define UTILS4CPP_ATTR_FALLTHROUGH                   [[fallthrough]]
#else
#   define UTILS4CPP_ATTR_FALLTHROUGH
#endif

/**
    \brief Encourages the compiler to issue a warning if the return value is discarded.
    \since C++17.

    Appears in a function declaration, enumeration declaration, or class declaration. \n
    If, from a discarded-value expression other than a cast to void,
    \li a function declared nodiscard is called, or
    \li a function returning an enumeration or class declared nodiscard by value is called, or
    \li a constructor declared nodiscard is called by explicit type conversion or static_cast, or
    \li an object of an enumeration or class type declared nodiscard is initialized by explicit
        type conversion or static_cast, \n
    the compiler is encouraged to issue a warning.

    \sa UTILS4CPP_ATTR_NODISCARD_REASON
*/
#if UTILS4CPP_HAS_ATTR_NODISCARD
#   define UTILS4CPP_ATTR_NODISCARD                     [[nodiscard]]
#else
#   define UTILS4CPP_ATTR_NODISCARD
#endif

/**
    \brief Encourages the compiler to issue a warning if the return value is discarded.
    \since C++20.

    The \p "_reason_" , if specified, is usually included in the warnings.

    \sa UTILS4CPP_ATTR_NODISCARD
*/
#if UTILS4CPP_HAS_ATTR_NODISCARD_REASON
#   define UTILS4CPP_ATTR_NODISCARD_REASON(_reason_)    [[nodiscard(_reason_)]]
#else
#   define UTILS4CPP_ATTR_NODISCARD_REASON(_reason_)
#endif

/**
    \brief Suppresses compiler warnings on unused entities, if any.
    \since C++17.

    This attribute can appear in the declaration of the following entities:

    \li class/struct/union: <code> struct [[maybe_unused]] S; </code>
    \li typedef, including those declared by alias declaration:
        <code> [[maybe_unused]] typedef S* PS;, using PS [[maybe_unused]] = S*; </code>
    \li variable, including static data member: <code> [[maybe_unused]] int x; </code>
    \li non-static data member: <code> union U { [[maybe_unused]] int n; }; </code>
    \li function: <code> [[maybe_unused]] void f(); </code>
    \li enumeration: <code> enum [[maybe_unused]] E {}; </code>
    \li enumerator: <code> enum { A [[maybe_unused]], B [[maybe_unused]] = 42 }; </code>

    If the compiler issues warnings on unused entities, that warning is suppressed for any
    entity declared maybe_unused.
*/
#if UTILS4CPP_HAS_ATTR_MAYBE_UNUSED
#   define UTILS4CPP_ATTR_MAYBE_UNUSED                  [[maybe_unused]]
#else
#   define UTILS4CPP_ATTR_MAYBE_UNUSED
#endif

/**
    \brief Indicates that the compiler should optimize for the case where a path of execution
    through a statement is more likely than any other path of execution.
    \since C++20.

    Applies to a statement to allow the compiler to optimize for the case where paths of
    execution including that statement is more likely than any alternative path of execution
    that does not include such a statement. \n
    A path of execution is deemed to include a label if and only if it contains a jump to that label:
    \code
        int func(int i)
        {
            switch(i) {
            case 1: [[fallthrough]];
            [[likely]] case 2: return 1;
            }
            return 2;
        }
    \endcode
    <code> i == 2 </code> is considered more likely than any other value of i, but the <b> [[likely]] </b>
    has no effect on the <code> i == 1 </code> case even though it falls through the <code> case 2: </code> label.

    \sa UTILS4CPP_ATTR_UNLIKELY
*/
#if UTILS4CPP_HAS_ATTR_LIKELY
#   define UTILS4CPP_ATTR_LIKELY                        [[likely]]
#else
#   define UTILS4CPP_ATTR_LIKELY                        
#endif

/**
    \brief Indicates that the compiler should optimize for the case where a path of execution
    through a statement is less likely than any other path of execution.
    \since C++20.

    Applies to a statement to allow the compiler to optimize for the case where paths of
    execution including that statement is less likely than any alternative path of execution
    that does not include such a statement.

    \sa UTILS4CPP_ATTR_LIKELY
*/
#if UTILS4CPP_HAS_ATTR_UNLIKELY
#   define UTILS4CPP_ATTR_UNLIKELY                      [[unlikely]]
#else
#   define UTILS4CPP_ATTR_UNLIKELY                        
#endif

/**
    \brief Indicates that a non-static data member need not have an address distinct from
    all other non-static data members of its class.
    \since C++20

    Applies to the name being declared in the declaration of a non-static data member that's
    not a bit field. \n
    Indicates that this data member need not have an address distinct from all other non-static
    data members of its class. This means that if the member has an empty type (e.g. stateless Allocator),
    the compiler may optimise it to occupy no space, just like if it were an empty base. If the
    member is not empty, any tail padding in it may be also reused to store other data members.
*/
#if UTILS4CPP_HAS_ATTR_NO_UNIQUE_ADDRESS
#   define UTILS4CPP_ATTR_NO_UNIQUE_ADDRESS             [[no_unique_address]]
#else
#   define UTILS4CPP_ATTR_NO_UNIQUE_ADDRESS
#endif

/**
    \brief indicates that the function definition should be optimized for invocation from
    a synchronized statement. <strong> (TM TS) </strong>

    Applies to the name being declared in a function declaration, which must be the first
    declaration of the function. \n
    Indicates that the function definition should be optimized for invocation from a
    synchronized statement. In particular, it avoids serializing synchronized blocks that make
    a call to a function that is transaction-safe for the majority of calls, but not for all calls.
*/
#if UTILS4CPP_HAS_ATTR_OPTIMIZE_FOR_SYNCHRONIZED
#   define UTILS4CPP_ATTR_OPTIMIZE_FOR_SYNCHRONIZED     [[optimize_for_synchronized]]
#else
#   define UTILS4CPP_ATTR_OPTIMIZE_FOR_SYNCHRONIZED
#endif

#endif // UTILS4CPP_CORE_UCPPSTANDARDATTRIBUTES_HPP