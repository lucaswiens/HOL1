#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>

#include <HOAnalysis/HOL1/interface/DataReader.h>
#include <HOAnalysis/HOL1/interface/HoProduct.h>
#include <HOAnalysis/HOL1/interface/HoHistogramCollection.h>
#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoCoincidenceProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoHistogramProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/TagAndProbeProducer.h>

void ProgressBar(const int &, const int &, const std::string &);

int main(int argc, char* argv[]) {
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	bool useEmulated = (std::string)argv[2] == "0" ? false : true;
	bool splitByRun = (std::string)argv[3] == "0" ? false : true;
	std::string outputFile = std::string(argv[1]) + (useEmulated ? "Emu" : "") + ".root";
	std::cout << (useEmulated ? "Using the emulated branch.\n" : "") << "Output file is named: " << outputFile << std::endl;
	TFile *file = new TFile(outputFile.c_str(), "RECREATE");

	bool hasRecoMuons;

	// Define Cuts used during matching
	int iEtaCut = 999;
	double tagPtCut = 3,
		probePtCut = 3,
		etaCut = 2.40,
		l1PtCut = 3,
		l1EtaCut = 999,
		deltaPhiCut = 0.4,
		deltaRProbeAndTfCut = 0.2,
		deltaRProbeAndHoCut = 0.4,
		deltaRTagAndTfCut = 0.1,
		deltaRTagAndProbeCut = 0.4;

	// Choose the working point of tag muon
	char tagWorkingPointCut = 't'; // t = tight, m = medium, l = loose, a = all
	char probeWorkingPointCut = 'a'; // t = tight, m = medium, l = loose, a = all

	// Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers;
	if (strstr(argv[4], "SingleMuon") != NULL || strstr(argv[4], "MET") != NULL) {
		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer()));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer(l1EtaCut, l1PtCut)));
		producers.push_back(std::shared_ptr<MuonProducer>(new MuonProducer()));
		producers.push_back(std::shared_ptr<TagAndProbeProducer>(new TagAndProbeProducer(tagPtCut, probePtCut, l1PtCut, etaCut, deltaRTagAndTfCut, deltaRTagAndProbeCut, tagWorkingPointCut, probeWorkingPointCut)));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer(iEtaCut, etaCut, l1EtaCut, probePtCut, l1PtCut, deltaPhiCut, deltaRProbeAndTfCut, deltaRProbeAndHoCut)));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()));

		hasRecoMuons = true;
	} else {
		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer()));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer(l1EtaCut, l1PtCut)));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer(iEtaCut, etaCut, l1EtaCut, probePtCut, l1PtCut, deltaPhiCut, deltaRProbeAndTfCut, deltaRProbeAndHoCut)));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()));

		hasRecoMuons = false;
	}

	// Histograms are stored inside a specific class to allow access to them for all producers
	std::map<int, HoHistogramCollection> histCollections;

	int rate = 0, elapsedTime = 0, totalProcessed = 0, runNumber = 0;
	int runMin = 320000, runMax = 330000;
	TH1D *histRunNumber = new TH1D("runNumber", "", runMax - runMin, runMin, runMax);

	for (int iFile = 4; iFile < argc; iFile ++) {
		int  processed = 0;
		const char* inputFile = argv[iFile];
		DataReader* dataReader = new DataReader(inputFile, &useEmulated);

		std::cout << "Processing(" << iFile - 3 << "/" << argc - 3 << "): "<< inputFile << " with " << dataReader->GetEntries() << " events" << std::endl;
		while (dataReader->Next()) {
			totalProcessed++;
			elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
			rate = totalProcessed / elapsedTime;

			// Prepare the histcollection
			HoHistogramCollection *histCollection;
			runNumber = !splitByRun ? 1 : *dataReader->runNumber->Get();
			histRunNumber->Fill(*dataReader->runNumber->Get());
			if (histCollections.find(runNumber) == histCollections.end() ) { // runNumber not found in histCollection
				file->mkdir(std::to_string(runNumber).c_str());
				file->cd(std::to_string(runNumber).c_str());
				histCollections.insert({runNumber, HoHistogramCollection(hasRecoMuons)});
				histCollection = &histCollections.at(runNumber);
			} else { // runNumber found in histCollection
				file->cd(std::to_string(runNumber).c_str());
				histCollection = &histCollections.at(runNumber);
			}

			// Production of Ho Coincidence
			HoProduct product;
			if (processed % 1000 == 0) { ProgressBar((int) 101 * processed/dataReader->GetEntries(), rate, ""); }
			for (std::shared_ptr<BaseProducer> producer: producers) {
				producer->Produce(dataReader, &product, histCollection);
			}
			processed++;
		}
		ProgressBar(100, rate, "");
		histCollections.at(runNumber).numberOfEvents->Fill("Number of Events", dataReader->GetEntries());
		delete dataReader;
	}

	for (std::shared_ptr<BaseProducer> producer: producers) {
		for (std::map<int, HoHistogramCollection>::iterator histIterator = histCollections.begin(); histIterator != histCollections.end(); histIterator++) {
			file->cd(std::to_string(histIterator->first).c_str());
			producer->EndJob(&histIterator->second);
		}
	}


	file->Write();
	file->Close();

	delete file;

	std::cout << std::endl << "Processed " << argc - 3 << " files in " << std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - start).count() << " minutes" << std::endl;
	std::cout << "The name of the outputfile is " << outputFile << std::endl;

	return 0;
}

void ProgressBar(const int &progress, const int &rate, const std::string &producerName) {
	if (producerName == "") {
		std::cout << progress << "\% of events at a rate of " << rate << " Hz" << std::endl;
	} else {
		std::cout << std::setw(24) << producerName +":" << progress << "\% of events at a rate of " << rate << " Hz" << std::endl;
	}
}
