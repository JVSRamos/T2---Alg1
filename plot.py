import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline, BSpline

line = ''
COLORS = ['r', 'g', 'k', 'b', 'm', 'y']
DS_VALUES = list()
N_SIZES = [100, 1000, 10000]
with open("tabelas.txt", "r") as inp:
    for _ in range(9):
        while True:
            line = inp.readline()
            GRAPH_TITLE = line.replace("Tabela", "Gráfico")
            line = inp.readline()
            for i in range(6):
                DS_VALUES = list(inp.readline().split())
                DS_VALUES[1:4] = [float(x) for x in DS_VALUES[1:4]]
                plt.plot(N_SIZES, DS_VALUES[1:4], label=DS_VALUES[0], color=COLORS[i])

            inp.readline()
            #plt.xscale("log")
            plt.yscale("log")
            plt.title(GRAPH_TITLE)
            plt.legend()
            plt.show()
            break
