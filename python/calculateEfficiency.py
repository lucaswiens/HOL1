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
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	dustDir = GetOsVariable("DUSTDIR")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("--run1", default = True, action = "store_false", help = "Create only 1D historams")
	parser.add_argument("--run2", default = True, action = "store_false", help = "Create only 2D historams")
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

	create1DEfficiency = args.run2
	create2DEfficiency = args.run1

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
			if create2DEfficiency:
				os.makedirs(args.output_directory + "/efficiency/" + runNumber + "/2D/log")
				os.makedirs(args.output_directory + "/efficiency/" + runNumber + "/2D/ratio/log")

		if create1DEfficiency:
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

		#2d
		if create2DEfficiency:
			for name in ["Pt", "Phi"]:
				bmtfHist = Make2DEfficiencyPlot(histogramFile, runNumber, "BMTF", args, name = name, cut = "")
				for cut in ["", "N3x3", "AbsIEta3", "HighADC"]:
					for algorithm in ["IsoMB1", "IsoMB2", "IsoMB12"]:
						print("")
						print(name + " " + cut + " " + algorithm)
						isoMbHist = Make2DEfficiencyPlot(histogramFile, runNumber, algorithm, args, name = name, cut = cut)
						Make2DRatioPlot(bmtfHist, isoMbHist, algorithm, runNumber, args, name = name, cut = cut)

def MakeEfficiencyPlot(histogramFile, runNumber, efficiencyMap, args, name = "Pt", cut = "", width = 1200, height = 1000):
	SetupStyle()

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
	fontSize = 30
	effBmtfGraph    = GetEfficiencyGraph(bmtfMatchedMuon,    muon, xLabel, yLabel, args, algorithm = "BMTF",    yMin = yMin, yMax = yMax, fontSize = fontSize)
	effIsoMb1Graph  = GetEfficiencyGraph(isoMb1MatchedMuon,  muon, xLabel, yLabel, args, algorithm = "IsoMB1",  yMin = yMin, yMax = yMax, fontSize = fontSize)
	effIsoMb2Graph  = GetEfficiencyGraph(isoMb2MatchedMuon,  muon, xLabel, yLabel, args, algorithm = "IsoMB2",  yMin = yMin, yMax = yMax, fontSize = fontSize)
	effIsoMb12Graph = GetEfficiencyGraph(isoMb12MatchedMuon, muon, xLabel, yLabel, args, algorithm = "IsoMB12", yMin = yMin, yMax = yMax, fontSize = fontSize)

	canvas = ROOT.TCanvas(name, name, width, height)
	canvas.cd()
	efficiencyPad = None
	padBorder = 0.4
	if args.ratio:
		efficiencyPad = ROOT.TPad("Pad", "Pad", 0, padBorder, 1, 1);
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
		canvas.cd()
		ratioPad = ROOT.TPad("ratioPad", "ratioPad", 0, 0, 1, padBorder);
		ratioPad.SetBottomMargin(0.3);
		ratioPad.SetFillStyle(0);
		ratioPad.SetTicks()
		ratioPad.SetGrid()
		ratioPad.Update()
		ratioPad.Draw("SAME");

		ratioLabel = "#frac{IsoMB}{BMTF}"

		effIsoMb1Ratio  = GetRatio(isoMb1MatchedMuon,  bmtfMatchedMuon, xLabel, ratioLabel, args, algorithm = "IsoMB1",  yMin = 0, yMax = 0.05, fontSize = fontSize)
		effIsoMb2Ratio  = GetRatio(isoMb2MatchedMuon,  bmtfMatchedMuon, xLabel, ratioLabel, args, algorithm = "IsoMB2",  yMin = 0, yMax = 0.05, fontSize = fontSize)
		effIsoMb12Ratio = GetRatio(isoMb12MatchedMuon, bmtfMatchedMuon, xLabel, ratioLabel, args, algorithm = "IsoMB12", yMin = 0, yMax = 0.05, fontSize = fontSize)

		if name == "Pt":
			effIsoMb1Ratio.GetXaxis().SetRangeUser(0, float(args.x_max))

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
	pass

