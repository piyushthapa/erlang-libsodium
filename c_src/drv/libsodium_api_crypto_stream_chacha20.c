// -*- mode: c; tab-width: 4; indent-tabs-mode: nil; st-rulers: [132] -*-
// vim: ts=4 sw=4 ft=c et

#include "libsodium_api_crypto_stream_chacha20.h"

static void LS_API_EXEC(crypto_stream_chacha20, keybytes);
static void LS_API_EXEC(crypto_stream_chacha20, noncebytes);
static int LS_API_INIT(crypto_stream_chacha20, crypto_stream_chacha20);
static void LS_API_EXEC(crypto_stream_chacha20, crypto_stream_chacha20);
static int LS_API_INIT(crypto_stream_chacha20, xor);
static void LS_API_EXEC(crypto_stream_chacha20, xor);
static int LS_API_INIT(crypto_stream_chacha20, xor_ic);
static void LS_API_EXEC(crypto_stream_chacha20, xor_ic);
static void LS_API_EXEC(crypto_stream_chacha20, ietf_noncebytes);
static int LS_API_INIT(crypto_stream_chacha20, ietf);
static void LS_API_EXEC(crypto_stream_chacha20, ietf);
static int LS_API_INIT(crypto_stream_chacha20, ietf_xor);
static void LS_API_EXEC(crypto_stream_chacha20, ietf_xor);
static int LS_API_INIT(crypto_stream_chacha20, ietf_xor_ic);
static void LS_API_EXEC(crypto_stream_chacha20, ietf_xor_ic);

libsodium_function_t libsodium_functions_crypto_stream_chacha20[] = {
    LS_API_R_ARG0(crypto_stream_chacha20, keybytes),
    LS_API_R_ARG0(crypto_stream_chacha20, noncebytes),
    LS_API_R_ARGV(crypto_stream_chacha20, crypto_stream_chacha20, 3),
    LS_API_R_ARGV(crypto_stream_chacha20, xor, 3),
    LS_API_R_ARGV(crypto_stream_chacha20, xor_ic, 4),
    LS_API_R_ARG0(crypto_stream_chacha20, ietf_noncebytes),
    LS_API_R_ARGV(crypto_stream_chacha20, ietf, 3),
    LS_API_R_ARGV(crypto_stream_chacha20, ietf_xor, 3),
    LS_API_R_ARGV(crypto_stream_chacha20, ietf_xor_ic, 4),
    {NULL}};

/* crypto_stream_chacha20_keybytes/0 */

static void
LS_API_EXEC(crypto_stream_chacha20, keybytes)
{
    size_t keybytes;

    keybytes = crypto_stream_chacha20_keybytes();

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_UINT, (ErlDrvUInt)(keybytes), ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}

/* crypto_stream_chacha20_noncebytes/0 */

static void
LS_API_EXEC(crypto_stream_chacha20, noncebytes)
{
    size_t noncebytes;

    noncebytes = crypto_stream_chacha20_noncebytes();

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_UINT, (ErlDrvUInt)(noncebytes), ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}

/* crypto_stream_chacha20_crypto_stream_chacha20/3 */

typedef struct LS_API_F_ARGV(crypto_stream_chacha20, crypto_stream_chacha20) {
    unsigned long long clen;
    const unsigned char *n;
    const unsigned char *k;
} LS_API_F_ARGV_T(crypto_stream_chacha20, crypto_stream_chacha20);

static int
LS_API_INIT(crypto_stream_chacha20, crypto_stream_chacha20)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, crypto_stream_chacha20) * argv;
    int skip;
    int type;
    int type_length;
    unsigned long long clen;
    size_t noncebytes;
    size_t keybytes;
    ErlDrvSizeT x;
    void *p;

    if (ei_decode_ulong(buffer, index, (unsigned long *)&(clen)) < 0) {
        return -1;
    }

    noncebytes = crypto_stream_chacha20_noncebytes();

    if (ei_get_type(buffer, index, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != noncebytes) {
        return -1;
    }

    skip = *index;

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    keybytes = crypto_stream_chacha20_keybytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != keybytes) {
        return -1;
    }

    x = (ErlDrvSizeT)(noncebytes + keybytes + (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, crypto_stream_chacha20))));
    p = (void *)(driver_alloc(x));

    if (p == NULL) {
        return -1;
    }

    argv = (LS_API_F_ARGV_T(crypto_stream_chacha20, crypto_stream_chacha20) *)(p);
    p += (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, crypto_stream_chacha20)));
    argv->clen = clen;
    argv->n = (const unsigned char *)(p);
    p += noncebytes;
    argv->k = (const unsigned char *)(p);

    if (ei_decode_binary(buffer, index, (void *)(argv->n), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->k), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    request->argv = (void *)(argv);

    return 0;
}

