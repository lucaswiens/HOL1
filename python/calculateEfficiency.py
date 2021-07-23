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
		#[
		#	["bmtfEfficiencyPt", "bmtfMatchedMuonPt20", "muonPt20"],
		#	["bmtfMb34EfficiencyPt", "usedMuonPt20", "muonPt20"],
		#	["bmtfUsedMuon", "bmtfMatchedMuonPt20", "muonPt20"]
		#],
		#[
		#	["bmtfEfficiencyEta", "bmtfMatchedMuonEta", "muonEta"],
		#	["bmtfMb34EfficiencyEta", "usedMuonEta", "muonEta"],
		#],

		#["bmtfEfficiencyDeltaR", "bmtfMatchedMuonDeltaR", "muonDeltaR"],
		["muonBmtfEfficiencyPt", "bmtfMatchedMuonPt", "muonPt"],
		["usedMuonBmtfEfficiencyPt", "bmtfMatchedMuonPt", "usedMuonPt"],
		["usedMuonBmtfEfficiencyEta", "bmtfMatchedMuonEta", "usedMuonEta"],
		#["unusedMuonBmtfEfficiencyPt", "bmtfMatchedMuonPt", "unusedMuonPt"],
		#["bmtfEffPt", "muonMatchedBmtfCmsPt", "bmtfCmsPt"],
		#["bmtfEffEta", "muonMatchedBmtfCmsEta", "bmtfCmsEta"],
		#["bmtfBmtfEfficiencyPt", "bmtfMatchedMuonPt", "bmtfCmsPt"],
		#["testBmtfEfficiencyEta", "bmtfMatchedMuonEta", "muonEta"],
		#["testBmtfMb34EfficiencyPt", "bmtfMb34MatchedMuonPt", "muonPt"],
		#["bmtfEfficiencyPt", "bmtfMatchedMuonPt", "usedMuonPt"],
		#["bmtfEfficiencyEta", "bmtfMatchedMuonEta", "usedMuonEta"],
		#["bmtfMb34EfficiencyPt", "bmtfMb34MatchedMuonPt", "usedMuonPt"],
	]

	#colorList = [1, 46]#, 9, 29]
	colorList = [ROOT.kBlack, ROOT.kAzure-2, ROOT.kRed-2, ROOT.kTeal+3]


	for eff in efficiencyList:

		xLabel = ""
		yLabel = "Efficiency"
		width = 1200
		height = int(width / 1.618030)
		effName = ""
		if isinstance(eff[0], list):
			effName = eff[0][0]
		else:
			effName = eff[0]
		canvas = ROOT.TCanvas(effName, effName, width, height)
		canvas.cd()

		#efficiencyGraphs = []
		if isinstance(eff[0], list):
			print(eff)
			eff = np.array(eff)
			efficiencyArray = eff[:,0]
			matchedMuonArray = eff[:,1]
			muonArray = eff[:,2]

			xLabel = findLabel(efficiencyArray[0])

			for efficiency, matchedMuon, muon, color in zip(efficiencyArray, matchedMuonArray, muonArray, colorList):
				#muonHist = histogramFile.Get(muon)
				tmpMuonHist = ROOT.TH1D(histogramFile.Get(muon).Clone("tmpMuon"))
				tmpMatchedMuonHist = ROOT.TH1D(histogramFile.Get(matchedMuon).Clone("tmpMatchedMuon"))
				muonHist = None
				matchedMuonHist = None
				# Rebinning for Pt.. Most other variable can be shown in full range
				if args.bins != None and "Pt" in muon:
					minimum = tmpMuonHist.GetBinCenter(1)
					maximum = 0.5 * int(args.bins)
					muonHist = ROOT.TH1D(muon, muon, int(args.bins), minimum, maximum)
					matchedMuonHist = ROOT.TH1D(matchedMuon, matchedMuon, int(args.bins), minimum, maximum)
					for bin in range(1, int(args.bins) + 1):
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
				efficiencyGraph.SetLineColor(ROOT.kBlack)
				efficiencyGraph.SetMarkerColor(ROOT.kBlack)
				efficiencyGraph.SetMarkerSize(0.8)
				efficiencyGraph.SetMarkerColor(color)
				#efficiencyGraphs.append(efficiencyGraph)

				efficiencyGraph.SetMinimum(0)
				efficiencyGraph.SetMaximum(1.0)

				efficiencyGraph.GetXaxis().SetTitle(xLabel);
				efficiencyGraph.GetYaxis().SetTitle(yLabel);
				efficiencyGraph.Draw("AP")


		else:
			efficiency, matchedMuon, muon = eff
			print(efficiency, matchedMuon, muon)

			xLabel = findLabel(efficiency)

			tmpMuonHist = ROOT.TH1D(histogramFile.Get(muon).Clone(muon + "_tmp"))
			tmpMatchedMuonHist = ROOT.TH1D(histogramFile.Get(matchedMuon).Clone(matchedMuon + "_tmp"))
			muonHist = None
			matchedMuonHist = None
			if args.bins != None and "Pt" in muon:
				minimum = tmpMuonHist.GetBinCenter(1)
				maximum = 0.5 * int(args.bins)
				muonHist = ROOT.TH1D(muon, muon, int(args.bins), minimum, maximum)
				matchedMuonHist = ROOT.TH1D(matchedMuon, matchedMuon, int(args.bins), minimum, maximum)

				for bin in range(1, int(args.bins) + 1):
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
			efficiencyGraph.SetLineColor(ROOT.kBlack)
			efficiencyGraph.SetMarkerColor(ROOT.kBlack)
			efficiencyGraph.SetMarkerSize(0.8)
			#efficiencyGraphs.append(efficiencyGraph)

			efficiencyGraph.SetMinimum(0)
			efficiencyGraph.SetMaximum(1.0)

			efficiencyGraph.GetXaxis().SetTitle(xLabel);
			efficiencyGraph.GetYaxis().SetTitle(yLabel);
			efficiencyGraph.Draw("AP")

		canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + effName + ".pdf")

		canvas.SetLogy()
		canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + ".pdf")
		canvas.Close()

	common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)

	#plottingUrl = common.GetOSVariable("PLOTTING_URL")
	#print(plottingUrl + "/" + args.output_directory)