def Make2DEfficiencyPlot(histogramFile, runNumber, algorithm, args, name = "Pt", cut =  "", width = 1200, height = 1000):
	SetupStyle(option = "2D")

	recoMuon = histogramFile.Get(runNumber + "/probeMuonEta_vs_ProbeMuon" + name)
	l1MuonString = (runNumber + "/tfMatchedMuon" + cut + "Eta_vs_Muon" + name + "_Bmtf") if algorithm == "BMTF" else (runNumber + "/" + algorithm.replace("I", "i").replace("MB", "Mb") + "MatchedMuon" + cut + "Eta_vs_Muon" + name)
	l1Muon = histogramFile.Get(l1MuonString)

	xLabel = findLabel("Eta") # The 2D histograms are always against eta
	yLabel = findLabel(name)
	effHist = Get2DEfficiency(l1Muon, recoMuon, xLabel, yLabel, args, algorithm =algorithm, fontSize = 40)
	common.GenerateColorGradient()

	effName = "Eta_vs_" + name + "_" + algorithm + ("_" + cut) * (cut != "")
	canvas = ROOT.TCanvas(effName, effName, width, height)
	#effHist.UseCurrentStyle()
	effHist.Draw("colz")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/2D/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/2D/" + effName + ".pdf")
	canvas.SetLogz()
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/2D/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/2D/log/" + effName + ".pdf")
	canvas.Close()
	return effHist

def Make2DRatioPlot(bmtf, isoMb, algorithm, runNumber, args, name = "Pt", cut =  "", width = 1200, height = 1000):
	SetupStyle(option = "2D")
	xLabel = findLabel("Eta")
	yLabel = findLabel(name)

	ratio = isoMb.Clone("_ratio")
	ratio.Divide(bmtf)

	zLabel = "#frac{Efficiency#left(BMTF + " + algorithm + "#right)}{Efficiency#left(BMTF#right)}"
	ratio = isoMb.Clone("_Clone")
	ratio.Divide(bmtf)
	ratio.GetZaxis().SetTitle(zLabel)
	ratio.SetMinimum(1.0);
	ratio.SetMaximum(1.1);

	#common.GenerateColorGradient()
	effName = "Eta_vs_" + name + "_" + algorithm + ("_" + cut) * (cut != "")
	canvas = ROOT.TCanvas(effName, effName, width, height)
	#ratio.UseCurrentStyle()
	ratio.Draw("colz")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/2D/ratio/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/2D/ratio/" + effName + ".pdf")
	canvas.SetLogz()
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/2D/ratio/log/" + effName + ".png")
	canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/2D/ratio/log/" + effName + ".pdf")
	canvas.Close()
	pass

def GetEfficiencyGraph(l1Muon, recoMuon, xLabel, yLabel, args, algorithm = "BMTF", yMin = 0, yMax = 1.01, fontSize = 20):
	effGraph = ROOT.TGraphAsymmErrors(recoMuon)
	effGraph.Divide(l1Muon, recoMuon, "cl=0.683 b(1,1) mode")
	effGraph.SetLineColor(common.COLORMAP[algorithm])
	effGraph.SetMarkerColor(common.COLORMAP[algorithm])
	effGraph.SetMarkerColor(common.COLORMAP[algorithm])
	effGraph.SetMarkerSize(1.0)
	effGraph.SetTitle(algorithm + " Muon")
	effGraph.GetXaxis().SetTitle(xLabel)
	effGraph.GetYaxis().SetTitle(yLabel)

	effGraph.SetMinimum(yMin)
	effGraph.SetMaximum(yMax)

	if args.ratio:
		effGraph.GetXaxis().SetLabelSize(0)

		effGraph.GetYaxis().SetLabelSize(fontSize)
		effGraph.GetYaxis().SetTitleSize(fontSize)
		effGraph.GetYaxis().SetTitleOffset(1.8)
	else:
		effGraph.GetXaxis().SetLabelSize(fontSize)
		effGraph.GetXaxis().SetTitleSize(fontSize)
		effGraph.GetXaxis().SetTitleOffset(1.8)

		effGraph.GetYaxis().SetLabelSize(fontSize)
		effGraph.GetYaxis().SetTitleSize(fontSize)
		effGraph.GetYaxis().SetTitleOffset(1.8)
	return effGraph

