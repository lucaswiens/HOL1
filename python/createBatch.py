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

	args = parser.parse_args()

	#Make specific subdirectory depending on input file (expects input file to be path/to/input/inputFile.md)
	#outputDirName = args.input_file.split("/")[-1][:-3]
	#args.output = args.output + "/" + outputDirName
	executable = cmsswBase + "/nfs/dust/cms/user/wiens/CMSSW/HO/CMSSW_11_0_2/src/HOAnalysis/HOL1/scripts/produceL1Ntuple"

	if  os.path.exists(args.output):
		shutil.rmtree(str(args.output))
	os.makedirs(str(args.output))
	os.makedirs(str(args.output) + "/logs")
	os.makedirs(str(args.output) + "/error")
	os.makedirs(str(args.output) + "/output")

	submitFileContent = open(cmsswBase + "/src/HOAnalysis/HOL1/scripts/condor.submit", "r").read()
	submitFileContent = submitFileContent.replace("@EXECUTABLE", executable)
	submitFileContent = submitFileContent.replace("@OUT", args.output)

	submitFile = open(args.output + "/condor.submit", "w")
	submitFile.write(submitFileContent)
	submitFile.close()

	sampleFile = open(args.input_file, "r")
	argumentFile = open(args.output + "/arguments.md", "w")
	for sample in sampleFile:
		### sample = sample.strip()
		sample = sample.replace("\n", "")
		if not (sample.startswith("#") or sample in ["", "\n", "\r\n"]):
			argumentFile.write(redirector + sample + " " + cmsswBase + "\n")
	sampleFile.close()
	argumentFile.close()
