void test(int RunNumber=111, int MaxEvent=10)
{

  const char* RunFileNamePattern = "run_%03d.dat.0.0";
  vector<TString> pathList;
  pathList.push_back("./rawdata");

  HKSSpectrometer* hks = new HKSSpectrometer("K", "HKS");
  gHaApps->Add(hks);

  HYPCherenkov* cer = new HYPCherenkov("cer", "cer");
  hks->AddDetector(cer);

  THaAnalyzer* analyzer = new THaAnalyzer;
  THaEvent* event = new THaEvent;

  THaRun* run = new THaRun(Form("rawdata/run_%d.dat.0.0",RunNumber));

  run->SetEventRange(1, MaxEvent);
  run->SetDataRequired(THaRunBase::kDate|THaRunBase::kRunNumber);
  run->Print();

  analyzer->SetEvent(event);
  analyzer->SetCountMode(2); // 2 = counter is event number

  analyzer->SetCrateMapFileName("DB2/db_cratemap2.dat");
  analyzer->SetOutFile("test_cer.root");
  analyzer->SetOdefFile("cer.def");

  analyzer->Process(run);

}
