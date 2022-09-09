typename_to_type = {
    'char':       'char',
    'schar':      'signed char',
    'short':      'short',
    'int':        'int',
    'long':       'long',
    'longlong':   'long long',
    'ptrdiff':    'ptrdiff_t',
    'uchar':      'unsigned char',
    'ushort':     'unsigned short',
    'uint':       'unsigned int',
    'ulong':      'unsigned long',
    'ulonglong':  'unsigned long long',
    'size':       'size_t',
    'int8':       'int8_t',
    'int16':      'int16_t',
    'int32':      'int32_t',
    'int64':      'int64_t',
    'uint8':      'uint8_t',
    'uint16':     'uint16_t',
    'uint32':     'uint32_t',
    'uint64':     'uint64_t',
    'float':      'float',
    'double':     'double',
    'longdouble': 'long double',
    'complexf':   'float _Complex',
    'complexd':   'double _Complex',
}

typesizes_rma = (
    8,
    16,
    32,
    64,
    128,
)

# Table 5
typenames_rma = (
    'float',
    'double',
    'longdouble',
    'char',
    'schar',
    'short',
    'int',
    'long',
    'longlong',
    'uchar',
    'ushort',
    'uint',
    'ulong',
    'ulonglong',
    'int8',
    'int16',
    'int32',
    'int64',
    'uint8',
    'uint16',
    'uint32',
    'uint64',
    'size',
    'ptrdiff',
)

# Table 6
typenames_amo_std = (
    'int',
    'long',
    'longlong',
    'uint',
    'ulong',
    'ulonglong',
    'int32',
    'int64',
    'uint32',
    'uint64',
    'size',
    'ptrdiff',
)

# Table 7
typenames_amo_ext = (
    'float',
    'double',
) + typenames_amo_std

# Table 8
typenames_amo_bit = (
    'uint',
    'ulong',
    'ulonglong',
    'int32',
    'int64',
    'uint32',
    'uint64',
)

# Table 10
typenames_reduce = {
    'char':       "           max min sum prod".split(),
    'schar':      "           max min sum prod".split(),
    'short':      "           max min sum prod".split(),
    'int':        "           max min sum prod".split(),
    'long':       "           max min sum prod".split(),
    'longlong':   "           max min sum prod".split(),
    'ptrdiff':    "           max min sum prod".split(),
    'uchar':      "and or xor max min sum prod".split(),
    'ushort':     "and or xor max min sum prod".split(),
    'uint':       "and or xor max min sum prod".split(),
    'ulong':      "and or xor max min sum prod".split(),
    'ulonglong':  "and or xor max min sum prod".split(),
    'int8':       "and or xor max min sum prod".split(),
    'int16':      "and or xor max min sum prod".split(),
    'int32':      "and or xor max min sum prod".split(),
    'int64':      "and or xor max min sum prod".split(),
    'uint8':      "and or xor max min sum prod".split(),
    'uint16':     "and or xor max min sum prod".split(),
    'uint32':     "and or xor max min sum prod".split(),
    'uint64':     "and or xor max min sum prod".split(),
    'size':       "and or xor max min sum prod".split(),
    'float':      "           max min sum prod".split(),
    'double':     "           max min sum prod".split(),
    'longdouble': "           max min sum prod".split(),
    'complexd':   "                   sum prod".split(),
    'complexf':   "                   sum prod".split(),
}


rma_elem = """
void shmem_ctx_{TYPENAME}_p(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
{TYPE} shmem_ctx_{TYPENAME}_g(shmem_ctx_t ctx, const {TYPE} *source, int pe);
"""  # noqa

rma_type = """
void shmem_ctx_{TYPENAME}_{RMA}(shmem_ctx_t ctx, {TYPE} *dest, const {TYPE} *source, size_t count, int pe);
void shmem_ctx_{TYPENAME}_i{RMA}(shmem_ctx_t ctx, {TYPE} *dest, const {TYPE} *source, ptrdiff_t dst, ptrdiff_t sst, size_t count, int pe);
void shmem_ctx_{TYPENAME}_{RMA}_nbi(shmem_ctx_t ctx, {TYPE} *dest, const {TYPE} *source, size_t count, int pe);
"""  # noqa

rma_size = """
void shmem_ctx_{RMA}{SIZE}(shmem_ctx_t ctx, void *dest, const void *source, size_t count, int pe);
void shmem_ctx_i{RMA}{SIZE}(shmem_ctx_t ctx, void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t count, int pe);
void shmem_ctx_{RMA}{SIZE}_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t count, int pe);
"""  # noqa

