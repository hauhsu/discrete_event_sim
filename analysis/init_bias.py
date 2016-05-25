from statistics import mean, stdev, variance
from mm1q import *

import matplotlib.pyplot as plt

def main():
    max_sim_people = 5000
    replication = 30
    data = []
    i_seed = 1
    s_seed = 9
    for i in range(replication):
        run_mm1q(max_sim_people, i_seed=i_seed, s_seed=s_seed)
        i_seed, s_seed = get_seeds_from_save('save.yaml')
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
