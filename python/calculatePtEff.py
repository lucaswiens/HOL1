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

import ROOT
ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTopMargin(0.05)
ROOT.gStyle.SetPadLeftMargin(0.1)
ROOT.gStyle.SetPadRightMargin(0.03)
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

def printEfficiency(hist1, hist2):
	histIntegral_1 = hist1.Integral()
	histIntegral_2 = hist2.Integral()

	print ('%s:%s%.1f +/- %.1f%%' % (hist1.GetName(), (" " * (25-len(hist1.GetName()))), 100 * histIntegral_1 / histIntegral_2,
			(100 * histIntegral_1 / histIntegral_2) * np.sqrt(histIntegral_2) / histIntegral_2
		)
	)

	return None


if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("--x-max", help="Number of bins", default = 60)
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

	xLabel = findLabel("Pt")
	yLabel = "Efficiency"
	width = 1200
	height = int(width * 3/4.)
	effName = "muonPt"

	canvas = ROOT.TCanvas(effName, effName, width, height)

	canvas.SetGrid()

	histogramFile = ROOT.TFile(args.input_file)
	histogramFile.cd("1")

	muonPt = histogramFile.Get("1/muonPt")
	bmtfMatchedMuonPt = histogramFile.Get("1/bmtfMatchedMuonPt")

	isoMb1MatchedMuonPt = histogramFile.Get("1/isoMb1MatchedMuonPt")
	isoMb2MatchedMuonPt = histogramFile.Get("1/isoMb2MatchedMuonPt")
	isoMb12MatchedMuonPt = histogramFile.Get("1/isoMb12MatchedMuonPt")

	isoMb1MatchedMuonN3x3Pt = histogramFile.Get("1/isoMb1MatchedMuonN3x3Pt")
	isoMb2MatchedMuonN3x3Pt = histogramFile.Get("1/isoMb2MatchedMuonN3x3Pt")
	isoMb12MatchedMuonN3x3Pt = histogramFile.Get("1/isoMb12MatchedMuonN3x3Pt")

	minimum = 0

	#yMin = 0
	yMin = 0
	yMax = 1.02
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

	effIsoMb1N3x3Graph = ROOT.TGraphAsymmErrors(muonPt)
	effIsoMb1N3x3Graph.Divide(isoMb1MatchedMuonN3x3Pt, muonPt, "cl=0.683 b(1,1) mode")
	effIsoMb1N3x3Graph.SetLineColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerSize(0.8)
	effIsoMb1N3x3Graph.SetTitle("BMTF+IsoMB1 Muon (N_{3x3} #leq 1)"); effIsoMb1N3x3Graph.GetXaxis().SetTitle(xLabel); effIsoMb1N3x3Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb1N3x3Graph.SetMinimum(yMin); effIsoMb1N3x3Graph.SetMaximum(yMax)

	effIsoMb12N3x3Graph = ROOT.TGraphAsymmErrors(muonPt)
	effIsoMb12N3x3Graph.Divide(isoMb12MatchedMuonN3x3Pt, muonPt, "cl=0.683 b(1,1) mode")
	effIsoMb12N3x3Graph.SetLineColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerSize(0.8)
	effIsoMb12N3x3Graph.SetTitle("BMTF+IsoMB12 Muon (N_{3x3} #leq 1)"); effIsoMb12N3x3Graph.GetXaxis().SetTitle(xLabel); effIsoMb12N3x3Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb12N3x3Graph.SetMinimum(yMin); effIsoMb12N3x3Graph.SetMaximum(yMax)

	effIsoMb1N3x3Graph.SetLineStyle(ROOT.kDotted)
	effIsoMb12N3x3Graph.SetLineStyle(ROOT.kDotted)


	effBmtfGraph.GetXaxis().SetRangeUser(0, float(args.x_max));
	effBmtfGraph.Draw("same ap")
	if not args.bmtf_only:
		effIsoMb1Graph.Draw("same p")
		effIsoMb1N3x3Graph.Draw("same p")

		effIsoMb12Graph.Draw("same p")
		effIsoMb12N3x3Graph.Draw("same p")

	ROOT.gPad.BuildLegend(0.6, 0.2, 0.9, 0.45);

	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")

	canvas.SetLogy()
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	canvas.Close()

	common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)

	printEfficiency(bmtfMatchedMuonPt, muonPt)
	printEfficiency(isoMb1MatchedMuonPt, muonPt)
	printEfficiency(isoMb12MatchedMuonPt, muonPt)
	printEfficiency(isoMb1MatchedMuonN3x3Pt, muonPt)
	printEfficiency(isoMb12MatchedMuonN3x3Pt, muonPt)
