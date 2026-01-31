# Gravity-simulation
A simple representation of gravity laws.

## Installation

Use the next command to clone the repository:
```shell
git clone https://github.com/blekki/Gravity-simulation.git
```

Install all dependities, if you don't have them already. If you use Linux, you can try this commands:
```shell
sudo apt update
sudo apt install cmake
sudo apt install libglew-dev 
sudo apt install libglfw3-dev
sudo apt install libglu1-mesa-dev
sudo apt install freeglut3-dev
```

Next step you need to build the project.
```shell
make
```

After all you can run the project on your personal computer.
```shell
make run
```

### Make commands

List of the commands for everyone who wants understand or rewrite the project.
| command | description |
| ------- | ----------- |
| `make` or `make all` | - Prepare the project to the correct work (build and compile). |
| `make build` | - Build the project. Process stops if the `./build` folder already exists.|
| `make rebuild` | - Forcibly rebuild. Recreate the `./build` folder. Be careful with this command. |
| `make rm-build` | - remove the `./build` folder and everything inside. |
| `make compile` | - Compile the project. |
| `cd ./build && make` | - The same as previously command. |
| `make run` | - Run the project binary file. |