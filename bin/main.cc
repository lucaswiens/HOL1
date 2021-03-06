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

void ProgressBar(const int &, const int &);

int main(int argc, char* argv[]) {
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	std::string outputFile = std::string(argv[1]);
	std::cout << "The name of the outputfile is " << outputFile << ".root" << std::endl;
	TFile *file = new TFile((outputFile + ".root").c_str(), "RECREATE");

	// Histograms are stored inside a specific class to allow access to them for all producers
	HoHistogramCollection histCollection;

	//Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers;
	if(strstr(argv[2], "SingleMuon") != NULL || strstr(argv[2], "MET") != NULL) {
		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer(&histCollection)));
		producers.push_back(std::shared_ptr<MuonProducer>(new MuonProducer(&histCollection)));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer(&histCollection)));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer()));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer(&histCollection)));

		histCollection.SetHasRecoMuon(true);
	} else {
		producers.push_back(std::shared_ptr<HoProducer>(new HoProducer(&histCollection)));
		producers.push_back(std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer(&histCollection)));
		producers.push_back(std::shared_ptr<HoCoincidenceProducer>(new HoCoincidenceProducer()));
		producers.push_back(std::shared_ptr<HoHistogramProducer>(new HoHistogramProducer(&histCollection)));

		histCollection.SetHasRecoMuon(false);
	}

	int totalProcessed = 0;
	for (int iFile = 2; iFile < argc; iFile ++) {
		const char* inputFile = argv[iFile];
		std::cout << "Processing(" << iFile - 1 << "/" << argc - 2 << "): "<< inputFile << std::endl;

		DataReader* dataReader = new DataReader(inputFile);

		int processed = 0;
		int rate = 0;
		float elapsedTime = 0;
		ProgressBar(0, 0);
		while(dataReader->Next()){
			// Progress Bar
			elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count();
			rate = totalProcessed / elapsedTime;
			/*
			if(processed % 1000) {
				ProgressBar((int) 101 * processed/dataReader->GetEntries(), rate);
			}
			*/
			ProgressBar((int) 101 * processed/dataReader->GetEntries(), rate);
			processed++;
			totalProcessed++;

			HoProduct product;
			for (std::shared_ptr<BaseProducer> producer: producers) {
				producer->Produce(dataReader, &product, &histCollection);
			}
		}
		ProgressBar(100, rate);
		std::cout << std::endl;

		delete dataReader;
	}

	for (std::shared_ptr<BaseProducer> producer: producers) {
		file->cd();
		producer->EndJob(&histCollection);
	}

	file->Write();
	file->Close();

	delete file;

	std::cout << "Processed " << argc - 2 << " files in " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() << "s" << std::endl;

	return 0;
}

void ProgressBar(const int &progress, const int &rate) {
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

	progressBar = progressBar + "] " + std::to_string(progress) + "% of Events processed at a rate of " + std::to_string(rate) + " Hz." ;
	std::cout << "\r" << progressBar << std::flush;
}
