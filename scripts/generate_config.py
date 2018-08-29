import sys

one_kb = 1024
one_mb = 1024 * one_kb
one_gb = 1024 * one_mb

def generate_file_name(data_size, data_unit, iterations, finite_field, threads, generation_sizes, file_format):

    # TODO: Update to new formating
    name = '{!s}_{!s}_{!s}_{!s}_{!s}_{!s}.{!s}'.format(data_size, data_unit, iterations, finite_field, threads, "_".join(str(gen) for gen in generation_sizes), file_format)
    return name

def convert_data_size_to_bytes(data_size, unit):

    if unit == 'b':
        return data_size
    elif unit == 'k':
        return data_size * one_kb
    elif unit == 'm':
        return data_size * one_mb
    elif unit == 'g':
        return data_size * one_gb
    else:
        print('Unsupported data unit, falling back to bytes')
        return data_size

def assert_valid_generation_size(generation_sizes, data_size):

    for gen in generation_sizes:
        if not gen < data_size and data_size % gen == 0:
            return False
    return True

def calculate_symbol_size(generation_sizes, data_size):

    obj = {}
    for gen in generation_sizes:
        obj[gen] = int(data_size / gen)
    return obj

def mk_config(iterations, data_size, finite_field, threads, systematic_on, gen_conf):
    obj = {}
    obj['iterations'] = iterations
    obj['data_size'] = data_size
    obj['finite_field'] = finite_field
    obj['threads'] = threads
    obj['systematic_on'] = systematic_on
    obj['gens'] = gen_conf

    print(obj)
    return obj

def write_csv(path, file_name, exp_config):

    config_lines = list()

    print(type(exp_config['gens']))
    for key, value in exp_config['gens'].items():
        config_lines.append('{!s},{!s},{!s},{!s},{!s},{!s}\n'.format(exp_config['iterations'],
                                   exp_config['threads'],
                                   key,
                                   value,
                                   exp_config['finite_field'],
                                   exp_config['systematic_on']))
    temp = config_lines.pop()
    temp = temp[:-1]
    config_lines.append(temp)

    with open(path + file_name, 'w') as file:
        file.writelines(config_lines)
    file.close()




def write_config(path, file_name, exp_config):

    if file_name.endswith('.csv'):
        write_csv(path, file_name, exp_config)




config_path = input("output path: ")
file_format = input("file format [csv]: ")
iterations = int(input("iterations: "))
threads = int(input("Number of threads: "))
finite_field = input('finite field [1,2]: ')
data_size = int(input("Data size in number: "))
data_unit = input("data unit [b,k,m,g]: ")
while (not data_unit in ['b','k','m','g']):
    data_unit = input("data unit [b,k,m,g]: ")
generation_sizes = input("generation size [command seperated list]: ")

systematic_on = int(input("Systematic on [0,1]: "))

generation_sizes = [int(gen) for gen in generation_sizes.split(',')]

data_size = convert_data_size_to_bytes(data_size, data_unit)

if not assert_valid_generation_size(generation_sizes, data_size):
    sys.exit()

gen_conf = calculate_symbol_size(generation_sizes, data_size)

file_name = generate_file_name(data_size, data_unit, iterations, finite_field, threads, generation_sizes, file_format)

exp_config = mk_config(iterations, data_size, finite_field, threads, systematic_on, gen_conf)

write_config(config_path, file_name, exp_config)