def Get2DEfficiency(l1Muon, recoMuon, xLabel, yLabel, args, algorithm = "BMTF", zMin = 0, zMax = 1., fontSize = 20):
	effHist = l1Muon.Clone("_eff")
	effHist.Divide(recoMuon)

	effHist.SetLineColor(common.COLORMAP[algorithm])
	effHist.SetMarkerColor(common.COLORMAP[algorithm])
	effHist.SetMarkerColor(common.COLORMAP[algorithm])

	effHist.SetContour(100)
	effHist.SetTitle(algorithm + "Muon")
	#return effHist

	effHist.GetXaxis().SetTitle(xLabel)
	effHist.GetXaxis().SetLabelFont(43)
	effHist.GetXaxis().SetTitleFont(43)
	effHist.GetXaxis().SetLabelSize(fontSize)
	effHist.GetXaxis().SetTitleSize(fontSize)
	effHist.GetXaxis().SetTitleOffset(1.)

	effHist.GetYaxis().SetTitle(yLabel)
	effHist.GetYaxis().SetLabelFont(43)
	effHist.GetYaxis().SetTitleFont(43)
	effHist.GetYaxis().SetLabelSize(fontSize)
	effHist.GetYaxis().SetTitleSize(fontSize)
	effHist.GetYaxis().SetTitleOffset(1.25)

	zLabel = "Efficiency#left(" + algorithm + "#right)"
	effHist.GetZaxis().SetTitle(zLabel)
	effHist.GetZaxis().SetLabelFont(43)
	effHist.GetZaxis().SetTitleFont(43)
	effHist.GetZaxis().SetLabelSize(fontSize)
	effHist.GetZaxis().SetTitleSize(fontSize)
	effHist.GetZaxis().SetTitleOffset(1.35)
	effHist.GetZaxis().SetNdivisions(505);
	effHist.SetMinimum(zMin);
	effHist.SetMaximum(zMax);
	effHist.GetZaxis().SetTitleOffset(1.6)
	ROOT.gStyle.SetPadRightMargin(0.20)

	effHist.GetXaxis().SetRangeUser(-1, 1);
	return effHist

def GetRatio(isoMb, bmtf, xLabel, yLabel, args, algorithm = "BMTF", yMin = 0, yMax = 0.05, fontSize = 20):
	pureIsoMb = isoMb.Clone()
	pureIsoMb.Add(bmtf, -1) # IsoMB histogram include BMTF muons
	effRatio = ROOT.TGraphAsymmErrors(bmtf)
	effRatio.Divide(pureIsoMb, bmtf, "cl=0.683 b(1,1) mode")
	effRatio.SetLineColor(common.COLORMAP[algorithm])
	effRatio.SetMarkerColor(common.COLORMAP[algorithm])
	effRatio.SetMarkerColor(common.COLORMAP[algorithm])
	effRatio.SetMarkerSize(1)
	effRatio.SetTitle(algorithm)

	effRatio.GetXaxis().SetTitle(xLabel)
	effRatio.GetXaxis().SetLabelSize(fontSize)
	effRatio.GetXaxis().SetTitleSize(fontSize* 1.35)
	effRatio.GetXaxis().SetTitleOffset(3)

	effRatio.GetYaxis().SetTitle(yLabel)
	effRatio.GetYaxis().SetLabelSize(fontSize)
	effRatio.GetYaxis().SetTitleSize(fontSize)
	effRatio.GetYaxis().SetTitleOffset(1.8)
	effRatio.GetYaxis().SetNdivisions(505);
	effRatio.SetMinimum(yMin)
	effRatio.SetMaximum(yMax)
	return effRatio

def SetupStyle(option = ""):
	ROOT.gStyle.SetOptTitle(0)
	ROOT.gStyle.SetOptStat(0)
	ROOT.gStyle.SetLegendBorderSize(0)
	ROOT.gStyle.SetLegendBorderSize(0)
	ROOT.gStyle.SetPadBorderSize(1)

	if option == "":
		ROOT.gStyle.SetPadTopMargin(0.05)
		ROOT.gStyle.SetPadBottomMargin(0.125)
		ROOT.gStyle.SetPadLeftMargin(0.115)
		ROOT.gStyle.SetPadRightMargin(0.03)
		ROOT.gStyle.SetLabelFont(43, "XYZ");
		ROOT.gStyle.SetTitleFont(43, "XYZ");
	if "2D" in option:
		#pass
		ROOT.gStyle.SetPadTopMargin(0.025)
		ROOT.gStyle.SetPadBottomMargin(0.09)
		ROOT.gStyle.SetPadLeftMargin(0.125)
		ROOT.gStyle.SetPadRightMargin(0.175)
		#ROOT.gStyle.SetLabelFont(42, "XYZ");
		#ROOT.gStyle.SetTitleFont(42, "XYZ");
	pass

if __name__=="__main__":
	main()

