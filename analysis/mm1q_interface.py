import yaml
from subprocess import call

def run_mm1q(people='10', interarrival_mean='11', **args):

    output = None
    if 'verbose' in args and args['verbose'] == 'False':
        output = open('/dev/null', 'w') 
        

    if 'i_seed' in args:
        interarrival_time_rand_seed = args['i_seed']

        if 's_seed' in args:
            service_time_rand_seed = args['s_seed']
            call(['../build/MM1QueueSimulator', 
                  '--max-number-of-sim-people', people, 
                  '--mean-of-interarrival-time', interarrival_mean,
                  '--interarrival-time-rand-seed', interarrival_time_rand_seed,
                  '--service-time-rand-seed', service_time_rand_seed],
                stdout=output)
        else:
            raise RuntimeError('i_seed and s_seed should both be provided.')

    elif 'init_seed' in args:
        init_seed = args['init_seed']

        call(['../build/MM1QueueSimulator', 
              '--max-number-of-sim-people', people, 
              '--mean-of-interarrival-time', interarrival_mean,
              '--init-seed', init_seed],
            stdout=output)

    else:
        call(['../build/MM1QueueSimulator', 
              '--max-number-of-sim-people', people, 
              '--mean-of-interarrival-time', interarrival_mean],
            stdout=output)

def run_mm1q_load(save_file, add_people, verbose=False):

    output = None
    if not verbose:
        output = open('/dev/null', 'w') 


    call(['../build/MM1QueueSimulator', 
          '--load', save_file,
          '--add-sim-people', add_people],
          stdout = output)


def get_seeds_from_save(save_file):
    with open(save_file) as save:
        configs = yaml.load_all(save)
        next(configs)
        config = next(configs)
        return (config['interarrival time seed'], 
                config['service time seed'])


def get_sim_result(bias=0):
    yi = []
    with open('person_sys_time.txt') as p_sys_time_file:
        for line in p_sys_time_file:
           yi.append(float(line)) 

    return yi[bias:]
