import argparse
#import json
import os
#import re
import subprocess

import ROOT

import common

from pandas import DataFrame

ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTopMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.1)
ROOT.gStyle.SetPadRightMargin(0.06)
#ROOT.gStyle.SetPadBottomMargin(0.175)
ROOT.gStyle.SetLegendBorderSize(0)
ROOT.gStyle.SetErrorX(0)

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
		args.output_directory + "/log",
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
		#print(runNumber)
		if runNumber == "runNumber": continue

		#if(runNumber in [
		#	"320888",
		#	"320900",
		#	"320901",
		#	"320902",
		#	"320907",
		#	"320908",
		#	"320911",
		#	"320914",
		#	"320916",
		#	"320917",
		#	"320936",
		#]): continue

		histNumberOfEvents          = histogramFile.Get(runNumber + "/numberOfEvents")
		histBmtfNumber              = histogramFile.Get(runNumber + "/bmtfNumber")
		histBmtfMb34MatchedHoNumber = histogramFile.Get(runNumber + "/bmtfMb34MatchedHoNumber")
		histDttpMatchedHoNumber     = histogramFile.Get(runNumber + "/dttpMatchedHoNumber")
		histDttpMatchedHoN3x3Number = histogramFile.Get(runNumber + "/dttpMatchedHoN3x3Number")

		histBmtfRate              = histBmtfNumber.Clone("bmtfRate")
		histBmtfMb34MatchedHoRate = histBmtfMb34MatchedHoNumber.Clone("bmtfMb34MatchedHoRate")
		histDttpMatchedHoRate     = histDttpMatchedHoNumber.Clone("dttpMatchedHoRate")
		histDttpMatchedHoN3x3Rate = histDttpMatchedHoN3x3Number.Clone("dttpMatchedHoN3x3Rate")

		histBmtfMb34MatchedHoRelativeRate = histBmtfMb34MatchedHoNumber.Clone("bmtfMb34MatchedHoRelativeRate")
		histDttpMatchedHoRelativeRate     = histDttpMatchedHoNumber.Clone("dttpMatchedHoRelativeRate")
		histDttpMatchedHoN3x3RelativeRate = histDttpMatchedHoN3x3Number.Clone("dttpMatchedHoN3x3RelativeRate")

		histBmtfRate.Scale(1. / histNumberOfEvents.GetBinContent(1))
		histBmtfMb34MatchedHoRate.Scale(1. / histNumberOfEvents.GetBinContent(1))
		histDttpMatchedHoRate.Scale(1. / histNumberOfEvents.GetBinContent(1))
		histDttpMatchedHoN3x3Rate.Scale(1. / histNumberOfEvents.GetBinContent(1))

		histBmtfMb34MatchedHoRelativeRate.Divide(histBmtfNumber)
		histDttpMatchedHoRelativeRate.Divide(histBmtfNumber)
		histDttpMatchedHoN3x3RelativeRate.Divide(histBmtfNumber)

		rateDf.loc[iKey, "runNumber"] = int(runNumber)
		for hist in [
				histBmtfRate,
				histDttpMatchedHoRate,
				histDttpMatchedHoRelativeRate,
				histDttpMatchedHoN3x3Rate,
				histDttpMatchedHoN3x3RelativeRate,
				histBmtfMb34MatchedHoRate,
				histBmtfMb34MatchedHoRelativeRate
			]:
			rateDf.loc[iKey, hist.GetName()] = hist.GetBinContent(1)

	#print(rateDf)
	print(rateDf["runNumber"].shape[0])
	#rateHist = ROOT.TH1I("", "", rateDf["runNumber"].shape[0], rateDf["runNumber"].min(), rateDf["runNumber"].max())
	bmtfRateHist = ROOT.TH1D("bmtf", "", int(rateDf["runNumber"].max() - rateDf["runNumber"].min()), rateDf["runNumber"].min(), rateDf["runNumber"].max())
	isoMBRateHist = ROOT.TH1D("DTTP matched to HO", "", int(rateDf["runNumber"].max() - rateDf["runNumber"].min()), rateDf["runNumber"].min(), rateDf["runNumber"].max())
	isoMBN3x3RateHist = ROOT.TH1D("DTTP matched to HO (with N_{3x3} #leq 1)", "", int(rateDf["runNumber"].max() - rateDf["runNumber"].min()), rateDf["runNumber"].min(), rateDf["runNumber"].max())

	bmtfRateHist.GetXaxis().SetName("run")
	bmtfRateHist.GetYaxis().SetName("rate")
	#bmtfRateHist.GetYaxis().SetOffset(0)
	bmtfRateHist.SetLineColor(ROOT.kBlack)
	isoMBRateHist.SetLineColor(ROOT.kRed-2)
	isoMBN3x3RateHist.SetLineColor(ROOT.kAzure-2)

	bmtfRateHist.SetMarkerColor(ROOT.kBlack)
	isoMBRateHist.SetMarkerColor(ROOT.kRed-2)
	isoMBN3x3RateHist.SetMarkerColor(ROOT.kAzure-2)

	for i in rateDf.index:
		#bmtfRateHist.Fill(rateDf.loc[i, "bmtfRate"])
		#isoMBRateHist.Fill(rateDf.loc[i, "dttpMatchedHoRate"])
		#isoMBN3x3RateHist.Fill(rateDf.loc[i, "dttpMatchedHoN3x3Rate"])

		bmtfRateHist.SetBinContent(i, rateDf.loc[i, "bmtfRate"])
		isoMBRateHist.SetBinContent(i, rateDf.loc[i, "dttpMatchedHoRate"])
		isoMBN3x3RateHist.SetBinContent(i, rateDf.loc[i, "dttpMatchedHoN3x3Rate"])

	width = 1200
	height = int(width * 3/4.)
	canvas = ROOT.TCanvas("rateHist", "rateHist", width, height)
	canvas.SetGrid()

	bmtfRateHist.Draw("HIST")
	isoMBRateHist.Draw("HIST SAME")
	isoMBN3x3RateHist.Draw("HIST SAME")
	ROOT.gPad.BuildLegend(0.6, 0.2, 0.9, 0.45);

	canvas.SaveAs(args.output_directory + "/rate.png")
	canvas.SaveAs(args.output_directory + "/rate.pdf")
	canvas.SetLogy()
	canvas.SaveAs(args.output_directory + "/log/rate.png")
	canvas.SaveAs(args.output_directory + "/log/rate.pdf")
	canvas.Close()

	#rateDf = rateDf[rateDf["dttpMatchedHoRate"] > 0.001]
	rateDf.to_csv(args.output_directory + "/rateFull.csv")
	rateDf = rateDf[rateDf["bmtfRate"] > 0.]
	rateDf.to_csv(args.output_directory + "/rate.csv")
	with open(args.output_directory + "/rate.md", "w") as outFile:
		for tp in rateDf.columns:
			if tp == "runNumber":
				outFile.write("Analzed %i run numbers\n" % (len(rateDf[tp])))
			else:
				outFile.write(tp + " " * (30 - len(tp)) + "= %2.2f +- %.2f\n" % (100 * rateDf[tp].mean(), 100 * rateDf[tp].std() / (rateDf.shape[0])**0.5))
