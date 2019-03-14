import pandas as pd
import matplotlib.pyplot as plt
import sys

X = pd.read_csv("saida.txt", header=-1, sep='\t')

plt.figure()
plt.subplots(figsize=[5, 5])
plt.subplots_adjust(left=0.15, right=0.99, top=0.99, bottom=0.11)
#plt.xlabel(r"$Time[ms]$", fontsize='16')
plt.xlabel(r"$%s$"%sys.argv[1], fontsize='16')
plt.ylabel(r"$%s$"%sys.argv[2], fontsize='16')
plt.plot(X[0], X[1])
plt.savefig('figura.eps', format='eps', dpi=5000, transparent = True)

