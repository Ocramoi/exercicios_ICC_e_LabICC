import matplotlib.pyplot as plt
import numpy as np
import sys

def main():
    if len(sys.argv) != 2:
        print("Passe o nome do arquivo txt e somente ele!")
        exit(1)

    try:
        linhas = open(sys.argv[1], "r").readlines()
    except:
        print("Não foi possível abrir o arquivo!")
        exit(1)
    
    vals = np.array([[float(x) for x in tup.split()] for tup in linhas])
    vals = vals[vals[:,0].argsort()]
    
    plt.title(sys.argv[1].split(".")[0])
    plt.ylabel("Segundos")
    plt.xlabel("Qnt elementos")
    plt.xticks(rotation=45)
    plt.plot(vals[:, 0], vals[:, 1])
    plt.tight_layout()
    plt.savefig("{}.jpg".format(sys.argv[1].split(".")[0]))

if __name__ == "__main__":
    main()