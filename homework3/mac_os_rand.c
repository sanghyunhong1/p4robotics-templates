/* Copyright (C) 1991-2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define TYPE_0 0

/* x**31 + x**3 + 1.  */
#define TYPE_3 3
#define BREAK_3 128
#define DEG_3 31
#define SEP_3 3

struct __MAC_OS_COPY_random_data {
    int32_t *fptr; /* Front pointer.  */
    int32_t *rptr; /* Rear pointer.  */
    int32_t *state; /* Array of state values.  */
    int rand_type; /* Type of random number generator.  */
    int rand_deg; /* Degree of random number generator.  */
    int rand_sep; /* Distance between front and rear.  */
    int32_t *end_ptr; /* Pointer behind state table.  */
};

int __random_r(struct __MAC_OS_COPY_random_data *buf, int32_t *result) {
    int32_t *state;
    if (!buf || !result)
        goto fail;
    state = buf->state;
    if (buf->rand_type == TYPE_0) {
        int32_t val = ((state[0] * 1103515245U) + 12345U) & 0x7fffffff;
        state[0] = val;
        *result = val;
    } else {
        int32_t *fptr = buf->fptr;
        int32_t *rptr = buf->rptr;
        int32_t *end_ptr = buf->end_ptr;
        uint32_t val;
        val = *fptr += (uint32_t)*rptr;
        /* Chucking least random bit.  */
        *result = val >> 1;
        ++fptr;
        if (fptr >= end_ptr) {
            fptr = state;
            ++rptr;
        } else {
            ++rptr;
            if (rptr >= end_ptr)
                rptr = state;
        }
        buf->fptr = fptr;
        buf->rptr = rptr;
    }
    return 0;
fail:
    errno = EINVAL;
    return -1;
}

static int32_t randtbl_original[DEG_3 + 1] = {
    TYPE_3,
    -1726662223,
    379960547,
    1735697613,
    1040273694,
    1313901226,
    1627687941,
    -179304937,
    -2073333483,
    1780058412,
    -1989503057,
    -615974602,
    344556628,
    939512070,
    -1249116260,
    1507946756,
    -812545463,
    154635395,
    1388815473,
    -1926676823,
    525320961,
    -1009028674,
    968117788,
    -123449607,
    1284210865,
    435012392,
    -2017506339,
    -911064859,
    -370259173,
    1132637927,
    1398500161,
    -205601318,
};

static int32_t randtbl[DEG_3 + 1] = {
    TYPE_3,
    -1726662223,
    379960547,
    1735697613,
    1040273694,
    1313901226,
    1627687941,
    -179304937,
    -2073333483,
    1780058412,
    -1989503057,
    -615974602,
    344556628,
    939512070,
    -1249116260,
    1507946756,
    -812545463,
    154635395,
    1388815473,
    -1926676823,
    525320961,
    -1009028674,
    968117788,
    -123449607,
    1284210865,
    435012392,
    -2017506339,
    -911064859,
    -370259173,
    1132637927,
    1398500161,
    -205601318,
};

static struct __MAC_OS_COPY_random_data unsafe_state = {
    .fptr = &randtbl[SEP_3 + 1],
    .rptr = &randtbl[1],
    .state = &randtbl[1],
    .rand_type = TYPE_3,
    .rand_deg = DEG_3,
    .rand_sep = SEP_3,
    .end_ptr = &randtbl[sizeof(randtbl) / sizeof(randtbl[0])]};

int rand_for_mac_os(void) {
    int32_t val;
    __random_r(&unsafe_state, &val);
    return val;
}

void srand0_for_mac_os(void) {
    unsafe_state.fptr = &randtbl[SEP_3 + 1];
    unsafe_state.rptr = &randtbl[1];
    memcpy(randtbl, randtbl_original, sizeof(randtbl));
}

// int main(void) {
//     for (int i = 0; i < 10; i++) {
//         printf("%d, %d\n", rand_for_mac_os(), rand());
//     }
//     printf("\n");
//     srand(0);
//     srand0_for_mac_os();
//     for (int i = 0; i < 10; i++) {
//         printf("%d, %d\n", rand_for_mac_os(), rand());
//     }
//     return 0;
// }
