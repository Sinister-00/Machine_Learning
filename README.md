# Machine Learning Algorithms in C++

This repository contains an implementation of machine learning algorithms in C++ using the MNIST Handwriting Dataset. The implemented algorithms include K-Nearest Neighbors (KNN), K-Means, and a basic Neural Network. Additionally, the Neural Network has been tested on the Iris Dataset.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [MNIST Handwriting Dataset](#mnist-handwriting-dataset)
- [Iris Dataset](#iris-dataset)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

<hr>

This project demonstrates the implementation of fundamental machine learning algorithms in C++. The algorithms implemented include K-Nearest Neighbors (KNN), K-Means, and a simple Neural Network. The main goal is to showcase the usage of these algorithms on real-world datasets such as the MNIST Handwriting Dataset and the Iris Dataset.

## Project Structure

<hr>

The project is organized as follows:

- `KNN/`: K-Nearest Neighbors implementation.
  - `src/`: Contains the source code (`src/knn.cpp`).
  - `include/`: Header files for the KNN module (`include/knn.hpp`).
  - `Makefile`: Makefile for compiling the KNN module.

- `KMEANS/`: K-Means implementation.
  - `src/`: Contains the source code (`src/kmeans.cpp`).
  - `include/`: Header files for the K-Means module (`include/kmeans.hpp`).
  - `Makefile`: Makefile for compiling the K-Means module.

- `NEURAL_NETWORK/`: Neural Network implementation.
  - `src/`: Contains the source code (`src/layer.cpp`, `src/network.cpp`, `src/neuron.cpp`).
  - `include/`: Header files for the Neural Network module (`include/layer.hpp`, `include/network.hpp`, `include/neuron.hpp`).
  - `Makefile`: Makefile for compiling the Neural Network module.

- `Dataset/`: Contains the MNIST Handwriting Dataset and Iris Dataset.

- `include/`: Common header files (`include/common.hpp`, `include/data.hpp`, `include/data_handler.hpp`).

- `lib/`: Contains the shared library (`lib/libdata.so`) used by multiple modules.

- `obj/`: Object files generated during compilation.

- `src/`: Common source files (`src/common.cpp`, `src/data.cpp`, `src/data_handler.cpp`).

- `test`: Executable file to test the data handling.

- `Makefile`: Top-level Makefile for compiling the entire project.

- `model.sh`: Script for creating new modules.

## Dependencies

<hr>

The project has the following dependencies:

- C++ Compiler (C++11 or later)

Make sure to install Eigen before running the code.


## MNIST Handwriting Dataset

<hr>

The [MNIST Handwriting Dataset](http://yann.lecun.com/exdb/mnist/) is used in training and testing of the algorithms. You can find the dataset in the `Dataset/` directory. The `./src/data_handler.cpp` file provides a simple utility to read and load the dataset.


## Iris Dataset

<hr>

The [Iris Dataset](https://www.kaggle.com/datasets/uciml/iris) is used specifically for testing the Neural Network implementation. You can find the dataset in the `Dataset/` directory.

<br>

## Usage

<hr>

### Clone the Repository

<br>

To get started, clone this repository to your local machine. Open a terminal and run the following commands:

```bash
git clone https://github.com/Sinister-00/Machine_Learning.git
  ```

<br>

Navigate to the project directory.

```bash
cd Machine_Learning
```

In order to run the make files of each module, you need to export the path of the working directory.<br>
Run this command on termiinal:

```bash
export MLINCPP_ROOT=$PWD
```

<br>
<br>

### Testing the Data Handling 

To check if the data handling, follow these steps:

1. Inside `./src` open `data_handler.cpp`.
2. At the very bottom you have to uncomment the driver code.
3. Save the file.
4. Then inside terminal you have to run `make`
5. New file named `test` will be created.
6. Run `./test` on terminal

<br>
<br>

### Testing K-Means <br>

To test the implemented K-Means algorithm, follow these steps:

1. Navigate to the K-Means directory: `cd KMEANS/`.
2. Compile the code using the provided Makefile: `make`.
3. Run the compiled executable `main` within the KMEANS directory.

<br>
   
> [!WARNING]
> This iterates through all k values, set the maximum value; otherwise, k equals the dataset's number of data points, treating each point as a cluster.

   

<br>

### Testing Best K using WCSS method for K-Means.

1. Navigate to the K-Means directory: `cd KMEANS/`.
2. Comment out the traditional method and uncomment the part for using the WCSS method inside `src/kmeans.cpp`.
3. Save the file.
4. Recompile the code using the Makefile: `make`.
5. Run the compiled executable `main` within the KMEANS directory.

<br>

> [!TIP]
> This uses elbow method to choose the best value of K.

<br>


<br>
<br>

### Testing KNN <br>

To test the implemented KNN algorithm, follow these steps:

1. Navigate to the KNN directory: `cd KNN/`.
2. Compile the code using the provided Makefile: `make`.
3. Run the compiled executable `main` within the KMEANS directory.

<br>

> [!NOTE]
> This will use euclidean distance by default.

<br>


#### To use manhattan distance to calculate the distance between two points in KNN, follow these steps:


1. Navigate to the KNN directory: `cd KNN/`.
2. Goto `Makefile` there you can find a line `CFLAGS := -std=c++11 -DEUCLID` change that to `CFLAGS := -std=c++11 -DMANHATTAN` and save file.
3. Compile the code using the provided Makefile: `make`.
4. Run the compiled executable `main` within the KMEANS directory.


<br>
<br>

### Testing Neural Network

To test the implementation of Neural Network, follow these steps: <br>
1. Navigate to NEURAL_NETWORK directory: `cd NEURAL_NETWORK`.
2. Compile the code using the provided Makefile: `make`.
3. Run the compiled executable `main` within the NEURAL_NETWORK directory.

<br>

> [!NOTE]
> This will use iris dataset by default.

<br>

#### To use MNIST Handwriting Dataset on Neural Network, follow these steps: <br>
1. Navigate to NEURAL_NETWORK directory: `cd NEURAL_NETWORK`.
2. Open `Makefile` inside `NEURAL_NETWORK`.
3. There you can find a line `CFLAGS := -std=c++11 -g`.
4. Change that to `CFLAGS := -std=c++11 -g -DMLINX`.
5. Save the file.
6. Compile the updated Makefile using `make` command in terminal.
7. Run the compiled executable `main` within the NEURAL_NETWORK directory.
<br>

> [!TIP]
> You can choose the number of epochs required while training. Inside `./src/network.cpp` at the very bottom update `net->train(17);` where `17` is the number of epoch.

<br>


## Contributing

<hr>

Your contributions are valued! If you encounter any issues or have suggestions for new features, please [report them](https://github.com/Sinister-00/Machine_Learning/issues). Before submitting pull requests, let's discuss the changes to ensure they align with the project goals.

### Reporting Issues

If you find any issues, please create a detailed [issue](https://github.com/Sinister-00/Machine_Learning/issues) with a clear description of the problem and, if possible, steps to reproduce it.

### Proposing Changes

If you have a new feature or improvement to propose, feel free to open a [pull request](https://github.com/Sinister-00/Machine_Learning/pulls). Ensure that your code follows the project's coding standards and practices.

