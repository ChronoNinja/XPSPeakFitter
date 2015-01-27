{
//..BABAR style from RooLogon.C in workdir
TStyle *babarStyle= new TStyle("BABAR","BaBar approved plots style");

// use plain black on white colors
babarStyle->SetFrameBorderMode(0);
babarStyle->SetFrameLineWidth(3);
babarStyle->SetCanvasBorderMode(0);
babarStyle->SetPadBorderMode(0);
babarStyle->SetPadColor(0);
babarStyle->SetCanvasColor(0);
babarStyle->SetStatColor(0);
//babarStyle->SetFillColor(0);

babarStyle->SetLineWidth(2);

// set the paper & margin sizes
babarStyle->SetPaperSize(20,26);
babarStyle->SetPadTopMargin(0.02);
babarStyle->SetPadRightMargin(0.02);
babarStyle->SetPadBottomMargin(0.02);
babarStyle->SetPadLeftMargin(0.02);

// use large Times-Roman fonts
babarStyle->SetTextFont(132);
babarStyle->SetTextSize(0.09);
babarStyle->SetLabelFont(132,"x");
babarStyle->SetLabelFont(132,"y");
babarStyle->SetLabelFont(132,"z");
babarStyle->SetLabelSize(0.00,"x"); // was 0.06
babarStyle->SetTitleSize(0.07,"x");
babarStyle->SetLabelSize(0.00,"y"); // was 0.06
babarStyle->SetTitleSize(0.07,"y");
babarStyle->SetLabelSize(0.06,"z");
babarStyle->SetTitleSize(0.07,"z");

//babarStyle->SetNdivisions(0.00,"y"); // default 510
//babarStyle->SetTickSize(0.05); // default 0.03

// use bold lines and markers
babarStyle->SetMarkerStyle(20);
babarStyle->SetMarkerSize(0.6);
babarStyle->SetHistLineWidth(1.85);
babarStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

// get rid of X error bars and y error bar caps
babarStyle->SetErrorX(0.001);

// do not display any of the standard histogram decorations
babarStyle->SetOptTitle(0);
babarStyle->SetOptStat(0);
babarStyle->SetOptFit(0);

// put tick marks on top and RHS of plots
babarStyle->SetPadTickX(0);
babarStyle->SetPadTickY(0);
}
