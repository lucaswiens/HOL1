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

	std::string outputFile = std::string(argv[1]);
	std::cout << "The name of the outputfile is " << outputFile << ".root" << std::endl;
	TFile *file = new TFile((outputFile + ".root").c_str(), "RECREATE");

	bool hasRecoMuons;

	char workingPointCut;
	double ptCut = 0, etaCut = 0.83, deltaPhiCut = 0.4, deltaRCut = 0.4;
	int iEtaCut = 10;
	//Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers;
	if (strstr(argv[2], "SingleMuon") != NULL || strstr(argv[2], "MET") != NULL) {
		// For the study of recoving the gap in iEta3
		if (strstr(argv[2], "SingleMuon") != NULL) {
			ptCut = 25;
		}

		//workingPoint = 't'; // Tight
		workingPointCut = 'm'; // Medium
		//workingPoint = 'l'; //Loose

		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer()));
		producers.push_back(std::shared_ptr<MuonProducer>(new MuonProducer(ptCut, etaCut, workingPointCut)));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer()));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer(iEtaCut, etaCut, ptCut, deltaPhiCut, deltaRCut)));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()));

		hasRecoMuons = true;
	} else {
		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer()));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer()));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer(iEtaCut, etaCut, ptCut, deltaPhiCut, deltaRCut)));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer()));

		hasRecoMuons = false;
	}

	// Histograms are stored inside a specific class to allow access to them for all producers
	HoHistogramCollection histCollection(hasRecoMuons);

	TH1I *numberOfEvents = new TH1I("numberOfEvents", "numberOfEvents", 1, 0, 1);
	int rate = 0, elapsedTime = 0, totalProcessed = 0;
	for (int iFile = 2; iFile < argc; iFile ++) {
		//std::chrono::steady_clock::time_point loopStart = std::chrono::steady_clock::now();
		int  processed = 0;
		const char* inputFile = argv[iFile];
		DataReader* dataReader = new DataReader(inputFile);
		std::cout << "Processing(" << iFile - 1 << "/" << argc - 2 << "): "<< inputFile << " with " << dataReader->GetEntries() << " events" << std::endl;

		ProgressBar(0, 0, "Starting");
		while (dataReader->Next()) {
			// Progress Bar
			elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
			rate = totalProcessed / elapsedTime;

			// Production of Ho Coincidence
			HoProduct product;
			for (std::shared_ptr<BaseProducer> producer: producers) {
				ProgressBar((int) 101 * processed/dataReader->GetEntries(), rate, producer->Name);
				producer->Produce(dataReader, &product, &histCollection);
			}

			totalProcessed++;
			processed++;
		}

		ProgressBar(100, rate, "Done");
		std::cout << std::endl;

		numberOfEvents->Fill("Number of Events", dataReader->GetEntries());

		delete dataReader;
	}

	for (std::shared_ptr<BaseProducer> producer: producers) {
		file->cd();
		producer->EndJob(&histCollection);
	}

	file->Write();
	file->Close();

	delete file;

	std::cout << "Processed " << argc - 2 << " files in " << std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - start).count() << " minutes" << std::endl;
	std::cout << "The name of the outputfile is " << outputFile << ".root" << std::endl;

	return 0;
}

void ProgressBar(const int &progress, const int &rate, const std::string &producerName) {
	std::string progressBar = "[";

	for (int i = 0; i < progress - 1; i++) {
		progressBar += "·";
	}

	if (progress == 100) { progressBar += "·";}
	else if (progress % 2 == 0) { progressBar += "c";}
	else { progressBar += "C";}

	for (int i = 0; i < 100 - progress; i++) {
		progressBar += "•";
	}

	progressBar =  progressBar + "] " + std::to_string(progress) + "% of Events processed at a rate of " + std::to_string(rate) + " Hz." ;
	std::cout << std::left;
	std::cout << "\r" << std::setw(24) << producerName +":" << progressBar << std::flush;
}
