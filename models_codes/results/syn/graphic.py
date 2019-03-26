import pandas as pd
import matplotlib.pyplot as plt
import sys

X = pd.read_csv("saida.txt", header=-1, sep='\t')

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
plt.xlabel(r"$Tempo[ms]$", fontsize='16')
plt.ylabel(r"$Potencial[mV]$", fontsize='16')
plt.plot(X[0], X[1], color='black')
plt.savefig('results/syn/syn_Vpre.eps', format='eps', dpi=5000, transparent = True)

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
plt.xlabel(r"$Tempo[ms]$", fontsize='16')
plt.ylabel(r"$T[mM]$", fontsize='16')
plt.plot(X[0], X[2], color='black')
plt.savefig('results/syn/syn_TA.eps', format='eps', dpi=5000, transparent = True)

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
plt.xlabel(r"$Tempo[ms]$", fontsize='16')
plt.ylabel(r"$r[1]$", fontsize='16')
plt.plot(X[0], X[3], color='black')
plt.savefig('results/syn/syn_rB.eps', format='eps', dpi=5000, transparent = True)

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
plt.xlabel(r"$Tempo[ms]$", fontsize='16')
plt.ylabel(r"$Potencial[mV]$", fontsize='16')
plt.plot(X[0], X[4], color='black')
plt.savefig('results/syn/syn_Vpos.eps', format='eps', dpi=5000, transparent = True)

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
plt.xlabel(r"$Tempo[ms]$", fontsize='16')
plt.ylabel(r"$T[mM]$", fontsize='16')
plt.plot(X[0], X[5], color='black')
plt.savefig('results/syn/syn_TB.eps', format='eps', dpi=5000, transparent = True)

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
plt.xlabel(r"$Tempo[ms]$", fontsize='16')
plt.ylabel(r"$r[1]$", fontsize='16')
plt.plot(X[0], X[6], color='black')
plt.savefig('results/syn/syn_rA.eps', format='eps', dpi=5000, transparent = True)



