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
ROOT.gStyle.SetPadLeftMargin(0.115)
ROOT.gStyle.SetPadRightMargin(0.03)
ROOT.gStyle.SetLegendBorderSize(0)
ROOT.gStyle.SetLegendBorderSize(0)
ROOT.gStyle.SetPadBorderSize(1)

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
	effName =  hist1.GetName().replace("N3x3", "").replace("Pt", "").replace("MatchedMuon", " (N_3x3 < 2) Efficiency") if "N3x3" in hist1.GetName() else hist1.GetName().replace("Pt", "").replace("MatchedMuon", " Efficiency")
	histIntegral_1 = hist1.Integral()
	histIntegral_2 = hist2.Integral()
	efficiencyString = '%s:%s%.1f +/- %.1f%%' % (effName, (" " * (31-len(effName))), 100 * histIntegral_1 / histIntegral_2, (100 * histIntegral_1 / histIntegral_2) * np.sqrt(histIntegral_2) / histIntegral_2)
	print (efficiencyString)
	return efficiencyString

if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	dustDir = GetOsVariable("DUSTDIR")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("--x-max", help="Number of bins", default = 60)
	parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/efficiency.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf efficiency")
	parser.add_argument("--do-ratio", default = False, action = "store_true", help = "Creates a ratio of isoMB1/Bmtf eff")

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

	xLabel = findLabel("Pt")
	yLabel = "Efficiency"
	width = 1200
	height = 1000
	#height = int(width / (3/4.))
	effName = "muonPt"

	canvas = ROOT.TCanvas(effName, effName, width, height)
	canvas.cd()

	histogramFile = ROOT.TFile(args.input_file)

	histogramFile.Print()
	print(histogramFile)
	print(histogramFile.GetListOfKeys())
	for key in histogramFile.GetListOfKeys():
		runNumber = key.GetName()
		print(runNumber)
		if runNumber == "runNumber": continue
		#print(runNumber)

		nEventsHist = histogramFile.Get(runNumber + "/numberOfEvents")
		#if isinstance(nEventsHist, ROOT.TH1I): continue
		nEvents = nEventsHist.GetBinContent(1)
		if not os.path.exists(args.output_directory + "/efficiency/" + runNumber + "/log"):
			os.makedirs(args.output_directory + "/efficiency/" + runNumber + "/log")


		muonPt = histogramFile.Get(runNumber + "/probeMuonPt_Bmtf")
		bmtfMatchedMuonPt = histogramFile.Get(runNumber + "/tfMatchedMuonPt_Bmtf")
		tfMatchedMuonPt = histogramFile.Get(runNumber + "/tfMatchedMuonPt")

		isoMb1MatchedMuonPt = histogramFile.Get(runNumber + "/isoMb1MatchedMuonPt")
		isoMb2MatchedMuonPt = histogramFile.Get(runNumber + "/isoMb2MatchedMuonPt")
		isoMb12MatchedMuonPt = histogramFile.Get(runNumber + "/isoMb12MatchedMuonPt")

		isoMb1MatchedMuonN3x3Pt = histogramFile.Get(runNumber + "/isoMb1MatchedMuonN3x3Pt")
		isoMb2MatchedMuonN3x3Pt = histogramFile.Get(runNumber + "/isoMb2MatchedMuonN3x3Pt")
		isoMb12MatchedMuonN3x3Pt = histogramFile.Get(runNumber + "/isoMb12MatchedMuonN3x3Pt")

		minimum = 0

		#yMin = 0
		yMin = 0
		yMax = 1.01
		#yMax = 1.02
		effBmtfGraph = ROOT.TGraphAsymmErrors(muonPt)
		effBmtfGraph.Divide(bmtfMatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
		effBmtfGraph.SetLineColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerSize(1.0)
		effBmtfGraph.SetTitle("BMTF Muon"); effBmtfGraph.GetXaxis().SetTitle(xLabel); effBmtfGraph.GetYaxis().SetTitle(yLabel);
		effBmtfGraph.SetMinimum(yMin); effBmtfGraph.SetMaximum(yMax)

		effIsoMb1Graph = ROOT.TGraphAsymmErrors(muonPt)
		effIsoMb1Graph.Divide(isoMb1MatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
		effIsoMb1Graph.SetLineColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerSize(1.0)
		effIsoMb1Graph.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Graph.GetXaxis().SetTitle(xLabel); effIsoMb1Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb1Graph.SetMinimum(yMin); effIsoMb1Graph.SetMaximum(yMax)

		effIsoMb12Graph = ROOT.TGraphAsymmErrors(muonPt)
		effIsoMb12Graph.Divide(isoMb12MatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
		effIsoMb12Graph.SetLineColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerSize(1.0)
		effIsoMb12Graph.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Graph.GetXaxis().SetTitle(xLabel); effIsoMb12Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb12Graph.SetMinimum(yMin); effIsoMb12Graph.SetMaximum(yMax)

		effIsoMb1N3x3Graph = ROOT.TGraphAsymmErrors(muonPt)
		effIsoMb1N3x3Graph.Divide(isoMb1MatchedMuonN3x3Pt, muonPt, "cl=0.683 b(1,1) mode")
		effIsoMb1N3x3Graph.SetLineColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerSize(1.0)
		effIsoMb1N3x3Graph.SetTitle("BMTF+IsoMB1 Muon (N_{3x3} #leq 1)"); effIsoMb1N3x3Graph.GetXaxis().SetTitle(xLabel); effIsoMb1N3x3Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb1N3x3Graph.SetMinimum(yMin); effIsoMb1N3x3Graph.SetMaximum(yMax)

		effIsoMb12N3x3Graph = ROOT.TGraphAsymmErrors(muonPt)
		effIsoMb12N3x3Graph.Divide(isoMb12MatchedMuonN3x3Pt, muonPt, "cl=0.683 b(1,1) mode")
		effIsoMb12N3x3Graph.SetLineColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerSize(1.0)
		effIsoMb12N3x3Graph.SetTitle("BMTF+IsoMB12 Muon (N_{3x3} #leq 1)"); effIsoMb12N3x3Graph.GetXaxis().SetTitle(xLabel); effIsoMb12N3x3Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb12N3x3Graph.SetMinimum(yMin); effIsoMb12N3x3Graph.SetMaximum(yMax)

		effIsoMb1N3x3Graph.SetLineStyle(ROOT.kDotted)
		effIsoMb12N3x3Graph.SetLineStyle(ROOT.kDotted)

		efficiencyPad = None
		if args.do_ratio:
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

		effBmtfGraph.GetXaxis().SetRangeUser(0, float(args.x_max));

		canvas.Modified()
		legend = ROOT.TLegend(0.6, 0.2, 0.9, 0.45)

		legendSize = 0.055
		legend.SetBorderSize(1)
		#legend.SetTextFont(62)
		legend.SetLineColor(0)
		legend.SetLineStyle(0)
		#legend.SetLineWidth(1)
		legend.SetFillColorAlpha(0,1)
		legend.SetFillStyle(1001)

		effBmtfGraph.Draw("SAME AP")
		legend.AddEntry(effBmtfGraph)
		if not args.bmtf_only:
			effIsoMb1Graph.Draw("SAME P")
			effIsoMb1N3x3Graph.Draw("SAME P")

			effIsoMb12Graph.Draw("SAME P")
			effIsoMb12N3x3Graph.Draw("SAME P")

			legend.AddEntry(effIsoMb1Graph)
			legend.AddEntry(effIsoMb1N3x3Graph)
			legend.AddEntry(effIsoMb12Graph)
			legend.AddEntry(effIsoMb12N3x3Graph)

		legend.Draw("SAME")

		if args.do_ratio:

			effBmtfGraph.GetXaxis().SetLabelSize(0)
			effIsoMb1Graph.GetXaxis().SetLabelSize(0)
			effIsoMb1N3x3Graph.GetXaxis().SetLabelSize(0)
			effIsoMb12Graph.GetXaxis().SetLabelSize(0)
			effIsoMb12N3x3Graph.GetXaxis().SetLabelSize(0)

			canvas.cd()
			ratioPad = ROOT.TPad("ratioPad", "ratioPad", 0, 0, 1, 0.31);
			#ratioPad = ROOT.TPad("ratioPad", "ratioPad", 0, 0, 1, 0.1);
			#ratioPad.SetTopMargin(0.05);
			ratioPad.SetBottomMargin(0.225);
			ratioPad.SetFillStyle(0);
			ratioPad.SetTicks()
			ratioPad.SetGrid()
			ratioPad.Update()
			ratioPad.Draw("SAME");

			ratioLabel = "#frac{IsoMB}{BMTF}"

			pureIsoMb1MatchedMuonPt = isoMb1MatchedMuonPt.Clone()
			pureIsoMb1MatchedMuonPt.Add(bmtfMatchedMuonPt, -1)
			effIsoMb1Ratio = ROOT.TGraphAsymmErrors(bmtfMatchedMuonPt)
			effIsoMb1Ratio.Divide(pureIsoMb1MatchedMuonPt, bmtfMatchedMuonPt, "cl=0.683 b(1,1) mode")
			#effIsoMb1Ratio = ROOT.TGraphAsymmErrors(isoMb1MatchedMuonPt, bmtfMatchedMuonPt)
			effIsoMb1Ratio.SetLineColor(ROOT.kRed-2); effIsoMb1Ratio.SetMarkerColor(ROOT.kRed-2); effIsoMb1Ratio.SetMarkerColor(ROOT.kRed-2); effIsoMb1Ratio.SetMarkerSize(0.9)
			effIsoMb1Ratio.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb1Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1Ratio.GetYaxis().SetTitle(ratioLabel);

			effIsoMb1Ratio.GetXaxis().SetLabelSize(0.07)
			effIsoMb1Ratio.GetXaxis().SetTitleSize(0.09)
			effIsoMb1Ratio.GetXaxis().SetTitleOffset(1.15)

			effIsoMb1Ratio.GetYaxis().SetLabelSize(0.07)
			effIsoMb1Ratio.GetYaxis().SetTitleSize(0.07)
			effIsoMb1Ratio.GetYaxis().SetTitleOffset(0.55)
			#effIsoMb1Ratio.SetMinimum(1); effIsoMb1Ratio.SetMaximum(1.5)
			effIsoMb1Ratio.GetXaxis().SetRangeUser(0, float(args.x_max))

			pureIsoMb12MatchedMuonPt = isoMb12MatchedMuonPt.Clone()
			pureIsoMb12MatchedMuonPt.Add(bmtfMatchedMuonPt, -1)
			effIsoMb12Ratio = ROOT.TGraphAsymmErrors(muonPt)
			effIsoMb12Ratio.Divide(pureIsoMb12MatchedMuonPt, bmtfMatchedMuonPt, "cl=0.683 b(1,1) mode")
			effIsoMb12Ratio.SetLineColor(ROOT.kAzure-2); effIsoMb12Ratio.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Ratio.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Ratio.SetMarkerSize(0.9)
			effIsoMb12Ratio.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Ratio.GetXaxis().SetTitle(xLabel); effIsoMb12Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb12Ratio.SetMinimum(yMin); effIsoMb12Ratio.SetMaximum(yMax)

			pureIsoMb1MatchedMuonN3x3Pt = isoMb1MatchedMuonN3x3Pt.Clone()
			pureIsoMb1MatchedMuonN3x3Pt.Add(bmtfMatchedMuonPt, -1)
			effIsoMb1N3x3Ratio = ROOT.TGraphAsymmErrors(muonPt)
			effIsoMb1N3x3Ratio.Divide(pureIsoMb1MatchedMuonN3x3Pt, bmtfMatchedMuonPt, "cl=0.683 b(1,1) mode")
			effIsoMb1N3x3Ratio.SetLineColor(ROOT.kRed-8); effIsoMb1N3x3Ratio.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Ratio.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Ratio.SetMarkerSize(0.9)
			effIsoMb1N3x3Ratio.SetTitle("BMTF+IsoMB1 Muon (N_{3x3} #leq 1)"); effIsoMb1N3x3Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1N3x3Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb1N3x3Ratio.SetMinimum(yMin); effIsoMb1N3x3Ratio.SetMaximum(yMax)

			pureIsoMb12MatchedMuonN3x3Pt = isoMb12MatchedMuonN3x3Pt.Clone()
			pureIsoMb12MatchedMuonN3x3Pt.Add(bmtfMatchedMuonPt, -1)
			effIsoMb12N3x3Ratio = ROOT.TGraphAsymmErrors(muonPt)
			effIsoMb12N3x3Ratio.Divide(pureIsoMb12MatchedMuonN3x3Pt, bmtfMatchedMuonPt, "cl=0.683 b(1,1) mode")
			effIsoMb12N3x3Ratio.SetLineColor(ROOT.kAzure-8); effIsoMb12N3x3Ratio.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Ratio.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Ratio.SetMarkerSize(0.9)
			effIsoMb12N3x3Ratio.SetTitle("BMTF+IsoMB12 Muon (N_{3x3} #leq 1)"); effIsoMb12N3x3Ratio.GetXaxis().SetTitle(xLabel); effIsoMb12N3x3Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb12N3x3Ratio.SetMinimum(yMin); effIsoMb12N3x3Ratio.SetMaximum(yMax)

			effIsoMb1N3x3Ratio.SetLineStyle(ROOT.kDotted)
			effIsoMb12N3x3Ratio.SetLineStyle(ROOT.kDotted)

			ratioPad.cd()
			effIsoMb1Ratio.Draw("SAME AP")
			if not args.bmtf_only:
				effIsoMb1Ratio.Draw("SAME P")
				effIsoMb1N3x3Ratio.Draw("SAME P")

				effIsoMb12Ratio.Draw("SAME P")
				effIsoMb12N3x3Ratio.Draw("SAME P")

		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".pdf")
		canvas.SetLogz()
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".pdf")
		canvas.Close()


		effTfGraph = ROOT.TGraphAsymmErrors(muonPt)
		effTfGraph.Divide(tfMatchedMuonPt, muonPt, "cl=0.683 b(1,1) mode")
		effTfGraph.SetLineColor(ROOT.kBlack); effTfGraph.SetMarkerColor(ROOT.kBlack); effTfGraph.SetMarkerColor(ROOT.kBlack); effTfGraph.SetMarkerSize(1.0)
		effTfGraph.SetTitle("TF Muon"); effTfGraph.GetXaxis().SetTitle(xLabel); effTfGraph.GetYaxis().SetTitle(yLabel);
		effTfGraph.SetMinimum(yMin); effTfGraph.SetMaximum(yMax)

		#canvas = ROOT.TCanvas(effName, effName, width, height)
		#canvas.Modified()
		#canvas.cd()
		#effTfGraph.Draw("SAME AP")
		#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + "_uGMT.png")
		#canvas.SaveAs(args.output_directory + "/efficiency/" + effName + "_uGMT.pdf")

		#canvas.SetLogy()
		#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + "_uGMT.png")
		#canvas.SaveAs(args.output_directory + "/efficiency/log/" + effName + "_uGMT.pdf")
		#canvas.Close()





		common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)

		effBmtfString        = printEfficiency(bmtfMatchedMuonPt, muonPt)
		effisoMB1String      = printEfficiency(isoMb1MatchedMuonPt, muonPt)
		effisoMB12String     = printEfficiency(isoMb12MatchedMuonPt, muonPt)
		effisoMB1N3x3String  = printEfficiency(isoMb1MatchedMuonN3x3Pt, muonPt)
		effisoMB12N3x3String = printEfficiency(isoMb12MatchedMuonN3x3Pt, muonPt)
		with open(args.output_directory + "/efficiency.txt", "w") as effFile:
			effFile.write("Total Efficiency using " + args.input_file + "\n")
			effFile.write(effBmtfString + "\n")
			effFile.write(effisoMB1String + "\n")
			effFile.write(effisoMB12String + "\n")
			effFile.write(effisoMB1N3x3String + "\n")
			effFile.write(effisoMB12N3x3String + "\n")
