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

class BaseProducer {
	public:
		virtual ~BaseProducer(){};
		BaseProducer();
		virtual void Produce(DataReader*) = 0;

		static float DeltaR(const float&, const float&, const float&, const float&);
};
