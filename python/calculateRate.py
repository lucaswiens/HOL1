import argparse
#import json
import os
#import re
import subprocess

import ROOT

import common

from pandas import DataFrame

ROOT.gStyle.SetOptTitle(0)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPadTopMargin(0.1)
ROOT.gStyle.SetPadLeftMargin(0.1)
ROOT.gStyle.SetPadRightMargin(0.08)
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

def findLabel(rateName):
	label = ""
	if "Pt" in rateName:
		label = "p_{T} / GeV"
	elif "Eta" in rateName:
		label = "#eta"
	elif "DeltaR" in rateName:
		label = "#DeltaR"
	elif "DeltaPhi" in rateName:
		label = "#Delta #phi"
	return label


if __name__=="__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = GetOsVariable("CMSSW_BASE")
	dustDir = GetOsVariable("DUSTDIR")

	parser = argparse.ArgumentParser(description="Runs a NAF batch system for nanoAOD", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file", required=True, help="Path to the file with the L1Ntuple + HO coincidence histograms")
	parser.add_argument("-o", "--output-directory", help="Path to the output directory", default = "")
	#parser.add_argument("--plot-config", default = cmsswBase + "/src/Plotting/Plotter/data/config/Rate.json", help = "Path to the json file used to create plots: %(default)s")
	parser.add_argument("--file-types", nargs = "+", default = ["png", "pdf"], help = "Set the filetypes of the output: %(default)s")
	parser.add_argument("--test", default = False, action = "store_true", help = "Use only the first five file for each sample for a quick run")
	parser.add_argument("--bmtf-only", default = False, action = "store_true", help = "Show only bmtf Rate")
	parser.add_argument("--do-ratio", default = False, action = "store_true", help = "Show relative Rate")

	args = parser.parse_args()

	args.output_directory = dustDir + "/HoPlots/" + date + "/" + args.output_directory

	outputDirectories = [
		args.output_directory,
		args.output_directory + "/log",
	]
	for dir in outputDirectories:
		if not os.path.exists(dir):
			os.makedirs(dir)



	xLabel = findLabel("Pt")
	yLabel = "Relative Rate"
	width = 1200
	height = 1200
	#height= 1500
	#height = int(width / 1.618030)
	rateName = "muonPt"

	canvas = ROOT.TCanvas(rateName, rateName, width, height)
	canvas.SetGrid()

	#rateDf = DataFrame(columns = ["runNumber", "bmtfRate", "bmtfMb34MatchedHoRate", "dttpMatchedHoRate", "dttpMatchedHoN3x3Rate", "bmtfMb34MatchedHoRelativeRate", "dttpMatchedHoRelativeRate", "dttpMatchedHoN3x3RelativeRate"])
	rateDf = DataFrame()
	histogramFile = ROOT.TFile(args.input_file)
	for iKey, key in enumerate(histogramFile.GetListOfKeys()):
		runNumber = key.GetName()
		#print(runNumber)
		if runNumber == "runNumber": continue
		histNumberOfEvents              = histogramFile.Get(runNumber + "/numberOfEvents")
		# Sometimes if there is a failure in a specific run, then this avoid crashing the program.. However, one should try to avoid that.
		try:
			histNumberOfEvents.GetName()
		except:
			print("NOT AVAILABLE RUN: ", runNumber)
			continue

		histBmtfNumber                  = histogramFile.Get(runNumber + "/bmtfNumber")
		#print(runNumber)
		tree = histogramFile.Get(runNumber)
		#print(tree)
		histBmtfNumber                  = histogramFile.Get(runNumber + "/bmtfNumber")
		histList = []
		rateDf.loc[iKey, "runNumber"] = int(runNumber)
		for iHist, histKey in enumerate(tree.GetListOfKeys()):
			if "Number" not in histKey.GetName(): continue
			#histlist.append(hist.ReadObj())
			hist = histKey.ReadObj()

			rateDf.loc[iKey, hist.GetName().replace("Number", "Rate")] = hist.GetBinContent(1) / histNumberOfEvents.GetBinContent(1)
			try:
				rateDf.loc[iKey, hist.GetName().replace("Number", "RelativeRate")] = hist.GetBinContent(1) / histBmtfNumber.GetBinContent(1)
			except:
				rateDf.loc[iKey, hist.GetName().replace("Number", "RelativeRate")] = -1

	#print(rateDf)
	#bmtfRateHist = ROOT.TH1D("bmtf", "", int(rateDf["runNumber"].max() - rateDf["runNumber"].min()), rateDf["runNumber"].min(), rateDf["runNumber"].max())
	#isoMBRateHist = ROOT.TH1D("DTTP matched to HO", "", int(rateDf["runNumber"].max() - rateDf["runNumber"].min()), rateDf["runNumber"].min(), rateDf["runNumber"].max())
	#isoMBN3x3RateHist = ROOT.TH1D("DTTP matched to HO (with N_{3x3} #leq 1)", "", int(rateDf["runNumber"].max() - rateDf["runNumber"].min()), rateDf["runNumber"].min(), rateDf["runNumber"].max())


	numberOfRuns = len(rateDf["runNumber"].to_numpy())
	print(rateDf["runNumber"])
	#print(numberOfRuns)
	bmtfRateHist = ROOT.TH1D("bmtf", "", numberOfRuns, 0, numberOfRuns)
	isoMBRateHist = ROOT.TH1D("DTTP matched to HO", "", numberOfRuns, 0, numberOfRuns)
	isoMBN3x3RateHist = ROOT.TH1D("DTTP matched to HO (with N_{3x3} #leq 1)", "", numberOfRuns, 0, numberOfRuns)
	isoMBAbsIEta3RateHist = ROOT.TH1D("DTTP matched to HO at |iEta|=3", "", numberOfRuns, 0, numberOfRuns)

	#bmtfRateHist = ROOT.TH1D()
	#isoMBRateHist = ROOT.TH1D()
	#isoMBN3x3RateHist = ROOT.TH1D()
	#isoMBAbsIEta3RateHist = ROOT.TH1D()

	bmtfRateHist.SetName("bmtf")
	isoMBRateHist.SetName("DTTP matched to HO")
	isoMBN3x3RateHist.SetName("DTTP matched to HO (with N_{3x3} #leq 1)")
	isoMBAbsIEta3RateHist.SetName("DTTP matched to HO at |iEta|=3")

	bmtfRateHist.SetTitle("bmtf")
	isoMBRateHist.SetTitle("DTTP matched to HO")
	isoMBN3x3RateHist.SetTitle("DTTP matched to HO (with N_{3x3} #leq 1)")
	isoMBAbsIEta3RateHist.SetTitle("DTTP matched to HO at |iEta|=3")
	xLabel = "run number"
	yLabel = "Rate"
	for hist in [bmtfRateHist, isoMBRateHist, isoMBN3x3RateHist, isoMBRateHist]:
		hist.GetXaxis().SetTitle(xLabel); hist.GetYaxis().SetTitle(yLabel);
		hist.GetXaxis().LabelsOption("v")

	bmtfRateHist.GetXaxis().SetName("run")
	bmtfRateHist.GetYaxis().SetName("rate")
	#bmtfRateHist.GetYaxis().SetOffset(0)
	bmtfRateHist.SetLineColor(ROOT.kBlack)
	isoMBRateHist.SetLineColor(ROOT.kRed-2)
	isoMBN3x3RateHist.SetLineColor(ROOT.kAzure-2)

	bmtfRateHist.SetMarkerColor(ROOT.kBlack)
	isoMBRateHist.SetMarkerColor(ROOT.kRed-2)
	isoMBN3x3RateHist.SetMarkerColor(ROOT.kAzure-2)

	bmtfRateHist.SetLineColor(ROOT.kBlack); bmtfRateHist.SetMarkerColor(ROOT.kBlack); bmtfRateHist.SetMarkerColor(ROOT.kBlack); bmtfRateHist.SetMarkerSize(1.0)
	isoMBRateHist.SetLineColor(ROOT.kRed-2); isoMBRateHist.SetMarkerColor(ROOT.kRed-2); isoMBRateHist.SetMarkerColor(ROOT.kRed-2); isoMBRateHist.SetMarkerSize(1.0)
	isoMBN3x3RateHist.SetLineColor(ROOT.kAzure-2); isoMBN3x3RateHist.SetMarkerColor(ROOT.kAzure-2); isoMBN3x3RateHist.SetMarkerColor(ROOT.kAzure-2); isoMBN3x3RateHist.SetMarkerSize(1.0)
	isoMBAbsIEta3RateHist.SetLineColor(ROOT.kGreen-2); isoMBAbsIEta3RateHist.SetMarkerColor(ROOT.kGreen-2); isoMBAbsIEta3RateHist.SetMarkerColor(ROOT.kGreen-2); isoMBAbsIEta3RateHist.SetMarkerSize(1.0)



	for i in rateDf.index:
		#print(i)
		runNumber = str(int(rateDf.loc[i, "runNumber"]))
		#bmtfRateHist.Fill(runNumber, rateDf.loc[i, "bmtfRate"])
		#isoMBRateHist.Fill(runNumber, rateDf.loc[i, "dttpMatchedHoRate"])
		#isoMBN3x3RateHist.Fill(runNumber, rateDf.loc[i, "dttpMatchedHoN3x3Rate"])
		#isoMBAbsIEta3RateHist.Fill(runNumber, rateDf.loc[i, "dttpMatchedHoAbsIEta3Rate"])

		bmtfRateHist.SetBinContent(i+1, rateDf.loc[i, "bmtfRate"])
		isoMBRateHist.SetBinContent(i+1, rateDf.loc[i, "dttpMatchedHoRate"])
		isoMBN3x3RateHist.SetBinContent(i+1, rateDf.loc[i, "dttpMatchedHoN3x3Rate"])
		isoMBAbsIEta3RateHist.SetBinContent(i+1, rateDf.loc[i, "dttpMatchedHoAbsIEta3Rate"])

		bmtfRateHist.GetXaxis().SetBinLabel(i+1, runNumber)
		isoMBRateHist.GetXaxis().SetBinLabel(i+1, runNumber)
		isoMBN3x3RateHist.GetXaxis().SetBinLabel(i+1, runNumber)
		isoMBAbsIEta3RateHist.GetXaxis().SetBinLabel(i+1, runNumber)

	width = 2000
	#height = int(width * 3/4.)
	height = 1200
	canvas = ROOT.TCanvas("rateHist", "rateHist", width, height)
	canvas.SetGrid()
	yMax = 1.1*max([bmtfRateHist.GetMaximum(), isoMBRateHist.GetMaximum(), isoMBN3x3RateHist.GetMaximum(), isoMBAbsIEta3RateHist.GetMaximum()])
	#yMax = 0.02 # hardcoded for now

	bmtfRateHist.SetMaximum(yMax)
	bmtfRateHist.Draw("HIST")
	isoMBRateHist.Draw("HIST SAME")
	isoMBN3x3RateHist.Draw("HIST SAME")
	isoMBAbsIEta3RateHist.Draw("HIST SAME")
	#ROOT.gPad.BuildLegend(0.6, 0.2, 0.9, 0.45);
	canvas.Modified()
	legend = ROOT.TLegend(0.15, 0.91, 0.9, 0.985)
	legendSize = 0.055
	legend.SetBorderSize(1)
	legend.SetLineColor(0)
	legend.SetLineStyle(0)
	legend.SetFillColorAlpha(0,1)
	legend.SetFillStyle(1001)
	legend.SetNColumns(4)

	legend.AddEntry(bmtfRateHist, bmtfRateHist.GetName())
	legend.AddEntry(isoMBRateHist, isoMBRateHist.GetName())
	legend.AddEntry(isoMBN3x3RateHist, isoMBN3x3RateHist.GetName())
	legend.AddEntry(isoMBAbsIEta3RateHist, isoMBAbsIEta3RateHist.GetName())

	legend.Draw("SAME")

	if args.do_ratio:
		bmtfRateHist.SetLabelSize(0)
		isoMBRateHist.SetLabelSize(0)
		isoMBN3x3RateHist.SetLabelSize(0)
		isoMBAbsIEta3RateHist.SetLabelSize(0)
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

		bmtfRateHist.SetLabelSize(0)
		relRateIsoMBRatio = ROOT.TGraphAsymmErrors(bmtfRateHist)
		relRateIsoMBRatio.Divide(isoMBRateHist, bmtfRateHist, "cl=0.683 b(1,1) mode")
		relRateIsoMBRatio.SetLineColor(ROOT.kRed-2); relRateIsoMBRatio.SetMarkerColor(ROOT.kRed-2); relRateIsoMBRatio.SetMarkerColor(ROOT.kRed-2); relRateIsoMBRatio.SetMarkerSize(0.9)
		relRateIsoMBRatio.SetTitle("BMTF+IsoMB Muon"); relRateIsoMBRatio.GetXaxis().SetTitle(xLabel); relRateIsoMBRatio.GetYaxis().SetTitle(ratioLabel);
		relRateIsoMBRatio.GetXaxis().SetTitle(xLabel); relRateIsoMBRatio.GetYaxis().SetTitle(ratioLabel);

		relRateIsoMBN3x3Ratio = ROOT.TGraphAsymmErrors(bmtfRateHist)
		relRateIsoMBN3x3Ratio.Divide(isoMBN3x3RateHist, bmtfRateHist, "cl=0.683 b(1,1) mode")
		relRateIsoMBN3x3Ratio.SetLineColor(ROOT.kAzure-2); relRateIsoMBN3x3Ratio.SetMarkerColor(ROOT.kAzure-2); relRateIsoMBN3x3Ratio.SetMarkerColor(ROOT.kAzure-2); relRateIsoMBN3x3Ratio.SetMarkerSize(0.9)
		relRateIsoMBN3x3Ratio.SetTitle("BMTF+IsoMBN3x3 Muon"); relRateIsoMBN3x3Ratio.GetXaxis().SetTitle(xLabel); relRateIsoMBN3x3Ratio.GetYaxis().SetTitle(ratioLabel);
		relRateIsoMBN3x3Ratio.GetXaxis().SetTitle(xLabel); relRateIsoMBN3x3Ratio.GetYaxis().SetTitle(ratioLabel);

		relRateIsoMBAbsIEta3Ratio = ROOT.TGraphAsymmErrors(bmtfRateHist)
		relRateIsoMBAbsIEta3Ratio.Divide(isoMBAbsIEta3RateHist, bmtfRateHist, "cl=0.683 b(1,1) mode")
		relRateIsoMBAbsIEta3Ratio.SetLineColor(ROOT.kAzure-2); relRateIsoMBAbsIEta3Ratio.SetMarkerColor(ROOT.kAzure-2); relRateIsoMBAbsIEta3Ratio.SetMarkerColor(ROOT.kAzure-2); relRateIsoMBAbsIEta3Ratio.SetMarkerSize(0.9)
		relRateIsoMBAbsIEta3Ratio.SetTitle("BMTF+IsoMBAbsIEta3 Muon"); relRateIsoMBAbsIEta3Ratio.GetXaxis().SetTitle(xLabel); relRateIsoMBAbsIEta3Ratio.GetYaxis().SetTitle(ratioLabel);
		relRateIsoMBAbsIEta3Ratio.GetXaxis().SetTitle(xLabel); relRateIsoMBAbsIEta3Ratio.GetYaxis().SetTitle(ratioLabel);

		ratioPad.cd()
		relRateIsoMBRatio.Draw("SAME AP")
		relRateIsoMBN3x3Ratio.Draw("SAME P")
		relRateIsoMBAbsIEta3Ratio.Draw("SAME P")

	canvas.SaveAs(args.output_directory + "/rate.png")
	canvas.SaveAs(args.output_directory + "/rate.pdf")
	canvas.SetLogy()
	canvas.SaveAs(args.output_directory + "/log/rate.png")
	canvas.SaveAs(args.output_directory + "/log/rate.pdf")
	canvas.Close()

	#rateDf = rateDf[rateDf["dttpMatchedHoRate"] > 0.001]
	rateDf.to_csv(args.output_directory + "/rateFull.csv", index="runNumber")
	rateDf = rateDf[rateDf["bmtfRate"] > 0.]
	rateDf.to_csv(args.output_directory + "/rate.csv", index="runNumber")
	with open(args.output_directory + "/rate.md", "w") as outFile:
		for tp in rateDf.columns:
			if tp == "runNumber":
				outFile.write("Analzed %i run numbers\n" % (len(rateDf[tp])))
			else:
				outFile.write(tp + " " * (30 - len(tp)) + "= %.2f +- %.2f\n" % (100 * rateDf[tp].mean(), 100 * rateDf[tp].std() / (rateDf.shape[0])**0.5))
