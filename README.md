# **Flight Simulator**

In this program, we created an interpreter for running the flight gear simulator.
Upon receiving a text files with commands, we will want to interpret it. We created a set of commands that are being
executed by the interpreter with the given parameters.
The interpreter is both client and server for the simulator - it receives data from the simulator and updates its own
information, and also sends data to the simulator and updates it's state.  

**Getting Started**

First install [flight gear](https://www.flightgear.org/)

Then, in the additional settings section write the following lines:

--telnet=socket,in,10,127.0.0.1,5402,tcp

--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
   
In addition, create a .txt file with a set of commands for the interpreter. Also create a xml file of the data the
simulator will send and put it in the protocol folder of the simulator.

Now you are able to run the program in the command line with an argument which is the the name of your .txt file.
Press "fly" on the simulator and the interpreter will start interpreting your .txt file. 

**Built With**

Clion - Ide by JetBrains

**Versioning**

We used [Github](https://github.com/giladashe/flightSimulator) for version control.

**Authors**

Tal Zigdon and Yoel Sherwin.
