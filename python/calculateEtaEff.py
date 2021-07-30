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

#import common

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
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "hostudy/" + date)
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("-b", "--bins", help="Number of bins", default = None)
	parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/efficiency.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")

	args = parser.parse_args()

	#executable = cmsswBase + "/nfs/dust/cms/user/wiens/CMSSW/HO/CMSSW_11_0_2/src/HOAnalysis/HOL1/scripts/produceL1Ntuple"

	outputDirectories = [
		args.output_directory,
		args.output_directory + "/efficiency/log",
	]
	for dir in outputDirectories:
		if not os.path.exists(dir):
			os.makedirs(dir)
	histogramFile = ROOT.TFile(args.input_file)


	xLabel = findLabel("Eta")
	yLabel = "Efficiency"
	width = 1200
	height = int(width / 1.618030)
	effName = "muonEta"

	canvas = ROOT.TCanvas(effName, effName, width, height)


	muonEta = histogramFile.Get("muonEta")
	bmtfMatchedMuonEta = histogramFile.Get("bmtfMatchedMuonEta")

	isoMb1MatchedMuonEta = histogramFile.Get("isoMb1MatchedMuonEta")
	isoMb2MatchedMuonEta = histogramFile.Get("isoMb2MatchedMuonEta")
	isoMb12MatchedMuonEta = histogramFile.Get("isoMb12MatchedMuonEta")

	effBmtfGraph = ROOT.TGraphAsymmErrors(muonEta)
	effBmtfGraph.Divide(bmtfMatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
	effBmtfGraph.SetLineColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerSize(0.8)
	effBmtfGraph.SetTitle("BMTF Muon"); effBmtfGraph.GetXaxis().SetTitle(xLabel); effBmtfGraph.GetYaxis().SetTitle(yLabel);
	effBmtfGraph.SetMinimum(0); effBmtfGraph.SetMaximum(1.0)

	effIsoMb1Graph = ROOT.TGraphAsymmErrors(muonEta)
	effIsoMb1Graph.Divide(isoMb1MatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
	effIsoMb1Graph.SetLineColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerSize(0.8)
	effIsoMb1Graph.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Graph.GetXaxis().SetTitle(xLabel); effIsoMb1Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb1Graph.SetMinimum(0); effIsoMb1Graph.SetMaximum(1.0)

	effIsoMb12Graph = ROOT.TGraphAsymmErrors(muonEta)
	effIsoMb12Graph.Divide(isoMb12MatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
	effIsoMb12Graph.SetLineColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerSize(0.8)
	effIsoMb12Graph.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Graph.GetXaxis().SetTitle(xLabel); effIsoMb12Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb12Graph.SetMinimum(0); effIsoMb12Graph.SetMaximum(1.0)

	effBmtfGraph.Draw("same ap")
	effIsoMb1Graph.Draw("same p")
	effIsoMb12Graph.Draw("same p")

	ROOT.gPad.BuildLegend();

	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")

	canvas.SetLogy()
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	canvas.Close()

	#common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)

	#plottingUrl = common.GetOSVariable("PLOTTING_URL")
	#print(plottingUrl + "/" + args.output_directory)
