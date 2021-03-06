/** @file
    @brief Header

    Must be c-safe!

    @date 2014

    @author
    Sensics, Inc.
    <http://sensics.com/tvr>
*/

/*
// Copyright 2014 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef INCLUDED_Vec3C_h_GUID_BF4E98ED_74CF_4785_DB61_109A00BA74DE
#define INCLUDED_Vec3C_h_GUID_BF4E98ED_74CF_4785_DB61_109A00BA74DE

/* Internal Includes */
#include <tvr/Util/APIBaseC.h>

/* Library/third-party includes */
/* none */

/* Standard includes */
/* none */

TVR_EXTERN_C_BEGIN

/** @addtogroup UtilMath
    @{
*/
/** @brief A structure defining a 3D vector, often a position/translation.
*/
typedef struct TVR_Vec3 {
    /** @brief Internal array data. */
    double data[3];
} TVR_Vec3;

#define TVR_VEC_MEMBER(COMPONENT, INDEX)                                      \
    /** @brief Accessor for Vec3 component COMPONENT */                        \
    TVR_INLINE double tvrVec3Get##COMPONENT(TVR_Vec3 const *v) {            \
        return v->data[INDEX];                                                 \
    }                                                                          \
    /** @brief Setter for Vec3 component COMPONENT */                          \
    TVR_INLINE void tvrVec3Set##COMPONENT(TVR_Vec3 *v, double val) {        \
        v->data[INDEX] = val;                                                  \
    }

TVR_VEC_MEMBER(X, 0)
TVR_VEC_MEMBER(Y, 1)
TVR_VEC_MEMBER(Z, 2)

#undef TVR_VEC_MEMBER

/** @brief Set a Vec3 to the zero vector */
TVR_INLINE void tvrVec3Zero(TVR_Vec3 *v) {
    tvrVec3SetX(v, 0);
    tvrVec3SetY(v, 0);
    tvrVec3SetZ(v, 0);
}

/** @} */

TVR_EXTERN_C_END

#ifdef __cplusplus
template <typename StreamType>
inline StreamType &operator<<(StreamType &os, TVR_Vec3 const &vec) {
    os << "(" << vec.data[0] << ", " << vec.data[1] << ", " << vec.data[2]
       << ")";
    return os;
}
#endif

#endif
