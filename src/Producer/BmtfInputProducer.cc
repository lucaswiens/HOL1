#include <HOAnalysis/HOL1/interface/Producer/BmtfInputProducer.h>

BmtfInputProducer::BmtfInputProducer() {
	histBmtfPhSize = new TH1I("bmtfPhSize", "bmtfPhSize", 15, 0, 15);
	histBmtfThSize = new TH1I("bmtfThSize", "bmtfThSize", 25, 0, 25);
	histBmtfPhBx = new TH1I("bmtfPhBx", "bmtfPhBx", 5, -2, 2);
	histBmtfPhWh = new TH1I("bmtfPhWh", "bmtfPhWh", 10, 0, 10);
	histBmtfPhSe = new TH1I("bmtfPhSe", "bmtfPhSe", 20, 0, 20);
	histBmtfPhSt = new TH1I("bmtfPhSt", "bmtfPhSt", 10, 0, 10);
	histBmtfPhCode = new TH1I("bmtfPhCode", "bmtfPhCode", 10, 0, 10);
	histBmtfPhTs2Tag = new TH1I("bmtfPhTs2Tag", "bmtfPhTs2Tag", 2, 0, 2);
	histBmtfThBx = new TH1I("bmtfThBx", "bmtfThBx", 6, -3, 3);
	histBmtfThWh = new TH1I("bmtfThWh", "bmtfThWh", 6, -3, 3);
	histBmtfThSe = new TH1I("bmtfThSe", "bmtfThSe", 15, 0, 15);
	histBmtfThSt = new TH1I("bmtfThSt", "bmtfThSt", 5, 0, 5);
	histBmtfThTheta = new TH1I("bmtfThTheta", "bmtfThTheta", 100, 8e7, 1e8);
	histBmtfThCode = new TH1I("bmtfThCode", "bmtfThCode", 10, 8e7, 2e8);
	histBmtfPhAng = new TH1F("bmtfPhAng", "bmtfPhAng", 100, -1750, 1750);
	histBmtfPhBandAng = new TH1F("bmtfPhBandAng", "bmtfPhBandAng", 100, -250, 250);
}

void BmtfInputProducer::Produce(DataReader* dataReader) {
	const int &phSize = *dataReader->bmtfPhSize->Get();
	const int &thSize = *dataReader->bmtfThSize->Get();
	histBmtfPhSize->Fill(phSize);
	histBmtfThSize->Fill(thSize);

	for (int i = 0; i < phSize; i++) {
		histBmtfPhBx->Fill(dataReader->bmtfPhBx->At(i));
		histBmtfPhWh->Fill(dataReader->bmtfPhWh->At(i));
		histBmtfPhSe->Fill(dataReader->bmtfPhSe->At(i));
		histBmtfPhSt->Fill(dataReader->bmtfPhSt->At(i));
		histBmtfPhCode->Fill(dataReader->bmtfPhCode->At(i));
		histBmtfPhTs2Tag->Fill(dataReader->bmtfPhTs2Tag->At(i));
		histBmtfPhAng->Fill(dataReader->bmtfPhAng->At(i));
		histBmtfPhBandAng->Fill(dataReader->bmtfPhBandAng->At(i));
	}

	for (int i = 0; i < thSize; i++) {
		histBmtfThBx->Fill(dataReader->bmtfThBx->At(i));
		histBmtfThWh->Fill(dataReader->bmtfThWh->At(i));
		histBmtfThSe->Fill(dataReader->bmtfThSe->At(i));
		histBmtfThSt->Fill(dataReader->bmtfThSt->At(i));
		histBmtfThTheta->Fill(dataReader->bmtfThTheta->At(i));
		histBmtfThCode->Fill(dataReader->bmtfThCode->At(i));
	}
}

BmtfInputProducer::~BmtfInputProducer() {}
