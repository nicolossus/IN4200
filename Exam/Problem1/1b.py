import numpy as np

N = 5
P = 3


T1 = np.ceil((N**2 - P) / P + P)
T2 = (N**2 - 1) // P + P
T3 = np.floor(N**2 / P) + N**2 % P

print(np.floor((N**2 - 1) / P) + P)
print(np.floor(N**2 / P) + P)
print((N**2 - 1) // P)

print('T1:', T1)
print('T2:', T2)
print('T3', T3)


def cT(P, N=5):
    return (N**2 - 1) // P + P


def cT2(P, N=5):
    return np.floor((N**2 - 1) / P) + P


def cT3(P, N=5):
    return np.ceil((N**2 - P) / P) + P


P = [i for i in range(1, 26)]

for i in range(len(P)):
    T = cT(P[i])
    print(f"cT1 | Workers: {P[i]} | Time: {T}")
    T2 = cT2(P[i])
    print(f"cT2 | Workers: {P[i]} | Time: {T2}")
    print(np.floor((N**2 - 1) / P[i]))
    T3 = cT3(P[i])
    print(f"cT3 | Workers: {P[i]} | Time: {T3}")
    print(np.ceil((N**2 - P[i]) / P[i]))
    print("")