static void
LS_API_EXEC(crypto_stream_chacha20, crypto_stream_chacha20)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, crypto_stream_chacha20) * argv;
    LS_API_READ_ARGV(crypto_stream_chacha20, crypto_stream_chacha20);
    unsigned char *c;

    c = (unsigned char *)(driver_alloc((ErlDrvSizeT)(argv->clen)));

    if (c == NULL) {
        LS_FAIL_OOM(request->port->drv_port);
        return;
    }

    (void)crypto_stream_chacha20(c, argv->clen, argv->n, argv->k);

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_BUF2BINARY, (ErlDrvTermData)(c), argv->clen, ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);

    (void)driver_free(c);
}

/* crypto_stream_chacha20_xor/3 */

typedef struct LS_API_F_ARGV(crypto_stream_chacha20, xor) {
    const unsigned char *m;
    unsigned long long mlen;
    const unsigned char *n;
    const unsigned char *k;
} LS_API_F_ARGV_T(crypto_stream_chacha20, xor);

static int
LS_API_INIT(crypto_stream_chacha20, xor)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, xor) * argv;
    int skip;
    int type;
    int type_length;
    unsigned long long mlen;
    size_t noncebytes;
    size_t keybytes;
    ErlDrvSizeT x;
    void *p;

    if (ei_get_type(buffer, index, &type, &type_length) < 0 || type != ERL_BINARY_EXT) {
        return -1;
    }

    mlen = (unsigned long long)(type_length);

    skip = *index;

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    noncebytes = crypto_stream_chacha20_noncebytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != noncebytes) {
        return -1;
    }

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    keybytes = crypto_stream_chacha20_keybytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != keybytes) {
        return -1;
    }

    x = (ErlDrvSizeT)(mlen + noncebytes + keybytes + (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, xor))));
    p = (void *)(driver_alloc(x));

    if (p == NULL) {
        return -1;
    }

    argv = (LS_API_F_ARGV_T(crypto_stream_chacha20, xor) *)(p);
    p += (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, xor)));
    argv->m = (const unsigned char *)(p);
    p += mlen;
    argv->n = (const unsigned char *)(p);
    p += noncebytes;
    argv->k = (const unsigned char *)(p);

    if (ei_decode_binary(buffer, index, (void *)(argv->m), (long *)&(argv->mlen)) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->n), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->k), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    request->argv = (void *)(argv);

    return 0;
}

static void
LS_API_EXEC(crypto_stream_chacha20, xor)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, xor) * argv;
    LS_API_READ_ARGV(crypto_stream_chacha20, xor);
    unsigned char *c;

    c = (unsigned char *)(argv->m);

    (void)crypto_stream_chacha20_xor(c, argv->m, argv->mlen, argv->n, argv->k);

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_BUF2BINARY, (ErlDrvTermData)(c), argv->mlen, ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}

/* crypto_stream_chacha20_xor_ic/4 */

typedef struct LS_API_F_ARGV(crypto_stream_chacha20, xor_ic) {
    const unsigned char *m;
    unsigned long long mlen;
    const unsigned char *n;
    uint64_t ic;
    const unsigned char *k;
} LS_API_F_ARGV_T(crypto_stream_chacha20, xor_ic);

static int
LS_API_INIT(crypto_stream_chacha20, xor_ic)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, xor_ic) * argv;
    int skip;
    int type;
    int type_length;
    unsigned long long mlen;
    size_t noncebytes;
    uint64_t ic;
    size_t keybytes;
    ErlDrvSizeT x;
    void *p;

    if (ei_get_type(buffer, index, &type, &type_length) < 0 || type != ERL_BINARY_EXT) {
        return -1;
    }

    mlen = (unsigned long long)(type_length);

    skip = *index;

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    noncebytes = crypto_stream_chacha20_noncebytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != noncebytes) {
        return -1;
    }

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    if (ei_decode_ulong(buffer, &skip, (unsigned long *)&(ic)) < 0) {
        return -1;
    }

    keybytes = crypto_stream_chacha20_keybytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != keybytes) {
        return -1;
    }

    x = (ErlDrvSizeT)(mlen + noncebytes + keybytes + (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, xor_ic))));
    p = (void *)(driver_alloc(x));

    if (p == NULL) {
        return -1;
    }

    argv = (LS_API_F_ARGV_T(crypto_stream_chacha20, xor_ic) *)(p);
    p += (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, xor_ic)));
    argv->m = (const unsigned char *)(p);
    p += mlen;
    argv->n = (const unsigned char *)(p);
    argv->ic = ic;
    p += noncebytes;
    argv->k = (const unsigned char *)(p);

    if (ei_decode_binary(buffer, index, (void *)(argv->m), (long *)&(argv->mlen)) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->n), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_skip_term(buffer, index) < 0) {
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->k), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    request->argv = (void *)(argv);

    return 0;
}

