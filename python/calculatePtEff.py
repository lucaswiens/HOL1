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

import ROOT

import common

def GetOsVariable(Var):
	try:
		variable = os.environ[Var]
	except KeyError:
		print("Please set the environment variable " + Var)
		sys.exit(1)
	return variable

def findLabel(efficiencyName):
	label = ""
	if "Pt" in efficiencyName:
		label = "p_{T} / GeV"
	elif "Eta" in efficiencyName:
		label = "#eta"
	elif "DeltaR" in efficiencyName:
		label = "#DeltaR"
	elif "DeltaPhi" in efficiencyName:
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
	parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/efficiency.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf efficiency")

	args = parser.parse_args()

	args.output_directory = "hostudy/" + date + "/" + args.output_directory

	outputDirectories = [
		args.output_directory,
		args.output_directory + "/efficiency/log",
	]
	for dir in outputDirectories:
		if not os.path.exists(dir):
			os.makedirs(dir)
	histogramFile = ROOT.TFile(args.input_file)


	xLabel = findLabel("Pt")
	yLabel = "Efficiency"
	width = 1200
	height = width
	#height= 1500
	#height = int(width / 1.618030)
	effName = "muonPt"

	canvas = ROOT.TCanvas(effName, effName, width, height)

	canvas.SetGrid()



	tmpMuonPt = histogramFile.Get("muonPt")
	tmpBmtfMatchedMuonPt = histogramFile.Get("bmtfMatchedMuonPt")

	tmpIsoMb1MatchedMuonPt = histogramFile.Get("isoMb1MatchedMuonPt")
	tmpIsoMb2MatchedMuonPt = histogramFile.Get("isoMb2MatchedMuonPt")
	tmpIsoMb12MatchedMuonPt = histogramFile.Get("isoMb12MatchedMuonPt")

	minimum = 0
	maximum = int(args.x_max)
	#nBins = 2 * int(args.x_max)
	nBins = int(args.x_max)

	muonPt = ROOT.TH1D("muonPt", "", nBins, minimum, maximum)
	bmtfMatchedMuonPt = ROOT.TH1D("bmtfMatchedMuonPt", "", nBins, minimum, maximum)

	isoMb1MatchedMuonPt = ROOT.TH1D("isoMb1MatchedMuonPt", "", nBins, minimum, maximum)
	isoMb2MatchedMuonPt = ROOT.TH1D("isoMb2MatchedMuonPt", "", nBins, minimum, maximum)
	isoMb12MatchedMuonPt = ROOT.TH1D("isoMb12MatchedMuonPt", "", nBins, minimum, maximum)

	for bin in range(0, nBins + 1):
		muonPt.SetBinContent(bin, tmpMuonPt.GetBinContent(bin))
		muonPt.SetBinError(bin, tmpMuonPt.GetBinError(bin))

		bmtfMatchedMuonPt.SetBinContent(bin, tmpBmtfMatchedMuonPt.GetBinContent(bin))
		bmtfMatchedMuonPt.SetBinError(bin, tmpBmtfMatchedMuonPt.GetBinError(bin))

		isoMb1MatchedMuonPt.SetBinContent(bin, tmpIsoMb1MatchedMuonPt.GetBinContent(bin))
		isoMb1MatchedMuonPt.SetBinError(bin, tmpIsoMb1MatchedMuonPt.GetBinError(bin))

		isoMb2MatchedMuonPt.SetBinContent(bin, tmpIsoMb2MatchedMuonPt.GetBinContent(bin))
		isoMb2MatchedMuonPt.SetBinError(bin, tmpIsoMb2MatchedMuonPt.GetBinError(bin))

		isoMb12MatchedMuonPt.SetBinContent(bin, tmpIsoMb12MatchedMuonPt.GetBinContent(bin))
		isoMb12MatchedMuonPt.SetBinError(bin, tmpIsoMb12MatchedMuonPt.GetBinError(bin))

	yMin = 0
	yMax = 1.1
	effBmtfGraph = ROOT.TGraphAsymmErrors(muonPt)
	effBmtfGraph.Divide(bmtfMatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
	effBmtfGraph.SetLineColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerSize(0.8)
	effBmtfGraph.SetTitle("BMTF Muon"); effBmtfGraph.GetXaxis().SetTitle(xLabel); effBmtfGraph.GetYaxis().SetTitle(yLabel);
	effBmtfGraph.SetMinimum(yMin); effBmtfGraph.SetMaximum(yMax)

	effIsoMb1Graph = ROOT.TGraphAsymmErrors(muonPt)
	effIsoMb1Graph.Divide(isoMb1MatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
	effIsoMb1Graph.SetLineColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerSize(0.8)
	effIsoMb1Graph.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Graph.GetXaxis().SetTitle(xLabel); effIsoMb1Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb1Graph.SetMinimum(yMin); effIsoMb1Graph.SetMaximum(yMax)

	effIsoMb12Graph = ROOT.TGraphAsymmErrors(muonPt)
	effIsoMb12Graph.Divide(isoMb12MatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
	effIsoMb12Graph.SetLineColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerSize(0.8)
	effIsoMb12Graph.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Graph.GetXaxis().SetTitle(xLabel); effIsoMb12Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb12Graph.SetMinimum(yMin); effIsoMb12Graph.SetMaximum(yMax)

	effBmtfGraph.Draw("same ap")
	if not args.bmtf_only:
		effIsoMb1Graph.Draw("same p")
		effIsoMb12Graph.Draw("same p")

	ROOT.gPad.BuildLegend();

	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")

	canvas.SetLogy()
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	canvas.Close()

	common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)

	#plottingUrl = common.GetOSVariable("PLOTTING_URL")
	#print(plottingUrl + "/" + args.output_directory)
