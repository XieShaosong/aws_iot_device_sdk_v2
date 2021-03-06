/*
 * Copyright 2010-2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#include <aws/cal/hash.h>

#include <CommonCrypto/CommonDigest.h>

static void s_destroy(struct aws_hash *hash);
static int s_update(struct aws_hash *hash, const struct aws_byte_cursor *to_hash);
static int s_finalize(struct aws_hash *hash, struct aws_byte_buf *output);

static struct aws_hash_vtable s_vtable = {
    .destroy = s_destroy,
    .update = s_update,
    .finalize = s_finalize,
    .alg_name = "SHA256",
    .provider = "CommonCrypto",
};

struct cc_sha256_hash {
    struct aws_hash hash;
    CC_SHA256_CTX cc_hash;
};

struct aws_hash *aws_sha256_default_new(struct aws_allocator *allocator) {
    struct cc_sha256_hash *sha256_hash = aws_mem_acquire(allocator, sizeof(struct cc_sha256_hash));

    if (!sha256_hash) {
        return NULL;
    }

    sha256_hash->hash.allocator = allocator;
    sha256_hash->hash.vtable = &s_vtable;
    sha256_hash->hash.impl = sha256_hash;
    sha256_hash->hash.digest_size = AWS_SHA256_LEN;
    sha256_hash->hash.good = true;

    CC_SHA256_Init(&sha256_hash->cc_hash);
    return &sha256_hash->hash;
}

static void s_destroy(struct aws_hash *hash) {
    struct cc_sha256_hash *ctx = hash->impl;
    aws_mem_release(hash->allocator, ctx);
}

static int s_update(struct aws_hash *hash, const struct aws_byte_cursor *to_hash) {
    if (!hash->good) {
        return aws_raise_error(AWS_ERROR_INVALID_STATE);
    }

    struct cc_sha256_hash *ctx = hash->impl;

    CC_SHA256_Update(&ctx->cc_hash, to_hash->ptr, (CC_LONG)to_hash->len);
    return AWS_OP_SUCCESS;
}

static int s_finalize(struct aws_hash *hash, struct aws_byte_buf *output) {
    if (!hash->good) {
        return aws_raise_error(AWS_ERROR_INVALID_STATE);
    }

    struct cc_sha256_hash *ctx = hash->impl;

    size_t buffer_len = output->capacity - output->len;

    if (buffer_len < AWS_SHA256_LEN) {
        return aws_raise_error(AWS_ERROR_SHORT_BUFFER);
    }

    CC_SHA256_Final(output->buffer + output->len, &ctx->cc_hash);
    hash->good = false;
    output->len += buffer_len;
    return AWS_OP_SUCCESS;
}
