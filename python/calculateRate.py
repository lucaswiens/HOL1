import argparse
#import json
import os
#import re
import subprocess

import ROOT

import common

from pandas import DataFrame

def GetOsVariable(Var):
	try:
		variable = os.environ[Var]
	except KeyError:
		print("Please set the environment variable " + Var)
		sys.exit(1)
	return variable

def findLabel(rateName):
	label = ""
	if "Pt" in rateName:
		label = "p_{T} / GeV"
	elif "Eta" in rateName:
		label = "#eta"
	elif "DeltaR" in rateName:
		label = "#DeltaR"
	elif "DeltaPhi" in rateName:
		label = "#Delta #phi"
	return label


if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("--x-max", help="Number of bins", default = 20)
	#parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/Rate.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf Rate")

	args = parser.parse_args()

	args.output_directory = "hostudy/" + date + "/" + args.output_directory

	outputDirectories = [
		args.output_directory,
		args.output_directory + "/Rate/log",
	]
	for dir in outputDirectories:
		if not os.path.exists(dir):
			os.makedirs(dir)



	xLabel = findLabel("Pt")
	yLabel = "Relative Rate"
	width = 1200
	height = width
	#height= 1500
	#height = int(width / 1.618030)
	rateName = "muonPt"

	canvas = ROOT.TCanvas(rateName, rateName, width, height)
	canvas.SetGrid()

	#rateDf = DataFrame(columns = ["runNumber", "bmtfRate", "bmtfMb34MatchedHoRate", "dttpMatchedHoRate", "dttpMatchedHoN3x3Rate", "bmtfMb34MatchedHoRelativeRate", "dttpMatchedHoRelativeRate", "dttpMatchedHoN3x3RelativeRate"])
	rateDf = DataFrame()
	histogramFile = ROOT.TFile(args.input_file)
	for iKey, key in enumerate(histogramFile.GetListOfKeys()):
		runNumber = key.GetName()
		if runNumber == "runNumber": continue

		histNumberOfEvents          = histogramFile.Get(str(runNumber) + "/numberOfEvents")
		histBmtfNumber              = histogramFile.Get(str(runNumber) + "/bmtfNumber")
		histBmtfMb34MatchedHoNumber = histogramFile.Get(str(runNumber) + "/bmtfMb34MatchedHoNumber")
		histDttpMatchedHoNumber     = histogramFile.Get(str(runNumber) + "/dttpMatchedHoNumber")
		histDttpMatchedHoN3x3Number = histogramFile.Get(str(runNumber) + "/dttpMatchedHoN3x3Number")

		histBmtfRate              = histBmtfNumber.Clone("bmtfRate")
		histBmtfMb34MatchedHoRate = histBmtfMb34MatchedHoNumber.Clone("bmtfMb34MatchedHoRate")
		histDttpMatchedHoRate     = histDttpMatchedHoNumber.Clone("dttpMatchedHoRate")
		histDttpMatchedHoN3x3Rate = histDttpMatchedHoN3x3Number.Clone("dttpMatchedHo3x3Rate")

		histBmtfMb34MatchedHoRelativeRate = histBmtfMb34MatchedHoNumber.Clone("bmtfMb34MatchedHoRelativeRate")
		histDttpMatchedHoRelativeRate     = histDttpMatchedHoNumber.Clone("dttpMatchedHoRelativeRate")
		histDttpMatchedHoN3x3RelativeRate = histDttpMatchedHoN3x3Number.Clone("dttpMatchedHo3x3RelativeRate")

		histBmtfRate.Scale(1. / histNumberOfEvents.GetBinContent(1))
		histBmtfMb34MatchedHoRate.Scale(1. / histNumberOfEvents.GetBinContent(1))
		histDttpMatchedHoRate.Scale(1. / histNumberOfEvents.GetBinContent(1))
		histDttpMatchedHoN3x3Rate.Scale(1. / histNumberOfEvents.GetBinContent(1))

		histBmtfMb34MatchedHoRelativeRate.Divide(histBmtfNumber)
		histDttpMatchedHoRelativeRate.Divide(histBmtfNumber)
		histDttpMatchedHoN3x3RelativeRate.Divide(histBmtfNumber)

		#for hist in [histBmtfRate, histBmtfMb34MatchedHoRate, histDttpMatchedHoRate, histDttpMatchedHoN3x3Rate, histBmtfMb34MatchedHoRelativeRate, histDttpMatchedHoRelativeRate, histDttpMatchedHoN3x3RelativeRate]:
		rateDf.loc[iKey, "runNumber"] = runNumber
		for hist in [histBmtfRate, histDttpMatchedHoRate, histDttpMatchedHoN3x3Rate, histDttpMatchedHoRelativeRate, histDttpMatchedHoN3x3RelativeRate, histBmtfMb34MatchedHoRate, histBmtfMb34MatchedHoRelativeRate]:
			rateDf.loc[iKey, hist.GetName()] = hist.GetBinContent(1)

	#print(rateDf)
	with open("rate.md", "w") as outFile:
		for tp in rateDf.columns:
			if tp == "runNumber":
				outFile.write("Analzed %i run numbers\n" % (len(rateDf[tp])))
			else:
				outFile.write(tp + " " * (30 - len(tp)) + "= %.4f\n" % (rateDf[tp].mean()))
