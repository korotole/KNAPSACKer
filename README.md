## KNAPSACKer

**KNAPSACKer** is a universal toolset for solving different types of knapsack problems mentioned in the MI-KOP course at the Faculty of Information Technologies, Czech Technical University.

### Brief overview

**KNAPSACKer** is a command line tool that compounds *bash scripts* and *C++ executable*. The tool currently solves the following types of problems:
* Desicive (rozhodovací)
* Constructive (konstruktivní)
* Exact (exaktní)

The description of these can be easily found in the open sources. Each problem can be solved using the following set of methods (algorithms):
* Brute force
* Branch and bound
* Dynamic programming

The parameters of execution are passed 

### Prepositions to build

Executable is being built via the CMake toolchain. The toolchain can be installed from the command line at the linux environment with the next command:

`sudo apt-get install cmake`

Also, in order to check for runtime memory leaks during the development, valgrind tool must be installed.

`sudo apt-get install valgrind`

### Build the project

Firstly, if the project is being built at first, the `out` directory must be empty or be removed. In order to build the project `build.sh` script must be run from the root directory of a project. 
NOTE: since the projet is being developed under the linux platform, some building issues might appear at the moment.

### Run KNAPSACKer from the command line

In order to run the project, `run.sh` or `v-run.sh` (valgrind-run, to trace memory behavoiur) script must be executed from the root directory of a project.





