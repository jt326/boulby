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
//
/// \file simple_geom_EventAction.cc
/// \brief Implementation of the simple_geom_EventAction class

#include "simple_geom_EventAction.hh"
#include "simple_geom_RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "AnaManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

simple_geom_EventAction::simple_geom_EventAction(simple_geom_RunAction* runAction, AnaManager* anam)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  mAnaM(anam)
{
    fRunVerboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
    G4cout<<"EventAction: Setting Run Verbose Level to: "<<fRunVerboseLevel<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

simple_geom_EventAction::~simple_geom_EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void simple_geom_EventAction::BeginOfEventAction(const G4Event* evt)
{
    // if (evt->GetEventID() == 0) {
    // 	fRunVerboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
    // }

    // if (fRunVerboseLevel>1) {
    // 	G4cout<<"Starting event number "<<evt->GetEventID()<<G4endl;
    // }
    //G4RunManager::GetRunManager()->RestoreRandomNumberStatus("currentEvent.rndm");

  fEdep = 0.;
  mAnaM->Reset();
  mAnaM->mEvent.runNo = fRunAction->mRunID;
  mAnaM->mEvent.eventNo = evt->GetEventID();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void simple_geom_EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  if (mAnaM->mEvent.n_neutrons > 0)
      mAnaM -> FillTree();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
