"""
Parses a folder of results spitting out a csv with the mean and median
for each of the data counts for each core. Files in the folder must be
of the format

    ${cores}-${n}.log

And the contents of the file consist of one or more lines of the format:

    ${result},${time}

Written using Python 3 and Pandas.
"""
import re
from collections import defaultdict
from datetime import timedelta
from os import listdir, path
from sys import argv, stderr
from typing import Dict

import pandas as pd

if len(argv) != 2:
    print("Must provide a path to read", file=stderr)
    exit(1)

files = []
try:
    files = listdir(argv[1])
except:
    print("Could not read folder", file=stderr)
    exit(1)

experiments: Dict[int, Dict[str, timedelta]] = defaultdict(dict)
pattern = re.compile("^(\\d+)-(\\d+).log$")
for file_name in files:
    match = re.search(pattern, file_name)
    if not match:
        continue

    cores, n = match.group(1, 2)
    times = pd.read_csv(path.join(argv[1], file_name), names=["result", "time"])

    experiments[int(cores)][f"{n}_mean"] = times["time"].mean()
    experiments[int(cores)][f"{n}_median"] = times["time"].median()

pd.DataFrame.from_dict(experiments, orient="index").sort_index().to_csv(argv[1] + ".csv")