static void
LS_API_EXEC(crypto_stream_chacha20, xor_ic)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, xor_ic) * argv;
    LS_API_READ_ARGV(crypto_stream_chacha20, xor_ic);
    unsigned char *c;

    c = (unsigned char *)(argv->m);

    (void)crypto_stream_chacha20_xor_ic(c, argv->m, argv->mlen, argv->n, argv->ic, argv->k);

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_BUF2BINARY, (ErlDrvTermData)(c), argv->mlen, ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}

/* crypto_stream_chacha20_ietf_noncebytes/0 */

static void
LS_API_EXEC(crypto_stream_chacha20, ietf_noncebytes)
{
    size_t ietf_noncebytes;

    ietf_noncebytes = crypto_stream_chacha20_ietf_noncebytes();

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_UINT, (ErlDrvUInt)(ietf_noncebytes), ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}

/* crypto_stream_chacha20_ietf/3 */

typedef struct LS_API_F_ARGV(crypto_stream_chacha20, ietf) {
    unsigned long long clen;
    const unsigned char *n;
    const unsigned char *k;
} LS_API_F_ARGV_T(crypto_stream_chacha20, ietf);

static int
LS_API_INIT(crypto_stream_chacha20, ietf)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, ietf) * argv;
    int skip;
    int type;
    int type_length;
    unsigned long long clen;
    size_t ietf_noncebytes;
    size_t keybytes;
    ErlDrvSizeT x;
    void *p;

    if (ei_decode_ulong(buffer, index, (unsigned long *)&(clen)) < 0) {
        return -1;
    }

    ietf_noncebytes = crypto_stream_chacha20_ietf_noncebytes();

    if (ei_get_type(buffer, index, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != ietf_noncebytes) {
        return -1;
    }

    skip = *index;

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    keybytes = crypto_stream_chacha20_keybytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != keybytes) {
        return -1;
    }

    x = (ErlDrvSizeT)(ietf_noncebytes + keybytes + (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, ietf))));
    p = (void *)(driver_alloc(x));

    if (p == NULL) {
        return -1;
    }

    argv = (LS_API_F_ARGV_T(crypto_stream_chacha20, ietf) *)(p);
    p += (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, ietf)));
    argv->clen = clen;
    argv->n = (const unsigned char *)(p);
    p += ietf_noncebytes;
    argv->k = (const unsigned char *)(p);

    if (ei_decode_binary(buffer, index, (void *)(argv->n), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->k), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    request->argv = (void *)(argv);

    return 0;
}

static void
LS_API_EXEC(crypto_stream_chacha20, ietf)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, ietf) * argv;
    LS_API_READ_ARGV(crypto_stream_chacha20, ietf);
    unsigned char *c;

    c = (unsigned char *)(driver_alloc((ErlDrvSizeT)(argv->clen)));

    if (c == NULL) {
        LS_FAIL_OOM(request->port->drv_port);
        return;
    }

    (void)crypto_stream_chacha20_ietf(c, argv->clen, argv->n, argv->k);

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_BUF2BINARY, (ErlDrvTermData)(c), argv->clen, ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);

    (void)driver_free(c);
}

/* crypto_stream_chacha20_ietf_xor/3 */

typedef struct LS_API_F_ARGV(crypto_stream_chacha20, ietf_xor) {
    const unsigned char *m;
    unsigned long long mlen;
    const unsigned char *n;
    const unsigned char *k;
} LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor);

