#import matplotlib
#matplotlib.use('Agg')
#import matplotlib.pyplot as plt

#import awkward1 as ak
#import mplhep as hep
#import uproot4 as uproot

import numpy as np
import argparse
import json
import os
#import re
import subprocess

import common
from common import findLabel, GetOsVariable

import ROOT

def printEfficiency(hist1, hist2):
	effName =  hist1.GetName().replace("N3x3", "").replace("Pt", "").replace("MatchedMuon", " (N_3x3 < 2) Efficiency") if "N3x3" in hist1.GetName() else hist1.GetName().replace("Pt", "").replace("MatchedMuon", " Efficiency")
	histIntegral_1 = hist1.Integral()
	histIntegral_2 = hist2.Integral()
	efficiencyString = '%s:%s%.1f +/- %.1f%%' % (effName, (" " * (31-len(effName))), 100 * histIntegral_1 / histIntegral_2, (100 * histIntegral_1 / histIntegral_2) * np.sqrt(histIntegral_2) / histIntegral_2)
	print (efficiencyString)
	return efficiencyString

def main():
	common.SetupStyle()

	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	dustDir = GetOsVariable("DUSTDIR")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("--x-max", help="Number of bins", default = 150)
	parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/efficiency.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf efficiency")
	parser.add_argument("--ratio", default = False, action = "store_true", help = "Creates a ratio of isoMB1/Bmtf eff")

	args = parser.parse_args()

	args.output_directory = dustDir + "/HoPlots/" + date + "/" + args.output_directory

	outputDirectories = [
		args.output_directory,
		args.output_directory + "/efficiency/log",
	]
	for DIR in outputDirectories:
		print(DIR)
		if not os.path.exists(DIR):
			os.makedirs(DIR)

	histogramFile = ROOT.TFile(args.input_file)

	print(histogramFile)
	for key in histogramFile.GetListOfKeys():
		runNumber = key.GetName()
		print(runNumber)
		if runNumber == "runNumber": continue
		#print(runNumber)

		nEventsHist = histogramFile.Get(runNumber + "/numberOfEvents")
		nEvents = nEventsHist.GetBinContent(1)
		if not os.path.exists(args.output_directory + "/efficiency/" + runNumber + "/log"):
			os.makedirs(args.output_directory + "/efficiency/" + runNumber + "/log")

		efficiencyMap = {}
		for name in ["Pt", "Eta", "Phi"]:
			for cut in ["", "N3x3", "AbsIEta3", "HighADC"]:
				MakeEfficiencyPlot(histogramFile, runNumber, efficiencyMap, args, name = name, cut = cut)

		with open(args.output_directory + "/efficiency.txt", "w") as effFile:
			effFile.write("Total Efficiency using " + args.input_file + "\n")
			for cut in ["", "N3x3", "AbsIEta3", "HighADC"]:
				effFile.write(efficiencyMap["bmtf" + cut + "Pt"] + "\n")
				effFile.write(efficiencyMap["isoMB1" + cut + "Pt"] + "\n")
				effFile.write(efficiencyMap["isoMB2" + cut + "Pt"] + "\n")
				effFile.write(efficiencyMap["isoMB12" + cut + "Pt"] + "\n")

