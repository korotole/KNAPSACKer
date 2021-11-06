## KNAPSACKer

"Stop talking to me just like I don't even bleed, this cross is heavy when you're my **KNAPSACKer**"

### Brief overview

**KNAPSACKer** is a universal toolset for solving different types of knapsack (0/1) problems (mainly mentioned in the MI-KOP course at the Faculty of Information Technologies, Czech Technical University).

**KNAPSACKer** is a command line tool that compounds *bash scripts* *python* and *C++ executable*. The tool currently solves the following types of problems:
* Desicive (rozhodovací) - sum of all values in knapsack is less then B (4th number in the example datasets);  `-d`
* Constructive (konstruktivní) - sum of all values in knapsack is optimal;  `-c`
* Exact (exaktní) - sum of all values in knapsack has to match predefined number;  `-e`

Each problem can be solved using the following set of methods (algorithms):
* Brute Force  `0`
* Branch and Bound  `1`
* Dynamic Programming  `2`
* Greedy Heruistic `3`

### Prepositions to build

Executable is being built via the CMake toolchain. The toolchain can be installed from the command line at the linux environment with the next command:

`sudo apt-get install cmake`

Also, in order to check for runtime memory leaks during the development, valgrind tool must be installed.

`sudo apt-get install valgrind`

### Build the project

Firstly, if the project is being built at first, the `out` directory must be empty or be removed. In order to build the project `build.sh` script must be run from the root directory of a project. 
NOTE: since the projet is being developed under the linux platform, some building issues might appear at the moment.

### Run KNAPSACKer from the command line

In order to run the project, `run.sh -e/-c/-d 0/1/2 (-err)` or `v-run.sh -e/-c/-d 0/1/2` (valgrind-run, to trace memory behavoiur) script must be executed from the root directory of a project.

**Example:** `bash ./run.sh -d 1 NR -err`

### Runtime description

The executable scrit runs a program, passing each line of an each file in the `/data/` directory as one of command line arguments (program is being executed `N` times, where `N = lines(file1) + lines(file2) + ... lines(lastFile)`). **NOTE:** `/data/` folder includes some input data examples. 

KNAPSACKer scans knapsack metadata from the line beginning and then scans the proerties of an each item (weight, value). Later, KNAPSACKer creates folders corresponding to the input filenames at the `/out/output/` directory. This provides a user with a possibility of tracking the performance of KNAPSACKer for the each run while processing the same file. 

KNAPSACKer allows user to verify results by saving the information which results do not correspond with the solutions dataset (if it's present). **NOTE:** in order to disable - comment the corresponding line(s) at the `run.sh` script.

For each processed file there are two files that are being generated at the folder corresponding to the filename:
 * `InputFileBasename_Arg1Arg2_month_day@hour:minute:second:nanosecond.out` - run records for each line of the file
 * `InputFileBasename_Arg1Arg2_month_day@hour:minute:second:nanosecond.err`- results-solutions mismatching info

### Results processing


After a `.out` file was generated, `plotter.py` plots the distribution of computational times per file, storing the output in the `FILENAME.out.png` format.

![computational times distribution](https://github.com/csraea/KNAPSACKer/blob/main/out/output/ZR30/ZR30_0-d_24-10%4001:55:21:167431827.out.png?raw=true)

Also, the statistics of all runs is being stored and the `./out/output/` directory which can be furtherly proceeded by the `statplot.py` manually.

![time dependence on the number of items](https://github.com/csraea/KNAPSACKer/blob/main/out/output/all.png?raw=true)




