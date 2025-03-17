import os
import subprocess


def prettify_json(file):
    prettify_json_file = 'prettify_json.js'
    command = ['node', prettify_json_file, file]
    subprocess.run(command, check = True)


def map_list(f, lst):
    return list(map(f, lst))


def join_file(lst):
    return 'tsp_' + '_'.join(map_list(str, lst[0])) + lst[1]


def get_input_file_list(folder_path):
    input_file_list = []
    for file in os.listdir(folder_path):
        filename, extension = os.path.splitext(file)
        tsp, N, I = filename.split('_')
        input_file_list.append([map_list(int, [N, I]), extension])
    input_file_list.sort()
    return map_list(join_file, input_file_list)


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
                print(f'Processing {filename}...')
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
    input_folder = 'data'
    output_folder = 'output'
    exe_file = r'Solver\x64\Release\TSP-2-3-OPT.exe'
    try:
        process_files(input_folder, output_folder, exe_file)
    except Exception as e:
        print('Global error!')
        print(e)
    input('Press enter to exit')
