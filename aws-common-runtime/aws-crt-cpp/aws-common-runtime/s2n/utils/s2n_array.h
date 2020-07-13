/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
#pragma once

#include <s2n.h>
#include "utils/s2n_blob.h"

struct s2n_array {
    /* Pointer to elements in array */
    struct s2n_blob mem;

    /* The total number of elements currently in the array. */
    uint32_t num_of_elements;

    /* The total capacity of the array, in number of elements. */
    uint32_t capacity;

    /* The size of each element in the array */
    size_t element_size;
};

#define s2n_array_num_elements( a )   ((a)->num_of_elements)
#define S2N_ELEMENT_ALREADY_IN_ARRAY -1

extern struct s2n_array *s2n_array_new(size_t element_size);
extern void *s2n_array_pushback(struct s2n_array *array);
extern void *s2n_array_get(struct s2n_array *array, uint32_t index);
extern void *s2n_array_insert(struct s2n_array *array, uint32_t index);
extern int s2n_array_remove(struct s2n_array *array, uint32_t index);
extern int s2n_array_free_p(struct s2n_array **parray);
extern int s2n_array_free(struct s2n_array *array);
extern int s2n_array_insert_and_copy(struct s2n_array *array, void* element, uint32_t index);