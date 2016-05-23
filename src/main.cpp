#include <string>
#include "SimpleQueue.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

void conflicting_options(const boost::program_options::variables_map & vm,
                         const std::string & opt1, const std::string & opt2)
{
    if (vm.count(opt1) && !vm[opt1].defaulted() &&
        vm.count(opt2) && !vm[opt2].defaulted())
    {
        throw std::logic_error(std::string("Conflicting options '") +
                               opt1 + "' and '" + opt2 + "'.");
    }
}

int main(int argc, char *argv[])
{
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")

    //options are passed from cmd line arguments
    ("max-number-of-sim-people", po::value<unsigned>(), "set the maximum number of people to be simulated")
    ("max-time-of-simulation", po::value<Time>(), "set the maximum simulation time")
    ("mean-of-interarrival-time", po::value<Time>(), "set the mean value of interarrival time")
    ("init-seed", po::value<unsigned>(), "set the seed for interarrival time randgen and service time randgen (use rand stream)")
    ("interarrival-time-rand-seed", po::value<unsigned>(), "set the seed for interarrival time randgen")
    ("service-time-rand-seed", po::value<unsigned>(), "set the seed for service time randgen")
    ("waiting-queue-depth", po::value<unsigned>(), "set the depth of waiting queue")

    //configurations are passed from a config file
    ("config-file", po::value<std::string>(), "set configurations from config file")

    //load simulation
    ("load", po::value<std::string>(), "load simulation from saved file")
    ("add-sim-people", po::value<unsigned>(), "set additional people to simulate")
    ;


  po::variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("config-file")) {
    std::ifstream config_file(vm["config-file"].as<std::string>());
    store(parse_config_file(config_file, desc), vm);
    notify(vm);
  }

  conflicting_options(vm, "init-seed", "interarrival-time-rand-seed");
  conflicting_options(vm, "init-seed", "service-time-rand-seed");
 
  //Default config values 
  auto max_people = 5;
  Time max_sim_time = 1000;
  unsigned init_seed = 10;
  unsigned interarrival_rand_seed = 0;
  unsigned service_time_rand_seed = 0;
  auto interarrival_time_mean = 11.0;
  unsigned waiting_queue_depth = 1000;
  std::string load_file("save.yaml");

  if (vm.count("help")) {
    std::cout << desc << std::endl;
  }

  SimpleQueueSim sqs;

  std::cout << std::endl;
  std::cout << "----------  Configurations ----------" << std::endl;
  //Load
  if (vm.count("load")) {
    load_file = vm["load"].as<std::string>();
    sqs.load_simulation(load_file);
    std::cout << "Load simulation from file: " << load_file<< std::endl;

    auto additional_people = vm["add-sim-people"].as<unsigned>();
    std::cout << "Add simulation people: " << additional_people << std::endl;
    sqs.increase_max_people(additional_people);
  }

  //New simulation
  else {
    if (vm.count("max-number-of-sim-people")) {
      max_people = vm["max-number-of-sim-people"].as<unsigned>();
    }
    if (vm.count("max-time-of-simulation")) {
      max_sim_time = vm["max-time-of-simulation"].as<Time>();
    }
    if (vm.count("mean-of-interarrival-time")) {
      interarrival_time_mean = vm["mean-of-interarrival-time"].as<Time>();
    }

    if (vm.count("init-seed")) {
      init_seed = vm["init-seed"].as<unsigned>();
    } 
    else if (vm.count("interarrival-time-rand-seed") && vm.count("service-time-rand-seed")) {
      interarrival_rand_seed = vm["interarrival-time-rand-seed"].as<unsigned>();

      service_time_rand_seed = vm["service-time-rand-seed"].as<unsigned>();
    } else {
    }

    if (vm.count("waiting-queue-depth")) {
      waiting_queue_depth = vm["waiting-queue-depth"].as<unsigned>();
    }

    std::cout << "Maximum number of simulated people: " << max_people << std::endl;
    std::cout << "Maximum simulation time: " << max_sim_time << std::endl;
    std::cout << "Mean of interarrival time: " << interarrival_time_mean << std::endl;
    std::cout << "Depth of waiting queue: " << waiting_queue_depth << std::endl;

    sqs.set_max_people(max_people);
    sqs.set_max_sim_time(max_sim_time);
    sqs.set_interarrival_lambda(1.0 / interarrival_time_mean);
    sqs.set_queue_depth(waiting_queue_depth);
    if (vm.count("interarrival-time-rand-seed") && vm.count("service-time-rand-seed")) {
      std::cout << "Interarrival time rand seed: " << interarrival_rand_seed << std::endl;
      sqs.set_interarrival_rand_seed(interarrival_rand_seed);
      sqs.set_service_rand_seed(service_time_rand_seed);
    }
    else {
      std::cout << "Init seed: " << init_seed << std::endl;
      sqs.set_seed(init_seed);
    }
  }
  std::cout << "--------------------------------------\n" << std::endl;




  sqs.run();
  sqs.save_simulation();

  return 0;
}
