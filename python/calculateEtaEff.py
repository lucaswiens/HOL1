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
	dustDir = GetOsVariable("DUSTDIR")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	parser.add_argument("-n", "--number-of-files", help="Number of files that will be processed at once", default = 100)
	parser.add_argument("-b", "--bins", help="Number of bins", default = None)
	parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/efficiency.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf efficiency")
	parser.add_argument("--do-ratio", default = False, action = "store_true", help = "Creates a ratio of isoMB1/Bmtf eff")

	args = parser.parse_args()


	args.output_directory = dustDir + "/HoPlots/" + date + "/" + args.output_directory

	histogramFile = ROOT.TFile(args.input_file)


	for key in histogramFile.GetListOfKeys():
		runNumber = key.GetName()
		if runNumber == "runNumber": continue

		nEventsHist = histogramFile.Get(runNumber + "/numberOfEvents")
		#if isinstance(nEventsHist, ROOT.TH1I): continue
		nEvents = nEventsHist.GetBinContent(1)
		if not os.path.exists(args.output_directory + "/efficiency/" + runNumber + "/log"):
			os.makedirs(args.output_directory + "/efficiency/" + runNumber + "/log")


		xLabel = findLabel("Eta")
		yLabel = "Efficiency"
		width = 1200
		height = 1000
		#height = int(width / 1.618030)
		#height = int(width * 3/4.)
		#height = int(width / (3/4.))
		effName = "muonEta"

		canvas = ROOT.TCanvas(effName, effName, width, height)
		canvas.SetGrid()


		muonEta = histogramFile.Get(runNumber + "/probeMuonEta_Bmtf")
		bmtfMatchedMuonEta = histogramFile.Get(runNumber + "/tfMatchedMuonEta_Bmtf")
		tfMatchedMuonEta = histogramFile.Get(runNumber + "/tfMatchedMuonEta")

		isoMb1MatchedMuonEta = histogramFile.Get(runNumber + "/isoMb1MatchedMuonEta")
		isoMb2MatchedMuonEta = histogramFile.Get(runNumber + "/isoMb2MatchedMuonEta")
		isoMb12MatchedMuonEta = histogramFile.Get(runNumber + "/isoMb12MatchedMuonEta")

		isoMb1MatchedMuonN3x3Eta = histogramFile.Get(runNumber + "/isoMb1MatchedMuonN3x3Eta")
		isoMb2MatchedMuonN3x3Eta = histogramFile.Get(runNumber + "/isoMb2MatchedMuonN3x3Eta")
		isoMb12MatchedMuonN3x3Eta = histogramFile.Get(runNumber + "/isoMb12MatchedMuonN3x3Eta")

		bmtfMatchedMuonEta.SetTitle("")

		isoMb1MatchedMuonEta.SetTitle("")
		isoMb2MatchedMuonEta.SetTitle("")
		isoMb12MatchedMuonEta.SetTitle("")

		isoMb1MatchedMuonN3x3Eta.SetTitle("")
		isoMb2MatchedMuonN3x3Eta.SetTitle("")
		isoMb12MatchedMuonN3x3Eta.SetTitle("")

		yMin = 0
		yMax = 1.01
		#yMin = 0.6
		#yMax = 1.01

		effBmtfGraph = ROOT.TGraphAsymmErrors(muonEta)
		effBmtfGraph.Divide(bmtfMatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
		effBmtfGraph.SetLineColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerColor(ROOT.kBlack); effBmtfGraph.SetMarkerSize(1.0)
		effBmtfGraph.SetTitle("BMTF Muon"); effBmtfGraph.GetXaxis().SetTitle(xLabel); effBmtfGraph.GetYaxis().SetTitle(yLabel);
		effBmtfGraph.SetMinimum(yMin); effBmtfGraph.SetMaximum(yMax)

		effIsoMb1Graph = ROOT.TGraphAsymmErrors(muonEta)
		effIsoMb1Graph.Divide(isoMb1MatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
		effIsoMb1Graph.SetLineColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerColor(ROOT.kRed-2); effIsoMb1Graph.SetMarkerSize(1.0)
		effIsoMb1Graph.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Graph.GetXaxis().SetTitle(xLabel); effIsoMb1Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb1Graph.SetMinimum(yMin); effIsoMb1Graph.SetMaximum(yMax)

		effIsoMb12Graph = ROOT.TGraphAsymmErrors(muonEta)
		effIsoMb12Graph.Divide(isoMb12MatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
		effIsoMb12Graph.SetLineColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Graph.SetMarkerSize(1.0)
		effIsoMb12Graph.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Graph.GetXaxis().SetTitle(xLabel); effIsoMb12Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb12Graph.SetMinimum(yMin); effIsoMb12Graph.SetMaximum(yMax)

		effIsoMb1N3x3Graph = ROOT.TGraphAsymmErrors(muonEta)
		effIsoMb1N3x3Graph.Divide(isoMb1MatchedMuonN3x3Eta, muonEta, "cl=0.683 b(1,1) mode")
		effIsoMb1N3x3Graph.SetLineColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Graph.SetMarkerSize(1.0)
		effIsoMb1N3x3Graph.SetTitle("BMTF+IsoMB1 Muon (N_{3x3} #leq 1)"); effIsoMb1N3x3Graph.GetXaxis().SetTitle(xLabel); effIsoMb1N3x3Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb1N3x3Graph.SetMinimum(yMin); effIsoMb1N3x3Graph.SetMaximum(yMax)

		effIsoMb12N3x3Graph = ROOT.TGraphAsymmErrors(muonEta)
		effIsoMb12N3x3Graph.Divide(isoMb12MatchedMuonN3x3Eta, muonEta, "cl=0.683 b(1,1) mode")
		effIsoMb12N3x3Graph.SetLineColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerColor(ROOT.kAzure-8); effIsoMb12N3x3Graph.SetMarkerSize(1.0)
		effIsoMb12N3x3Graph.SetTitle("BMTF+IsoMB12 Muon (N_{3x3} #leq 1)"); effIsoMb12N3x3Graph.GetXaxis().SetTitle(xLabel); effIsoMb12N3x3Graph.GetYaxis().SetTitle(yLabel);
		effIsoMb12N3x3Graph.SetMinimum(yMin); effIsoMb12N3x3Graph.SetMaximum(yMax)

		effIsoMb1N3x3Graph.SetLineStyle(ROOT.kDotted)
		effIsoMb12N3x3Graph.SetLineStyle(ROOT.kDotted)

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

		effBmtfGraph.Draw("same ap")
		legend.AddEntry(effBmtfGraph)
		if not args.bmtf_only:
			effIsoMb1Graph.Draw("same p")
			effIsoMb1N3x3Graph.Draw("same p")

			effIsoMb12Graph.Draw("same p")
			effIsoMb12N3x3Graph.Draw("same p")

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

			pureIsoMb1MatchedMuonEta = isoMb1MatchedMuonEta.Clone()
			pureIsoMb1MatchedMuonEta.Add(bmtfMatchedMuonEta, -1)
			effIsoMb1Ratio = ROOT.TGraphAsymmErrors(bmtfMatchedMuonEta)
			effIsoMb1Ratio.Divide(pureIsoMb1MatchedMuonEta, bmtfMatchedMuonEta, "cl=0.683 b(1,1) mode")
			#effIsoMb1Ratio = ROOT.TGraphAsymmErrors(isoMb1MatchedMuonEta, bmtfMatchedMuonEta)
			effIsoMb1Ratio.SetLineColor(ROOT.kRed-2); effIsoMb1Ratio.SetMarkerColor(ROOT.kRed-2); effIsoMb1Ratio.SetMarkerColor(ROOT.kRed-2); effIsoMb1Ratio.SetMarkerSize(0.9)
			effIsoMb1Ratio.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb1Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1Ratio.GetYaxis().SetTitle(ratioLabel);

			effIsoMb1Ratio.GetXaxis().SetLabelSize(0.07)
			effIsoMb1Ratio.GetXaxis().SetTitleSize(0.09)
			effIsoMb1Ratio.GetXaxis().SetTitleOffset(1.1)

			effIsoMb1Ratio.GetYaxis().SetLabelSize(0.07)
			effIsoMb1Ratio.GetYaxis().SetTitleSize(0.07)
			effIsoMb1Ratio.GetYaxis().SetTitleOffset(0.5)
			#effIsoMb1Ratio.SetMinimum(1); effIsoMb1Ratio.SetMaximum(1.5)
			#effIsoMb1Ratio.GetXaxis().SetRangeUser(0, float(args.x_max))

			pureIsoMb12MatchedMuonEta = isoMb12MatchedMuonEta.Clone()
			pureIsoMb12MatchedMuonEta.Add(bmtfMatchedMuonEta, -1)
			effIsoMb12Ratio = ROOT.TGraphAsymmErrors(muonEta)
			effIsoMb12Ratio.Divide(pureIsoMb12MatchedMuonEta, bmtfMatchedMuonEta, "cl=0.683 b(1,1) mode")
			effIsoMb12Ratio.SetLineColor(ROOT.kAzure-2); effIsoMb12Ratio.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Ratio.SetMarkerColor(ROOT.kAzure-2); effIsoMb12Ratio.SetMarkerSize(0.9)
			effIsoMb12Ratio.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Ratio.GetXaxis().SetTitle(xLabel); effIsoMb12Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb12Ratio.SetMinimum(yMin); effIsoMb12Ratio.SetMaximum(yMax)

			pureIsoMb1MatchedMuonN3x3Eta = isoMb1MatchedMuonN3x3Eta.Clone()
			pureIsoMb1MatchedMuonN3x3Eta.Add(bmtfMatchedMuonEta, -1)
			effIsoMb1N3x3Ratio = ROOT.TGraphAsymmErrors(muonEta)
			effIsoMb1N3x3Ratio.Divide(pureIsoMb1MatchedMuonN3x3Eta, bmtfMatchedMuonEta, "cl=0.683 b(1,1) mode")
			effIsoMb1N3x3Ratio.SetLineColor(ROOT.kRed-8); effIsoMb1N3x3Ratio.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Ratio.SetMarkerColor(ROOT.kRed-8); effIsoMb1N3x3Ratio.SetMarkerSize(0.9)
			effIsoMb1N3x3Ratio.SetTitle("BMTF+IsoMB1 Muon (N_{3x3} #leq 1)"); effIsoMb1N3x3Ratio.GetXaxis().SetTitle(xLabel); effIsoMb1N3x3Ratio.GetYaxis().SetTitle(ratioLabel);
			effIsoMb1N3x3Ratio.SetMinimum(yMin); effIsoMb1N3x3Ratio.SetMaximum(yMax)

			pureIsoMb12MatchedMuonN3x3Eta = isoMb12MatchedMuonN3x3Eta.Clone()
			pureIsoMb12MatchedMuonN3x3Eta.Add(bmtfMatchedMuonEta, -1)
			effIsoMb12N3x3Ratio = ROOT.TGraphAsymmErrors(muonEta)
			effIsoMb12N3x3Ratio.Divide(pureIsoMb12MatchedMuonN3x3Eta, bmtfMatchedMuonEta, "cl=0.683 b(1,1) mode")
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



		effTfGraph = ROOT.TGraphAsymmErrors(muonEta)
		effTfGraph.Divide(tfMatchedMuonEta, muonEta, "cl=0.683 b(1,1) mode")
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



		muonEta_vs_MuonPt = histogramFile.Get(runNumber + "/probeMuonEta_vs_ProbeMuonPt")
		bmtfMatchedMuonEta_vs_MuonPt = histogramFile.Get(runNumber + "/bmtfMatchedMuonEta_vs_MuonPt")

		isoMb1MatchedMuonEta_vs_MuonPt = histogramFile.Get(runNumber + "/isoMb1MatchedMuonEta_vs_MuonPt")
		isoMb2MatchedMuonEta_vs_MuonPt = histogramFile.Get(runNumber + "/isoMb2MatchedMuonEta_vs_MuonPt")
		isoMb12MatchedMuonEta_vs_MuonPt = histogramFile.Get(runNumber + "/isoMb12MatchedMuonEta_vs_MuonPt")

		xLabel = findLabel("Eta")
		yLabel = findLabel("Pt")

		zOffset = 1.65

		effBmtfHist = ROOT.TH2D(bmtfMatchedMuonEta_vs_MuonPt)
		effBmtfHist.Divide(muonEta_vs_MuonPt)
		effBmtfHist.SetLineColor(ROOT.kBlack); effBmtfHist.SetMarkerColor(ROOT.kBlack); effBmtfHist.SetMarkerColor(ROOT.kBlack); effBmtfHist.SetMarkerSize(1.0)
		effBmtfHist.SetTitle("BMTF Muon"); effBmtfHist.GetXaxis().SetTitle(xLabel); effBmtfHist.GetYaxis().SetTitle(yLabel); effBmtfHist.GetZaxis().SetTitle("BMTF efficiency");
		effBmtfHist.GetZaxis().SetTitleOffset(zOffset)
		effBmtfHist.SetStats(False);


		effIsoMb1Hist = ROOT.TH2D(isoMb1MatchedMuonEta_vs_MuonPt)
		effIsoMb1Hist.Divide(muonEta_vs_MuonPt)
		effIsoMb1Hist.SetLineColor(ROOT.kRed); effIsoMb1Hist.SetMarkerColor(ROOT.kRed); effIsoMb1Hist.SetMarkerColor(ROOT.kRed); effIsoMb1Hist.SetMarkerSize(1.0)
		effIsoMb1Hist.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Hist.GetXaxis().SetTitle(xLabel); effIsoMb1Hist.GetYaxis().SetTitle(yLabel); effIsoMb1Hist.GetZaxis().SetTitle("BMTF+IsoMB1 efficiency");
		effIsoMb1Hist.GetZaxis().SetTitleOffset(zOffset)
		effIsoMb1Hist.SetStats(False);

		effIsoMb12Hist = ROOT.TH2D(isoMb12MatchedMuonEta_vs_MuonPt)
		effIsoMb12Hist.Divide(muonEta_vs_MuonPt)
		effIsoMb12Hist.SetLineColor(ROOT.kAzure); effIsoMb12Hist.SetMarkerColor(ROOT.kAzure); effIsoMb12Hist.SetMarkerColor(ROOT.kAzure); effIsoMb12Hist.SetMarkerSize(1.0)
		effIsoMb12Hist.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Hist.GetXaxis().SetTitle(xLabel); effIsoMb12Hist.GetYaxis().SetTitle(yLabel); effIsoMb12Hist.GetZaxis().SetTitle("BMTF+IsoMB12 efficiency");
		effIsoMb12Hist.GetZaxis().SetTitleOffset(zOffset)
		effIsoMb12Hist.SetStats(False);

		#ROOT.gPad.BuildLegend();
		ROOT.gStyle.SetPadRightMargin(0.18)

		effName = "muonEta_vs_muonPt_bmtf"
		canvas = ROOT.TCanvas(effName, effName, width, height)
		effBmtfHist.Draw("colz")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".pdf")
		canvas.SetLogz()
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".pdf")
		canvas.Close()



		effName = "muonEta_vs_muonPt_isoMB1"
		canvas = ROOT.TCanvas(effName, effName, width, height)
		effIsoMb1Hist.Draw("colz")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".pdf")
		canvas.SetLogz()
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".pdf")
		canvas.Close()



		effName = "muonEta_vs_muonPt_isoMB12"
		canvas = ROOT.TCanvas(effName, effName, width, height)
		effIsoMb12Hist.Draw("colz")

		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".pdf")
		canvas.SetLogz()
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".pdf")
		canvas.Close()



		yMin = 1
		yMax = 1.1
		effBmtfHist.SetMinimum(yMin); effBmtfHist.SetMaximum(yMax)
		effIsoMb1Hist.SetMinimum(yMin); effIsoMb1Hist.SetMaximum(yMax)
		effIsoMb12Hist.SetMinimum(yMin); effIsoMb12Hist.SetMaximum(yMax)

		effRatioIsoMb1Hist = ROOT.TH2D(effIsoMb1Hist)
		effRatioIsoMb1Hist.Divide(effBmtfHist)
		effRatioIsoMb1Hist.SetLineColor(ROOT.kRed); effIsoMb1Hist.SetMarkerColor(ROOT.kRed); effIsoMb1Hist.SetMarkerColor(ROOT.kRed); effIsoMb1Hist.SetMarkerSize(1.0)
		effRatioIsoMb1Hist.SetTitle("BMTF+IsoMB1 Muon"); effIsoMb1Hist.GetXaxis().SetTitle(xLabel); effIsoMb1Hist.GetYaxis().SetTitle(yLabel); effRatioIsoMb1Hist.GetZaxis().SetTitle("#frac{BMTF+IsoMB1 efficiency}{BMTF efficiency}");
		effRatioIsoMb1Hist.GetZaxis().SetTitleOffset(zOffset)

		effName = "muonEta_vs_muonPt_effRatio_isoMB1"
		canvas = ROOT.TCanvas(effName, effName, width, height)
		effRatioIsoMb1Hist.SetMinimum(1.); effIsoMb1Hist.SetMaximum(1.1)
		effRatioIsoMb1Hist.Draw("colz")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".pdf")
		canvas.SetLogz()
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".pdf")
		canvas.Close()



		effRatioIsoMb12Hist = ROOT.TH2D(effIsoMb12Hist)
		effRatioIsoMb12Hist.SetMinimum(1.); effIsoMb12Hist.SetMaximum(1.5)
		effRatioIsoMb12Hist.Divide(effBmtfHist)
		effRatioIsoMb12Hist.SetLineColor(ROOT.kRed); effIsoMb12Hist.SetMarkerColor(ROOT.kRed); effIsoMb12Hist.SetMarkerColor(ROOT.kRed); effIsoMb12Hist.SetMarkerSize(1.0)
		effRatioIsoMb12Hist.SetTitle("BMTF+IsoMB12 Muon"); effIsoMb12Hist.GetXaxis().SetTitle(xLabel); effIsoMb12Hist.GetYaxis().SetTitle(yLabel); effRatioIsoMb12Hist.GetZaxis().SetTitle("#frac{BMTF+IsoMB12 efficiency}{BMTF efficiency}");
		effRatioIsoMb12Hist.GetZaxis().SetTitleOffset(zOffset)

		effName = "muonEta_vs_muonPt_effRatio_isoMB12"
		canvas = ROOT.TCanvas(effName, effName, width, height)
		effRatioIsoMb12Hist.Draw("colz")

		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber + "/" + effName + ".pdf")
		canvas.SetLogz()
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".png")
		canvas.SaveAs(args.output_directory + "/efficiency/" + runNumber +"/log/" + effName + ".pdf")
		canvas.Close()



		common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)
		#plottingUrl = common.GetOSVariable("PLOTTING_URL")
		#print(plottingUrl + "/" + args.output_directory)
