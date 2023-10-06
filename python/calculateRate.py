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
ROOT.gStyle.SetPadTopMargin(0.1)
#ROOT.gStyle.SetPadBottomMargin(0.1)
ROOT.gStyle.SetPadLeftMargin(0.1)
ROOT.gStyle.SetPadRightMargin(0.02)
ROOT.gStyle.SetLegendBorderSize(0)
#ROOT.gStyle.SetErrorX(0)
#ROOT.gStyle.SetLabelFont(43, "XYZ");
#ROOT.gStyle.SetTitleFont(43, "XYZ");

#Define as global variables to save time.. Might be better to make a member of common
COLORMAP = {
	"BMTF"          : ROOT.TColor.GetColor("#000000"),
	"IsoMB"         : ROOT.TColor.GetColor("#ff4da6"),
	"IsoMBN3x3"     : ROOT.TColor.GetColor("#ff4d4d"),
	"IsoMBAbsIEta3" : ROOT.TColor.GetColor("#4dffa6"),
	"IsoMBHighADC"  : ROOT.TColor.GetColor("#4da6ff"),
}

def main():
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	dustDir = GetOsVariable("DUSTDIR")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	#parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/Rate.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf Rate")
	parser.add_argument("--ratio", default = False, action = "store_true", help = "Show relative Rate")

	args = parser.parse_args()

	args.output_directory = dustDir + "/HoPlots/" + date + "/" + args.output_directory

	outputDirectories = [
		args.output_directory + "/rate/log",
	]
	for dir in outputDirectories:
		if not os.path.exists(dir):
			os.makedirs(dir)

	xLabel = findLabel("Pt")
	width = 1200
	height = 1200
	#height= 1500
	#height = int(width / 1.618030)
	rateName = "muonPt"

	canvas = ROOT.TCanvas(rateName, rateName, width, height)
	canvas.SetGrid()

	#rateDf = DataFrame(columns = ["runNumber", "bmtfRate", "bmtfMb34MatchedHoRate", "dttpMatchedHoRate", "dttpMatchedHoN3x3Rate", "bmtfMb34MatchedHoRelativeRate", "dttpMatchedHoRelativeRate", "dttpMatchedHoN3x3RelativeRate"])
	rateDf = GetRateDf(args)
	numberOfRuns = len(rateDf["runNumber"].to_numpy())

	#for muonStation in ["", "MB1", "MB2", "MB12"]:
	for muonStation in ["MB1", "MB2", "MB12"]:
		MakeRatePlot(rateDf, numberOfRuns, muonStation, args)

	#rateDf = rateDf[rateDf["dttpMatchedHoRate"] > 0.001]
	rateDf.to_csv(args.output_directory + "/rateFull.csv", index="runNumber")
	rateDf = rateDf[rateDf["bmtfRate"] > 0.]
	rateDf.to_csv(args.output_directory + "/rate.csv", index="runNumber")
	with open(args.output_directory + "/rate.md", "w") as outFile:
		for tp in rateDf.columns:
			if tp == "runNumber":
				outFile.write("Analzed %i run numbers\n" % (len(rateDf[tp])))
			else:
				outFile.write(tp + " " * (30 - len(tp)) + "= %.2f +- %.2f\n" % (100 * rateDf[tp].mean(), 100 * rateDf[tp].std() / (rateDf.shape[0])**0.5))

