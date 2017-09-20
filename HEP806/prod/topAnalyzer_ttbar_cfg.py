import FWCore.ParameterSet.Config as cms
process = cms.Process("TopTree")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        #'file:catTuple.root'
        '/store/group/CAT/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/v7-6-4_RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/160325_073338/0000/catTuple_1.root'
        #'file:/afs/cern.ch/user/b/brochero/CATTuples_August/v7-3-6/cat74/src/CATTools/CatProducer/prod/catTuple-PUPPI-v7-3-6.root' # -- MC PUPPI (v7-3-6)
       #'file:catTuple.root'
    )
)

isData = False

# json file (Only Data)
if isData:
  import FWCore.PythonUtilities.LumiList as LumiList
  process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt').getVLuminosityBlockRange()

process.TopTree = cms.EDAnalyzer('TopAnalyzer',
                                           genTopLabel   = cms.InputTag("catGenTops"),
                                           genLabel      = cms.InputTag("prunedGenParticles"),
                                           muonLabel     = cms.InputTag("catMuons"),
                                           electronLabel = cms.InputTag("catElectrons"),
                                           jetLabel      = cms.InputTag("catJets"),
                                           metLabel      = cms.InputTag("catMETs"),
                                           pvLabel       = cms.InputTag("catVertex:nGoodPV"),
                                           puWeight      = cms.InputTag("pileupWeight"),
                                           genWeightLabel = cms.InputTag("genWeight"),
                                     triggerBits       = cms.InputTag("TriggerResults::HLT"), 
                                     triggerObjects    = cms.InputTag("catTrigger"), 
                                           )

process.TFileService = cms.Service("TFileService",
                                       fileName = cms.string('hep.root')
                                   )


#process.Tracer = cms.Service("Tracer")
#process.dump=cms.EDAnalyzer('EventContentAnalyzer')
#process.p = cms.Path(process.demo*process.dump)
process.p = cms.Path(process.TopTree)
