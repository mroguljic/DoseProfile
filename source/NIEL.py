#Transforms proton damage in silicon to 1MeV neutron equivalent (Non Ionizing Energy Loss)
import ROOT as r
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import interp1d

def plotNIEL(rootFiles,pltMin,pltMax,nPoints=100):

	energies=[]
	damageFactors=[]
	weights = open("rd50DamageCoeff.txt", "r") 

	for line in weights:
	  energies.append(float(line.split('\t')[0]))
	  damageFactors.append(float(line.split('\t')[1]))
	weights.close()

	interpolation = interp1d(energies, damageFactors)


	currentEvent 	= 0
	plotStep		= (pltMax-pltMin)/nPoints
	checkpoint		= pltMin
	NIEL 			= nPoints*[0]
	depth 			= np.linspace(pltMin,pltMax,nPoints)


	for filename in rootFiles:
		print(filename)
		tfile = r.TFile.Open(filename)
		ttree = tfile.Get("ttree")
		for event in ttree:

			evtNumber 	= ttree.EventNumber
			stepZ 	  	= ttree.StepZ
			kinE	  	= ttree.kineticEnergy
			
			if(currentEvent!=evtNumber):
				currentEvent	= evtNumber
				checkpoint		= pltMin

			if(stepZ>pltMax or kinE<0.001):#check in literature if the 1keV threshold holds!
				continue

			if(stepZ>checkpoint):
				binN			= int((stepZ-pltMin)/plotStep)
				checkpoint		+=plotStep
				NIEL[binN]		+=interpolation(kinE)/10000

	plt.plot(depth,NIEL,'r+')
	plt.ylabel('NIEL')
	plt.xlabel('Depth')
	#plt.savefig('test.pdf')

	power_smooth = interp1d(depth,NIEL)
	plt.plot(depth,power_smooth(depth))
	print(np.average(power_smooth(depth)), np.average(NIEL))
	plt.savefig('NIEL.pdf')