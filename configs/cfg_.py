# For MC Trigger
import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
process = cms.Process("TagAndProbeMC")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# Define files of dataset
files = [''] # FileUtils.loadListFromFile("data/CMS_MonteCarlo2011_Summer11LegDR_JPsiToMuMu_2MuPEtaFilter_7TeV-pythia6-evtgen-v2_AODSIM_PU_S13_START53_LV6-v1_00000_file_index.txt")
#files.extend(FileUtils.loadListFromFile("data/CMS_MonteCarlo2011_Summer11LegDR_JPsiToMuMu_2MuPEtaFilter_7TeV-pythia6-evtgen-v2_AODSIM_PU_S13_START53_LV6-v1_10000_file_index.txt"))

process.source = cms.Source(
    "PoolSource", fileNames=cms.untracked.vstring(*files))






process.TFileService = cms.Service ('TFileService',
    fileName = cms.string (
    'TagAndProbeMC.root'
    )
)
  
process.tagandprobe = cms.EDAnalyzer('TagAndProbe2019',
	verbose = cms.bool(False),
	triggerflag = cms.bool(True), 		      
	# Trigger
	TriggerResultsTag = cms.untracked.InputTag("TriggerResults", "", "HLT"),
	TriggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD", "", "HLT"),
	PathName = cms.untracked.vstring(["HLT_Dimuon10_Jpsi_Barrel_v"]),
	# RECO Labels
	primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
	recoMuonsLabel = cms.InputTag("muons"), 
	# RECO Configs
	minResonanceMass = cms.double(2.5),# in GeV
	maxResonanceMass = cms.double(3.5)# in GeV 
)


process.p = cms.Path(process.tagandprobe)