rma_mem = """
void shmem_ctx_{RMA}mem(shmem_ctx_t ctx, void *dest, const void *source, size_t count, int pe);
void shmem_ctx_{RMA}mem_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t count, int pe);
"""  # noqa

amo_type_std = """
{TYPE} shmem_ctx_{TYPENAME}_atomic_compare_swap(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} cond, {TYPE} value, int pe);
{TYPE} shmem_ctx_{TYPENAME}_atomic_fetch_inc(shmem_ctx_t ctx, {TYPE} *dest, int pe);
void shmem_ctx_{TYPENAME}_atomic_inc(shmem_ctx_t ctx, {TYPE} *dest, int pe);
{TYPE} shmem_ctx_{TYPENAME}_atomic_fetch_add(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_add(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_compare_swap_nbi(shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, {TYPE} cond, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_fetch_inc_nbi(shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, int pe);
void shmem_ctx_{TYPENAME}_atomic_fetch_add_nbi(shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, {TYPE} value, int pe);
"""  # noqa

amo_type_ext = """
{TYPE} shmem_ctx_{TYPENAME}_atomic_fetch(shmem_ctx_t ctx, const {TYPE} *source, int pe);
void shmem_ctx_{TYPENAME}_atomic_set(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
{TYPE} shmem_ctx_{TYPENAME}_atomic_swap(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_fetch_nbi(shmem_ctx_t ctx, {TYPE} *fetch, const {TYPE} *source, int pe);
void shmem_ctx_{TYPENAME}_atomic_swap_nbi(shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, {TYPE} value, int pe);
"""  # noqa

amo_type_bit = """
{TYPE} shmem_ctx_{TYPENAME}_atomic_fetch_and(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_and(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
{TYPE} shmem_ctx_{TYPENAME}_atomic_fetch_or(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_or(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
{TYPE} shmem_ctx_{TYPENAME}_atomic_fetch_xor(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_xor(shmem_ctx_t ctx, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_fetch_and_nbi(shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_fetch_or_nbi (shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, {TYPE} value, int pe);
void shmem_ctx_{TYPENAME}_atomic_fetch_xor_nbi(shmem_ctx_t ctx, {TYPE} *fetch, {TYPE} *dest, {TYPE} value, int pe);
"""  # noqa

sig_type = """
void shmem_ctx_{TYPENAME}_{RMA}_signal(shmem_ctx_t ctx, {TYPE} *dest, const {TYPE} *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
void shmem_ctx_{TYPENAME}_{RMA}_signal_nbi(shmem_ctx_t ctx, {TYPE} *dest, const {TYPE} *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
"""  # noqa: E501

sig_size = """
void shmem_ctx_{RMA}{SIZE}_signal(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
void shmem_ctx_{RMA}{SIZE}_signal_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
"""  # noqa

sig_mem = """
void shmem_ctx_{RMA}mem_signal(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
void shmem_ctx_{RMA}mem_signal_nbi(shmem_ctx_t ctx, void *dest, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
"""  # noqa

coll_type = """
int shmem_{TYPENAME}_broadcast(shmem_team_t team, {TYPE} *dest, const {TYPE} *source, size_t nelems, int pe_root);
int shmem_{TYPENAME}_collect(shmem_team_t team, {TYPE} *dest, const {TYPE} *source, size_t nelems);
int shmem_{TYPENAME}_fcollect(shmem_team_t team, {TYPE} *dest, const {TYPE} *source, size_t nelems);
int shmem_{TYPENAME}_alltoall(shmem_team_t team, {TYPE} *dest, const {TYPE} *source, size_t nelems);
int shmem_{TYPENAME}_alltoalls(shmem_team_t team, {TYPE} *dest, const {TYPE} *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
"""  # noqa

coll_mem = """
int shmem_broadcastmem(shmem_team_t team, void *dest, const void *source, size_t nelems, int pe_root);
int shmem_collectmem(shmem_team_t team, void *dest, const void *source, size_t nelems);
int shmem_fcollectmem(shmem_team_t team, void *dest, const void *source, size_t nelems);
int shmem_alltoallmem(shmem_team_t team, void *dest, const void *source, size_t nelems);
int shmem_alltoallsmem(shmem_team_t team, void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
"""  # noqa