def MakeRatePlot(rateDf, numberOfRuns, muonStation, args):
	xLabel = "run number"
	yLabel = "rate"
	offset = 0
	bmtfRateHist = GetRateHist(rateDf, "BMTF", muonStation, numberOfRuns, xLabel, yLabel, offset = offset)
	isoMBRateHist = GetRateHist(rateDf, "IsoMB", muonStation, numberOfRuns, xLabel, yLabel, offset = offset)
	isoMBN3x3RateHist = GetRateHist(rateDf, "IsoMBN3x3", muonStation, numberOfRuns, xLabel, yLabel, offset = offset)
	isoMBAbsIEta3RateHist = GetRateHist(rateDf, "IsoMBAbsIEta3", muonStation, numberOfRuns, xLabel, yLabel, offset = offset)
	isoMBHighADCRateHist = GetRateHist(rateDf, "IsoMBHighADC", muonStation, numberOfRuns, xLabel, yLabel, offset = offset)

	width = 2000
	height = 1200
	canvas = ROOT.TCanvas("rateHist", "rateHist", width, height)
	canvas.SetGrid()

	#yMax = 1.1*max([bmtfRateHist.GetMaximum(), isoMBRateHist.GetMaximum(), isoMBN3x3RateHist.GetMaximum(), isoMBAbsIEta3RateHist.GetMaximum()])
	yMax = 0.02/2

	ratePad = None
	padBorder = 0.4
	if args.ratio:
		ratePad = ROOT.TPad("Pad", "Pad", 0, padBorder, 1, 1);
		ratePad.Draw();
		ratePad.SetBottomMargin(0.025);
		ratePad.SetTicks()
		ratePad.SetGrid()
		ratePad.Update()
		ratePad.cd()

	bmtfRateHist.SetMaximum(yMax); isoMBRateHist.SetMaximum(yMax); isoMBN3x3RateHist.SetMaximum(yMax); isoMBAbsIEta3RateHist.SetMaximum(yMax); isoMBHighADCRateHist.SetMaximum(yMax);
	bmtfRateHist.Draw("HIST")
	isoMBRateHist.Draw("HIST SAME")
	isoMBN3x3RateHist.Draw("HIST SAME")
	isoMBAbsIEta3RateHist.Draw("HIST SAME")
	isoMBHighADCRateHist.Draw("HIST SAME")

	canvas.Modified()
	legend, legend2, legend3 = GetLegend()

	legend.AddEntry(bmtfRateHist, bmtfRateHist.GetName())
	legend.AddEntry(isoMBRateHist, isoMBRateHist.GetName())
	legend3.AddEntry(isoMBN3x3RateHist, isoMBN3x3RateHist.GetName())
	legend2.AddEntry(isoMBAbsIEta3RateHist, isoMBAbsIEta3RateHist.GetName())
	legend2.AddEntry(isoMBHighADCRateHist, isoMBHighADCRateHist.GetName())

	legend.Draw("SAME")
	legend2.Draw("SAME")
	legend3.Draw("SAME")

	if args.ratio:
		canvas.cd()

		relRateIsoMBRatio = GetRelativeRate(bmtfRateHist, isoMbRateHist, "IsoMB", xLabel)
		relRateIsoMBN3x3Ratio = GetRelativeRate(bmtfRateHist, isoMbN3x3RateHist, "IsoMBN3x3", xLabel)
		relRateIsoMBAbsIEta3Ratio = GetRelativeRate(bmtfRateHist, isoMbAbsIEta3RateHist, "IsoMBAbsIEta3", xLabel)
		relRateIsoMBHighADCRatio = GetRelativeRate(bmtfRateHist, isoMbHighADCRateHist, "IsoMBHighADC", xLabel)

		ratioPad = ROOT.TPad("ratioPad", "ratioPad", 0, 0, 1, padBorder);
		ratioPad.SetTopMargin(0.025);
		ratioPad.SetBottomMargin(0.3);
		ratioPad.SetFillStyle(0);
		ratioPad.SetTicks()
		ratioPad.SetGrid()
		ratioPad.Update()
		ratioPad.Draw("SAME");

		ratioPad.cd()
		relRateIsoMBRatio.Draw("SAME AP")
		relRateIsoMBN3x3Ratio.Draw("SAME P")
		relRateIsoMBAbsIEta3Ratio.Draw("SAME P")
		relRateIsoMBHighADCRatio.Draw("SAME P")

	canvas.Update();
	canvas.RedrawAxis();
	mbStation = "" if muonStation == "" else ("_" + muonStation)
	canvas.SaveAs(args.output_directory + "/rate/rate" + mbStation + ".png")
	canvas.SaveAs(args.output_directory + "/rate/rate" + mbStation + ".pdf")
	canvas.SetLogy()
	if args.ratio:
		ratePad.SetLogy()
		ratioPad.SetLogy()
	canvas.SaveAs(args.output_directory + "/log/rate" + mbStation + ".png")
	canvas.SaveAs(args.output_directory + "/log/rate" + mbStation + ".pdf")
	canvas.Close()
	pass

