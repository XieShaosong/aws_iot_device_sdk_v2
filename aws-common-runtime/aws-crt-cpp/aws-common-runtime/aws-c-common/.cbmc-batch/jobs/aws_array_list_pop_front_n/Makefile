# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0.

###########
include ../Makefile.aws_array_list

UNWINDSET +=

CBMCFLAGS +=

DEPENDENCIES += $(HELPERDIR)/source/proof_allocators.c
DEPENDENCIES += $(HELPERDIR)/source/make_common_data_structures.c
DEPENDENCIES += $(HELPERDIR)/source/utils.c
DEPENDENCIES += $(HELPERDIR)/stubs/error.c
DEPENDENCIES += $(HELPERDIR)/stubs/memmove_override_no_op.c
DEPENDENCIES += $(SRCDIR)/source/array_list.c
DEPENDENCIES += $(SRCDIR)/source/common.c

ENTRY = aws_array_list_pop_front_n_harness
###########

include ../Makefile.common
