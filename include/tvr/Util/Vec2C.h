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

#ifndef INCLUDED_Vec2C_h_GUID_F9715DE4_2649_4182_0F4C_D62121235D5F
#define INCLUDED_Vec2C_h_GUID_F9715DE4_2649_4182_0F4C_D62121235D5F

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
/** @brief A structure defining a 2D vector, which represents position
*/
typedef struct TVR_Vec2 {
    /** @brief Internal array data. */
    double data[2];
} TVR_Vec2;

#define TVR_VEC_MEMBER(COMPONENT, INDEX)                                      \
    /** @brief Accessor for Vec2 component COMPONENT */                        \
    TVR_INLINE double tvrVec2Get##COMPONENT(TVR_Vec2 const *v) {            \
        return v->data[INDEX];                                                 \
    }                                                                          \
    /** @brief Setter for Vec2 component COMPONENT */                          \
    TVR_INLINE void tvrVec2Set##COMPONENT(TVR_Vec2 *v, double val) {        \
        v->data[INDEX] = val;                                                  \
    }

TVR_VEC_MEMBER(X, 0)
TVR_VEC_MEMBER(Y, 1)

#undef TVR_VEC_MEMBER

/** @brief Set a Vec2 to the zero vector */
TVR_INLINE void tvrVec2Zero(TVR_Vec2 *v) {
    tvrVec2SetX(v, 0);
    tvrVec2SetY(v, 0);
}

/** @} */

TVR_EXTERN_C_END

#ifdef __cplusplus
template <typename StreamType>
inline StreamType &operator<<(StreamType &os, TVR_Vec2 const &vec) {
    os << "(" << vec.data[0] << ", " << vec.data[1] << ")";
    return os;
}
#endif

#endif // INCLUDED_Vec2C_h_GUID_F9715DE4_2649_4182_0F4C_D62121235D5F
