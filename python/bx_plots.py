#!/nfs/dust/cms/user/frengelk/Anaconda/envs/EPR_env/bin/python
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

import awkward as ak
import mplhep as hep
import uproot as up
import numpy as np
import ROOT

# file_qie4_cut = up.open("output_bx_qie4_cut.root")
file_no_cut = up.open("/nfs/dust/cms/user/frengelk/Code/cmssw/CMSSW_11_2_0/src/HOAnalysis/HOL1/output/output_muon_matching.root")
# file_qie4_cut_wo_matching = up.open("output_bx_qie4_cut_woDTTPHO_matching.root")
# file_no_cut_wo_matching = up.open("output_bx_NO_qie4_cut_woDTTPHO_matching.root")
file_muon_matching = up.open(
    "/nfs/dust/cms/user/frengelk/Code/cmssw/CMSSW_11_2_0/src/HOAnalysis/HOL1/output/output_muon_xroot.root"
)  # output/output_muon_matching.root

file_ntuple = up.open(
    "/nfs/dust/cms/user/frengelk/Code/cmssw/CMSSW_11_0_2/src/HcalTrigger/Validation/scripts/Lucas_L1Ntuple_112-muon_reco.root"
)

# dttpBx = file_qie4_cut['dttpBx'].values()
# dttpBx = file_qie4_cut['dttpBx']

keys = ["dttpBx", "hcal_Weighted_QIESampleAdc", "corrected_dttpBx", "HoMatched_dttpBx"]

etaSt1 = file_ntuple["l1MuonRecoTree/Muon2RecoTree;1"]["Muon"]["etaSt1"].array()
hlt_mu = file_ntuple["l1MuonRecoTree/Muon2RecoTree;1"]["Muon"]["hlt_mu"].array()

bmtf_muon_bx = file_ntuple["l1UpgradeTfMuonTree/L1UpgradeTfMuonTree;1"][
    "L1UpgradeBmtfMuon/tfMuonBx"
].array()
bmtf_input_phBx = file_ntuple["l1UpgradeTfMuonTree/L1UpgradeTfMuonTree;1"][
    "L1UpgradeBmtfInputs/phBx"
].array()
bmtf_input_thBx = file_ntuple["l1UpgradeTfMuonTree/L1UpgradeTfMuonTree;1"][
    "L1UpgradeBmtfInputs/thBx"
].array()

# btmf_phBx = file_nt

# from IPython import embed

# embed()

bins = np.arange(-2.5, 2.5, 1)

for bx, bx_str in [
    (bmtf_muon_bx, "bmtf_muon_bx"),
    (bmtf_input_phBx, "bmtf_input_phBx"),
    (bmtf_input_thBx, "bmtf_input_thBx"),
]:
    plt.figure(figsize=(12, 9))
    plt.hist(
        ak.flatten(bx),
        label=bx_str,  # total yields={}".format(np.round(ak.sum(h_350), 2)),
        # density=True,
        bins=bins,
        histtype="step",
        linewidth=1.5,
    )
    hep.style.use("CMS")
    hep.cms.label(llabel="Work in progress", loc=0)
    plt.xlabel("BX ID", fontsize=16)
    # plt.ylabel("Normalised")
    plt.legend(loc="best", ncol=1)
    plt.tight_layout()
    plt.savefig(
        "bx_plots/xroot_{}".format(bx_str) + ".png",
        bbox_inches="tight",
    )
    plt.yscale("log")
    plt.savefig(
        "bx_plots/xroot_{}_log".format(bx_str) + ".png",
        bbox_inches="tight",
    )
    plt.close()


"""
for key in keys:
    plt.figure(figsize=(12, 9))
    file_qie4_cut[key].to_hist().plot()
    # plt.hist(
        # dttpBx,
        # label="dttpBx, qie4 cut, Ho Matching ",  # total yields={}".format(np.round(ak.sum(h_350), 2)),
        # #density=True,
        # #bins=bins,
        # histtype="step",
        # linewidth=1.5,
    # )
    hep.style.use("CMS")
    hep.cms.label(llabel="Work in progress", loc=0)
    plt.xlabel(key, fontsize=16)
    #plt.ylabel("Normalised")
    #plt.legend(loc="best", ncol=1)
    plt.tight_layout()
    plt.savefig(
        "bx_plots/qie4_cut_{}".format(key)  + ".png",
        bbox_inches="tight",
    )
    plt.yscale("log")
    plt.savefig(
        "bx_plots/qie4_cut_{}_log".format(key)  + ".png",
        bbox_inches="tight",
    )
    plt.close()
"""

#from IPython import embed;embed()

counts_before = file_no_cut[keys[3]].values()
counts_after = file_no_cut[keys[2]].values()

# b[0].stairs.properties()["data"].edges
uproot_bins = np.array([-2. , -1.2, -0.4,  0.4,  1.2,  2. ])

plt.figure(figsize=(12, 9))
# file_muon_matching[keys[3]].to_hist().plot(label="before")
# file_no_cut[keys[2]].to_hist().plot(label="after")
file_no_cut[keys[3]].to_hist().plot(density=True,
    label="DTTP", linewidth=1.5,
    #bins=bins
    #label="before in middle bin {}".format(
    #    np.round(counts_before[2] / np.sum(counts_before), 4)
    #)
)
file_no_cut[keys[2]].to_hist().plot(density=True,
    label="HO corrected", linewidth=1.5,
    #bins=bins
    #label="after in middle bin {}".format(
    #    np.round(counts_after[2] / np.sum(counts_after), 4)
    #)
)
plt.hist(
        ak.flatten(bmtf_muon_bx),
        label="BMTF Muons",
        density=True,
        bins=uproot_bins,
        histtype="step",
        linewidth=1.5,
    )
# plt.hist(file_no_cut_wo_matching[keys[0]], label="before")
hep.style.use("CMS")
hep.cms.label(llabel="Work in progress", loc=0)
plt.title("dttp bx correction", fontsize=16)  # qie4 cut
plt.xlabel("BX", fontsize=16)
# plt.ylabel("Normalised")
plt.legend(loc="best", ncol=1)
plt.tight_layout()
plt.savefig(
    "bx_plots/bmtfbx_dttb_bx_correction_qie4_cut" + ".png",
    bbox_inches="tight",
)
plt.yscale("log")
plt.savefig(
    "bx_plots/bmtfbx_dttb_bx_correction_qie4_cut_log" + ".png",
    bbox_inches="tight",
)
plt.close()

print("bx_plots/dttb_bx_correction_qie4_cut_log" + ".png")


# from IPython import embed;embed()

"""
w qie4 cut, wo matching:
right bx: 17487 false bx: 2961 ratio 0.169326
leftover: 0

no qie4 cut, wo matching:
right bx: 1665 false bx: 292 ratio 0.175375
leftover: 2669

w qie4 cut:
right bx: 4901 false bx: 0 ratio 0
leftover: 0

no qie4 cut:
right bx: 261 false bx: 0 ratio 0
leftover: 0
"""
