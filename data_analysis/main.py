import os
import json

import pandas as pd
import matplotlib.pyplot as plt


class CONSTANTS:
    FOLDER_PATH = '../output'
    OPT2_NAME = 'opt-2'
    OPT3_NAME = 'opt-3'
    VERTICES = 'vertices'
    INITIAL_PATH_LENGTH = 'initial_path_length'
    OPT2_LENGTH = 'opt2_length'
    OPT3_LENGTH = 'opt3_length'
    OPT2_TIME = 'opt2_time'
    OPT3_TIME = 'opt3_time'


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


def parse_json(data):
    return {
        CONSTANTS.VERTICES: len(data['initial_path']['vertices']),
        CONSTANTS.INITIAL_PATH_LENGTH: data['initial_path']['length'],
        CONSTANTS.OPT2_LENGTH: data['solutions'][0]['path']['length'],
        CONSTANTS.OPT3_LENGTH: data['solutions'][1]['path']['length'],
        CONSTANTS.OPT2_TIME: data['solutions'][0]['time'],
        CONSTANTS.OPT3_TIME: data['solutions'][1]['time']
    }


def read_data(folder_path):
    data = []
    if not os.path.isdir(folder_path):
        print(f'The provided path "{folder_path}" is not a valid directory.')
        return

    for filename in get_input_file_list(folder_path):
        if filename.endswith('.json'):
            file_path = os.path.join(folder_path, filename)
            with open(file_path, 'r') as file:
                data.append(parse_json(json.load(file)))
    return data


def show():
    plt.legend()
    plt.grid(True, which = 'both', linestyle = '--', linewidth = 0.7)
    plt.tight_layout()
    mng = plt.get_current_fig_manager()
    mng.window.state('zoomed')
    plt.show()


def draw_all_lengths(df):
    plt.figure(figsize = (18, 9))

    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.INITIAL_PATH_LENGTH], label = CONSTANTS.INITIAL_PATH_LENGTH, marker = '*', color = 'green', markerfacecolor = 'cyan')
    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT2_LENGTH], label = CONSTANTS.OPT2_NAME, marker = 's', color = 'blue', markerfacecolor = '#10bbdd', markersize=8)
    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT3_LENGTH], label = CONSTANTS.OPT3_NAME, marker = 'o', color = 'red', markerfacecolor = 'yellow')

    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Path length (log scale)')
    plt.title('Dependency of length on number of vertices')
    show()


def draw_opt_lengths(df):
    plt.figure(figsize = (18, 9))

    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT2_LENGTH], label = CONSTANTS.OPT2_NAME, marker = 's', color = 'blue', markerfacecolor = '#10bbdd', markersize=8)
    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT3_LENGTH], label = CONSTANTS.OPT3_NAME, marker = 'o', color = 'red', markerfacecolor = 'yellow')

    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Path length (log scale)')
    plt.title('Dependency of length on number of vertices')
    show()


def draw_diff_lengths(X, Y):
    plt.figure(figsize = (18, 9))

    plt.plot(X, Y, label = 'opt-2 length - opt-3 length', marker = 'o', color = 'green', markerfacecolor = 'cyan')

    plt.yscale('symlog')
    plt.xlabel('Number of vertices')
    plt.ylabel('Differences between opt-3 and opt-3 lengths (log scale)')
    plt.title('Dependency of length difference on number of vertices')
    show()


def draw_times(df):
    plt.figure(figsize = (18, 9))

    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT2_TIME], label = CONSTANTS.OPT2_NAME, marker = 's', color = 'blue', markerfacecolor = '#10bbdd', markersize=8)
    plt.plot(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT3_TIME], label = CONSTANTS.OPT3_NAME, marker = 'o', color = 'red', markerfacecolor = 'yellow')

    plt.yscale('log')
    plt.xlabel('Number of vertices')
    plt.ylabel('Time (log scale)')
    plt.title(f'Dependency of {CONSTANTS.OPT2_NAME} and {CONSTANTS.OPT3_NAME} times on number of vertices')
    show()


if __name__ == '__main__':
    df = pd.DataFrame(sorted(read_data(CONSTANTS.FOLDER_PATH), key = lambda data: data[CONSTANTS.VERTICES]))
    draw_all_lengths(df)
    draw_opt_lengths(df)
    draw_diff_lengths(df[CONSTANTS.VERTICES], df[CONSTANTS.OPT2_LENGTH] - df[CONSTANTS.OPT3_LENGTH])
    draw_times(df)
