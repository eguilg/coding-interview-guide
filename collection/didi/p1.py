def process_vals(out, vals, indices):
    vals.sort(reverse=True)
    indices.sort()

    for val, idx in zip(vals, indices):
        out[idx] = str(val)
    vals.clear()
    indices.clear()


def solve(tokens):
    pro = dict(zip('*/+-#', [2, 2, 1, 1, 0]))
    out = []
    ops = []
    ops.append('#')
    op_set = set(list('*/+-'))
    for token in tokens:
        if token in op_set:
            while pro[token] <= pro[ops[-1]]:
                t = ops.pop()
                out.append(t)

            ops.append(token)
        else:
            out.append(token)

    while len(ops) > 0:
        out.append(ops.pop())

    out.reverse()
    vals = []
    indices = []
    last_pro = 0
    l = 1
    while l < len(out):
        token = out[l]
        if token in op_set:
            if pro[token] != last_pro:
                process_vals(out, vals, indices)
            last_pro = pro[token]
        else:
            vals.append(int(token))
            indices.append(l)
        l += 1
    process_vals(out, vals, indices)
    out.reverse()
    return out[:-1]


def restore(tokens):
    out = []
    op_set = set(list('*/+-'))
    s = []
    for token in tokens:
        if token in op_set:
            num2, num1 = s.pop(), s.pop()
            if num1 != '#':
                out.append(num1)
            out.append(token)
            if num2 != '#':
                out.append(num2)
            r = '#'
            s.append(r)
        else:
            s.append(token)
    return out


def solve5(tokens):
    calc = {
        '*': lambda x, y: x * y,
        '/': lambda x, y: x / y,
        '+': lambda x, y: x + y,
        '-': lambda x, y: x - y
    }
    op_set = set(list('*/+-'))
    s = []
    for token in tokens:
        if token in op_set:
            num2, num1 = s.pop(), s.pop()
            r = calc[token](float(num1), float(num2))
            s.append(r)
        else:
            s.append(token)

    return s.pop()


# bds1 = '44 * -15 * 100 - 3 + 2 + 1 + -4 * -5 * 10 + 1'  # abcd^/+e-
bds1 = '3 + 2 + 1 + -4 * -5 + 1'  # abcd^/+e-
tokens = bds1.split(' ')
print(' '.join(solve(tokens)))
print((solve5(solve(tokens))))
print(' '.join(restore(solve(tokens))))
