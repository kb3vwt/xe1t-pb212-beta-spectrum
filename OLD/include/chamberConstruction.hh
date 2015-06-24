/*
Liquid Xenon Chamber Design Header File for Geant4.9.4
For use in determining the Pb-212 beta spectrum. 

File started by J.Sheldon, June 17, 2015
*/


#ifndef chamberConstruction_h
#define chamberConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Region;
//class pbDetectorMessenger;
//class pbMaterial;

class chamberConstruction : public G4VUserDetectorConstruction
{
public:
  chamberConstruction();
  ~chamberConstruction();

  G4VPhysicalVolume* Construct();
  
private:
  G4String worldMatNISTName;
  G4String fill_PrimaryNISTNAME;
  G4String fill_SecondaryNAME;
  G4String chamberMatNISTName;
  G4String fillMaterialName;
  G4double lXePercent;
  G4double Pb212Percent;
  G4NistManager* nist;
  G4Material* worldMat;
  G4Material* chamberMat;
  G4Element* elPb;
  G4Isotope* PB212;
  G4Material* FillerLiquidMat;
  G4Material* FillerMIX;

  G4double CS_OD;
  G4double CS_Height;
  G4double CS_Thickness;
  G4double worldX_ext;
  G4double worldY_ext;
  G4double worldZ_ext;

  G4Box* sworldVol;
  G4LogicalVolume* lworldVol;
  G4VPhysicalVolume* pworldVol;

  G4Tubs* schamberWall;
  G4LogicalVolume* lchamberWall;
  G4VPhysicalVolume* pchamberWall;

  G4Tubs* schamberCapTop;
  G4LogicalVolume* lchamberCapTop;
  G4VPhysicalVolume* pchamberCapTop;

  G4Tubs* schamberCapBottom;
  G4LogicalVolume* lchamberCapBottom;
  G4VPhysicalVolume* pchamberCapBottom;

  G4Tubs* sfillVolume;
  G4LogicalVolume* lfillVolume;
  G4VPhysicalVolume* pfillVolume;


};

#endif
