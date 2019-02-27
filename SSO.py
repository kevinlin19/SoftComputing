import numpy as np
import time
# parameters
MaxNsol = 300
MaxNvar = 150


global Nrun
global Ngen
global Nsol
global Nvar
Nrun = 50
Ngen = 1000
Nsol = 100
Nvar = 30

Cg = 0.4
Cp = 0.7
Cw = 0.9

Xub = 100
Xlb = -100

global X
global P
global F
global pF

X = np.zeros(shape=(MaxNsol, MaxNvar))
P = np.zeros(shape=(MaxNsol, MaxNsol))
F = np.zeros(shape=(MaxNsol,))
pF = np.zeros(shape=(MaxNsol,))

def FIT_cal(XX):
    SUM = 0 # inital sum
    for var in range(Nvar):
        SUM += XX[var]*XX[var] - XX[var] # fitness function x**2
    return SUM


def SSO_init():
    gBest = 0
    for sol in range(Nsol):
        for var in range(Nsol):
            P[sol][var] = X[sol][var] = (Xub - Xlb) * np.random.random() + Xlb

        F[sol] = FIT_cal(X[sol])
        if F[sol] < F[gBest]:
            gBest = sol


def SSO_update(Nsol=100, Nvar=30):
    gBest = 0

    for sol in range(Nsol):

        for var in range(Nvar):
            rnd = np.random.random()
            if rnd < Cg:
                X[sol][var] = P[gBest][var]
            elif rnd < Cp:
                X[sol][var] = P[sol][var]
            elif rnd > Cw:
                X[sol][var] = (Xub-Xlb) * np.random.random() + Xlb

        F[sol] = FIT_cal(X[sol])
        if F[sol] < pF[sol]:
            pF[sol] = F[sol]
            if F[sol] < pF[gBest]:
                gBest = sol
    return gBest


def OUTPUT(run, start):
    print('SSO {0} {1} {2}'.format(run, time.time() - start, pF[gBest]))
    # print('{} \n'.format(pF[gBest]))


if __name__ == '__main__':

    for run in range(Nrun):
        SSO_init()
        # print(P[0])
        start = time.time()
        for gen in range(Ngen):
            gen_1 = gen + 1
            gBest = SSO_update()
        OUTPUT(run, start)