def GetRateHist(rateDf, algorithm, muonStation, numberOfRuns, xLabel, yLabel, fontSize = 40, offset = 0.2):
	mbStation = "" if muonStation == "" else ("(" + muonStation + ")")

	ALGORITHMMAP = {
		"BMTF" : "BMTF",
		"IsoMB" : "DTTP" + mbStation + " matched to HO",
		"IsoMBN3x3" : "DTTP" + mbStation + " matched to HO (N_{3x3} #leq 1)",
		"IsoMBAbsIEta3" : "DTTP" + mbStation + " matched to HO (|i#eta|=3)",
		"IsoMBHighADC" : "DTTP" + mbStation + " matched to HO (N_{ADC}^{HOTP} #geq 20)",
	}

	KEYMAP = {
		"BMTF"          : "bmtfRate",
		"IsoMB"         : "dttp" + muonStation + "MatchedHoRate",
		"IsoMBN3x3"     : "dttp" + muonStation + "MatchedHoN3x3Rate",
		"IsoMBAbsIEta3" : "dttp" + muonStation + "MatchedHoAbsIEta3Rate",
		"IsoMBHighADC"  : "dttp" + muonStation + "MatchedHoHighADCRate",
	}

	rateHist = ROOT.TH1D(ALGORITHMMAP[algorithm], "", numberOfRuns, 0, numberOfRuns)
	rateHist.SetName(ALGORITHMMAP[algorithm])
	rateHist.SetTitle(ALGORITHMMAP[algorithm])

	rateHist.SetLineColor(COLORMAP[algorithm])
	rateHist.SetMarkerColor(COLORMAP[algorithm])
	rateHist.SetMarkerSize(1.0)

	for i, index in enumerate(rateDf.index):
		iBin = i+1
		runNumber = str(int(rateDf.loc[index, "runNumber"]))
		rateHist.SetBinContent(iBin, rateDf.loc[index, KEYMAP[algorithm]])
		rateHist.GetXaxis().SetBinLabel(iBin, runNumber)

	rateHist.GetXaxis().SetName(xLabel)
	rateHist.GetXaxis().SetTitle(xLabel)
	rateHist.GetXaxis().SetLabelFont(43)
	rateHist.GetXaxis().SetLabelSize(fontSize)
	rateHist.GetXaxis().SetTitleOffset(offset)

	rateHist.GetYaxis().SetName(yLabel)
	rateHist.GetYaxis().SetTitle(yLabel)
	rateHist.GetYaxis().SetLabelFont(43)
	rateHist.GetYaxis().SetLabelSize(fontSize)
	rateHist.GetYaxis().SetTitleOffset(offset)

	rateHist.GetXaxis().LabelsOption("v")
	rateHist.GetXaxis().CenterLabels()

	rateHist.SetLineWidth(2)
	rateHist.SetNdivisions(505)
	rateHist.SetMinimum(1)
	return rateHist

