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
##ROOT.gStyle.SetPadBottomMargin(0.175)
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


if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("-b", "--bins", help="Number of bins", default = None)
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

	xLabel = findLabel("Eta")
	yLabel = "Efficiency"
	width = 1200
	#height = width
	#height = 1500
	#height = int(width / 1.618030)
	height = int(width * 3/4.)
	effName = "muonEta"

	canvas = ROOT.TCanvas(effName, effName, width, height)
	canvas.SetGrid()


	muonEta = histogramFile.Get("1/muonEta")
	bmtfMatchedMuonEta = histogramFile.Get("1/bmtfMatchedMuonEta")

	isoMb1MatchedMuonEta = histogramFile.Get("1/isoMb1MatchedMuonEta")
	isoMb2MatchedMuonEta = histogramFile.Get("1/isoMb2MatchedMuonEta")
	isoMb12MatchedMuonEta = histogramFile.Get("1/isoMb12MatchedMuonEta")

	bmtfMatchedMuonEta.SetTitle("")

	isoMb1MatchedMuonEta.SetTitle("")
	isoMb2MatchedMuonEta.SetTitle("")
	isoMb12MatchedMuonEta.SetTitle("")

	yMin = 0
	yMax = 1.1

	effBmtfGraph = ROOT.TGraphAsymmErrors(muonEta)
	effBmtfGraph.Divide(bmtfMatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
	effBmtfGraph.SetLineColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerSize(0.8)
	effBmtfGraph.SetTitle("BMTF Muon"); effBmtfGraph.GetXaxis().SetTitle(xLabel); effBmtfGraph.GetYaxis().SetTitle(yLabel);
	effBmtfGraph.SetMinimum(yMin); effBmtfGraph.SetMaximum(yMax)

	effIsoMb1Graph = ROOT.TGraphAsymmErrors(muonEta)
	effIsoMb1Graph.Divide(isoMb1MatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
	effIsoMb1Graph.SetLineColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerSize(0.8)
	effIsoMb1Graph.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Graph.GetXaxis().SetTitle(xLabel); effIsoMb1Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb1Graph.SetMinimum(yMin); effIsoMb1Graph.SetMaximum(yMax)

	effIsoMb12Graph = ROOT.TGraphAsymmErrors(muonEta)
	effIsoMb12Graph.Divide(isoMb12MatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
	effIsoMb12Graph.SetLineColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerSize(0.8)
	effIsoMb12Graph.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Graph.GetXaxis().SetTitle(xLabel); effIsoMb12Graph.GetYaxis().SetTitle(yLabel);
	effIsoMb12Graph.SetMinimum(yMin); effIsoMb12Graph.SetMaximum(yMax)

	effBmtfGraph.Draw("same ap")
	if not args.bmtf_only:
		effIsoMb1Graph.Draw("same p")
		effIsoMb12Graph.Draw("same p")

	ROOT.gPad.BuildLegend(0.6, 0.2, 0.9, 0.45);

	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")

	canvas.SetLogy()
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	canvas.Close()

	muonEta_vs_MuonPt = histogramFile.Get("1/muonEta_vs_MuonPt")
	bmtfMatchedMuonEta_vs_MuonPt = histogramFile.Get("1/bmtfMatchedMuonEta_vs_MuonPt")

	isoMb1MatchedMuonEta_vs_MuonPt = histogramFile.Get("1/isoMb1MatchedMuonEta_vs_MuonPt")
	isoMb2MatchedMuonEta_vs_MuonPt = histogramFile.Get("1/isoMb2MatchedMuonEta_vs_MuonPt")
	isoMb12MatchedMuonEta_vs_MuonPt = histogramFile.Get("1/isoMb12MatchedMuonEta_vs_MuonPt")

	xLabel = findLabel("Eta")
	yLabel = findLabel("Pt")

	effBmtfHist = ROOT.TH2D(bmtfMatchedMuonEta_vs_MuonPt)
	effBmtfHist.Divide(muonEta_vs_MuonPt)
	effBmtfHist.SetLineColor(ROOT.kBlack); effBmtfHist.SetMarkerColor(ROOT.kBlack); effBmtfHist.SetMarkerColor(ROOT.kBlack); effBmtfHist.SetMarkerSize(0.8)
	effBmtfHist.SetTitle("BMTF Muon"); effBmtfHist.GetXaxis().SetTitle(xLabel); effBmtfHist.GetYaxis().SetTitle(yLabel);
	effBmtfHist.SetStats(False);

	effIsoMb1Hist = ROOT.TH2D(isoMb1MatchedMuonEta_vs_MuonPt)
	effIsoMb1Hist.Divide(muonEta_vs_MuonPt)
	effIsoMb1Hist.SetLineColor(ROOT.kRed-2); effIsoMb1Hist.SetMarkerColor(ROOT.kRed-2); effIsoMb1Hist.SetMarkerColor(ROOT.kRed-2); effIsoMb1Hist.SetMarkerSize(0.8)
	effIsoMb1Hist.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Hist.GetXaxis().SetTitle(xLabel); effIsoMb1Hist.GetYaxis().SetTitle(yLabel);
	effIsoMb1Hist.SetStats(False);

	effIsoMb12Hist = ROOT.TH2D(isoMb12MatchedMuonEta_vs_MuonPt)
	effIsoMb12Hist.Divide(muonEta_vs_MuonPt)
	effIsoMb12Hist.SetLineColor(ROOT.kAzure-2); effIsoMb12Hist.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Hist.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Hist.SetMarkerSize(0.8)
	effIsoMb12Hist.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Hist.GetXaxis().SetTitle(xLabel); effIsoMb12Hist.GetYaxis().SetTitle(yLabel);
	effIsoMb12Hist.SetStats(False);

	#ROOT.gPad.BuildLegend();

	effName = "muonEta_vs_muonPt_bmtf"
	canvas = ROOT.TCanvas(effName, effName, width, height)
	#effBmtfHist.Draw("colz")
	#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")
	#canvas.SetLogz()
	#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	#canvas.Close()

	effName = "muonEta_vs_muonPt_isoMB1"
	#canvas = ROOT.TCanvas(effName, effName, width, height)
	#effIsoMb1Hist.Draw("colz")
	#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")
	#canvas.SetLogz()
	#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	#canvas.Close()

	effName = "muonEta_vs_muonPt_isoMB12"
	#canvas = ROOT.TCanvas(effName, effName, width, height)
	#effIsoMb12Hist.Draw("colz")
	#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")
	#canvas.SetLogz()
	#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	#canvas.Close()

	yMin = 1
	yMax = 1.1
	ROOT.gStyle.SetPadRightMargin(0.125)
	effBmtfHist.SetMinimum(yMin); effBmtfHist.SetMaximum(yMax)
	effIsoMb1Hist.SetMinimum(yMin); effIsoMb1Hist.SetMaximum(yMax)
	effIsoMb12Hist.SetMinimum(yMin); effIsoMb12Hist.SetMaximum(yMax)

	effRatioIsoMb1Hist = ROOT.TH2D(effIsoMb1Hist)
	effRatioIsoMb1Hist.Divide(effBmtfHist)
	effRatioIsoMb1Hist.SetLineColor(ROOT.kRed-2); effIsoMb1Hist.SetMarkerColor(ROOT.kRed-2); effIsoMb1Hist.SetMarkerColor(ROOT.kRed-2); effIsoMb1Hist.SetMarkerSize(0.8)
	effRatioIsoMb1Hist.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Hist.GetXaxis().SetTitle(xLabel); effIsoMb1Hist.GetYaxis().SetTitle(yLabel);

	effName = "effRatio_isoMB1"
	canvas = ROOT.TCanvas(effName, effName, width, height)
	effRatioIsoMb1Hist.SetMinimum(1.); effIsoMb1Hist.SetMaximum(1.1)
	effRatioIsoMb1Hist.Draw("colz")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")
	canvas.SetLogz()
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	canvas.Close()

	effRatioIsoMb12Hist = ROOT.TH2D(effIsoMb12Hist)
	effRatioIsoMb12Hist.SetMinimum(1.); effIsoMb12Hist.SetMaximum(1.5)
	effRatioIsoMb12Hist.Divide(effBmtfHist)
	effRatioIsoMb12Hist.SetLineColor(ROOT.kRed-2); effIsoMb12Hist.SetMarkerColor(ROOT.kRed-2); effIsoMb12Hist.SetMarkerColor(ROOT.kRed-2); effIsoMb12Hist.SetMarkerSize(0.8)
	effRatioIsoMb12Hist.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Hist.GetXaxis().SetTitle(xLabel); effIsoMb12Hist.GetYaxis().SetTitle(yLabel);

	effName = "effRatio_isoMB12"
	canvas = ROOT.TCanvas(effName, effName, width, height)
	effRatioIsoMb12Hist.Draw("colz")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")
	canvas.SetLogz()
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
	canvas.Close()

	common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)
	#plottingUrl = common.GetOSVariable("PLOTTING_URL")
	#print(plottingUrl + "/" + args.output_directory)
