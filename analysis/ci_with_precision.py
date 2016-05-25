from scipy.stats import t
from subprocess import call
from statistics import mean, stdev, variance
import matplotlib.pyplot as plt

from mm1q import *




def ci_with_precision(l=12, confidence=0.95, precision=0.9):

    sim_people = 300
    run_mm1q(people = sim_people, interarrival_mean = l)
    data = get_sim_result()

    Yi_average = mean(data)
    Yi_variance = variance(data)
    epsilon = confidence_interval_half_width(data, confidence) / mean(data)
    replication = 1

    if  epsilon > (1-precision):
        epsilon = 1
        yi_average_list = [mean(data)]

        while epsilon > (1-precision):
            i_seed, s_seed = get_seeds_from_save('save.yaml')
            run_mm1q(people = sim_people, interarrival_mean = l, 
                    i_seed = i_seed, s_seed = s_seed)
            data = get_sim_result()
            yi_average_list.append( mean(data) )
            Yi_average = mean(yi_average_list)
            Yi_variance = variance(yi_average_list)

            
            epsilon = confidence_interval_half_width(yi_average_list)\
                                                    / mean(yi_average_list)

            replication += 1

    print()
    print( '----- Analysis -----')
    print( 'sample mean: ', Yi_average )
    print( 'sample variance: ', Yi_variance )
    print( 'epsilon: ', epsilon)
    print( 'replication: ', replication)
    print( '--------------------')


    return Yi_average, epsilon


def plot(x, y, epsilon):
    fig = plt.figure(0)
    plt.errorbar(x, y, yerr=epsilon)
    plt.show()

def main():
    x = []
    y = []
    epsilon = []
    for i in range(100, 10, -1):
        result = ci_with_precision(l = i)
        x.append(10/i)
        y.append(result[0])
        epsilon.append(result[1])

    plot(x, y, epsilon)

    

if __name__ == "__main__":
    main()
