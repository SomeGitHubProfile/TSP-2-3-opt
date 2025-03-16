import os
import subprocess


def prettify_json(file):
    prettify_json_file = 'prettify_json.js'
    command = ['node', prettify_json_file, file]
    subprocess.run(command, check = True)


def map_list(f, lst):
    return list(map(f, lst))


def join_file_name(lst):
    return 'tsp_' + '_'.join(map_list(str, lst))


def get_input_file_list(input_folder):
    input_file_list = []
    for filename in os.listdir(input_folder):
        tsp, N, I = filename.split('_')
        input_file_list.append(map_list(int, [int(N), int(I)]))
    input_file_list.sort()
    return map_list(join_file_name, input_file_list)


def process_files(input_folder, output_folder, exe_file):
    os.makedirs(output_folder, exist_ok = True)

    number_of_errors = 0
    for filename in get_input_file_list(input_folder):
        input_file_path = os.path.join(input_folder, filename)
        if os.path.isfile(input_file_path):
            output_file_name = os.path.splitext(filename)[0] + '.json'
            output_file_path = os.path.join(output_folder, output_file_name)

            command = [exe_file, '--input', input_file_path, '--output', output_file_path]
            try:
                subprocess.run(command, check = True)
                print(f'Processed {filename} -> {output_file_name}')
                prettify_json(output_file_path)
                print(f'Prettified {output_file_name}')
                print()
            except subprocess.CalledProcessError as e:
                number_of_errors += 1
                print(f'Error №{number_of_errors} occured!')
                print(f'File: {filename}')
                print(f'Error message: {e}')
                print()
    print(f'Number of errors: {number_of_errors}')


if __name__ == '__main__':
    try:
        input_folder = 'data'
        output_folder = 'output'
        exe_file = r'Solver\x64\Release\TSP-2-3-OPT.exe'
        process_files(input_folder, output_folder, exe_file)
        input('Press enter to exit')
    except Exception as e:
        print(e)
        input()
