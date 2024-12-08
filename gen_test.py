import random

def gen(n):
    tipo = random.randint(0, 1)
    tam_A = random.randint(1, 100)
    tam_B = random.randint(1, 100)

    m = 3*max(tam_A, tam_B)

    A = set(random.sample(range(m), tam_A))
    B = set(random.sample(range(m), tam_B))
    A_ = list(A)
    A_.sort()
    B_ = list(B)
    B_.sort()

    op = random.randint(1, 4)

    fin = open('cases/{}.in'.format(n), 'w')
    fout = open('cases/{}.out'.format(n), 'w')

    print(tipo, file=fin)
    print(tam_A, file=fin)
    print(tam_B, file=fin)

    for a in A_:
        print(a, end=' ', file=fin)
    print(file=fin)

    for b in B_:
        print(b, end=' ', file=fin)
    print(file=fin)

    print(op, file=fin)

    if op == 1:
        b = random.choice(B_)
        print(b, file=fin)
        if b in A:
            print('Pertence', file=fout)
        else:
            print('Nao pertence', file=fout)

    if op == 2:
        C = A | B
        C_ = list(C)
        C_.sort()
        for c in C_:
            print(c, end=', ', file=fout)
        print(file=fout)

    if op == 3:
        C = A & B
        C_ = list(C)
        C_.sort()
        for c in C_:
            print(c, end=', ', file=fout)
        print(file=fout)

    if op == 4:
        a = random.choice(A_)
        print(a, file=fin)
        C = A - {a}
        C_ = list(C)
        C_.sort()
        for c in C_:
            print(c, end=', ', file=fout)
        print(file=fout)

    fin.close()
    fout.close()

for n in range(1, 100):
    gen(n)