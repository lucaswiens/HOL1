from __future__ import print_function

import os
import re
import string
import numpy as np

import awkward as ak
import boost_histogram as bh

import ROOT
#from getXSection import GetXSection

BMTFCOLOR = ROOT.TColor.GetColor("#000000")
ISOMB1COLOR = ROOT.TColor.GetColor("#ff4da6")
ISOMB13x3COLOR = ROOT.TColor.GetColor("#ff4d4d")
ISOMB2COLOR = ROOT.TColor.GetColor("#4dffa6")
ISOMB12COLOR = ROOT.TColor.GetColor("#4da6ff")
ISOMB123x3COLOR = ROOT.TColor.GetColor("#4d4dff")

COLORMAP = {
        "BMTF" : BMTFCOLOR,
        "IsoMB1" : ISOMB1COLOR,
        "IsoMB2" : ISOMB2COLOR,
        "IsoMB12" : ISOMB12COLOR,
}

def SetupStyle(option = ""):
	ROOT.gStyle.SetOptTitle(0)
	ROOT.gStyle.SetOptStat(0)
	ROOT.gStyle.SetLegendBorderSize(0)
	ROOT.gStyle.SetLegendBorderSize(0)
	ROOT.gStyle.SetPadBorderSize(1)

	if option == "":
		ROOT.gStyle.SetPadTopMargin(0.05)
		ROOT.gStyle.SetPadLeftMargin(0.115)
		ROOT.gStyle.SetPadRightMargin(0.03)
	if "2D" in option:
		ROOT.gStyle.SetPadTopMargin(0.05)
		ROOT.gStyle.SetPadLeftMargin(0.115)
		ROOT.gStyle.SetPadRightMargin(0.03)
	pass

def GetLegend(variable):
	if variable == "Pt":
		legend = ROOT.TLegend(0.6, 0.2, 0.9, 0.45)

		legendSize = 0.055
		legend.SetBorderSize(1)
		#legend.SetTextFont(62)
		legend.SetLineColor(0)
		legend.SetLineStyle(0)
		#legend.SetLineWidth(1)
		legend.SetFillColorAlpha(0,1)
		legend.SetFillStyle(1001)
	elif variable == "Pt":
		pass
	elif variable == "Pt":
		pass
	return legend

def HexToRgb(hex_code):
	# Convert a hexadecimal color code to RGB values
	hex_code = hex_code.lstrip("#")
	return [int(hex_code[i:i+2], 16) / 255.0 for i in (0, 2, 4)]

#def GenerateColorGradient(color_lower = "#4da6ff", color_upper = "#ff4da6", number = 100):
def GenerateColorGradient(color_lower = "#370e3a", color_upper = "#f73393", number = 100):
	#red1, green1, blue1, alpha1 = ROOT.Double_t(0), ROOT.Double_t(0), ROOT.Double_t(0), ROOT.Double_t(1)
	#red2, green2, blue2, alpha2 = ROOT.Double_t(0), ROOT.Double_t(0), ROOT.Double_t(0), ROOT.Double_t(1)

	rgb_lower = HexToRgb(color_lower)
	rgb_upper = HexToRgb(color_upper)
	color_lower = ROOT.TColor(*rgb_lower)
	color_upper = ROOT.TColor(*rgb_upper)

	#color_lower.GetRGB(red1, green1, blue1)
	#color_upper.GetRGB(red2, green2, blue2)
	red = np.linspace(rgb_lower[0], rgb_upper[0], number)
	green = np.linspace(rgb_lower[1], rgb_upper[1], number)
	blue = np.linspace(rgb_lower[2], rgb_upper[2], number)

	ROOT.TColor.CreateGradientColorTable(number, np.linspace(0, 1, number), red, green, blue, number)
	return None

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
		label = "p_{T}^{offline} / GeV"
	elif "Eta" in efficiencyName:
		label = "#eta^{offline}"
	elif "DeltaR" in efficiencyName:
		label = "#DeltaR^{offline}"
	elif "DeltaPhi" in efficiencyName:
		label = "#Delta #phi^{offline}"
	return label



