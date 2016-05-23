#ifndef INC_Util_AnnotationMacrosC_h
#define INC_Util_AnnotationMacrosC_h

#ifndef TVR_DISABLE_ANALYSIS

#if defined(_MSC_VER) && (_MSC_VER >= 1700)
/* Visual C++ (2012 and newer) */
/* Using SAL attribute format:
 * http://msdn.microsoft.com/en-us/library/ms182032(v=vs.120).aspx */

#include <sal.h>

#define TVR_IN _In_
#define TVR_IN_PTR _In_
#define TVR_IN_OPT _In_opt_
#define TVR_IN_STRZ _In_z_
#define TVR_IN_READS(NUM_ELEMENTS) _In_reads_(NUM_ELEMENTS)

#define TVR_OUT _Out_
#define TVR_OUT_PTR _Outptr_
#define TVR_OUT_OPT _Out_opt_

#define TVR_INOUT _Inout_
#define TVR_INOUT_PTR _Inout_

#define TVR_RETURN_WARN_UNUSED _Must_inspect_result_
#define TVR_RETURN_SUCCESS_CONDITION(X) _Return_type_success_(X)

/* end of msvc section */
#elif defined(__GNUC__) && (__GNUC__ >= 4)
/* section for GCC and GCC-alikes */

#if defined(__clang__)
/* clang-specific section */
#endif

#define TVR_FUNC_NONNULL(X) __attribute__((__nonnull__ X))
#define TVR_RETURN_WARN_UNUSED __attribute__((warn_unused_result))

/* end of gcc section and compiler detection */
#endif

/* end of ndef disable analysis */
#endif

/* Fallback declarations */
/**
@defgroup annotation_macros Static analysis annotation macros
@brief Wrappers for Microsoft's SAL annotations and others
@ingroup Util

Use of these is optional, but recommended particularly for C APIs,
as well as any methods handling a buffer with a length.
@{
*/
/** @name Parameter annotations

    These indicate the role and valid values for parameters to functions.

    At most one of these should be placed before a parameter's type name in the
   function parameter list, in both the declaration and definition. (They must
   match!)
   @{
*/
/** @def TVR_IN
    @brief Indicates a required function parameter that serves only as input.
*/
#ifndef TVR_IN
#define TVR_IN
#endif

/** @def TVR_IN_PTR
    @brief Indicates a required pointer (non-null) function parameter that
    serves only as input.
*/
#ifndef TVR_IN_PTR
#define TVR_IN_PTR
#endif

/** @def TVR_IN_OPT
    @brief Indicates a function parameter (pointer) that serves only as input,
   but is optional and might be NULL.
*/
#ifndef TVR_IN_OPT
#define TVR_IN_OPT
#endif

/** @def TVR_IN_STRZ
    @brief Indicates a null-terminated string function parameter that serves
   only as input.
*/
#ifndef TVR_IN_STRZ
#define TVR_IN_STRZ
#endif

/** @def TVR_IN_READS(NUM_ELEMENTS)
    @brief Indicates a buffer containing input with the specified number of
   elements.

    The specified number of elements is typically the name of another parameter.
*/
#ifndef TVR_IN_READS
#define TVR_IN_READS(NUM_ELEMENTS)
#endif

/** @def TVR_OUT
    @brief Indicates a required function parameter that serves only as output.
    In C code, since this usually means "pointer", you probably want
   TVR_OUT_PTR instead.
*/
#ifndef TVR_OUT
#define TVR_OUT
#endif

/** @def TVR_OUT_PTR
    @brief Indicates a required pointer (non-null) function parameter that
    serves only as output.
*/
#ifndef TVR_OUT_PTR
#define TVR_OUT_PTR
#endif

/** @def TVR_OUT_OPT
    @brief Indicates a function parameter (pointer) that serves only as output,
   but is optional and might be NULL
*/
#ifndef TVR_OUT_OPT
#define TVR_OUT_OPT
#endif

/** @def TVR_INOUT
    @brief Indicates a required function parameter that is both read and written
   to.

    In C code, since this usually means "pointer", you probably want
   TVR_INOUT_PTR instead.
*/
#ifndef TVR_INOUT
#define TVR_INOUT
#endif

/** @def TVR_INOUT_PTR
    @brief Indicates a required pointer (non-null) function parameter that is
    both read and written to.
*/
#ifndef TVR_INOUT_PTR
#define TVR_INOUT_PTR
#endif

/* End of parameter annotations. */
/** @} */

/** @name Function annotations

    These indicate particular relevant aspects about a function. Some
    duplicate the effective meaning of parameter annotations: applying both
    allows the fullest extent of static analysis tools to analyze the code,
    and in some compilers, generate warnings.

   @{
*/
/** @def TVR_FUNC_NONNULL(X)
    @brief Indicates the parameter(s) that must be non-null.

    @param X A parenthesized list of parameters by number (1-based index)

    Should be placed after a function declaration (but before the
   semicolon). Repeating in the definition is not needed.
*/
#ifndef TVR_FUNC_NONNULL
#define TVR_FUNC_NONNULL(X)
#endif

/** @def TVR_RETURN_WARN_UNUSED
    @brief Indicates the function has a return value that must be used (either a
   security problem or an obvious bug if not).

    Should be placed before the return value (and virtual keyword, if
   applicable) in both declaration and definition.
*/
#ifndef TVR_RETURN_WARN_UNUSED
#define TVR_RETURN_WARN_UNUSED
#endif
/* End of function annotations. */
/** @} */

/** @def TVR_RETURN_SUCCESS_CONDITION
    @brief Applied to a typedef, indicates the condition for `return` under
   which a function returning it should be considered to have succeeded (thus
   holding certain specifications).

    Should be placed before the typename in a typedef, with the parameter
   including the keyword `return` to substitute for the return value.
*/
#ifndef TVR_RETURN_SUCCESS_CONDITION
#define TVR_RETURN_SUCCESS_CONDITION(X)
#endif

/* End of annotation group. */
/** @} */
#endif
