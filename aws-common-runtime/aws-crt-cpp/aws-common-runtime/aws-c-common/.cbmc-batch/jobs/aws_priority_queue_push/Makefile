# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0.

###########
include ../Makefile.aws_array_list

###########
#
# Runtime: 1200s

# This is the minimum bound to reach full coverage rate
UNWINDSET += 

CBMCFLAGS +=

DEPENDENCIES += $(HELPERDIR)/source/make_common_data_structures.c
DEPENDENCIES += $(HELPERDIR)/source/proof_allocators.c
DEPENDENCIES += $(HELPERDIR)/source/utils.c
DEPENDENCIES += $(HELPERDIR)/stubs/error.c
DEPENDENCIES += $(HELPERDIR)/stubs/memcpy_override_no_op.c
DEPENDENCIES += $(SRCDIR)/source/array_list.c
DEPENDENCIES += $(SRCDIR)/source/common.c
DEPENDENCIES += $(SRCDIR)/source/priority_queue.c

ABSTRACTIONS +=  $(HELPERDIR)/stubs/s_sift_up_override.c

ADDITIONAL_REMOVE_FUNCTION_BODY += --remove-function-body __CPROVER_file_local_priority_queue_c_s_sift_up

ENTRY = aws_priority_queue_push_harness
###########

include ../Makefile.common
