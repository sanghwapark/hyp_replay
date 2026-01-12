void test_dc(int RunNumber=111, int MaxEvent=10)
{

  const char* RunFileNamePattern = "run_%03d.dat.0.0";
  vector<TString> pathList;
  pathList.push_back("./rawdata");

  HKSSpectrometer* hks = new HKSSpectrometer("K", "HKS");
  gHaApps->Add(hks);

  HYPDC* dc = new HYPDC("dc", "dc");
  hks->AddDetector(dc);

  THaAnalyzer* analyzer = new THaAnalyzer;
  THaEvent* event = new THaEvent;

  THaRun* run = new THaRun(Form("rawdata/run_%d.dat.0.0",RunNumber));

  run->SetEventRange(1, MaxEvent);
  run->SetDataRequired(THaRunBase::kDate|THaRunBase::kRunNumber);
  run->Print();

  analyzer->SetEvent(event);
  analyzer->SetCountMode(2); // 2 = counter is event number

  analyzer->SetCrateMapFileName("DB_ESB/db_cratemap.dat");
  analyzer->SetOutFile("test.root");
  //  analyzer->SetCutFile("test_cuts.def");
  analyzer->SetOdefFile("test.def");

  analyzer->Process(run);

}
