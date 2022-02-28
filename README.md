# HOL1
A framework to study the effect of using multiple HO feature bits in the L1 Trigger of CMS

This framwork is designed to run inside a CMSSW environment.
Most recent instructions can be found here (or better yet, use the checkout script):
https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideL1TStage2Instructions

#Checkout this repository:
``` git clone git@github.com:lucaswiens/HOL1.git HOAnalysis/HOL1
#or
curl -LO https://raw.githubusercontent.com/lucaswiens/HOL1/main/scripts/checkoutHo
source checkoutHo
```

#After compilation, you can use this framwork via:
```HOStudy OutputFilename 0 input_file1.root input_file2.root input_file3.root # [...]
```
The first argument is the name of the output file. The second decides whether or not to use emulated branches as input.
The rest of the arguments are input files, since each file on its own is fairly small it can loop over any number of files given.

#To submit via HTC:
```python python/createBatch.py -i data/SingleMuonRun2018D.md
```
All the arguments are explained by ```python python/createBatch.py -h ```

Something useful you can put in your ```~/.bashrc```:
```
hoanalysis ()
{
    module use -a /afs/desy.de/group/cms/modulefiles/;
    module load cmssw;
    cd /nfs/dust/cms/user/${USER}/HO/CMSSW_11_0_2/src/HOAnalysis/HOL1;
    eval `scramv1 runtime -sh`
}

alias myvomsproxyinit='voms-proxy-init --voms cms --valid 168:00'
```
