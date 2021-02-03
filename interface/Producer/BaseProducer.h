#pragma once

#include <memory>
#include <map>
#include <vector>
#include <cmath>
#include <bitset>

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>

#include <HOAnalysis/HOL1/interface/DataReader.h>
#include <HOAnalysis/HOL1/interface/HoProduct.h>
#include <HOAnalysis/HOL1/interface/HoHistogramCollection.h>
#include <HOAnalysis/HOL1/interface/Utility/Utility.h>

class BaseProducer {
	public:
		virtual ~BaseProducer(){};
		BaseProducer();
		virtual void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection) = 0;
		virtual void EndJob(HoHistogramCollection* histCollection) = 0;

		//static float DeltaR(const float &eta1, const float &phi1, const float &eta2, const float &phi2);
};
