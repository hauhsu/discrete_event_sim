from scipy.stats import t
from subprocess import call
from statistics import mean, stdev, variance
import matplotlib.pyplot as plt

interarrival_mean = 12
def run_mm1(sim_people='10'):
    global interarrival_mean
    try:
        seed_file = open('next_seed.txt')
        seed = seed_file.readline()

    except FileNotFoundError:
        seed = '100'


    devnull = open('/dev/null', 'w')
    call(['./a.out', sim_people, seed, str(interarrival_mean)],
        stdout=devnull)


def get_sim_result(bias=0):
    yi = []
    with open('person_sys_time.txt') as p_sys_time_file:
        for line in p_sys_time_file:
           yi.append(float(line)) 

    return yi[bias:]

def confidence_interval_half_width(data, confidence=0.95):
    n = len(data)
    standard_deviation = stdev(data)
    avg = mean(data)

    return t.interval(confidence, n-1)[1] * (standard_deviation / n**0.5)


def ci_with_precision(l=12, confidence=0.95, precision=0.9):
    global interarrival_mean
    interarrival_mean = l
    run_mm1('30')
    data = get_sim_result()

    Yi_average = mean(data)
    Yi_variance = variance(data)
    epsilon = confidence_interval_half_width(data, confidence) / mean(data)
    replication = 1

    if  epsilon > (1-precision):
        epsilon = 1
        yi_average_list = [mean(data)]

        while epsilon > (1-precision):
            run_mm1('300')
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
