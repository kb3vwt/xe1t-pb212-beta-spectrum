/*
Liquid Xenon Chamber Design File for Geant4.9.4
For use in determining the Pb-212 beta spectrum. 

File started by J.Sheldon, June 04, 2015
*/

#include "chamberConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"



//==================Stuff that needs to be added but won't be just yet. =====================
//Depending on the analysis, this stuff likely varies.
//To Do: Look into how that part is done.
//===========================================================================================


G4VPhysicalVolume* chamberConstruction::Construct()
{
  const double Pi = 3.14159265359;

  //Check for Overlaps:
  G4bool checkOverlaps = true;


  //System Configurable(s):
  //G4double TEMPERATURE = 160*Kelvin; //Check this!

  ///=============================Materials=============================
  //**************==Configurables==**************
  //Strings to search for in the NIST DB
  G4String worldMatNISTName   = "G4_WATER"; //World Material
  G4String fill_PrimaryNISTNAME   = "G4_lXe"; //Filler Material NIST Name - Major Component
  //G4String fill_SecondaryNAME   = "Pb-212"; //Filler Material NIST Name - Major Component
  G4String chamberMatNISTName = "G4_STAINLESS-STEEL"; //Stainless Steel NIST Name - unsure of 
  
  //Filler Reported Name:
  //G4String fillMaterialName = "Liquid Xenon";
  
  //Percent of Initial Filler that is lXe and Pb-212:
  G4double lXePercent   = 100.*perCent;
  G4double Pb212Percent = 100.*perCent - lXePercent;
  //Decays: This is handled by the G4Decay class. These serve as initial values.
  //Warning: The filler should have Pb212 inside it! Unknown amount needed.
  //**************==End Configurables==**************

  


  //Obtain the NIST material manager, look for materials named above, assign to material:
  G4NistManager* nist    = G4NistManager::Instance(); //starts instance of NIST Material DB
  G4Material* worldMat   = nist->FindOrBuildMaterial(worldMatNISTName); //World Material (nominally water)
  G4Material* chamberMat = nist->FindOrBuildMaterial(chamberMatNISTName); //Chamber Material (nominally stainless steel 316 series)
  //Configure FILLER material:
  /*
		Note: Decay is added by G4Decay, across all materials. 
			ToDo: 
				+Find what Pb-212 is listed under.
				+Make a "Mixture" with initial filler amounts - about 3-5Bq of Pb-212 within the 3300kg tank should be 'enough'.
				+Save as filler material
		
  */
  //Lead 212 Definition:
  G4Element* elPb  = new G4Element("Lead","Pb",1);
  G4Isotope* PB212 = new G4Isotope("Pb212",82,212,212.997*g/mole);//a value from http://en.wikipedia.org/wiki/Isotopes_of_lead
  elPb->AddIsotope(PB212,100*perCent); // In this case we have "pure" Lead-212.
  
  
  //Define Filler Liquid:
  G4Material* FillerLiquidMat    = nist->FindOrBuildMaterial(fill_PrimaryNISTNAME); //Filler Material (nominally lXe)

  //Define Filler Mix (Pb212 and lXe, nominally)
  G4Material* FillerMIX = new G4Material("lXe + Pb-212 Mixture",2.96*g/cm3,2);
  FillerMIX->AddMaterial(FillerLiquidMat,lXePercent);
  FillerMIX->AddElement(elPb,Pb212Percent);
  
  
  ///========================End Materials=============================
  ///=============================Geometry==============================
  //**************==Configurables==**************
  //World Volume (ext = extent)
  //G4double worldX_ext = 0*cm,
  //        worldY_ext = 0*cm,
  //        worldZ_ext = 0*cm;

  //Cryostat Volume
  G4double CS_OD        = 110.0*cm;  //Outer Diameter of Chamber
  G4double CS_Height    = 120.0*cm;  //Height of the chamber (inner cap to inner cap)
  G4double CS_Thickness = 1.25*cm;  //Thickness of the sheet metal
  //********==End Configurables==**************


  //World Extents
  G4double worldX_ext = 1.5*CS_OD; // 150% Diameter of tank
  G4double worldY_ext = worldX_ext;
  G4double worldZ_ext = 1.5*(2.0*CS_Thickness + CS_Height); //150% outer cap-cap tube heights

  //Create World Solid, Logical Volume, and Physical Volume:
  G4Box* sworldVol             = new G4Box("World", worldX_ext, worldY_ext, worldZ_ext);
  G4LogicalVolume* lworldVol   = new G4LogicalVolume(sworldVol, worldMat, "World");
  G4VPhysicalVolume* pworldVol = new G4PVPlacement(0, G4ThreeVector(), "World", 0, false, 0, checkOverlaps);
  
  //Create Chamber Solid, Logical Volume, and Physical Volume:
  //First, create outside walls
  G4Tubs* schamberWall            = new G4Tubs("Chamber Wall", CS_OD - CS_Thickness, CS_OD, CS_Height / 2.0, 0.*Pi, 2.*Pi);
  G4LogicalVolume* lchamberWall   = new G4LogicalVolume(schamberWall, chamberMat, "Chamber Wall");
  G4VPhysicalVolume* pchamberWall = new G4PVPlacement(0, G4ThreeVector(), "Chamber Wall", lworldVol, false, 0, checkOverlaps);
  //Next, cap off ends (Use boolean? Or not? Also: Could use copies, but object is simple enough not to)
  //top 
  G4Tubs* schamberCapTop            = new G4Tubs("Chamber Lid", 0, CS_OD, CS_Thickness / 2.0, 0.*Pi, 2.*Pi);
  G4LogicalVolume* lchamberCapTop   = new G4LogicalVolume(schamberCapTop, chamberMat, "Chamber Lid");
  G4VPhysicalVolume* pchamberCapTop = new G4PVPlacement(0, G4ThreeVector(0, 0, (CS_Height + CS_Thickness) / 2.0), "Chamber Lid", lworldVol, false, 0, checkOverlaps);
  //bottom
  G4Tubs* schamberCapBottom            = new G4Tubs("Chamber Bottom", 0, CS_OD, CS_Thickness / 2.0, 0.*Pi, 2.*Pi);
  G4LogicalVolume* lchamberCapBottom   = new G4LogicalVolume(schamberCapBottom, chamberMat, "Chamber Bottom");
  G4VPhysicalVolume* pchamberCapBottom = new G4PVPlacement(0, G4ThreeVector(0, 0, -(CS_Height + CS_Thickness) / 2.0), "Chamber Bottom", lworldVol, false, 0, checkOverlaps);

  //The Fill (lXe) solid, Logical Volume, and Physical Volume:
  G4Tubs* sfillVolume            = new G4Tubs("Liquid Xenon Filler", 0, CS_OD - CS_Thickness, CS_Thickness, 0., 2.*Pi);
  G4LogicalVolume* lfillVolume   = new G4LogicalVolume(sfillVolume, FillerMIX, fillMaterialName);
  G4VPhysicalVolume* pfillVolume = new G4PVPlacement(0, G4ThreeVector(), fillMaterialName, lworldVol, false, 0, checkOverlaps);
  ///========================End Geometry==========================

  return pworldVol;
}
