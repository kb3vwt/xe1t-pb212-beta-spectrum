#ifndef pbEventActionMessenger_h
#define pbEventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class pbEventAction;
class G4UIcmdWithAString;

class pbEventActionMessenger: public G4UImessenger
{
public:
  pbEventActionMessenger(pbEventAction*);
  ~pbEventActionMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  pbEventAction*   eventAction;
  G4UIcmdWithAString* DrawCmd;
};

#endif
