import subprocess
from multiprocessing import Pool
from datetime import datetime
import time
import random


# Define the maximum number of parallel processes
MAX_PARALLEL = 5


def run_command(command):
    try:
        time.sleep(command[1])
        subprocess.run(command[0], shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {command[0]}")
        print(e)


def run_in_batches(commands, batch_size, skip_time=0):
    for i in range(0, len(commands), batch_size):
        batch = commands[i:i + batch_size]
        with Pool(len(batch)) as pool:
            pool.map(run_command, batch)


if __name__ == "__main__":
    test_list = "regression/all_sdf_gf180.yaml"
    sdf_types = ["high", "low"]
    corners = ["nom-t", "min-t", "max-t", "nom-f", "min-f", "max-f", "nom-s", "min-s", "max-s"]
    # corners = ["nom-s", "min-s", "max-s"]
    commands = []
    for sdf_type in sdf_types:
        for corner in corners:
            command = f"caravel_cocotb -tl {test_list} -sim GL_SDF -vcs  -no_wave -tag run_GF_sdf_{sdf_type}_{corner}_30ns_{datetime.now().strftime('%d_%b_%H_%M_%S_%f')[:-4]}  -corner {corner} -verbosity quiet "
            if sdf_type == "high":
                command += " -sdf_setup "
            commands.append(command)

    # add delay with each command
    command_with_delay = []
    count = 0
    for command in commands:
        count += 1
        skip_time = count * 10
        command_with_delay.append([command, skip_time])
    commands = command_with_delay
    while commands:
        batch = min(len(commands), MAX_PARALLEL)
        run_in_batches(commands[:batch], batch)
        commands = commands[batch:]
