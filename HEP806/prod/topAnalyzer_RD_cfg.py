import FWCore.ParameterSet.Config as cms
process = cms.Process("TopTree")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
)
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

from CATTools.Validation.commonTestInput_cff import commonTestCATTuples
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        commonTestCATTuples["sig"]
    )
)

#isData = True 
isData = False

# json file (Only Data)
if isData:
    from CATTools.CatProducer.catDefinitions_cfi import lumiJSON
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = '%s.txt' % lumiJSON).getVLuminosityBlockRange()

process.load("CATTools.CatAnalyzer.flatGenWeights_cfi")

process.TopTree = cms.EDAnalyzer('TopAnalyzer',
    genTopLabel   = cms.InputTag("catGenTops"),
    genLabel      = cms.InputTag("prunedGenParticles"),
    muonLabel     = cms.InputTag("catMuons"),
    electronLabel = cms.InputTag("catElectrons"),
    jetLabel      = cms.InputTag("catJets"),
    metLabel      = cms.InputTag("catMETs"),
    pvLabel       = cms.InputTag("catVertex:nGoodPV"),
    puWeight      = cms.InputTag("pileupWeight"),
    puWeightUp    = cms.InputTag("pileupWeight","up"),
    puWeightDown  = cms.InputTag("pileupWeight","dn"),
#    puWeightUp    = cms.InputTag("pileupWeight:up"),
#    puWeightDown  = cms.InputTag("pileupWeight:dn"),
    genWeightLabel = cms.InputTag("genWeight"),
    pdfweights     = cms.InputTag("flatGenWeights", "pdf"),
    scaleupweights = cms.InputTag("flatGenWeights", "scaleup"),
    scaledownweights = cms.InputTag("flatGenWeights", "scaledown"),
    #pdfWeightLabel    = cms.InputTag("flatGenWeights", "pdf"),
    triggerBits    = cms.InputTag("TriggerResults::HLT"), 
  #  triggerBits2   = cms.InputTag("TriggerResults::HLT2"), 
    triggerObjects = cms.InputTag("catTrigger"),# we don't really use this objects 
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('vallot.root')
)


#process.Tracer = cms.Service("Tracer")
#process.dump=cms.EDAnalyzer('EventContentAnalyzer')
#process.p = cms.Path(process.demo*process.dump)
process.p = cms.Path(process.flatGenWeights*
                     process.TopTree)
#process.p = cms.Path(process.TopTree)
