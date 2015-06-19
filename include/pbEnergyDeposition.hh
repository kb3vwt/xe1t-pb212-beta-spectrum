// Energy Deposition header file
// Copied from geant4 rdecay02 Example

#ifndef pbEnergyDeposition_h
#define pbEnergyDeposition_h 1

#include "globals.hh"

class pbEnergyDeposition
{
  public:   // with description

    pbEnergyDeposition();
    pbEnergyDeposition( const pbEnergyDeposition &right );
    pbEnergyDeposition( G4double, G4double, G4double );
    virtual ~pbEnergyDeposition();
         // Constructor and virtual destructor

    G4bool operator==(const pbEnergyDeposition &right) const ;
    G4bool operator< (const pbEnergyDeposition &right) const ;
    G4bool operator<=(const pbEnergyDeposition &right) const ;
  // Operators  

  G4double GetEnergy() {return Energy;};
  G4double GetTime() {return Time;};
  G4double GetWeight() {return Weight;};
  // Accessors

  private:

    G4double Energy;  
    G4double Time;    
    G4double Weight;
};
#endif



