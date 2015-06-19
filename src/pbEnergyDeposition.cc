// Energy Deposition src file
// Copied from geant4 rdecay02 Example
#include "pbEnergyDeposition.hh"


//
// Default constructor
//
pbEnergyDeposition::pbEnergyDeposition()
{;}
//
// Specific constructor
//
pbEnergyDeposition::pbEnergyDeposition( G4double energy,
				    G4double time,
                                    G4double weight )
  : Energy(energy),
    Time(time),
    Weight(weight)
{;}


//
// Copy constructor
//
pbEnergyDeposition::pbEnergyDeposition( const pbEnergyDeposition &right )
  : Energy(right.Energy),
    Time(right.Time),
    Weight(right.Weight)
{;}

//
// Destructor
//
pbEnergyDeposition::~pbEnergyDeposition() {;}

//
// Equivalence operator
//
G4bool pbEnergyDeposition::operator==( const pbEnergyDeposition &right ) const
{
  return Time == right.Time;
}

//
// Order operators
//
G4bool pbEnergyDeposition::operator<( const pbEnergyDeposition &right ) const
{
  return Time < right.Time;
}

G4bool pbEnergyDeposition::operator<=( const pbEnergyDeposition &right ) const
{
  return Time <= right.Time;
}

