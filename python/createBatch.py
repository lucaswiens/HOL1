#!/cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_6_8/external/slc7_amd64_gcc700/bin/python3
import sys, os
import argparse
import subprocess
#import shutil
from re import findall

import uproot
from collections import defaultdict

def GetOsVariable(Var):
	try:
		variable = os.environ[Var]
	except KeyError:
		print("Please set the environment variable " + Var)
		sys.exit(1)
	return variable

def makeDirs(path):
	try:
		os.makedirs(path)
	except:
		pass


if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	#redirector = "root://cms-xrd-global.cern.ch/"
	redirector = "root://xrootd-cms.infn.it/"

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file containing a list of samples.")
	parser.add_argument("-o", "--output", help="Path to the output directory", default = cmsswBase + "/" "Batch")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 50)
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("-e", "--use-emulated", default = False, action = "store_true", help = "Use the emulated branch to read BMTF information")

	args = parser.parse_args()
	fileName = "SingleMuon" if "SingleMuon" in args.input_file else "ZeroBias"
	fileName = args.input_file.split("/")[1].split(".")[0]
	args.output = args.output + "/" + fileName + "/" + date

	#executable = cmsswBase + "/nfs/dust/cms/user/wiens/CMSSW/HO/CMSSW_11_0_2/src/HOAnalysis/HOL1/scripts/produceL1Ntuple"

	# Order by run number.. should be parts of args or so because it is much slower and only needed for rate
	sampleDict = defaultdict(list)
	with open(args.input_file, "r") as sampleFile:
		for sample in sampleFile:
			sample = sample.replace("\n", "")
			runNumberArray = uproot.open(sample)["l1EventTree/L1EventTree/Event"]["run"].array()
			run = runNumberArray[0]
			sampleDict[run].append(sample)
			#if len(set(runNumberArray)) > 1:
				#print "Oha", set(runNumberArray)

	#if os.path.exists(args.output):
	#shutil.rmtree(str(args.output))
	#makeDirs(cmsswBase + "/L1Hist/" + "/" + fileName + "/" + date)
	for runNumber in sampleDict.keys():
		makeDirs(cmsswBase + "/L1Hist/" + "/" + fileName + "/" + date + "/" + str(runNumber))
	#makeDirs(str(args.output) + "/L1Hist")
	makeDirs(str(args.output) + "/error")
	makeDirs(str(args.output) + "/log")
	makeDirs(str(args.output) + "/output")

	numberOfFiles = int(args.number_of_files)
	number = 0

	condorFile = open(args.output + "/condor.submit", "w")
	condorFile.write("executable = " + args.output + "/produceNtuple\n")
	condorFile.write("arguments = L1Hist_$(Process) " + str(runNumber) + "$(arguments)\n")
	condorFile.write("getenv = True\n")
	condorFile.write("universe = vanilla\n")
	condorFile.write("request_memory = 400MB\n")
	condorFile.write("output = " + args.output + "/output/job$(Cluster)_$(Process).stdout\n")
	condorFile.write("error ="   + args.output + "/error/job$(Cluster)_$(Process).stderr\n")
	condorFile.write("log = "    + args.output + "/log/job$(Cluster)_$(Process).log\n")
	condorFile.write("queue arguments from arguments.md\n")
	condorFile.close()

	execFile = open(args.output + "/produceNtuple", "w")
	execFile.write("#!/bin/sh\n")
	execFile.write("RUNNUMBER=${1}\n")
	execFile.write("EXECFILE=${2}\n")
	execFile.write("cd " + cmsswBase + "\n")
	execFile.write("eval `scramv1 runtime -sh` #cmsenv\n")
	execFile.write("cd " + cmsswBase + "/L1Hist/" + fileName + "/" + date + "/${RUNNUMBER}\n")
	execFile.write("bash " + args.output + "/${EXECFILE}\n")
	os.system("chmod 744 " + args.output + "/produceNtuple")
	argumentFile = open(args.output + "/arguments.md", "w")

	if args.test:
		numberOfFiles = 5

	shellNumber = 0
	#sampleFile = open(args.input_file, "r")

	#sampleList = [sample.replace("\n", "") for sample in sampleFile]

	print "List of run numbers:", sampleDict.keys()
	print(args.use_emulated)
	for runNumber in sampleDict.keys():
		print "run = %i" % (runNumber), "with %i files" % (len(sampleDict[runNumber]))
		lastSample = sampleDict[runNumber][-1]
		for sample in sampleDict[runNumber]:
			#sample = sample.replace("\n", "")
			if number == 0:
				shellFile = open(args.output + "/processNtuple_" + str(shellNumber), "w")
				os.system("chmod 744 " + args.output + "/processNtuple_" + str(shellNumber))
				shellFile.write("#!/bin/sh\n")
				shellFile.write("HOStudy L1" + fileName + "_" + str(shellNumber) + " " + ("1" if args.use_emulated else "0") + " ")
				shellFile.write(sample + " ")
				number += 1

				#argumentFile.write(args.output + "/L1Hist/L1Hist_" + str(shellNumber) + " ")
				argumentFile.write(str(runNumber) + " processNtuple_" + str(shellNumber) + "\n")
			else:
				shellFile.write(sample + " ")
				number += 1
				#argumentFile.write(sample + " ")
			if number == numberOfFiles - 1 or sample == lastSample:
				shellFile.write(sample + "\n")
				shellFile.close()
				number = 0
				shellNumber += 1
				if args.test:
					break
	argumentFile.close()

	print("To execute, go to {}".format(args.output))