def MakeEfficiencyPlot(histogramFile, runNumber, efficiencyMap, args, name = "Pt", cut = "", width = 1200, height = 1000):

	xLabel = findLabel(name)
	yLabel = "Efficiency"

	muon = histogramFile.Get(runNumber + "/probeMuon" + name + "_Bmtf")
	bmtfMatchedMuon = histogramFile.Get(runNumber + "/tfMatchedMuon" + name + "_Bmtf")
	tfMatchedMuon = histogramFile.Get(runNumber + "/tfMatchedMuon" + name + "_uGMT")

	isoMb1MatchedMuon = histogramFile.Get(runNumber + "/isoMb1MatchedMuon" + cut + name)
	isoMb2MatchedMuon = histogramFile.Get(runNumber + "/isoMb2MatchedMuon" + cut + name)
	isoMb12MatchedMuon = histogramFile.Get(runNumber + "/isoMb12MatchedMuon" + cut + name)

	efficiencyMap["bmtf"    + cut + name] = printEfficiency(bmtfMatchedMuon, muon)
	efficiencyMap["isoMB1"  + cut + name] = printEfficiency(isoMb1MatchedMuon, muon)
	efficiencyMap["isoMB2"  + cut + name] = printEfficiency(isoMb2MatchedMuon, muon)
	efficiencyMap["isoMB12" + cut + name] = printEfficiency(isoMb12MatchedMuon, muon)

	yMin = 0
	yMax = 1.01

	effBmtfGraph = ROOT.TGraphAsymmErrors(muon)
	effBmtfGraph.Divide(bmtfMatchedMuon, muon, "cl=0.683 b(1,1) mode")
	effBmtfGraph.SetLineColor(common.BMTFCOLOR); effBmtfGraph.SetMarkerColor(common.BMTFCOLOR); effBmtfGraph.SetMarkerColor(common.BMTFCOLOR); effBmtfGraph.SetMarkerSize(1.0)
	effBmtfGraph.SetTitle("BMTF Muon"); effBmtfGraph.GetXaxis().SetTitle(xLabel); effBmtfGraph.GetYaxis().SetTitle(yLabel);
	effBmtfGraph.SetMinimum(yMin); effBmtfGraph.SetMaximum(yMax)

	effIsoMb1Graph = ROOT.TGraphAsymmErrors(muon)
	effIsoMb1Graph.Divide(isoMb1MatchedMuon, muon, "cl=0.683 b(1,1) mode")
	effIsoMb1Graph.SetLineColor(common.ISOMB1COLOR); effIsoMb1Graph.SetMarkerColor(common.ISOMB1COLOR); effIsoMb1Graph.SetMarkerColor(common.ISOMB1COLOR); effIsoMb1Graph.SetMarkerSize(1.0)
	effIsoMb1Graph.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Graph.GetXaxis().SetTitle(xLabel); effIsoMb1Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb1Graph.SetMinimum(yMin); effIsoMb1Graph.SetMaximum(yMax)

	effIsoMb2Graph = ROOT.TGraphAsymmErrors(muon)
	effIsoMb2Graph.Divide(isoMb2MatchedMuon, muon, "cl=0.683 b(1,1) mode")
	effIsoMb2Graph.SetLineColor(common.ISOMB2COLOR); effIsoMb2Graph.SetMarkerColor(common.ISOMB2COLOR); effIsoMb2Graph.SetMarkerColor(common.ISOMB2COLOR); effIsoMb2Graph.SetMarkerSize(1.0)
	effIsoMb2Graph.SetTitle("BMTF+IsoMB2 Muon"); effIsoMb2Graph.GetXaxis().SetTitle(xLabel); effIsoMb2Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb2Graph.SetMinimum(yMin); effIsoMb2Graph.SetMaximum(yMax)

	effIsoMb12Graph = ROOT.TGraphAsymmErrors(muon)
	effIsoMb12Graph.Divide(isoMb12MatchedMuon, muon, "cl=0.683 b(1,1) mode")
	effIsoMb12Graph.SetLineColor(common.ISOMB12COLOR); effIsoMb12Graph.SetMarkerColor(common.ISOMB12COLOR); effIsoMb12Graph.SetMarkerColor(common.ISOMB12COLOR); effIsoMb12Graph.SetMarkerSize(1.0)
	effIsoMb12Graph.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Graph.GetXaxis().SetTitle(xLabel); effIsoMb12Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb12Graph.SetMinimum(yMin); effIsoMb12Graph.SetMaximum(yMax)

	canvas = ROOT.TCanvas(name, name, width, height)
	canvas.cd()
	efficiencyPad = None
	if args.ratio:
		efficiencyPad = ROOT.TPad("Pad", "Pad", 0, 0.31, 1, 1);
		efficiencyPad.Draw();
		efficiencyPad.SetBottomMargin(0.025);
		efficiencyPad.SetTicks()
		efficiencyPad.SetGrid()
		efficiencyPad.Update()
		efficiencyPad.cd()
	else:
		canvas.SetGrid()
		canvas.SetTicks()
		canvas.Update()

	if name == "Pt":
		effBmtfGraph.GetXaxis().SetRangeUser(0, float(args.x_max));

	canvas.Modified()
	legend = common.GetLegend("Pt")

	effBmtfGraph.Draw("SAME AP")
	legend.AddEntry(effBmtfGraph)
	if not args.bmtf_only:
		effIsoMb1Graph.Draw("SAME P")
		effIsoMb12Graph.Draw("SAME P")

		legend.AddEntry(effIsoMb1Graph)
		legend.AddEntry(effIsoMb2Graph)
		legend.AddEntry(effIsoMb12Graph)

	legend.Draw("SAME")

	if args.ratio:
		effBmtfGraph.GetXaxis().SetLabelSize(0)
		effIsoMb1Graph.GetXaxis().SetLabelSize(0)
		effIsoMb12Graph.GetXaxis().SetLabelSize(0)

		canvas.cd()
		ratioPad = ROOT.TPad("ratioPad", "ratioPad", 0, 0, 1, 0.31);
		ratioPad.SetBottomMargin(0.225);
		ratioPad.SetFillStyle(0);
		ratioPad.SetTicks()
		ratioPad.SetGrid()
		ratioPad.Update()
		ratioPad.Draw("SAME");

		ratioLabel = "#frac{IsoMB}{BMTF}"

		pureIsoMb1MatchedMuon = isoMb1MatchedMuon.Clone()
		pureIsoMb1MatchedMuon.Add(bmtfMatchedMuon, -1)
		effIsoMb1Ratio = ROOT.TGraphAsymmErrors(bmtfMatchedMuon)
		effIsoMb1Ratio.Divide(pureIsoMb1MatchedMuon, bmtfMatchedMuon, "cl=0.683 b(1,1) mode")
		effIsoMb1Ratio.SetLineColor(common.ISOMB1COLOR); effIsoMb1Ratio.SetMarkerColor(common.ISOMB1COLOR); effIsoMb1Ratio.SetMarkerColor(common.ISOMB1COLOR); effIsoMb1Ratio.SetMarkerSize(0.9)
		effIsoMb1Ratio.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1Ratio.GetYaxis().SetTitle(ratioLabel);
		effIsoMb1Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1Ratio.GetYaxis().SetTitle(ratioLabel);

		effIsoMb1Ratio.GetXaxis().SetLabelSize(0.07)
		effIsoMb1Ratio.GetXaxis().SetTitleSize(0.09)
		effIsoMb1Ratio.GetXaxis().SetTitleOffset(1.15)

		effIsoMb1Ratio.GetYaxis().SetLabelSize(0.07)
		effIsoMb1Ratio.GetYaxis().SetTitleSize(0.07)
		effIsoMb1Ratio.GetYaxis().SetTitleOffset(0.58)
		effIsoMb1Ratio.SetMinimum(0); effIsoMb1Ratio.SetMaximum(0.05)
		if name == "Pt":
			effIsoMb1Ratio.GetXaxis().SetRangeUser(0, float(args.x_max))

		pureIsoMb2MatchedMuon = isoMb2MatchedMuon.Clone()
		pureIsoMb2MatchedMuon.Add(bmtfMatchedMuon, -1)
		effIsoMb2Ratio = ROOT.TGraphAsymmErrors(bmtfMatchedMuon)
		effIsoMb2Ratio.Divide(pureIsoMb2MatchedMuon, bmtfMatchedMuon, "cl=0.683 b(1,1) mode")
		effIsoMb2Ratio.SetLineColor(common.ISOMB2COLOR); effIsoMb2Ratio.SetMarkerColor(common.ISOMB2COLOR); effIsoMb2Ratio.SetMarkerColor(common.ISOMB2COLOR); effIsoMb2Ratio.SetMarkerSize(0.9)
		effIsoMb2Ratio.SetTitle("BMTF+IsoMB2 Muon"); effIsoMb2Ratio.GetXaxis().SetTitle(xLabel); effIsoMb2Ratio.GetYaxis().SetTitle(ratioLabel);
		effIsoMb2Ratio.GetXaxis().SetTitle(xLabel); effIsoMb2Ratio.GetYaxis().SetTitle(ratioLabel);

		pureIsoMb12MatchedMuon = isoMb12MatchedMuon.Clone()
		pureIsoMb12MatchedMuon.Add(bmtfMatchedMuon, -1)
		effIsoMb12Ratio = ROOT.TGraphAsymmErrors(muon)
		effIsoMb12Ratio.Divide(pureIsoMb12MatchedMuon, bmtfMatchedMuon, "cl=0.683 b(1,1) mode")
		effIsoMb12Ratio.SetLineColor(common.ISOMB12COLOR); effIsoMb12Ratio.SetMarkerColor(common.ISOMB12COLOR); effIsoMb12Ratio.SetMarkerColor(common.ISOMB12COLOR); effIsoMb12Ratio.SetMarkerSize(0.9)
		effIsoMb12Ratio.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Ratio.GetXaxis().SetTitle(xLabel); effIsoMb12Ratio.GetYaxis().SetTitle(ratioLabel);

		effIsoMb12Ratio.SetMinimum(yMin); effIsoMb12Ratio.SetMaximum(yMax)

		ratioPad.cd()
		effIsoMb1Ratio.Draw("SAME AP")
		effIsoMb2Ratio.Draw("SAME P")
		effIsoMb12Ratio.Draw("SAME P")

	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + name + cut + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + name + cut + ".pdf")
	canvas.SetLogz()
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + name + cut + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + name + cut + ".pdf")
	canvas.Close()

	#effTfGraph = ROOT.TGraphAsymmErrors(muon)
	#effTfGraph.Divide(tfMatchedMuon, muon, "cl=0.683 b(1,1) mode")
	#effTfGraph.SetLineColor(common.BMTFCOLOR); effTfGraph.SetMarkerColor(common.BMTFCOLOR); effTfGraph.SetMarkerColor(common.BMTFCOLOR); effTfGraph.SetMarkerSize(1.0)
	#effTfGraph.SetTitle("TF Muon"); effTfGraph.GetXaxis().SetTitle(xLabel); effTfGraph.GetYaxis().SetTitle(yLabel);
	#effTfGraph.SetMinimum(yMin); effTfGraph.SetMaximum(yMax)

if __name__=="__main__":
	main()