def GetFromDict(tree, dictionairy, key):
	keyString = re.sub("_[0-9]", "", key)
	if not keyString in dictionairy.keys():
		dictionairy[keyString] = tree[keyString].array(library="ak")
	if re.search("_[1-9]", key):
		indexOfInterest = int(key[-1]) - 1
		return dictionairy[keyString].mask[ak.num(dictionairy[keyString]) > indexOfInterest][:,indexOfInterest]
	else:
		return dictionairy[keyString]

def MaskQuantity(currentTree, currentQuantity, cutDict, cut, condition):
	cut = cut.replace(" ", "").replace("\t", "")
	if re.search("\|\|", cut):
		orStrings = cut.split("||")
		if re.search("\&\&", orStrings[0]):
			andStrings = orStrings[0].split("&&")
			currentCut = GetFromDict(currentTree, cutDict, andStrings[0])
			for andCut in andStrings[1:]:
				currentCut = currentCut and GetFromDict(currentTree, cutDict, andCut)
		else:
			currentCut = GetFromDict(currentTree, cutDict, orStrings[0])
		for orCut in orStrings[1:]:
			if re.search("\&\&", orCut):
				andStrings = orCut.split("&&")
				currentCut = GetFromDict(currentTree, cutDict, andStrings[0])
				for andCut in andStrings[1:]:
					currentCut = currentCut and GetFromDict(currentTree, cutDict, andCut)
			currentCut = currentCut or GetFromDict(currentTree, cutDict, orCut)
	elif re.search("\&\&", cut):
		andStrings = cut.split("&&")
		currentCut = GetFromDict(currentTree, cutDict, andStrings[0])
		for andCut in andStrings[1:]:
			currentCut = currentCut and GetFromDict(currentTree, cutDict, andCut)
	elif re.search("abs", cut):
		currentCut = abs(GetFromDict(currentTree, cutDict, re.sub("\)", "", re.sub("abs\(", "", cut))))
	else:
		currentCut = GetFromDict(currentTree, cutDict, cut)

	if (condition == "True"):
		return currentQuantity.mask[currentCut]
	elif (condition == "False"):
		return currentQuantity.mask[~currentCut]
	elif (condition[0:2] == ">="):
		return currentQuantity.mask[currentCut >= float(condition[2:])]
	elif (condition[0:2] == "<="):
		return currentQuantity.mask[currentCut <= float(condition[2:])]
	elif (condition[0] == ">"):
		return currentQuantity.mask[currentCut > float(condition[1:])]
	elif (condition[0] == "<"):
		return currentQuantity.mask[currentCut > float(condition[1:])]
	elif (condition[0:2] == "!="):
		return currentQuantity.mask[currentCut != int(condition[2:])]
	elif (condition[0:2] == "=="):
		return currentQuantity.mask[currentCut == int(condition[2:])]
	else:
		print("Check your plot config json! The cut condition is improperly defined!")
		exit(-1)

def ConstructHistogram(plotConfig, quantity):
	if plotConfig[quantity]["isRegular"] == "True":
		return bh.axis.Regular(plotConfig[quantity]["nBins"], plotConfig[quantity]["x_min"], plotConfig[quantity]["x_max"])
	else:
		return bh.axis.Variable(plotConfig[quantity]["binning"])

def GetLuminosity(fileName): #[fb^-1]
		if re.search("2016", fileName) or re.search("RunIISummer16", fileName):
			return 35.90
		elif re.search("2017", fileName):
			return 41.90
		elif re.search("2018", fileName):
			return 59.74
		else:
			print("Luminosity not defined for %s!!" % fileName)
			return 0

def GetOSVariable(Var):
	try:
		variable = os.environ[Var]
	except KeyError:
		print("Please set the environment variable " + Var)
		sys.exit(1)
	return variable

def progressBar(nSamples, nFiles, nQuantities, sampleIndex, fileIndex, quantityIndex, quantity, barSize = 20):
	sampleRatio = float(sampleIndex) / nSamples
	fileRatio = float(fileIndex) / nFiles
	quantityRatio = float(quantityIndex) / nQuantities

	if nFiles < barSize:
		barSize = nFiles

	print("[" + "S" * sampleIndex   + "s" * (nSamples - sampleIndex) + "] " +
		"[" + "F" * int(fileRatio * barSize) + "f" * int((1 - fileRatio) * barSize) + "] " +
		"[" + "Q" * quantityIndex + "q" * (nQuantities - quantityIndex) + "] " + quantity,
		end="\r"
	)
	return 0

