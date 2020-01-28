# G2S: The GeoStatistical Server

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Brief overview

**G2S** is composed of 2 parts:
- the first one is a server that manages computations and can be compiled for each hardware to obtain optimal performance.
- the second part is composed of different interfaces that communicate with the server through ZeroMQ. Interfaces can be added for each software. Similarly, G2S can be extended for any other geostatistical simulation algorithm.

Currently the **G2S** interface is available for *MATLAB* and *Python*. **G2S** is provided with both simulation algorithms **QS** (Quantile Sampling) and **NDS** (Narrow Distribution Selection).

**G2S** is currently only available for *UNIX*-based system, *Linux* and *macOS*. A solution for *Windows 10* is provided using *WSL* (Windows Subsystem for Linux). However, for previous *Windows* versions, the only solution currently available is to install a *Linux* system manually inside a virtual machine. 


## An interactive and complete documentation is available [here](https://gaia-unil.github.io/G2S/).
