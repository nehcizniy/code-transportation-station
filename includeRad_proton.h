Emiss = tt->GetLeaf("Em")->GetValue();
Weight = tt->GetLeaf("Weight")->GetValue();
spdelta = tt->GetLeaf("ssdelta")->GetValue();
hsdelta = tt->GetLeaf("hsdelta")->GetValue();
//z = tt->GetLeaf("z")->GetValue();
sighad = tt->GetLeaf("sighad")->GetValue();
theta = tt->GetLeaf("thetapq")->GetValue();
mom = tt->GetLeaf("ppi")->GetValue();
ptsquare = tt->GetLeaf("pt2")->GetValue();
nu = tt->GetLeaf("nu")->GetValue();
q = tt->GetLeaf("q")->GetValue();
Q2 = tt->GetLeaf("Q2")->GetValue();
pm= tt->GetLeaf("Pm")->GetValue();
hxptar=tt->GetLeaf("hsxptar")->GetValue();
hyptar=tt->GetLeaf("hsyptar")->GetValue();
pxptar=tt->GetLeaf("ssxptar")->GetValue();
pyptar=tt->GetLeaf("ssyptar")->GetValue();
xbj = tt->GetLeaf("xbj")->GetValue();
w = tt->GetLeaf("W")->GetValue();
W2=w*w;
phi=tt->GetLeaf("phipq")->GetValue();
Epi = sqrt(pow(protonmass,2) + pow(mom,2));//proton not pion==========================================================>imp made pion mass for now
z = Epi/nu;
mx2 = (protonmass + nu - z*nu) * (protonmass + nu - z*nu) - abs(pm)*abs(pm);
normwt = Weight*normfac_value/rad_evts;

normwt_sig=normwt*sighad;
pt=sqrt(ptsquare);
ptrack_x_fp=tt->GetLeaf("ssxfp")->GetValue();
ptrack_xp_fp=tt->GetLeaf("ssxpfp")->GetValue();
ptrack_y_fp=tt->GetLeaf("ssyfp")->GetValue();
ptrack_yp_fp=tt->GetLeaf("ssypfp")->GetValue();
htrack_x_fp=tt->GetLeaf("hsxfp")->GetValue();
htrack_xp_fp=tt->GetLeaf("hsxpfp")->GetValue();
htrack_y_fp=tt->GetLeaf("hsyfp")->GetValue();
htrack_yp_fp=tt->GetLeaf("hsypfp")->GetValue();



xathgcer = ptrack_x_fp + 156.27  * ptrack_xp_fp;
yathgcer = ptrack_y_fp + 156.27  * ptrack_yp_fp;
central_hole = (pow(yathgcer-1.33, 2) +  pow(xathgcer-0.83, 2) >= pow(6.0, 2));//radius = 
   
right_or_left_of_hole = ((yathgcer > 1.33 && (xathgcer < 0. ||  xathgcer > 3.0) ) ||  (yathgcer < 1.33 && (xathgcer < 0.||  xathgcer > 3)  ));
remove_region = central_hole && right_or_left_of_hole;//ok	 
//hgcer done


acceptance_cut_coin = spdelta > pdelta_min && spdelta < pdelta_max && hsdelta > hdelta_min && hsdelta < hdelta_max && hxptar > hms_xptar_min  && hxptar < hms_xptar_max &&  hyptar > hms_yptar_min  && hyptar < hms_yptar_max && pxptar > shms_xptar_min  && pxptar < shms_xptar_max && pyptar > shms_yptar_min  && pyptar < shms_yptar_max;

//geom cuts:
xatpreshower = ptrack_x_fp + 292.64 * (ptrack_xp_fp);
yatpreshower = ptrack_y_fp + 292.64 * (ptrack_yp_fp);

xatshower = ptrack_x_fp + 306.44 * (ptrack_xp_fp);
yatshower = ptrack_y_fp + 306.44 * (ptrack_yp_fp);

xatpreshowerback = ptrack_x_fp + 302.64 * (ptrack_xp_fp);
yatpreshowerback = ptrack_y_fp + 302.64 * (ptrack_yp_fp);

xatshowerback = ptrack_x_fp + 356.44 * (ptrack_xp_fp);
yatshowerback = ptrack_y_fp + 356.44 * (ptrack_yp_fp);
		
xataero = ptrack_x_fp + 231.0 * (ptrack_xp_fp);
yataero = ptrack_y_fp + 231.0 * (ptrack_yp_fp);

pcal_geom_cut_hem =  xatshowerback>-60  &&  xatshowerback < 60  && yatshowerback>-60  && yatshowerback < 60 && xatpreshowerback  > -60 && xatpreshowerback  < 60  && yatpreshowerback >-60 && yatpreshowerback < 60;
paero_geom_cut =  xataero >-50 && xataero < 50 && yataero >-50 && yataero<50;

xathcal = htrack_x_fp + hcal_4ta_zpos * htrack_xp_fp;
yathcal = htrack_y_fp + hcal_4ta_zpos * htrack_yp_fp;
hcal_geom_cut =  (yathcal <= (hcal_left-2.0)  &&  yathcal >= (hcal_right+2.0)   &&  xathcal <= (hcal_bottom-2.0) && xathcal >= (hcal_top+2.0));
//hms focal plane cuts
hms_dc_fp_cut = abs(htrack_x_fp)<=58;
//hms hodo cut
xathhodo = htrack_x_fp + 318 *  htrack_xp_fp;
hms_hodo_cut = abs(xathhodo)<=59;
//shms cal cut (peters)
xatpcal = ptrack_x_fp + scal_4ta_zpos *ptrack_xp_fp;
yatpcal = ptrack_y_fp + scal_4ta_zpos *ptrack_yp_fp;

pcal_geom_cut = (yatpcal <= (scal_left-2.0) &&  yatpcal >= (scal_right+2.0)) &&  (xatpcal <= (scal_bottom-2.0) &&   xatpcal>= (scal_top+2.0));

//shms focal plane cuts
shms_dc_fp_cut = abs(ptrack_x_fp) <=38 && abs(ptrack_y_fp) <=38;
//! Hourglass cut: 
hourglass_cut = (ptrack_y_fp <= (10 + abs(ptrack_x_fp)))  && (ptrack_y_fp >= (-10 - abs(ptrack_x_fp)));

peter_all_geom_cut =  pcal_geom_cut && hcal_geom_cut && paero_geom_cut &&  shms_dc_fp_cut && hms_dc_fp_cut && hms_hodo_cut &&   hourglass_cut;
 	
if(acceptance_cut_coin && peter_all_geom_cut && pt< 0.186 && mx2 > 1.1664 ){
//if(acceptance_cut_coin && peter_all_geom_cut){