reduce_ops = ('and', 'or', 'xor', 'max', 'min', 'sum', 'prod')
reduce_team = """
int shmem_{TYPENAME}_{OP}_reduce(shmem_team_t team, {TYPE} *dest, const {TYPE} *source, size_t nreduce);
"""  # noqa

wait = """
void shmem_{TYPENAME}_wait_until({TYPE} *ivar, int cmp, {TYPE} cmp_value);
void shmem_{TYPENAME}_wait_until_all({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} cmp_value);
size_t shmem_{TYPENAME}_wait_until_any({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} cmp_value);
size_t shmem_{TYPENAME}_wait_until_some({TYPE} *ivars, size_t nelems, size_t *indices, const int *status, int cmp, {TYPE} cmp_value);
void shmem_{TYPENAME}_wait_until_all_vector({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} *cmp_values);
size_t shmem_{TYPENAME}_wait_until_any_vector({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} *cmp_values);
size_t shmem_{TYPENAME}_wait_until_some_vector({TYPE} *ivars, size_t nelems, size_t *indices, const int *status, int cmp, {TYPE} *cmp_values);
"""  # noqa

test = """
int shmem_{TYPENAME}_test({TYPE} *ivar, int cmp, {TYPE} cmp_value);
int shmem_{TYPENAME}_test_all({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} cmp_value);
size_t shmem_{TYPENAME}_test_any({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} cmp_value);
size_t shmem_{TYPENAME}_test_some({TYPE} *ivars, size_t nelems, size_t *indices, const int *status, int cmp, {TYPE} cmp_value);
int shmem_{TYPENAME}_test_all_vector({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} *cmp_values);
size_t shmem_{TYPENAME}_test_any_vector({TYPE} *ivars, size_t nelems, const int *status, int cmp, {TYPE} *cmp_values);
size_t shmem_{TYPENAME}_test_some_vector({TYPE} *ivars, size_t nelems, size_t *indices, const int *status, int cmp, {TYPE} *cmp_values);
"""  # noqa


def apigen(template, ctx=False, **kwargs):
    if not ctx:
        template = template.replace('(shmem_ctx_t ctx, ', '(')
        template = template.replace('shmem_ctx_', 'shmem_')
    if 'TYPENAME' in kwargs:
        typename = kwargs['TYPENAME']
        kwargs['TYPE'] = typename_to_type[typename]
    return template.format(**kwargs)


def generate():
    # typedefs
    for typename, ctype in typename_to_type.items():
        if ctype != typename:
            yield f'typedef {ctype} {typename};'

    # RMA
    for ctx in (True, False):
        for typename in typenames_rma:
            yield apigen(rma_elem, ctx, TYPENAME=typename)
        for typename in typenames_rma:
            yield apigen(rma_type, ctx, TYPENAME=typename, RMA='put')
            yield apigen(rma_type, ctx, TYPENAME=typename, RMA='get')
        for size in typesizes_rma:
            yield apigen(rma_size, ctx, SIZE=size, RMA='put')
            yield apigen(rma_size, ctx, SIZE=size, RMA='get')
        yield apigen(rma_mem, ctx, RMA='put')
        yield apigen(rma_mem, ctx, RMA='get')

    # AMO
    for ctx in (True, False):
        for typenames, amo_type in (
            (typenames_amo_std, amo_type_std),
            (typenames_amo_ext, amo_type_ext),
            (typenames_amo_bit, amo_type_bit),
        ):
            for typename in typenames:
                yield apigen(amo_type, ctx, TYPENAME=typename)

    # SIG
    for ctx in (True, False):
        for typename in typenames_rma:
            yield apigen(sig_type, ctx, TYPENAME=typename, RMA='put')
        for size in typesizes_rma:
            yield apigen(sig_size, ctx, SIZE=size, RMA='put')
        yield apigen(sig_mem, ctx, RMA='put')

    # Collectives
    for typename in typenames_rma:
        yield apigen(coll_type, True, TYPENAME=typename)
    yield apigen(coll_mem, True)

    # Reductions
    for typename in typenames_reduce:
        for op in reduce_ops:
            if op in typenames_reduce[typename]:
                yield apigen(reduce_team, False, TYPENAME=typename, OP=op)

    # P2P synchronization
    yield 'const size_t SIZE_MAX;'
    for typename in typenames_amo_std:
        yield apigen(wait, TYPENAME=typename)
        yield apigen(test, TYPENAME=typename)


if __name__ == '__main__':
    for code in generate():
        print(code.strip(), end='\n')