def getOutputs(outputdir, **kwargs):
	fileTypes = kwargs.get("fileTypes", ["png", "jpg", "pdf", "svg", "eps"])

	outputdirContent = os.listdir(outputdir)

	plotFiles = {}
	subdirs = []
	for OutputObject in outputdirContent:
		fullOutputObject = os.path.join(outputdir, OutputObject)

		if os.path.isfile(fullOutputObject):
			splitOutputObject = os.path.splitext(OutputObject)
			extension = splitOutputObject[-1].replace(".", "").lower()

			if extension in fileTypes:
				plotFiles.setdefault(splitOutputObject[0], []).append(extension)

		else:
			subdirs.append(fullOutputObject)

	for filename, extensions in plotFiles.items():
		extensions.sort(key=lambda extension: fileTypes.index(extension))
	subdirs.sort()

	return plotFiles, subdirs

def CreateIndexHtml(templateDir, outputDir, **kwargs):
	plotFiles, subdirs = getOutputs(outputDir, **kwargs)
	htmlTexts = {}
	for var in ["overview", "description", "subdir", "plot", "link"]:
		with open(os.path.expandvars(templateDir + "/template_webplot_{}.html".format(var))) as htmlFile:
			htmlTexts[var] = string.Template(htmlFile.read())
	with open(os.path.expandvars(templateDir + "/template_webplotting_{}.html".format("plot"))) as htmlFile:
		htmlTexts["plotjson"] = string.Template(htmlFile.read())

	# create remote dir
	print("Creating directory " + outputDir + "...")
	mkdirCommand = os.path.expandvars("$WEB_PLOTTING_MKDIR_COMMAND").format(subdir=outputDir)
	os.system(mkdirCommand)

	# treat subdirs recursively
	htmlDesciption = ""
	htmlSubdirs = ""
	for subdir in subdirs:
		CreateIndexHtml(templateDir, subdir, **kwargs)
		htmlSubdirs += htmlTexts["subdir"].substitute(subdir=os.path.relpath(subdir, outputDir))
	htmlDesciption = htmlTexts["description"].substitute(subdirs=htmlSubdirs)

	htmlPlots = ""
	for filename, extensions in sorted(plotFiles.items()):
		if os.path.isfile(os.path.join(outputDir, filename+".json")):
			htmlPlots += htmlTexts["plotjson"].substitute(
					image=filename+"."+extensions[0],
					json=filename+".json",
					title=filename,
					links=" ".join([htmlTexts["link"].substitute(
							plot=filename+"."+extension,
							title=filename,
							extension=extension
					) for extension in extensions])
			)
		else:
			htmlPlots += htmlTexts["plot"].substitute(
					image=filename+"."+extensions[0],
					title=filename,
					links=" ".join([htmlTexts["link"].substitute(
							plot=filename+"."+extension,
							title=filename,
							extension=extension
					) for extension in extensions])
			)

	if not plotFiles == {}:
		htmlIndexFilename = os.path.join(outputDir, "index.html")
		with open(htmlIndexFilename, "w") as htmlIndexFile:
			htmlIndexFile.write(htmlTexts["overview"].substitute(
					title=kwargs.get("title", outputDir),
					description=htmlDesciption,
					plots=htmlPlots
				)
			)

	# copy files
	fullOutputDir = os.path.abspath(outputDir)
	outputDirContent = os.listdir(fullOutputDir)
	for OutputObject in outputDirContent:
		fullOutputObject = os.path.join(fullOutputDir, OutputObject)
		if os.path.isfile(fullOutputObject):
			#print("Copying " + OutputObject + " into " + outputDir + "...")
			copyCommand = os.path.expandvars("$WEB_PLOTTING_COPY_COMMAND").format(source=fullOutputObject, subdir=outputDir)
			os.system(copyCommand)
