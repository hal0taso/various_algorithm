def is_LLL_reduced(B, c = 2):
    n = B.nrows()
    m = B.ncols()
    U = matrix(RR, m, m)
    O = matrix(RR, n, m)
    for i in range(0, m) :
        U[i,i] = 1
        O.set_column(i, B.column(i))
        for j in range(0, i) :
            U[j,i] = (B.column(i)*O.column(j)) / (O.column(j)*O.column(j))
            O.set_column(i, O.column(i) - U[j,i]*O.column(j))
    for i in range(0, m-1) :
        if O.column(i)*O.column(i) > c*O.column(i+1)*O.column(i+1) :
            return False
        return True


def reduce(i, B, U):
    j = i-1
    while j >= 0 :
        B.set_column(i, B.column(i) - round(U[j,i])*B.column(j))
        U.set_column(i, U.column(i) - round(U[j,i])*U.column(j))
        j=j-1


def LLL(B, c = 2):
    n = B.nrows()
    m = B.ncols()
    U = matrix(RR, m, m)
    O = matrix(RR, n, m)
    for i in range(0, m) :
        U[i,i] = 1
        O.set_column(i, B.column(i))
        for j in range(0, i) :
            U[j,i] = (B.column(i)*O.column(j)) / (O.column(j)*O.column(j))
            O.set_column(i, O.column(i) - U[j,i]*O.column(j))
            reduce(i, B, U)
        i=0
        while i < m-1 :
            if O.column(i)*O.column(i) <= c*O.column(i+1)*O.column(i+1) :
                i=i+1
            else :
                O.set_column(i+1, O.column(i+1) + U[i,i+1]*O.column(i))
                U[i,i] = (B.column(i)*O.column(i+1)) / (O.column(i+1)*O.column(i+1))
                U[i+1,i] = 1
                U[i, i+1] = 1
                U[i+1,i+1] = 0
                O.set_column(i, O.column(i)-U[i,i]*O.column(i+1))
                U.swap_columns(i,i+1)
                O.swap_columns(i,i+1)
                B.swap_columns(i,i+1)
                for k in range(i+2, m) :
                    U[i,k] = (B.column(k)*O.column(i)) / (O.column(i)*O.column(i))
                    U[i+1, k] = (B.column(k)*O.column(i+1)) / (O.column(i+1)*O.column(i+1))
                    if abs(U[i,i+1]) > 0.5 : reduce(i+1, B, U)
                    i = max(i-1,0)
                return B

### LLL test
runtimes = []   
for i in range(0, 39) :
    runtimes.append(0.0)
    for k in range(0, 10) :
        r=0
        while r != i+2 :
            A = random_matrix(ZZ, i+2)
            r = A.rank()
        t = cputime()
        res = LLL(A)
        runtimes[i] = runtimes[i] + cputime(t)*0.1
        if is_LLL_reduced(res) == False :
            print("LLL FAILURE")
print(runtimes)
