import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


import awkward as ak
import boost_histogram as bh
import mplhep as hep
import uproot as uproot

import argparse
import json
import os
import re
import subprocess
import sys

import common

if __name__ == "__main__":
	date = subprocess.check_output("date +\"%Y_%m_%d\"", shell=True).decode("utf-8").replace("\n", "")
	cmsswBase = common.GetOSVariable("CMSSW_BASE")

	parser = argparse.ArgumentParser(description = "Creates plots from flat ntuples, requires config files in JSON format.", formatter_class = argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument("-i", "--input-file",
		required = True,
		help = "Path to the file containing Histograms."
	)
	parser.add_argument("-o", "--output-directory",
		default = "hostudy/" + date,
		help = "Path to the output directory to store the plots."
	)
	parser.add_argument("--y-label",
		default = "Events",
		help = "Label of the y-axis"
	)
	parser.add_argument("--plot-config",
			default = cmsswBase + "/src/HOAnalysis/HOL1/data/config/histConfig.json",
		help = "Path to the json file used to create plots: %(default)s"
	)
	parser.add_argument("-dpi", "--dots-per-inch",
		default = 120,
		help = "Set the dpi of the plot: %(default)s"
	)
	parser.add_argument("--width",
		default = 600,
		help = "Set the width of the plot: %(default)s"
	)
	parser.add_argument("--height",
		default = 400,
		help = "Set the height of the plot: %(default)s"
	)
	parser.add_argument("--file-types",
		nargs = "+",
		default = ["png", "pdf"],
		help = "Set the filetypes of the output: %(default)s"
	)
	parser.add_argument("--font-size",
		default = 18,
		help = "Set the filetypes of the output: %(default)s"
	)
	parser.add_argument("--number-of-cols",
		default = 1,
		help = "Set the filetypes of the output: %(default)s"
	)
	parser.add_argument("-v", "--verbose",
		help = "Print more information, useful for debugging",
		default = False,
		action = "store_true"
	)
	parser.add_argument("--cms-label",
		help = "Print CMS Preliminary and Lumi information",
		default = False,
		action = "store_true"
	)

	args = parser.parse_args()

	outputDirectories = [args.output_directory,
			args.output_directory + "/dttpMatchedMuon", args.output_directory + "/dttpMatchedMuon/log",
			args.output_directory + "/dttpMatchedHo", args.output_directory + "/dttpMatchedHo/log",
			args.output_directory + "/bmtfMatchedDttp", args.output_directory + "/bmtfMatchedDttp/log",
			args.output_directory + "/bmtfMatchedMuon", args.output_directory + "/bmtfMatchedMuon/log",
			args.output_directory + "/bmtfMb34Matched", args.output_directory + "/bmtfMb34Matched/log",
			args.output_directory + "/unused", args.output_directory + "/unused/log",
			args.output_directory + "/used", args.output_directory + "/used/log",
			args.output_directory + "/dttp", args.output_directory + "/dttp/log",
			args.output_directory + "/bmtf", args.output_directory + "/bmtf/log",
			args.output_directory + "/hcal", args.output_directory + "/hcal/log",
			args.output_directory + "/muon", args.output_directory + "/muon/log",
			args.output_directory + "/efficiency", args.output_directory + "/efficiency/log",
			args.output_directory + "/rest", args.output_directory + "/rest/log"]

	for dir in outputDirectories:
		if not os.path.exists(dir):
			os.makedirs(dir)



	with open(args.plot_config) as config_file:
		histConfig = json.load(config_file)

	histograms = uproot.open(args.input_file)

	# Create the plots
	numberOfHists = len(histograms.keys())
	for figureNumber, key in enumerate(histograms.keys()):
		if(args.verbose):
			print(key)
		else:
			#print("[" + "H" * figureNumber + "h" * (numberOfHists - figureNumber) + "] %i" % int(figureNumber / numberOfHists * 100) + '%', end="\r")
			print("[" + "H" * figureNumber + "h" * (numberOfHists - figureNumber) + "] %i" % int(figureNumber / numberOfHists * 100) + '%')
			sys.stdout.flush()

		if key in histConfig.keys():
			continue

		if "efficiency" in key:
			plt.figure(figureNumber)

			print(key)
			histNumerator = histograms[key.replace("", "")]
			histDenominator = histograms[key]

			efficiencyGraph = histNumerator.Divide(histDenominator)

			hep.histplot(efficiencyGraph, color = histConfig[key]["color"], histtype = histConfig[key]["histtype"])

			plt.ylabel(histConfig[key]["ylabel"])
			plt.style.use(hep.style.CMS)
			if args.cms_label:
				hep.cms.label()
			plt.xlabel(histConfig[key]["xlabel"])

			plt.savefig(args.output_directory + "/efficiency/" + re.sub(";1", "", key) + ".png")
			plt.savefig(args.output_directory + "/efficiency/" + re.sub(";1", "", key) + ".pdf")

			plt.yscale("log")
			plt.savefig(args.output_directory + "/efficiency/log/" + re.sub(";1", "", key) + ".png")
			plt.savefig(args.output_directory + "/efficiency/log/" + re.sub(";1", "", key) + ".pdf")

			plt.close()

			continue


		if key not in histConfig.keys():
			continue

		plt.figure(figureNumber)

		if re.search("_vs_", key):
			hep.hist2dplot(histograms[key], color = histConfig[key]["color"])
		else:
			hep.histplot(histograms[key], color = histConfig[key]["color"], histtype = histConfig[key]["histtype"])
		#plt.legend(fontsize = args.font_size, ncol = args.number_of_cols)

		plt.ylabel(histConfig[key]["ylabel"])
		plt.style.use(hep.style.CMS)
		if args.cms_label:
			hep.cms.label()
		plt.xlabel(histConfig[key]["xlabel"])


		plt.savefig(args.output_directory + "/" + histConfig[key]["subdir"] + "/" + re.sub(";1", "", key) + ".png")
		plt.savefig(args.output_directory + "/" + histConfig[key]["subdir"] + "/" + re.sub(";1", "", key) + ".pdf")

		plt.yscale("log")
		plt.savefig(args.output_directory + "/" + histConfig[key]["subdir"] + "/log/" + re.sub(";1", "", key) + ".png")
		plt.savefig(args.output_directory + "/" + histConfig[key]["subdir"] + "/log/" + re.sub(";1", "", key) + ".pdf")

		plt.close()

	common.CreateIndexHtml(templateDir = cmsswBase + "/src/HOAnalysis/HOL1/data/html", outputDir = args.output_directory, fileTypes = args.file_types)

	copyCommand = "rsync -a " + args.output_directory + " lxplus:/eos/home-l/lwiens/www"
	os.system(copyCommand)

	plottingUrl = common.GetOSVariable("PLOTTING_URL")
	print(plottingUrl + "/" + args.output_directory)
