# DoseProfile
 Studying profile of the dose delivered by a proton beam in silicon (can be changed to human tissue or some other material).
 First goal is to produce a "spread-out" Bragg peak as described here (https://www.ncbi.nlm.nih.gov/pubmed/8858723). This ensures uniform deposition
 of energy in the desired layer, while keeping delivered dose as low as possible in the outside region(s).  
 However, silicon sensor irradiation damage is not linearly proportional to deposited energy, but rather on the Non-ionizing energy loss
 (NIEL) as can be seen here (https://rd50.web.cern.ch/rd50/NIEL/default.html). Conversion factors - protons to equivalent number of 1 MeV neutron damage
 are also taken from the rd50 page.  
 After installing, calculation can be run by running (from the "build" folder)
 ```
 python spectrumCalc.py
```
and giving it the argument depending on what you need (going 1,2,3 in order is usually the best).
Range of the layer where we want to irradiate is  edited in spectrumCalc.py and you have to ensure that detectorThickness in configuration.txt is larger than Rmax.
Further adjustments to the target can be made in ProfileDetectorConstruction.cc as well as minimum simulation step.


Tested on ubuntu 14.04. LTS, python 2.7.6. 
Simulations are performed using Geant (4.10.3)            - https://geant4.web.cern.ch/  
To install geant4 and compile the code, cmake 3 is needed - https://cmake.org/download/    
Root installation is required to produce output           - https://root.cern.ch/  
 
To compile, make a directory where your project will be (doseProfile for example), copy source folder to the directory. In the doseProfile, do:
```
mkdir build
cd build  
cmake -DGeant4_DIR=...../geantInstallation/lib/Geant4-10.3.3 ../source  
make  
 
 To run:    
source ..../geantInstallation/bin/geant4.sh (or .csh)
cd build
python spectrumCalc.py
           

