from statistics import mean, stdev, variance
from analysis import *

import matplotlib.pyplot as plt

def main():
    max_sim_people = 1000
    replication = 30
    data = []
    for i in range(replication):
        run_mm1(str(max_sim_people))
        data.append(get_sim_result())

    avg_data = []
    H = []
    LCU = []
    UCU = []
    for p in range(max_sim_people):
        avg_data.append( mean([data[rep][p] for rep in range(replication)]) )
        H.append( confidence_interval_half_width([data[j][p]\
            for j in range(replication)]))
        UCU.append(avg_data[p]+H[p])
        LCU.append(avg_data[p]-H[p])
        


    fig = plt.figure(0)
    x = [i for i in range(max_sim_people)]
    plt.errorbar(x, avg_data)
    #plt.errorbar(x, UCU)
    #plt.errorbar(x, LCU)
    plt.show()
    

if __name__ == "__main__":
    main()
