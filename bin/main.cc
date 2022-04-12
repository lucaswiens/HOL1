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
	std::string outputFile = std::string(argv[1]) + (useEmulated ? "Emu" : "") + ".root";
	std::cout << (useEmulated ? "Using the emulated branch.\n" : "") << "Output file is named: " << outputFile << std::endl;
	TFile *file = new TFile(outputFile.c_str(), "RECREATE");

	bool hasRecoMuons;

	int iEtaCut = 999;
	double ptCut = 0, etaCut = 0.83, l1PtCut = 0, l1EtaCut = 999, deltaPhiCut = 0.4, deltaRCut = 0.4;

	// Choose the working point of tag muon
	//char workingPointCut = 't'; // Tight
	char workingPointCut = 'm'; // Medium
	//char workingPointCut = 'l'; //Loose
	//char workingPointCut = 'a'; //everything

	//Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers;
	if (strstr(argv[3], "SingleMuon") != NULL || strstr(argv[3], "MET") != NULL || strstr(argv[3], "MET") != NULL) {
		// For the study of recoving the gap in iEta3

		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer()));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer(l1EtaCut, l1PtCut)));
		producers.push_back(std::shared_ptr<MuonProducer>(new MuonProducer(ptCut, etaCut, workingPointCut)));
		producers.push_back(std::shared_ptr<TagAndProbeProducer>(new TagAndProbeProducer(ptCut, l1PtCut, etaCut, workingPointCut)));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer(iEtaCut, etaCut, l1EtaCut, ptCut, l1PtCut, deltaPhiCut, deltaRCut)));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()));

		hasRecoMuons = true;
	} else {
		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer()));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer(l1EtaCut, l1PtCut)));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer(iEtaCut, etaCut, l1EtaCut, ptCut, l1PtCut, deltaPhiCut, deltaRCut)));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()));

		hasRecoMuons = false;
	}

	//HoHistogramCollection histCollection(hasRecoMuons);
	// Histograms are stored inside a specific class to allow access to them for all producers
	std::map<int, HoHistogramCollection> histCollections;

	int rate = 0, elapsedTime = 0, totalProcessed = 0, runNumber = 0;
	int runMin = 320000, runMax = 330000;
	TH1I *histRunNumber = new TH1I("runNumber", "", runMax - runMin, runMin, runMax);
	for (int iFile = 3; iFile < argc; iFile ++) {
		int  processed = 0;
		const char* inputFile = argv[iFile];
		DataReader* dataReader = new DataReader(inputFile, &useEmulated);
		std::cout << "Processing(" << iFile - 2 << "/" << argc - 3 << "): "<< inputFile << " with " << dataReader->GetEntries() << " events" << std::endl;

		ProgressBar(0, 0, "Starting");
		while (dataReader->Next()) {
			// Timing Information
			elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
			rate = totalProcessed / elapsedTime;

			// Prepare the histcollection
			HoHistogramCollection *histCollection;
			runNumber = hasRecoMuons ? 1 : *dataReader->runNumber->Get();
			histRunNumber->Fill(runNumber);
			if (histCollections.find(runNumber) == histCollections.end() ) { // runNumber not found
				file->mkdir(std::to_string(runNumber).c_str());
				file->cd(std::to_string(runNumber).c_str());
				histCollections.insert({runNumber, HoHistogramCollection(hasRecoMuons)});
				histCollection = &histCollections.at(runNumber);
			} else { // runNumber found
				file->cd(std::to_string(runNumber).c_str());
				histCollection = &histCollections.at(runNumber);
			}

			// Production of Ho Coincidence
			HoProduct product;
			for (std::shared_ptr<BaseProducer> producer: producers) {
				if (processed % 100 == 0) { ProgressBar((int) 101 * processed/dataReader->GetEntries(), rate, producer->Name); }
				producer->Produce(dataReader, &product, histCollection);
			}
			totalProcessed++;
			processed++;
		}
		ProgressBar(100, rate, "Done");
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
	std::string progressBar = "[";
	int barLength = 100;

	for (int i = 0; i < progress - 1; i++) {
		progressBar += "·";
	}

	if (progress == barLength) { progressBar += "·";}
	else if (progress % 2 == 0) { progressBar += "c";}
	else { progressBar += "C";}

	for (int i = 0; i < barLength - progress; i++) {
		progressBar += "•";
	}

	progressBar =  progressBar + "] " + std::to_string(progress) + "% of Events processed at a rate of " + std::to_string(rate) + " Hz." ;
	std::cout << std::left;
	std::cout << "\r" << std::setw(24) << producerName +":" << progressBar << std::flush;
}
