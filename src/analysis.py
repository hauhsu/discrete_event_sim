from scipy.stats import t
from subprocess import call


def run_mm1(interarrival_time_lambda):
    with open('next_seed.txt') as seed_file:
        seed = seed_file.readline()

    call(['./a.out', '100', seed, interarrival_time_lambda])



def average(nums):
    return sum(nums) / len(nums)

def variance(nums):

    if (len(nums) == 1):
        return 0 

    avg = average(nums)
    tmp = [(num - avg) ** 2 for num in nums]

    return  (sum(tmp) / (len(nums)-1))**0.5

def run_1_replication(interarrival_time_lambda):
    run_mm1(interarrival_time_lambda)
    yi= []
    with open('person_sys_time.txt') as p_sys_time_file:
        for line in p_sys_time_file:
           yi.append(int(line)) 
    yi_average = sum(yi) / len(yi) 

    return yi_average

def compute_ci(interarrival_time_lambda):
    epsilon = 1
    replication = 1


    yi_average_list = []
    yi_average_list.append(run_1_replication(interarrival_time_lambda))

    while epsilon > 0.5:
        
        ## Across replications
        yi_average_list.append(run_1_replication)
        Yi_average = average(yi_average_list)
        Yi_variance = variance(yi_average_list)


        alpha = 0.9 
        t_interval = t.interval(alpha, len(Yi)-1)[1]
        epsilon = (t_interval * variance / (replication ** 0.5)) / average

        replication += 1

    print
    print '----- Analysis -----'
    print 'sample mean: ', Yi_average 
    print 'sample variance: ', Yi_variance 
    print 'epsilon: ', epsilon
    print 'replication: ', replication
    print '--------------------'

    with open('analysis_{}'.format(interarrival_time_lambda), 'w') as analysis_file:
        analysis_file.write(str(Yi_average)+'\n')
        analysis_file.write(str(Yi_variance)+'\n')
        analysis_file.write(str(epsilon)+'\n')
        analysis_file.write(str(replication)+'\n')

if __name__ == "__main__":

    compute_ci('5')
    #for i in range(3, 8):
    #    compute_ci(str(i))
