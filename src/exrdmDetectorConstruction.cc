//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
#include "exrdmDetectorConstruction.hh"
#include "exrdmDetectorMessenger.hh"
//#include "exrdmDetectorSD.hh"
#include "G4UImanager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
//#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"

#include "exrdmMaterial.hh"
#include "G4MaterialTable.hh"


#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
exrdmDetectorConstruction::exrdmDetectorConstruction()
:solidWorld(0),  logicWorld(0),  physiWorld(0),
 solidTarget(0), logicTarget(0), physiTarget(0), 
 solidDetector(0),logicDetector(0),physiDetector(0), 
 worldMat(0), chamberMat(0),
 fWorldLength(0.)
 */
exrdmDetectorConstruction::exrdmDetectorConstruction()
{
  detectorMessenger = new exrdmDetectorMessenger(this);
  
  
  DefineMaterials();
  /*
  fDetectorThickness = 2.* cm;
  fTargetRadius = 0.5 * cm;
  fDetectorLength = 5.0 * cm;      
  fTargetLength  = 1.0 * cm;         
//--------- Sizes of the principal geometrical components (solids)  ---------
  fWorldLength = std::max(fTargetLength,fDetectorLength);
  fWorldRadius = fTargetRadius + fDetectorThickness;
  */
  
  //Cryostat Volume
  CS_OD        = 110.0*cm;  //Outer Diameter of Chamber
  CS_Height    = 120.0*cm;  //Height of the chamber (inner cap to inner cap)
  CS_Thickness = 1.25*cm;  //Thickness of the sheet metal
  
  //World Extents
  worldX_ext = 1.5*CS_OD; // 150% Diameter of tank
  worldY_ext = 1.5*CS_OD;
  worldZ_ext = 1.5*(2.0*CS_Thickness + CS_Height); //150% outer cap-cap tube heights
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
exrdmDetectorConstruction::~exrdmDetectorConstruction()
{
  delete detectorMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void exrdmDetectorConstruction::DefineMaterials()
{
//--------- Material definition ---------

/*
  materialsManager = new exrdmMaterial();
  // liquid xenon
  materialsManager->AddMaterial("Xenon","Xe",2.96*g/cm3,"liquid",160*kelvin);
  // S. Steel
  materialsManager->AddMaterial("Germanium","Ge",5.323*g/cm3,""); 
  // lXe+Pb
  materialsManager->AddMaterial("CsI","Cs-I",4.51*g/cm3,"");

  // G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  // G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  worldMat    = materialsManager->GetMaterial("");
  chamberMat  = materialsManager->GetMaterial("");
  lXeMix   = materialsManager->GetMaterial("");
  */
  
  //Obtain the NIST material manager, look for materials named above, assign to material:
	G4NistManager* nist    = G4NistManager::Instance(); //starts instance of NIST Material DB
	worldMat   = nist->FindOrBuildMaterial("G4_WATER"); //World Material (nominally water)
	chamberMat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL"); //Chamber Material (nominally stainless steel 316 series)
	
  //Filler Material:
	Pb212Percent = 1.06061e-28;
	lXePercent   = 100. - Pb212Percent;
	
	G4Element* PbSrc   = new G4Element("Lead","Pb",1);
	G4Isotope* PB212   = new G4Isotope("Pb212",82,212,212.997*g/mole);//a value from http://en.wikipedia.org/wiki/Isotopes_of_lead
        PbSrc->AddIsotope(PB212,100*perCent); // In this case we have "pure" Lead-212.
	G4Material* lXe    = new G4Material("lXe",54,131.29*g/mole,2.96*g/cm3); //Filler Material (nominally lXe)
	
	//***Material properties tables

  const G4int lXe_NUMENTRIES = 3;
  G4double lXe_Energy[lXe_NUMENTRIES]    = { 7.0*eV , 7.07*eV, 7.14*eV };

  G4double lXe_SCINT[lXe_NUMENTRIES] = { 0.1, 1.0, 0.1 };
  G4double lXe_RIND[lXe_NUMENTRIES]  = { 1.59 , 1.57, 1.54 };
  G4double lXe_ABSL[lXe_NUMENTRIES]  = { 35.*cm, 35.*cm, 35.*cm}; 
  lXe_mt = new G4MaterialPropertiesTable();
  lXe_mt->AddProperty("FASTCOMPONENT", lXe_Energy, lXe_SCINT, lXe_NUMENTRIES);
  lXe_mt->AddProperty("SLOWCOMPONENT", lXe_Energy, lXe_SCINT, lXe_NUMENTRIES);
  lXe_mt->AddProperty("RINDEX",        lXe_Energy, lXe_RIND,  lXe_NUMENTRIES);
  lXe_mt->AddProperty("ABSLENGTH",     lXe_Energy, lXe_ABSL,  lXe_NUMENTRIES);
  lXe_mt->AddConstProperty("SCINTILLATIONYIELD",12000./MeV); 
  lXe_mt->AddConstProperty("RESOLUTIONSCALE",1.0);
  lXe_mt->AddConstProperty("FASTTIMECONSTANT",20.*ns);
  lXe_mt->AddConstProperty("SLOWTIMECONSTANT",45.*ns);
  lXe_mt->AddConstProperty("YIELDRATIO",1.0);
  lXe->SetMaterialPropertiesTable(lXe_mt);

  // Set the Birks Constant for the lXe scintillator

  lXe->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
	
  lXeMix = new G4Material("lXe+Pb212",2.96*g/cm3,2);
  lXeMix->AddMaterial(lXe,lXePercent*perCent);
  lXeMix->AddElement(PbSrc,Pb212Percent*perCent);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* exrdmDetectorConstruction::Construct()
{
//--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  //--------- Sizes of the principal geometrical components (solids)  ---------
  
  /*
  //Cryostat Volume
  CS_OD        = 110.0*cm;  //Outer Diameter of Chamber
  CS_Height    = 120.0*cm;  //Height of the chamber (inner cap to inner cap)
  CS_Thickness = 1.25*cm;  //Thickness of the sheet metal
  
  //World Extents
  worldX_ext = 1.5*CS_OD; // 150% Diameter of tank
  worldY_ext = 1.5*CS_OD;
  worldZ_ext = 1.5*(2.0*CS_Thickness + CS_Height); //150% outer cap-cap tube heights
  */
   
  //------------------------------ 
  // World
  //------------------------------ 

 solidWorld = new G4Box("World",worldX_ext,worldY_ext,worldZ_ext);
 logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
  
  //  Must place the World Physical volume unrotated at (0,0,0).
  // 
  physiWorld = new G4PVPlacement(0,               // no rotation
                                 G4ThreeVector(), // at (0,0,0)
                                 logicWorld,      // its logical volume
				 "World",         // its name
                                 0,               // its mother  volume
                                 false,           // no boolean operations
                                 0);              // no field specific to volume
				 
  //------------------------------ 
  // Chamber Walls, Caps
  //------------------------------
  
  //First, create outside walls
  schamberWall   = new G4Tubs("Chamber Wall", CS_OD - CS_Thickness, CS_OD, CS_Height / 2.0, 0., twopi);
  lchamberWall   = new G4LogicalVolume(schamberWall, chamberMat, "Chamber Wall");
  pchamberWall   = new G4PVPlacement(0, G4ThreeVector(), "Chamber Wall", logicWorld, false, 0, 0);
  //Next, cap off ends (Use boolean? Or not? Also: Could use copies, but object is simple enough not to)
  //top 
  schamberCapTop   = new G4Tubs("Chamber Lid", 0, CS_OD, CS_Thickness / 2.0, 0., twopi);
  lchamberCapTop   = new G4LogicalVolume(schamberCapTop, chamberMat, "Chamber Lid");
  pchamberCapTop   = new G4PVPlacement(0, G4ThreeVector(0, 0, (CS_Height + CS_Thickness) / 2.0), "Chamber Lid", logicWorld, false, 0, 0);
  //bottom
  schamberCapBottom   = new G4Tubs("Chamber Bottom", 0, CS_OD, CS_Thickness / 2.0, 0., twopi);
  lchamberCapBottom   = new G4LogicalVolume(schamberCapBottom, chamberMat, "Chamber Bottom");
  pchamberCapBottom   = new G4PVPlacement(0, G4ThreeVector(0, 0, -(CS_Height + CS_Thickness) / 2.0), "Chamber Bottom", logicWorld, false, 0, 0);          // no particular field 

  //  G4cout << "Target is a cylinder with rdius of " << targetradius/cm << " cm of " 
  //       << TargetMater->GetName() << G4endl;

  //------------------------------ 
  // Detector Fill
  //------------------------------
  
  G4ThreeVector positionDetector = G4ThreeVector(0,0,0);
  
  solidDetector = new G4Tubs("Fill Volume", 0, CS_OD - CS_Thickness, (CS_Height - 2.0 * CS_Thickness) / 2.0, 0., twopi);
  logicDetector = new G4LogicalVolume(solidDetector, lXeMix, "Detector Fill Volume");  
  //logicDetector = new G4LogicalVolume(solidDetector,FillerLiquidMat,"Fill Volume");
  physiDetector = new G4PVPlacement(0,              // no rotation
				  positionDetector, // at (x,y,z)
				  logicDetector,    // its logical volume				  
				  "Detector",       // its name
				  logicWorld,      // its mother  volume
				  false,           // no boolean operations
				  0);              // no particular field 

  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  //  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  // G4String detectortargetSDname = "exrdm/DetectorTargetSD";
  // exrdmDetectorSD* aDetectorSD = new exrdmDetectorSD( detectorTargetSDname );
  // SDman->AddNewDetector( aDetectorSD );
  //logicTarget->SetSensitiveDetector( aDetectorSD );
  // logicDetector->SetSensitiveDetector( aDetectorSD );
  //
  //-------------------------------------------------
  // regions
  //
  //  if(targetRegion) delete targetRegion;
  // if(detectorRegion) delete detectorRegion;
  targetRegion     = new G4Region("Target");
  detectorRegion   = new G4Region("Detector");
  targetRegion->AddRootLogicalVolume(lchamberWall);
  targetRegion->AddRootLogicalVolume(lchamberCapTop);
  targetRegion->AddRootLogicalVolume(lchamberCapBottom);
  detectorRegion->AddRootLogicalVolume(logicDetector);


  //--------- Visualization attributes -------------------------------
  /*
  logicWorld->SetVisAttributes(G4VisAttributes::Invisible);
  G4VisAttributes* TargetVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  logicTarget ->SetVisAttributes(TargetVisAtt);
  G4VisAttributes* DetectorVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,.0));
  logicDetector->SetVisAttributes(DetectorVisAtt);
  */

  //------------ set the incident position ------

 // get the pointer to the User Interface manager 
    
  G4UImanager* UI = G4UImanager::GetUIpointer();  
  //      UI->ApplyCommand("/run/verbose 1");
  //      UI->ApplyCommand("/event/verbose 2");
  //      UI->ApplyCommand("/tracking/verbose 1");  

  G4double zpos = -worldX_ext/2.;
  G4String command = "/gps/pos/centre ";
  std::ostringstream os;
  os << zpos ; 
  G4String xs = os.str();
  UI->ApplyCommand(command+"0. 0. "+xs+" mm");
  UI->ApplyCommand("/gps/pos/type Point");
  command = "/gps/position ";
  //  UI->ApplyCommand(command+"0. 0. "+xs+" mm");
  UI->ApplyCommand("/gps/particle proton");
  UI->ApplyCommand("/gps/direction 0 0 1");
  UI->ApplyCommand("/gps/energy 100 MeV");
  //       
  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void exrdmDetectorConstruction::setTargetMaterial(G4String materialName)
{
/*
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {TargetMater = pttoMaterial;
      if (logicTarget) logicTarget->SetMaterial(pttoMaterial); 
      G4cout << "\n----> The target has been changed to " << fTargetLength/cm << " cm of "
             << materialName << G4endl;
     }  
*/	 
	G4cout << "Function not implemented.\n";

}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void exrdmDetectorConstruction::setDetectorMaterial(G4String materialName)
{
	/*
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {DetectorMater = pttoMaterial;
      if (logicDetector) logicDetector->SetMaterial(pttoMaterial); 
      G4cout << "\n----> The Deetctor has been changed to" << fDetectorLength/cm << " cm of "
             << materialName << G4endl;
     }    
*/
	G4cout << "Function not implemented.\n";
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
