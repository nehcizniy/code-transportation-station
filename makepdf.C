void makepdf() {
	// normwt = Weight*normfac_value/rad_evts;
	double normfac =     0.160380E+12;
	double rad_evts = 20000;
	// proton_mass = 0.938Gev
	
    TFile *file = TFile::Open("treefiles/csv_100_D2_neg_delta.root");
    TTree *tree;
    file->GetObject("h10", tree);  
    
    
    TCanvas *c1 = new TCanvas("c1", "Q2", 800, 600);
    tree->Draw("Q2,Weight*normfac/rad_evts"); 
    c1->SaveAs("Q2_new.pdf");
    

    TCanvas *c2 = new TCanvas("c2", "W", 800, 600);
    tree->Draw("W"); 
    c2->SaveAs("W.pdf");
    

    TCanvas *c3 = new TCanvas("c3", "x", 800, 600);
    tree->Draw("Q2/(2*0.938*nu)"); 
    c3->SaveAs("x.pdf");


    TCanvas *c4 = new TCanvas("c4", "t", 800, 600);
    tree->Draw("t"); 
    c4->SaveAs("t.pdf");
    

    TCanvas *c5 = new TCanvas("c5", "hsxptar", 800, 600);
    tree->Draw("hsxptar"); 
    c5->SaveAs("hsxptar.pdf");
    

    TCanvas *c6 = new TCanvas("c6", "hsyptar", 800, 600);
    tree->Draw("hsyptar"); 
    c6->SaveAs("hsyptar.pdf");
	
    TCanvas *c7 = new TCanvas("c7", "Wvsx", 800, 600);
    tree->Draw("W:Q2/(2*0.938*nu)");
    c7->SaveAs("Wvsx.pdf");
	
}

