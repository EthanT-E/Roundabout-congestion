import matplotlib.pyplot as plt
from os import sys
import warnings
import pandas

warnings.simplefilter(action='ignore', category=pandas.errors.ParserWarning)


def main(plotflag=0):
    crash_df = pandas.read_csv("./coord_data.csv", index_col=False)
    crash_df.plot(x="time", y="dist", title="Distance")
    print(crash_df[crash_df.columns[1]].unique())

    speed_df = pandas.read_csv("./speed_data.csv", index_col=False)
    acc_df = pandas.read_csv("./acc_data.csv", index_col=False)

    fig, ax = plt.subplots()
    for col in speed_df.columns[1:]:
        speed_df.plot(x="time", y=col, title="Speed", ax=ax)

    fig, ax = plt.subplots()
    for col in acc_df.columns[1:]:
        acc_df.plot(x="time", y=col, title="Accerlation", ax=ax)
    if plotflag == 0:
        plt.show()


if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(1)
    else:
        main()
