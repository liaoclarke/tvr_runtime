#ifndef INC_Common_BoolC_h
#define INC_Common_BoolC_h

/* Internal Includes */
#include <tvr/Util/APIBaseC.h>
#include <tvr/Util/StdInt.h>

/* Library/third-party includes */
/* none */

/* Standard includes */
/* none */

TVR_EXTERN_C_BEGIN
/** @addtogroup Util
@{
*/

/** @brief A pre-C99-safe bool type. Canonical values for true and false are
 * provided. Interpretation of other values is not defined. */
typedef uint8_t TVR_CBool;
/** @brief Canonical "true" value for OSVR_CBool */
#define TVR_TRUE (1)
/** @brief Canonical "false" value for OSVR_CBool */
#define TVR_FALSE (0)

/** @} */
TVR_EXTERN_C_END

#endif
