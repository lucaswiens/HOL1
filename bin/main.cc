#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>

#include <HOAnalysis/HOL1/interface/DataReader.h>
#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/HoProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/MuonProducer.h>
#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>


int main(int argc, char* argv[]) {
	std::string inputFile = std::string(argv[1]);

	DataReader* dataReader = new DataReader(inputFile);

	TFile *file = new TFile("l1Histograms.root", "RECREATE");

	//Declare vector of Producers which will fill Histograms
	std::vector<std::shared_ptr<BaseProducer>> producers = {
		std::shared_ptr<HoProducer>(new HoProducer()),
		std::shared_ptr<MuonProducer>(new MuonProducer()),
		std::shared_ptr<BmtfInputProducer>(new BmtfInputProducer()),
	};

	while(dataReader->Next()){
		for (std::shared_ptr<BaseProducer> producer: producers) {
			producer->Produce(dataReader);
		}
	}

	file->Write();
	file->Close();

	delete dataReader;
	delete file;

	return 0;
}