def GetRelativeRate(bmtf, isoMB, algorithm, xLabel, fontSize = 40, offset = 0.2):
	relativeRateHist = isoMB.Clone("_Clone")
	relativeRateHist = Divide(bmtf)

	isoMB.SetLabelSize(0)
	bmtf.SetTitleSize(0)

	relativeRateGraph = ROOT.TGraphAsymmErrors(relRateIsoMBHist)
	relativeRateGraph.Divide(isoMBRateHist, bmtfRateHist, "cl=0.683 b(1,1) mode")

	relativeRateGraph.SetLineColor(COLORMAP[algorithm])
	relativeRateGraph.SetMarkerColor(COLORMAP[algorithm])
	relativeRateGraph.SetMarkerSize(0.9)
	relativeRateGraph.GetXaxis().SetTitle(xLabel)
	ratioLabel = "#frac{IsoMB}{BMTF}"
	relativeRateGraph.GetYaxis().SetTitle(ratioLabel)

	relativeRateGraph.GetXaxis().SetTitle(xLabel)
	relativeRateGraph.GetYaxis().SetTitle(ratioLabel)

	relativeRateGraph.GetXaxis().SetLabelSize(fontSize*0.8)
	relativeRateGraph.GetXaxis().SetTitleSize(fontSize*0.8)
	relativeRateGraph.GetXaxis().SetTitleOffset(offset)

	relativeRateGraph.GetYaxis().SetLabelSize(fontSize)
	relativeRateGraph.GetYaxis().SetTitleSize(fontSize)
	relativeRateGraph.GetYaxis().SetTitleOffset(offset)
	relativeRateGraph.SetLineWidth(2)

	#for i, index in enumerate(rateDf.index):
	#	iBin = i+1
	#	runNumber = str(int(rateDf.loc[index, "runNumber"]))
	#	relativeRateGraph.GetXaxis().SetBinLabel(iBin, runNumber)

	#relativeRateGraph.GetXaxis().LabelsOption("v")
	#relativeRateGraph.GetXaxis().CenterLabels()
	return relativeRateGraph

def GetRateDf(args):
	rateDf = DataFrame()
	histogramFile = ROOT.TFile(args.input_file)
	for iKey, key in enumerate(histogramFile.GetListOfKeys()):
		runNumber = key.GetName()
		if runNumber == "runNumber": continue
		histNumberOfEvents = histogramFile.Get(runNumber + "/numberOfEvents")
		# Sometimes if there is a failure in a specific run which crashes the program
		try:
			histNumberOfEvents.GetName()
		except:
			print("NOT AVAILABLE RUN: ", runNumber)
			continue

		histBmtfNumber = histogramFile.Get(runNumber + "/bmtfNumber")
		tree = histogramFile.Get(runNumber)
		histBmtfNumber = histogramFile.Get(runNumber + "/bmtfNumber")
		histList = []
		if histBmtfNumber.GetBinContent(1) < 10: continue
		rateDf.loc[iKey, "runNumber"] = int(runNumber)
		for iHist, histKey in enumerate(tree.GetListOfKeys()):
			if "Number" not in histKey.GetName(): continue
			hist = histKey.ReadObj()
			rateDf.loc[iKey, hist.GetName().replace("Mb", "MB").replace("Number", "Rate")] = hist.GetBinContent(1) / histNumberOfEvents.GetBinContent(1)
	return rateDf

def GetLegend():
	legend = ROOT.TLegend(0.1, 0.91, 0.35, 0.995)
	legend.SetBorderSize(1)
	legend.SetLineColor(0)
	legend.SetLineStyle(0)
	legend.SetFillColorAlpha(0,1)
	legend.SetFillStyle(1001)
	legend.SetTextFont(43)
	legend.SetTextSize(30)
	legend.SetNColumns(1)

	legend2 = ROOT.TLegend(0.355, 0.91, 0.605, 0.995)
	legend2.SetBorderSize(1)
	legend2.SetLineColor(0)
	legend2.SetLineStyle(0)
	legend2.SetFillColorAlpha(0,1)
	legend2.SetFillStyle(1001)
	legend2.SetTextFont(43)
	legend2.SetTextSize(30)
	legend2.SetNColumns(1)

	legend3 = ROOT.TLegend(0.65, 0.9525, 0.90, 0.995)
	legend3.SetBorderSize(1)
	legend3.SetLineColor(0)
	legend3.SetLineStyle(0)
	legend3.SetFillColorAlpha(0,1)
	legend3.SetFillStyle(1001)
	legend3.SetTextFont(43)
	legend3.SetTextSize(30)
	legend3.SetNColumns(1)

	return legend,legend2, legend3


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
	main()
