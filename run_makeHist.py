
m ROOT import *
import sys, os
import json
from multiprocessing import Pool, cpu_count

sys.path.append("%s/src/CATTools/CatAnalyzer/python" % os.environ['CMSSW_BASE'])
from HistMaker import *

basePath = '/xrootd/store/user/dygyun/Cattools/v744'
#basePath = '/xrootd/store/user/dygyun/Cattools/v743'
#basePath = 'root://cms-xrdr.sdfarm.kr///xrd/store/user/youngjo/Cattools/v736'
outPath = "test"

def makeHist(dset):
    timer = TStopwatch()
    timer.Start()

    name = dset['name']
    if 'nevt' in dset: nevt = dset['nevt']
    else: nevt = 0

    an = HistMaker(
        #inFileNames = ("%s/%s/vallot_%s.root" % (basePath,name, name)),
        inFileNames = ("%s/vallot_%s_25ns.root" % (basePath, name)),
        outFileName = ("%s/hist_%s.root" % (outPath, name)),
        modName = "ttbarSingleLepton", treeName = "tree",
  #      modName = "ntuple", treeName = "event",
        #eventCount = "hNEvent",
        eventCount = nevt,
    )
    if not an.isOK: return

    an.addH1("nvtx", "nGoodPV", "Vertex multiplicity;Vertex multiplicity;Events", 100, 0, 100)
    an.addH1("PUWeight", "PUWeight", "PileUp Weight;Events", 100, 0, 100)
    an.addH1("nJet30", "nJet30", "Number of Jets;Events", 20, 0, 20)
    an.addH1("nBJet30M", "nBJet30M", "Number of b Jets;Events", 20, 0, 20)
    an.addH1("MET", "MET", "MET;Events", 50, 0, 300)
    an.addH1("MET_phi", "MET_phi", "MET #phi;Events", 64., -3.2, 3.2)
    an.addH1("METPuppi", "METPuppi", "Puppi MET;Events", 100, 0, 300)
    an.addH1("METPuppi_phi", "METPuppi_phi", "Puppi MET #phi;Events", 64. , -3.2, 3.2)
    an.addH1("Wmass", "Wmass", "W Mass;Events", 100, 0, 200)

    an.addH1("lepton_pt", "lepton_pt[0]", "lepton p_{T};p_{T}^{l, 1st lead} (GeV);Events/20 GeV", 20. , 0, 200)
    an.addH1("lepton_eta", "lepton_eta[0]", "lepton #eta;#eta^{l, 1st lead};Events/0.1", 30. , -3, 3)
    an.addH1("lepton_phi", "lepton_phi[0]", "lepton #phi;#phi^{l, 1st lead};Events", 64., -3.2, 3.2)
    an.addH1("lepton_relIso", "lepton_relIso[0]", "lepton relIso;relIso {l, 1st lead};Events", 20., 0, 2)

    an.addH1("jet1_pt",  "jet_pt[0]",  "Leading jet p_{T};p_{T}^{j, 1st} (GeV);Events/20 GeV", 100, 0, 200)
    an.addH1("jet2_pt",  "jet_pt[1]",  "Trailing jet p_{T};p_{T}^{j, 2nd} (GeV);Events/20 GeV", 100, 0, 200)
    an.addH1("jet1_pt",  "jet_pt[0]",  "Leading jet p_{T};p_{T}^{j, 1st} (GeV);Events/20 GeV", 100, 0, 200)
    an.addH1("jet2_pt",  "jet_pt[1]",  "Trailing jet p_{T};p_{T}^{j, 2nd} (GeV);Events/20 GeV", 100, 0, 200)
    an.addH1("jet3_pt",  "jet_pt[2]",  "3rd jet p_{T};p_{T}^{j, 3rd} (GeV);Events/20 GeV", 100, 0, 200)
    an.addH1("jet4_pt",  "jet_pt[3]",  "4th jet p_{T};p_{T}^{j, 4th} (GeV);Events/20 GeV", 100, 0, 200)
    an.addH1("jet1_eta", "jet_eta[0]", "Leading jet #eta;#eta^{j, 1st};Events/0.1", 60., -3, 3)
    an.addH1("jet2_eta", "jet_eta[1]", "Trailing jet #eta;#eta^{j, 2nd};Events/0.1", 60., -3, 3)
    an.addH1("jet3_eta", "jet_eta[2]", "3rd jet #eta;#eta^{j, 3rd};Events/0.1", 60., -3, 3)
    an.addH1("jet4_eta", "jet_eta[3]", "4th jet #eta;#eta^{j, 4th};Events/0.1", 60., -3, 3)

    an.addCutStep("S0", "(1)",                     "lepton_pt,lepton_eta,nvtx,MET,nJet30")
    an.addCutStep("S1", "(lepton_pt > 30)",        "lepton_pt,lepton_eta,nvtx,MET,MET_phi,nJet30,nBJet30M,Wmass,PUWeight")
    an.addCutStep("S2", "(nJet30 > 3)",            "lepton_pt,MET,jet1_pt,nJet30,nBJet30M,Wmass,PUWeight")
    #an.addCutStep("S2", "(nJet30 > 3)",           "lepton_pt,lepton_eta,nvtx,MET,MET_phi,jet1_pt,jet1_eta,nJet30,nBJet30M,Wmass,PUWeight")
  #  an.addCutStep("S3", "(nBJet30M  >= 2)",       "lepton_pt,lepton_eta,nvtx,MET,MET_phi,jet1_pt,jet1_eta,nJet30,nBJet30M,Wmass")
 #   an.addCutStep("S4", "(MET.pt() > 30)",        "lepton_pt,lepton_eta,nvtx,MET,MET_phi,jet1_pt,jet1_eta,nJet30,nBJet30M,Wmass")
    #an.addCutStep("S2", "@jet_pt.size() >= 4", "lepton_pt,lepton_eta,nvtx,MET,jet1_pt1,jet_eta1,nJet30")
    #an.addCutStep("S4", "@MET_pt.size() > 30", "lepton_pt,lepton_eta,nvtx,MET,WMass")
    #an.addCutStep("S5", "jets_CSV.size() >= 2", "lepton_pt,lepton_eta,nvtx,MET,jet_CSV")
    #an.addCutStep("S2", "abs(mLL-91.2) > 15", "l1_pt,l2_pt,l1_eta,l2_eta")
    an.process()

    timer.Stop()
    return (name, timer.CpuTime(), timer.RealTime())

if __name__ == '__main__':
    if not os.path.exists(outPath): os.makedirs(outPath)
    datasets = json.load(open("%s/src/CATTools/CatAnalyzer/data/dataset.json" % os.environ['CMSSW_BASE']))
    #datasets = json.load(open("%s/src/CatAnalyzer/data/dataset.json" % os.environ['CMSSW_BASE']))

    nCPU = cpu_count()
    p = Pool(nCPU)
    print "="*40
    print "Start processing using %d CPUs" % nCPU
    print "="*40
    timer = TStopwatch()
    timer.Start()
    cpuTimes = p.map(makeHist, datasets)
    timer.Stop()
    print "="*40
    print "End of processing"
    print "."*40
    print "Total real time = %.1f s" % timer.RealTime()
    print "Total CPU time  = %.1f s" % sum(x[1] for x in cpuTimes)
    print "-"*40
    for l in cpuTimes:
        print "%s: CPU=%.1f s, Real=%.1f s" % (l[0], l[1], l[2])
    print "="*40

