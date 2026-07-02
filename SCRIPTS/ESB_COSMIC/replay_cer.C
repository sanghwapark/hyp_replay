#include "MultiFileRun.h"

void replay_cer(int RunNumber=0, int MaxEvent=10)
{

  const char* RunFileNamePattern = "run_%d.dat.0.0";
  //const char* RunFileNamePattern = "rsidis_production_%d.dat.0";

  // Raw data file paths
  vector<TString> pathList;
  pathList.push_back(".");
  pathList.push_back("raw");
  pathList.push_back("rawdata");
  //  pathList.push_back("cache_rsidis");
  //  pathList.push_back("./cache");

  // Read db, map, parameter files
  gHcParms->Define("gen_run_number", "Run Number", RunNumber);
  gHcParms->AddString("g_ctp_database_filename", "DB_ESB/standard.database");
  gHcParms->Load(gHcParms->GetString("g_ctp_database_filename"), RunNumber);
  gHcParms->Load(gHcParms->GetString("g_ctp_kinematics_filename"), RunNumber);
  gHcParms->Load("DB_ESB/CER/cer_geom.param");
  //  gHcParms->Load("DB_ESB/CER/cer_calib_1113.param");
  //  gHcParms->Load("DB_ESB/CER/cer_cuts_1113.param");
  gHcParms->Load("DB_ESB/CER/cer_calib_1114.param");
  gHcParms->Load("DB_ESB/CER/cer_cuts_1114.param");
  gHcParms->Load("DB_ESB/k_reftime_cut.param");

  // Load the Hall C detector map
  gHcDetectorMap = new THcDetectorMap();
  gHcDetectorMap->Load("DB_ESB/CER/cer_1103.map");

  //_____________________________________________

  // Spectrometer 
  HKSSpectrometer* hks = new HKSSpectrometer("K", "HKS");
  gHaApps->Add(hks);  

  // Cherenkov detector
  HYPCherenkov* cer = new HYPCherenkov("cer","cer");
  hks->AddDetector(cer);

  //_____________________________________________
  THcAnalyzer* analyzer = new THcAnalyzer;
  THaEvent* event = new THaEvent;

  THcRun* run = new THcRun(pathList, Form(RunFileNamePattern, RunNumber) );     
  run->SetRunParamClass("THcRunParameters");
  run->SetEventRange(1, MaxEvent);
  run->SetDataRequired(THaRunBase::kDate|THaRunBase::kRunNumber);
  run->Print();

  analyzer->SetEvent(event);
  analyzer->SetCountMode(2); // 2 = counter is event number                                                               
  analyzer->SetCrateMapFileName("DB_ESB/CER/db_cratemap_1103.dat");
  analyzer->SetOutFile(Form("ROOTfiles/replay_%d_%d.root",RunNumber, MaxEvent));
  analyzer->SetOdefFile( "DEF-files/ESB/cer.def" );
  analyzer->SetCutFile( "DEF-files/ESB/test_cuts.def" );
  analyzer->Process(run);
}
