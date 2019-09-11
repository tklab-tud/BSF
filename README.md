<div background-color="black" width="250" height="200" /><img align="center" src="https://github.com/tklab-tud/BSF/blob/master/resources/bsf2.jpg" alt="BSF Logo" title="BSF Logo" width="250" height="200" />
     
# BSF - Botnet Simulation Framework

BSF provides a discrete simulation environment to implement and extend peer-to-peer botnets, tweak their settings and allow defenders to evaluate monitoring and countermeasures .

## Synopsis

In the arms race between botmasters and defenders, the botmasters have the upper hand, as defenders have to react to actions and novel threats introduced by botmasters. The Botnet Simulation Framework (BSF) addresses this problem by leveling the playing field. It allows defenders to get ahead in the arms race by developing and evaluating new botnet monitoring techniques and countermeasures. This is crucial, as experimenting in the wild will interfere with other researchers and possibly alert botmasters. 

BSF allows realistic simulation of peer-to-peer botnets to explore and study the design and impact of monitoring mechanisms and takedown attempts before being deployed in the wild. BSF is a discrete event botnet simulator that provides a set of highly configurable (and customizable) botnet features including:
- realistic churn behavior
- variable bot behavior
- monitoring mechanisms (crawlers and sensors)
- anti-monitoring mechanisms

Moreover, BSF provides an interactive visualization module to further study the outcome of a simulation. BSF is aimed at enabling researchers and defenders to study the design of the different monitoring mechanisms in the presence of anti-monitoring mechanisms [1,2,3]. Furthermore, this tool allows the users to explore and understand the impact of design choices of botnets seen to date.

## Installation

BSF consists of the simulation framework and a visualization tool. The simulation framework itself is built on top of [OMNeT++](https://omnetpp.org/). Visualization is built on top of [Dash](https://plot.ly/dash/) to provide an interactive within your favorite browser.

### Setting up OMNeT++

The current version of BSF is built and tested with [OMNeT++ version 5.4.1.](https://omnetpp.org/download/old)

Please refer to the [OMNeT++ documentation](https://omnetpp.org/documentation/) for installation guidelines, tutorials and references regarding the provided functionalities.

### Setting up visualization components

To visualize the botnet simulations, the following python packages are required:
```
pip install dash==1.2.0      # The core dash backend
pip install dash-daq==0.1.0  # DAQ components (newly open-sourced!)

pip install networkx

pip install pandas
```

## Getting Started

OMNeT++ simulations are based on configurations defined in .ini files. The simulations folder of this repository contains a set of pre-defined configurations located in the tests.ini and sample.ini files.

To run a configuration, you may use either the OMNeT++ IDE or the command line. As BSF does not use any of the graphical features of OMNeT++ we recommend to run all simulations in the cmdenv, i.e., using just console output.

### Running Simulations within the IDE

To run a simulation within the IDE you need to setup a run configuration. For this, right click the \*.ini file and select *Run As* -> *Run Configurations*. Next setup your configuration file as shown in the image below:

![IDE run configuration setup](https://github.com/tklab-tud/BSF/blob/master/resources/omnet_run_config.png "IDE run configurations")

Now simply hit apply and run. The output of the simulation will appear in the IDE console.

### Running Simulations from the Command Line

To run from the command line, we need to first build the project. Navigate to the root folder and run:

```
make MODE=release all 
```

Afterwards navigate to the simulations folder and run:

```
../BSF -r 0 -m -u Cmdenv -c SampleConfig_Crawler -n .. samples.ini
```

### Simulation Output

Regardless of running the simulation from the IDE or the command line, you should see output similar to this:

```
** Event #577792   t=64831.46985369179   Elapsed: 4.21157s (0m 04s)  37% completed  (37% total)
     Speed:     ev/sec=180486   simsec/sec=14682   ev/simsec=12.293
     Messages:  created: 406512   present: 2108   in FES: 487
Just crawled: 24 nodes at 88983.25891616358
Just crawled: 40 nodes at 92583.25891616358
** Event #1050880   t=93607.74036896409   Elapsed: 6.28757s (0m 06s)  54% completed  (54% total)
     Speed:     ev/sec=227885   simsec/sec=13861.4   ev/simsec=16.4402
     Messages:  created: 729732   present: 2106   in FES: 630
Just crawled: 108 nodes at 96183.25891616358
Just crawled: 286 nodes at 99783.25891616358
Just crawled: 570 nodes at 103383.25891616358
```
The blocks start off with \*\* are standard outputs of OMNeT++ indicating the progress and statistics of the simulation. In the selected configuration, we have additional outputs by the crawler reporting the number of nodes discovered at each crawling interval. While this doesn't tell us much, we will show in the next section how you can visualize the output of both the botnet and the results of the crawler.

## Visualizing Results

The visualization is decoupled from the simulation framework and works on top of the generated graph and monitoring log files. We have also uploaded some sample data to explore the visualizations without running the main framework.

To visualize the results of the simulations you have to navigate to the *visualization* folder and call *app.py*. Afterwards open your favorite browser and open *http://127.0.0.1:8050/*. This should provide you with a graph view of one of the sample configurations looking something like this:

![Visualization demo](https://github.com/tklab-tud/BSF/blob/master/resources/visualization_graph_only.png "Visualization demo")

The dropdown menu in the top right of the screen allows you to choose between the results of different configurations. On the bottom of the screen you can see a timeline indicating all available snapshots of the botnet. This allows to visualize changes in the activity and connectivity of the bots. Furthermore, the menu on the right allows to visualize the information collected by crawlers or sensors. An example can be seen in the following figure, where the view of the crawler is highlighted in green.

![Visualization demo](https://github.com/tklab-tud/BSF/blob/master/resources/visualization_with_crawler.png "Visualization demo")

Furthermore, we are currently working on more advanced visualizations aiding the analysis of monitoring and takedown operations.

## References

The following publications present examples on the use cases of BSF:

\[1\]	[Leon Böck, Emmanouil Vasilomanolakis, Jan Helge Wolf, Max Mühlhäuser: Autonomously detecting sensors in fully distributed botnets. Computers & Security 83: 1-13 (2019)](https://www.sciencedirect.com/science/article/pii/S0167404818312094)

\[2\] [Leon Böck, Emmanouil Vasilomanolakis, Max Mühlhäuser, Shankar Karuppayah: Next Generation P2P Botnets: Monitoring Under Adverse Conditions. RAID 2018: 511-531](https://link.springer.com/chapter/10.1007/978-3-030-00470-5_24)

\[3\] [Emmanouil Vasilomanolakis, Max Mühlhäuser, Jan Helge Wolf, Leon Böck, Shankar Karuppayah](https://www.youtube.com/watch?v=m4rKqdQEqSo&t=1s)


