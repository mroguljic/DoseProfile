import numpy as np
import sys
import subprocess
import ROOT as r
from NIEL import plotNIEL
#Calculates proton beam spectrum to create a spread-out Bragg Peak
#(uniformly deilvered dose over a range, with minimum dose outside)
#Command line argument 1 sends the appropriate spectrum to geant
#Command line argument 2 creates a stacked histogram after geant sims are done
#Command line argument 3 calculates BULK silicon damage (NIEL) and plots it
#Before running set Rmin, Rmax and nInteverals to desired values


#alpha, p are parameters from Phys Med Biol 41 (1996) 1331-1339
alpha       = 0.012
p           = 1.77
x2          = 1 - 1/p

Rmin        = 0.1
Rmax        = 0.3
nIntervals  = 20
deltaX      = (Rmax-Rmin)/nIntervals
weightsDict = {}

print('Calculating energies for uniform dose in range '+str(Rmin)+' to '+str(Rmax)+'\n') 

print("  R     E    W")
#Formula is also from Phys Med Biol 41 (1996) 1331-1339
for i in xrange(nIntervals+1):
    R           = Rmin+i*deltaX
    E           = np.power(R/alpha,(1.0/p))
    if i==0:
        x1      = 1.0 - 1.0/(2.0*nIntervals)
        weight  = 1.0 - np.power(x1,x2)
        weightsDict[E]=weight
    elif i==nIntervals:
        x1      = 1.0/(2.0*nIntervals)
        weight  = np.power(x1,x2)
        weightsDict[E]=weight
    else:
        x11     = 1.0 - (i-1.0/2.0)/nIntervals
        x12     = 1.0 - (i+1.0/2.0)/nIntervals
        weight  = np.power(x11,x2)-np.power(x12,x2)
        weightsDict[E]=weight

    print "{:0.3f} {:0.3f} {:0.3f}".format(R,E,weight)

if(len(sys.argv)==1):
    print 'python sprectrumCalc.py 1 - to calculate weights and send jobs to geant'
    print 'python sprectrumCalc.py 2 - to make a stacked histogram after all jobs are complete'
    print 'python sprectrumCalc.py 3 - to make a plot of bulk silicon damage (NIEL)'
else:
    print "\n"

#if we do: python sprectrumCalc.py 1 - automatically runs jobs in geant
if(len(sys.argv)>1 and sys.argv[1]=='1'):
    print 'Sending jobs to geant'
    totalProtons = 10000    #number of protons summed in ALL the simulation runs (sum of all weights is 1)
    for energy, weight in weightsDict.items():

        #write proper energy and output file name in config file
        with open('configuration.txt', 'r') as file:
            data = file.readlines()
        data[0]  = 'particleEnergy={:0.3f}\n'.format(energy)
        data[2]  = 'outputTree={:0.3f}MeV.root\n'.format(energy)

        with open('configuration.txt', 'w') as file:
            file.writelines( data )

        #write macro to initialize run with proper number of events
        with open('{:0.3f}.mac'.format(energy),'w') as file:
            file.write('/run/initialize\n/run/beamOn '+str(int(totalProtons*weight)))

        command = './doseProfile {:0.3f}.mac > {:0.3f}.out'.format(energy,energy)
        print 'Running command - '+command
        status = subprocess.call(command, shell=True)
        if(status==0):
            print 'Simulation complete'
        else:
            print 'Error - status '+str(status)


#if we do: python sprectrumCalc.py 2 - produces a stack histogram
#performing step 1 is necessary to run this step
if(len(sys.argv)>1 and sys.argv[1]=='2'):
    print 'Making a stack histogram to get the total dose profile'
    stack           = r.THStack("hs","")
    histosList      = []
    filesList       = [] #this list is necessary to prevent root from closing files
    fileNames       = []
    for energy, weight in weightsDict.items():
        fileNames.append('{:0.3f}MeV.root'.format(energy))
    fileNames       = sorted(fileNames)

    for name in fileNames:
        tempFile    = r.TFile.Open(name)
        tempHisto   = tempFile.Get("dEdX")
        filesList.append(tempFile)
        histosList.append(tempHisto)

    for i,hist in enumerate(histosList):
        hist.SetFillStyle(1001)
        hist.SetFillColor(i+1)
        stack.Add(hist)

    c = r.TCanvas("c","c",10,10,700,900)
    stack.Draw("hist")
    c.SaveAs("stack.pdf")

#if we do: python sprectrumCalc.py 3 - produces a neutron-equivalent damage profile
if(len(sys.argv)>1 and sys.argv[1]=='3'):
    print 'Making a plot of the non-ionizing energy loss (NIEL) converted to 1MeV neutron equivalent fluence'
    rootFiles = []
    for energy, weight in weightsDict.items():
        rootFiles.append('{:0.3f}MeV.root'.format(energy))
    plotNIEL(rootFiles,Rmin,Rmax)