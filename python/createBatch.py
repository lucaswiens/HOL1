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
	parser.add_argument("-o", "--output", help="Path to the output directory", default = cmsswBase + "/" "L1Hist")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 50)
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("-e", "--use-emulated", default = False, action = "store_true", help = "Use the emulated branch to read BMTF information")
	parser.add_argument("-s", "--split-by-run", default = False, action = "store_true", help = "Store output split by run number")

	args = parser.parse_args()
	print(args.input_file)
	print(args.input_file.split("/"))
	hasRecoMuons = "SingleMuon" in args.input_file
	fileName = "SingleMuon" if hasRecoMuons else "ZeroBias"
	fileName = args.input_file.split("/")[1].split(".")[0]
	args.output = args.output + "/" + fileName + "/" + date


	makeDirs(str(args.output) + "/root")
	makeDirs(str(args.output) + "/batch")
	makeDirs(str(args.output) + "/error")
	makeDirs(str(args.output) + "/log")
	makeDirs(str(args.output) + "/output")

	numberOfFiles = int(args.number_of_files)
	number = 0

	condorFile = open(args.output + "/condor.submit", "w")
	condorFile.write("executable = " + args.output + "/produceHOL1\n")
	condorFile.write("arguments = L1Hist_$(Process) $(arguments)\n")
	condorFile.write("getenv = True\n")
	condorFile.write("universe = vanilla\n")
	condorFile.write("request_memory = 400MB\n")
	condorFile.write("output = " + args.output + "/output/job$(Cluster)_$(Process).stdout\n")
	condorFile.write("error ="   + args.output + "/error/job$(Cluster)_$(Process).stderr\n")
	condorFile.write("log = "    + args.output + "/log/job$(Cluster)_$(Process).log\n")
	condorFile.write("queue arguments from arguments.md\n")
	condorFile.close()

	execFile = open(args.output + "/produceHOL1", "w")
	execFile.write("#!/bin/sh\n")
	execFile.write("EXECFILE=${1}\n")
	execFile.write("cd " + cmsswBase + "\n")
	execFile.write("eval `scramv1 runtime -sh` #cmsenv\n")
	execFile.write("cd " + str(args.output) + "/root\n")
	execFile.write("bash " + args.output + "/${EXECFILE}\n")

	os.system("chmod 744 " + args.output + "/produceHOL1")
	argumentFile = open(args.output + "/arguments.md", "w")

	if args.test:
		numberOfFiles = 5

	shellNumber = 0
	sampleList = []
	with open(args.input_file, "r") as sampleFile:
		sampleList = sampleFile.readlines()

	for sample in sampleList:
		sample = sample.replace("\n", "")
		if number == 0:
			shellFile = open(args.output + "/batch/processNtuple_" + str(shellNumber), "w")
			os.system("chmod 744 " + args.output + "/batch/processNtuple_" + str(shellNumber))
			shellFile.write("#!/bin/sh\n")
			shellFile.write("HOStudy L1" + fileName + "_" + str(shellNumber) + " " + ("1" if args.use_emulated else "0") + " " + ("1" if args.split_by_run else "0") + " " + ("1" if hasRecoMuons else "0" + " "))
			shellFile.write(sample + " ")
			number += 1

			argumentFile.write("batch/processNtuple_" + str(shellNumber) + "\n")
		else:
			shellFile.write(sample + " ")
			number += 1
		if number == numberOfFiles - 1:
			shellFile.write(sample + "\n")
			shellFile.close()
			number = 0
			shellNumber += 1
			if args.test:
				break

	argumentFile.close()

	print("To execute, go to {}".format(args.output))
