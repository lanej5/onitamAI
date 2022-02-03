"""Summarize simulation outcomes."""

import pandas as pd
from os import listdir
import json
import numpy as np
from statsmodels.stats.proportion import binom_test

# load filenames
path = "./../data/"
files = listdir(path)
filenames = [s[:-4] for s in files if s[-4:] == ".csv" and s[:-4] + ".json" in files]

# summarize results
columns = ["Red Agent",
           "Red Param",
           "Blue Agent",
           "Blue Param",
           "Number of Games",
           "Number of Red Wins",
           "Winner",
           "p-value",
           "filename"]
summary = pd.DataFrame(columns=columns)

for s in filenames:

    # load metadata and csv
    with open(path + s + ".json") as f:
        metadata = json.load(f)
    df = pd.read_csv(path + s + ".csv")

    # distill winner from different win conditions
    # 1 = blue master taken, 2 = blue gate taken,
    # 3 = red master taken, 4 = red gate taken
    conditions = [(df[' result'] == 1) | (df[' result'] == 2),
                  (df[' result'] == 3) | (df[' result'] == 4)]
    choices = [1, 0]
    df['red_wins'] = np.select(conditions, choices, None)

    # determine winner, p-value
    total_red_wins = df['red_wins'].sum()
    num_games = df['red_wins'].count()
    p_value = binom_test(total_red_wins,
                         num_games,
                         prop=0.5,
                         alternative='two-sided')
    if p_value <= 0.05:
        winner = "Red" if total_red_wins > num_games / 2 else "Blue"
    else:
        winner = "Draw"

    row = pd.Series([metadata['red']['name'],
                     str(metadata['red']['param']),
                     metadata['blue']['name'],
                     str(metadata['blue']['param']),
                     num_games,
                     total_red_wins,
                     winner, p_value, s],
                    index=columns)
    summary = summary.append(row, ignore_index=True)

summary.to_csv("simulations_summary.csv")