static int
LS_API_INIT(crypto_stream_chacha20, ietf_xor)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor) * argv;
    int skip;
    int type;
    int type_length;
    unsigned long long mlen;
    size_t ietf_noncebytes;
    size_t keybytes;
    ErlDrvSizeT x;
    void *p;

    if (ei_get_type(buffer, index, &type, &type_length) < 0 || type != ERL_BINARY_EXT) {
        return -1;
    }

    mlen = (unsigned long long)(type_length);

    skip = *index;

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    ietf_noncebytes = crypto_stream_chacha20_ietf_noncebytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != ietf_noncebytes) {
        return -1;
    }

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    keybytes = crypto_stream_chacha20_keybytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != keybytes) {
        return -1;
    }

    x = (ErlDrvSizeT)(mlen + ietf_noncebytes + keybytes + (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor))));
    p = (void *)(driver_alloc(x));

    if (p == NULL) {
        return -1;
    }

    argv = (LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor) *)(p);
    p += (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor)));
    argv->m = (const unsigned char *)(p);
    p += mlen;
    argv->n = (const unsigned char *)(p);
    p += ietf_noncebytes;
    argv->k = (const unsigned char *)(p);

    if (ei_decode_binary(buffer, index, (void *)(argv->m), (long *)&(argv->mlen)) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->n), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->k), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    request->argv = (void *)(argv);

    return 0;
}

static void
LS_API_EXEC(crypto_stream_chacha20, ietf_xor)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor) * argv;
    LS_API_READ_ARGV(crypto_stream_chacha20, ietf_xor);
    unsigned char *c;

    c = (unsigned char *)(argv->m);

    (void)crypto_stream_chacha20_ietf_xor(c, argv->m, argv->mlen, argv->n, argv->k);

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_BUF2BINARY, (ErlDrvTermData)(c), argv->mlen, ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}

/* crypto_stream_chacha20_ietf_xor_ic/4 */

typedef struct LS_API_F_ARGV(crypto_stream_chacha20, ietf_xor_ic) {
    const unsigned char *m;
    unsigned long long mlen;
    const unsigned char *n;
    uint64_t ic;
    const unsigned char *k;
} LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor_ic);

static int
LS_API_INIT(crypto_stream_chacha20, ietf_xor_ic)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor_ic) * argv;
    int skip;
    int type;
    int type_length;
    unsigned long long mlen;
    size_t ietf_noncebytes;
    uint64_t ic;
    size_t keybytes;
    ErlDrvSizeT x;
    void *p;

    if (ei_get_type(buffer, index, &type, &type_length) < 0 || type != ERL_BINARY_EXT) {
        return -1;
    }

    mlen = (unsigned long long)(type_length);

    skip = *index;

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    ietf_noncebytes = crypto_stream_chacha20_ietf_noncebytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != ietf_noncebytes) {
        return -1;
    }

    if (ei_skip_term(buffer, &skip) < 0) {
        return -1;
    }

    if (ei_decode_ulong(buffer, &skip, (unsigned long *)&(ic)) < 0) {
        return -1;
    }

    keybytes = crypto_stream_chacha20_keybytes();

    if (ei_get_type(buffer, &skip, &type, &type_length) < 0 || type != ERL_BINARY_EXT || type_length != keybytes) {
        return -1;
    }

    x = (ErlDrvSizeT)(mlen + ietf_noncebytes + keybytes + (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor_ic))));
    p = (void *)(driver_alloc(x));

    if (p == NULL) {
        return -1;
    }

    argv = (LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor_ic) *)(p);
    p += (sizeof(LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor_ic)));
    argv->m = (const unsigned char *)(p);
    p += mlen;
    argv->n = (const unsigned char *)(p);
    argv->ic = ic;
    p += ietf_noncebytes;
    argv->k = (const unsigned char *)(p);

    if (ei_decode_binary(buffer, index, (void *)(argv->m), (long *)&(argv->mlen)) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->n), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    if (ei_skip_term(buffer, index) < 0) {
        return -1;
    }

    if (ei_decode_binary(buffer, index, (void *)(argv->k), NULL) < 0) {
        (void)driver_free(argv);
        return -1;
    }

    request->argv = (void *)(argv);

    return 0;
}

static void
LS_API_EXEC(crypto_stream_chacha20, ietf_xor_ic)
{
    LS_API_F_ARGV_T(crypto_stream_chacha20, ietf_xor_ic) * argv;
    LS_API_READ_ARGV(crypto_stream_chacha20, ietf_xor_ic);
    unsigned char *c;

    c = (unsigned char *)(argv->m);

    (void)crypto_stream_chacha20_ietf_xor_ic(c, argv->m, argv->mlen, argv->n, argv->ic, argv->k);

    ErlDrvTermData spec[] = {LS_RES_TAG(request), ERL_DRV_BUF2BINARY, (ErlDrvTermData)(c), argv->mlen, ERL_DRV_TUPLE, 2};

    LS_RESPOND(request, spec, __FILE__, __LINE__);
}
