
void simc_yield_radh2pos(){
  gStyle->SetOptStat(1000011);
  gStyle->SetOptStat(1111111);
  gROOT->SetBatch("kTRUE");
  gStyle->SetPalette(1,0);
  gStyle->SetOptFit(11);
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetTitleOffset(.7,"X");
  gStyle->SetLabelSize(0.08,"XY");
  gStyle->SetLabelSize(0.08);
  gStyle->SetTitleSize(0.08,"XY");
  gStyle->SetPadLeftMargin(0.12);
  
  const int runs[]={100/*70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,   590,600,610,620,630,640,650,660,670,680,690,700,710,720,730,740,750,760,770,850,860,870,880,890,900,910,930*/};


  ofstream txtsimch2pos("textfile/yield_simc_H2pos.txt",ios::app);
  const int numRuns = sizeof(runs)/sizeof(*runs);
  for (int r =0;r<numRuns;r++){
  ifstream infile(Form("/lustre24/expphy/volatile/hallc/c-csv/hdbhatt/simcjuly22/outfiles/csv_%d_H2_pos_inc_rad.hist",runs[r]));
    //ifstream infile(Form("/lustre24/expphy/volatile/hallc/c-rsidis/outfiles/csv_%d_H2_pos_inc_rad.hist",runs[r]));
    if(!infile){
      cout<<"Hist file Input file doesn't exist!"<<endl;
      //exit(0);
      continue;
    }

    TString tmp, content, text;

    Ssiz_t from=0;
    double normfac_value;

    while(tmp.ReadLine(infile)){
      if(tmp.Contains("normfac")){
	tmp.Tokenize(content,from,"=");
	text=atof(content.Data());
	tmp.Tokenize(content,from,"=");
	normfac_value=atof(content.Data());
	from=0;
      }
    }
    infile.close();
    const double normfac[]={normfac_value};
#include "double.h"
cout<<normfac_value<<endl;
    TH1F *h_z_simc = new TH1F("h_z_simc","Z;zhadron;Entries",100,0,1);
	TH1F *h_Q2_simc = new TH1F("h_Q2_simc","Q2;Q2;Entries",100,2,7);
	TH1F *h_W_simc = new TH1F("h_W_simc","W;W;Entries",100,1.5,5);
	TH1F *h_x_simc = new TH1F("h_x_simc","x;x;Entries",100,0.2,1);
	TH2D *h_Q2x_simc = new TH2D("h_Q2x_simc","Q2vsx;x;Q2",100,0.2,1,100,2,7);
	TH2D *h_Q2W_simc = new TH2D("h_Q2W_simc","Q2vsW;W;Q2",100,1.5,5,100,2,7);
	TH2D *h_Wx_simc = new TH2D("h_Wx_simc","Wvsx;x;W",100,0.2,1,100,1.5,5);
    TString filename  = Form("/lustre24/expphy/volatile/hallc/c-csv/hdbhatt/simcjuly22/worksim/csv_%d_H2_pos_inc_rad.root",runs[r]);
    //TString filename  = Form("/lustre24/expphy/volatile/hallc/c-rsidis/worksim/csv_%d_H2_pos_inc_rad.root",runs[r]);
    TFile *f = new TFile(filename, "READ");
    cout<< "Opening Run Num = "<<filename<<"\t"<< runs[r] <<endl;
    if(f->IsZombie()){
      std::cout << "Error opening file: Simc ROOTfile Not Found "<< std::endl;
      continue;
    }
    TTree * tt = (TTree *)f->Get("h10");
    Long64_t nentriesD = tt->GetEntries();
    double rad_evts = nentriesD;

    cout<<runs[r]<<"\t"<<nentriesD<<"\t"<<rad_evts<<"\t"<<normfac_value<<endl;
    for (int kk=0; kk<nentriesD;  kk++){
      tt->GetEntry(kk);
#include "includeRad.h"
      
      if(acceptance_cut_coin ){
          
	h_z_simc->Fill(z,normwt);
	h_x_simc->Fill(xbj,normwt);
	h_W_simc->Fill(w,normwt);
	h_Q2_simc->Fill(Q2,normwt);
	h_Q2x_simc->Fill(xbj,Q2,normwt);
	h_Q2W_simc->Fill(w,Q2,normwt);
	h_Wx_simc->Fill(xbj,w,normwt);
      
      
      }
    }
   
    double yield_simc=h_z_simc->Integral();
    cout<<"================> "<<runs[r]<<"\t"<<yield_simc<<endl;

    std::string rootfile_yield_name = Form("yield_hists/yield_simc_inc_h2pos_%d.root",runs[r]);
    TFile *rootfile_yield = new TFile(rootfile_yield_name.c_str(),"RECREATE");
    h_z_simc->Write();
    h_x_simc->Write();
    h_Q2_simc->Write();
    h_W_simc->Write();
    h_Q2x_simc->Write();
    h_Q2W_simc->Write();
    h_Wx_simc->Write();
    rootfile_yield->Close();
    txtsimch2pos<<runs[r]<<"\t"<<yield_simc<<endl;
  
    TCanvas *c1 = new TCanvas("c1","c1",1200,800);
    c1->Divide(2,2);
    c1->cd(1);
    h_z_simc->Draw("hist");
    h_z_simc->SetLineWidth(2);
    h_z_simc->SetTitle(Form("Z %d",runs[r]));
    
    c1->cd(2);
    h_x_simc->Draw("hist");
    h_x_simc->SetLineWidth(2);
    h_x_simc->SetTitle(Form("xbj %d",runs[r]));
    
    c1->cd(3);
    h_W_simc->Draw("hist");
    h_W_simc->SetLineWidth(2);
    h_W_simc->SetTitle(Form("W %d",runs[r]));
    
    c1->cd(4);
    h_Q2_simc->Draw("hist");
    h_Q2_simc->SetLineWidth(2);
    h_Q2_simc->SetTitle(Form("Q2 %d",runs[r]));

    c1->SaveAs(Form("plots_simc/plots_h2pos_incrad_%d.pdf",runs[r]));

  }
}
