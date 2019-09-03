#include "TCutG.h"

void cut_dedxtof(void){
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/34
   
   TCutG *cutg = new TCutG("CUTG",6);
   cutg->SetVarX("hdEdx_tof");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,291.139,9.43512);
   cutg->SetPoint(1,282.745,9.9236);
   cutg->SetPoint(2,166.91,2.03282);
   cutg->SetPoint(3,233.221,1.69464);
   cutg->SetPoint(4,327.232,5.41458);
   cutg->SetPoint(5,291.139,9.43512);

   TFile* file = new TFile("cut_dedxtof.root","RECREATE");
   cutg -> Write();
   file -> Write();
   file -> Close();
   delete file;
}
