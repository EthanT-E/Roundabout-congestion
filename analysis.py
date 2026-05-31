import matplotlib.pyplot as plt
from os import sys
import warnings
import pandas

warnings.simplefilter(action='ignore', category=pandas.errors.ParserWarning)


def main(plotflag=0):

    fig, ax = plt.subplots()
    crash_df = pandas.read_csv("./coord_data.csv", index_col=False)
    for col in crash_df.columns[1:]:
        crash_df.plot(x="time", y=col, title="Distance", ax=ax)

    speed_df = pandas.read_csv("./speed_data.csv", index_col=False)
    acc_df = pandas.read_csv("./acc_data.csv", index_col=False)

    fig, ax = plt.subplots()
    for col in acc_df.columns[1:]:
        acc_df.plot(x="time", y=col, title="Accerlation", ax=ax)

    fig, ax = plt.subplots()
    for col in speed_df.columns[1:]:
        speed_df.plot(x="time", y=col, title="Speed m/s", ax=ax)

    fig, ax = plt.subplots()
    for col in speed_df.columns[1:]:
        speed_df[col] = speed_df[col]*2.237
        speed_df.plot(x="time", y=col, title="Speed mph", ax=ax)

    if plotflag == 0:
        plt.show()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(1)
    else:
        main()
