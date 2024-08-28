# NeuralNetwork_MLP
An implementation of a Neuralnetwork Multilayered Perceptron model. Made in C++ from scratch and featuring a Qt5 GUI for visualisation and changing NN settings and parameters, like numbers of layers, layer size and learningrate.
The project is made for two training cases, an XOR and a sinus function case. 



## How to use
The easiest way to run this project is to download the "standalone_build" as it comes with an executable and all Qt5 dependencies that are needed. 

The XOR and the sinus case can be set via the Settings menue in the GUI. 
The Settings tab also has the settings window where the number of layers, the layers sizes and the learningrate can be configured. 
Note that for the XOR case, the first layer has to have a size of 2 and the last layer has to be of size 1.
For the sinus function case, the first layer has to be of size 1, same as the last layer. 

Once all the options are set press the "Start" button to start the training.

## XOR 
In the training set there is only 4 different inputs, which are all the possible combinations for 2 bits and their resulting XOR value as the ground truth.
If the XOR case is selected the the diagram titled "Result" can be interpreted as the 2D input space of the NN. The two axis represent the first and second bit of the XOR operator and the blue dots that show the results of the NN 
denote at which inputs the network outputs are above 0.5, which is handled as True in regards to the boolean XOR operation. 

When testing out different layer sizes for the hidden layers, it is possible to recreate and see the Linear separability in action. More info on Linear separability: https://en.wikipedia.org/wiki/Linear_separability
This image shows how the XOR operator can not be solved by a single perceptron but instead at least two are needed, as the input space can not be divided properly with only one straight line.
![image](https://github.com/user-attachments/assets/545d1e57-0ae2-4a99-b671-fe24ac7e7ec7)


## Sinus Function
In this case the training data is a sinus function with some added zero mean noise. The input then is can be described by y = sin(x) + noise. In the "Result" diagram of the GUI, this noisy sinus function is shown a the red dots and
the test data is the actual sinus function without the added noise. The blue dots is the output of the NN.

With the sinus function a valuable lesson in terms of NNs can be learned, that is overfitting. As the train data has some added noise the model will first generalise the problem, which leads to a good estimation of the actuall sinus function.
However if the NN model is complex enough, given enough time to train, the output of the NN will worsen and it will start to learn the noise that was added to the training set and stray further away from the real sinus function.
Recommended model settings for this to be as visual as possible in the GUI are as follows: 
- Learn rate: 0.05
- Number of layers: 4
- Neurons on each layer: 1, 40, 20, 1
With these settings the model is complex enough to overfit to the training data. 
