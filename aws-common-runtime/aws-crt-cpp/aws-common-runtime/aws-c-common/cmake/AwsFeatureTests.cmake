# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0.

include(CheckCSourceRuns)
include(AwsCFlags)

if(NOT CMAKE_CROSSCOMPILING)
    check_c_source_runs("
    #include <stdbool.h>
    bool foo(int a, int b, int *c) {
        return __builtin_mul_overflow(a, b, c);
    }

    int main() {
        int out;
        if (foo(1, 2, &out)) {
            return 0;
        }

        return 0;
    }" AWS_HAVE_GCC_OVERFLOW_MATH_EXTENSIONS)

    check_c_source_runs("
    int main() {
    int foo = 42;
    _mulx_u32(1, 2, &foo);
    return foo != 2;
    }" AWS_HAVE_MSVC_MULX)

endif()

check_c_source_compiles("
    int main() {
#if !(defined(__x86_64__) || defined(__i386__) || defined(_M_X64) || defined(_M_IX86))
#    error \"not intel\"
#endif
        return 0;
    }
" AWS_ARCH_INTEL)

check_c_source_compiles("
int main() {
    int foo = 42, bar = 24;
    __asm__ __volatile__(\"\":\"=r\"(foo):\"r\"(bar):\"memory\");
}" AWS_HAVE_GCC_INLINE_ASM)

string(REGEX MATCH "^(aarch64|arm)" ARM_CPU "${CMAKE_SYSTEM_PROCESSOR}")
if(NOT LEGACY_COMPILER_SUPPORT OR ARM_CPU)
    check_c_source_compiles("
    #include <execinfo.h>
    int main() {
        return 0;
    }" AWS_HAVE_EXECINFO)
endif()
