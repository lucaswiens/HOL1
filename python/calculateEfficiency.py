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

ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)

ROOT.gStyle.SetPadTopMargin(0.125)
ROOT.gStyle.SetPadLeftMargin(0.2)
ROOT.gStyle.SetPadRightMargin(0.03)
ROOT.gStyle.SetPadBottomMargin(0.175)
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

	#numberOfHists = len(histograms.keys())
	efficiencyList = [
		[
			["BMTF Muon Efficiency", "bmtfMatchedMuonPt", "muonPt"],
			["BMTF+IsoMB1 Muon Efficiency", "isoMb1MatchedMuonPt", "muonPt"],
			["BMTF+IsoMB12 Muon Efficiency", "isoMb12MatchedMuonPt", "muonPt"],
		],
		[
			["BMTF Muon Efficiency", "bmtfMatchedMuonEta", "muonEta"],
			["BMTF+IsoMB1 Muon Efficiency", "isoMb1MatchedMuonEta", "muonEta"],
			["BMTF+IsoMB12 Muon Efficiency", "isoMb12MatchedMuonEta", "muonEta"],
		],

		#["muonBmtfEfficiencyPt", "bmtfMatchedMuonPt", "muonPt"],
		#["muonBmtfEfficiencyEta", "bmtfMatchedMuonEta", "muonEta"],
		#["usedMuonBmtfEfficiencyPt", "bmtfMatchedMuonPt", "usedMuonPt"],
		#["usedMuonBmtfEfficiencyEta", "bmtfMatchedMuonEta", "usedMuonEta"],
		#["muonBmtfEfficiencyPt_vs_MuonEta", "bmtfMatchedMuonPt_vs_MuonEta", "muonPt_vs_MuonEta"],
		#["muonBmtfEfficiencyEta_vs_MuonPt", "bmtfMatchedMuonEta_vs_MuonPt", "muonEta_vs_MuonPt"],
	]

	#colorList = [1, 46]#, 9, 29]
	colorList = [ROOT.kBlack, ROOT.kAzure-2, ROOT.kRed-2, ROOT.kTeal+3]


	firstDraw = True
	for eff in efficiencyList:
		xLabel = ""
		yLabel = "Efficiency"
		width = 1200
		height = int(width / 1.618030)
		effName = ""
		if isinstance(eff[0], list):
			effName = eff[0][2]
		else:
			effName = eff[2]
		canvas = ROOT.TCanvas(effName, effName, width, height)
		canvas.SetTicks()
		efficiencyGraphs = []
		if isinstance(eff[0], list):
			eff = np.array(eff)
			efficiencyArray = eff[:,0]
			matchedMuonArray = eff[:,1]
			muonArray = eff[:,2]

			xLabel = findLabel(muonArray[0])

			for efficiency, matchedMuon, muon, color in zip(efficiencyArray, matchedMuonArray, muonArray, colorList):
				print(efficiency, matchedMuon, muon)

				tmpMuonHist = histogramFile.Get(muon).Clone(muon + "_tmp")
				tmpMatchedMuonHist = histogramFile.Get(matchedMuon).Clone(matchedMuon + "_tmp")

				muonHist = None
				matchedMuonHist = None
				if args.bins != None and "Pt" in muon:
					minimum = tmpMuonHist.GetBinCenter(1)
					maximum = 0.5 * int(args.bins)
					muonHist = ROOT.TH1D(muon, "", int(args.bins), minimum, maximum)
					matchedMuonHist = ROOT.TH1D(matchedMuon, "", int(args.bins), minimum, maximum)
					for bin in range(0, int(args.bins) + 1):
						muonHist.SetBinContent(bin, tmpMuonHist.GetBinContent(bin))
						muonHist.SetBinError(bin, tmpMuonHist.GetBinError(bin))

						matchedMuonHist.SetBinContent(bin, tmpMatchedMuonHist.GetBinContent(bin))
						matchedMuonHist.SetBinError(bin, tmpMatchedMuonHist.GetBinError(bin))
				else:
					muonHist = tmpMuonHist.Clone(muon)
					matchedMuonHist = tmpMatchedMuonHist.Clone(matchedMuon)


				#efficiencyGraph = ROOT.TGraphAsymmErrors(matchedMuonHist, muonHist)
				efficiencyGraph = ROOT.TGraphAsymmErrors(matchedMuonHist)
				efficiencyGraph.Divide(matchedMuonHist, muonHist, "cl=0.683 b(1,1) mode")
				efficiencyGraph.SetLineColor(color)
				efficiencyGraph.SetMarkerColor(color)
				efficiencyGraph.SetMarkerColor(color)
				efficiencyGraph.SetMarkerSize(0.8)

				efficiencyGraph.SetTitle(efficiency)
				efficiencyGraph.GetXaxis().SetTitle(xLabel);
				efficiencyGraph.GetYaxis().SetTitle(yLabel);

				efficiencyGraph.SetMinimum(0)
				efficiencyGraph.SetMaximum(1.0)

				efficiencyGraphs.append(efficiencyGraph)



		else:
			efficiency, matchedMuon, muon = eff
			print(efficiency, matchedMuon, muon)

			xLabel = findLabel(efficiency)

			#tmpMuonHist = ROOT.TH1D(histogramFile.Get(muon).Clone(muon + "_tmp"))
			#tmpMatchedMuonHist = ROOT.TH1D(histogramFile.Get(matchedMuon).Clone(matchedMuon + "_tmp"))
			tmpMuonHist = histogramFile.Get(muon).Clone(muon + "_tmp")
			tmpMatchedMuonHist = histogramFile.Get(matchedMuon).Clone(matchedMuon + "_tmp")
			muonHist = None
			matchedMuonHist = None

			if args.bins != None and "_vs_" in muon:
				histName = muon.split("_vs_")
				xLabel = findLabel(histName[0])
				yLabel = findLabel(histName[1])

				xMinimum, xMaximum, yMinimum, yMaximum = 0, 0, 0, 0
				nBins1, nBins2 = 0, 0

				if "Pt" in histName[0]:
					nBins1 = int(args.bins)
					nBins2 = tmpMuonHist.GetYaxis().GetNbins()
					xMinimum = 0
					xMaximum = 0.5 * int(args.bins)
					yMinimum = tmpMuonHist.GetYaxis().GetBinCenter(1) - tmpMuonHist.GetYaxis().GetBinWidth(nBins2 + 1)/2
					yMaximum = tmpMuonHist.GetYaxis().GetBinCenter(nBins2 + 1) - tmpMuonHist.GetYaxis().GetBinWidth(nBins2 + 1)/2
				if "Pt" in histName[1]:
					nBins1 = tmpMuonHist.GetXaxis().GetNbins()
					nBins2 = int(args.bins)
					xMinimum = tmpMuonHist.GetXaxis().GetBinCenter(1) - tmpMuonHist.GetXaxis().GetBinWidth(nBins1 + 1)/2
					xMaximum = tmpMuonHist.GetXaxis().GetBinCenter(nBins1 + 1) - tmpMuonHist.GetXaxis().GetBinWidth(nBins1 + 1)/2
					yMinimum = 0
					yMaximum = 0.5 * int(args.bins)

				muonHist = ROOT.TH2D(muon, muon, nBins1, xMinimum, xMaximum, nBins2, yMinimum, yMaximum)
				matchedMuonHist = ROOT.TH2D(matchedMuon, matchedMuon, nBins1, xMinimum, xMaximum, nBins2, yMinimum, yMaximum)

				for bin1 in range(0, nBins1 + 1):
					for bin2 in range(0, nBins2 + 1):
						muonHist.SetBinContent(bin1, bin2, tmpMuonHist.GetBinContent(bin1, bin2))
						muonHist.SetBinError(bin1, bin2, tmpMuonHist.GetBinError(bin1, bin2))

						matchedMuonHist.SetBinContent(bin1, bin2, tmpMatchedMuonHist.GetBinContent(bin1, bin2))
						matchedMuonHist.SetBinError(bin1, bin2, tmpMatchedMuonHist.GetBinError(bin1, bin2))
			elif args.bins != None and "Pt" in muon:
				minimum = tmpMuonHist.GetBinCenter(1)
				maximum = 0.5 * int(args.bins)
				muonHist = ROOT.TH1D(muon, muon, int(args.bins), minimum, maximum)
				matchedMuonHist = ROOT.TH1D(matchedMuon, matchedMuon, int(args.bins), minimum, maximum)

				for bin in range(0, int(args.bins) + 1):
					muonHist.SetBinContent(bin, tmpMuonHist.GetBinContent(bin))
					muonHist.SetBinError(bin, tmpMuonHist.GetBinError(bin))

					matchedMuonHist.SetBinContent(bin, tmpMatchedMuonHist.GetBinContent(bin))
					matchedMuonHist.SetBinError(bin, tmpMatchedMuonHist.GetBinError(bin))
			else:
				muonHist = tmpMuonHist.Clone(muon)
				matchedMuonHist = tmpMatchedMuonHist.Clone(matchedMuon)

			if "_vs_" in muon:
				efficiencyHist = ROOT.TH2D(matchedMuonHist)
				efficiencyHist.Divide(muonHist)

				efficiencyHist.SetMinimum(1.0)
				efficiencyHist.SetMaximum(1.1)

				efficiencyHist.GetXaxis().SetTitle(xLabel);
				efficiencyHist.GetYaxis().SetTitle(yLabel);
				efficiencyHist.Draw("colz")

			else:
				#efficiencyGraph = ROOT.TGraphAsymmErrors(matchedMuonHist, muonHist)
				efficiencyGraph = ROOT.TGraphAsymmErrors(matchedMuonHist)
				efficiencyGraph.Divide(matchedMuonHist, muonHist, "cl=0.683 b(1,1) mode")
				efficiencyGraph.SetLineColor(ROOT.kBlack)
				efficiencyGraph.SetMarkerColor(ROOT.kBlack)
				efficiencyGraph.SetMarkerSize(0.8)
				#efficiencyGraphs.append(efficiencyGraph)

				efficiencyGraph.SetMinimum(0)
				efficiencyGraph.SetMaximum(1.0)

				efficiencyGraph.GetXaxis().SetTitle(xLabel);
				efficiencyGraph.GetYaxis().SetTitle(yLabel);
				efficiencyGraph.Draw("AP")

		efficiencyGraphs[0].Draw("same ap")
		for graph in efficiencyGraphs[1:]:
			graph.Draw("same p")
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
