#!/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_6_8/external/slc7_amd64_gcc700/bin/python3
import sys, os
import argparse
import subprocess
import shutil
from re import findall

def GetOsVariable(Var):
	try:
		variable = os.environ[Var]
	except KeyError:
		print("Please set the environment variable " + Var)
		sys.exit(1)
	return variable

if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	#redirector = "root://cms-xrd-global.cern.ch/"
	redirector = "root://xrootd-cms.infn.it/"

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file containing a list of samples.")
	parser.add_argument("-o", "--output", help="Path to the output directory", default = cmsswBase + "/" "Batch/" + date)
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)

	args = parser.parse_args()

	#executable = cmsswBase + "/nfs/dust/cms/user/wiens/CMSSW/HO/CMSSW_11_0_2/src/HOAnalysis/HOL1/scripts/produceL1Ntuple"

	if os.path.exists(args.output):
		shutil.rmtree(str(args.output))
	os.makedirs(str(args.output) + "/L1Hist")
	os.makedirs(str(args.output) + "/error")
	os.makedirs(str(args.output) + "/log")
	os.makedirs(str(args.output) + "/output")

	numberOfFiles = int(args.number_of_files)
	number = 0

	condorFile = open(args.output + "/condor.submit", "w")
	condorFile.write("executable = " + args.output + "/produceNtuple\n")
	condorFile.write("arguments = L1Hist_$(Process) $(arguments)\n")
	condorFile.write("getenv = True\n")
	condorFile.write("universe = vanilla\n")
	condorFile.write("request_memory = 400 MB\n")
	condorFile.write("output = " + args.output + "/output/job$(Cluster)_$(Process).stdout\n")
	condorFile.write("error ="   + args.output + "/error/job$(Cluster)_$(Process).stderr\n")
	condorFile.write("log = "    + args.output + "/log/job$(Cluster)_$(Process).log\n")
	condorFile.write("queue arguments from arguments.md\n")
	condorFile.close()

	execFile = open(args.output + "/produceNtuple", "w")
	execFile.write("#!/bin/sh\n")
	execFile.write("cd " + cmsswBase + "\n")
	execFile.write("eval `scramv1 runtime -sh` #cmsenv\n")
	execFile.write("cd " + args.output + "/L1Hist\n")
	execFile.write("bash " + args.output + "/${1}\n")
	os.system("chmod 744 " + args.output + "/produceNtuple")
	argumentFile = open(args.output + "/arguments.md", "w")

	shellNumber = 0
	sampleFile = open(args.input_file, "r")
	for sample in sampleFile:
		sample = sample.replace("\n", "")
		if number == 0:
			shellFile = open(args.output + "/processNtuple_" + str(shellNumber), "w")
			os.system("chmod 744 " + args.output + "/processNtuple_" + str(shellNumber))
			shellFile.write("#!/bin/sh\n")
			shellFile.write("HOStudy L1Hist_" + str(shellNumber) + " ")
			shellFile.write(sample + " ")
			number += 1

			#argumentFile.write(args.output + "/L1Hist/L1Hist_" + str(shellNumber) + " ")
			argumentFile.write("processNtuple_" + str(shellNumber) + "\n")
		else:
			shellFile.write(sample + " ")
			number += 1
			#argumentFile.write(sample + " ")
		if number == numberOfFiles - 1:
			shellFile.write(sample + "\n")
			shellFile.close()
			number = 0
			shellNumber += 1

			#argumentFile.write(sample + "\n")
	sampleFile.close()
	argumentFile.close()

	print("To execute, go to {}".format(args.output))
