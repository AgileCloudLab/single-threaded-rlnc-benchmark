import sys

from os import listdir

def get_all_config_files(config_dir):

    return listdir(config_dir)

def generate_experiment_string(experiment_name,platform):

    return './build/{!s}/{!s}'.format(platform,experiment_name)

def generate_commands(cmd, conf_path, configs, results):
    res = list()
    for conf in configs:
        res.append(cmd + ' {!s}{!s} {!s}\n'.format(conf_path, conf, results))
    return res

def write_to_file(commands, experiment_name):
    with open('RUN_{!s}.sh'.format(experiment_name), 'a') as f:
        for cmd in commands:
            f.write(cmd)
            f.write('sleep 10\n')

config_dir = input('Configuration dir: ')
experiment_name = input('experiment name: ')
platform = input('Platform: ')
results = input('Result dir: ')

configs = get_all_config_files(config_dir)
cmd = generate_experiment_string(experiment_name,platform)

commands = generate_commands(cmd, config_dir, configs, results)

write_to_file(commands, experiment_name)
