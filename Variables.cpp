//
// Created by tal on 12.12.2019.
//

#include "Variables.h"
Variables *Variables::instance = 0;

double Variables::doShuntingYard(string str) {
  i1->shuntingYard(str);
  return i1->createExp()->calculate();
}

void Variables::addVarToMap(string str) {
  i1->generateVarAndVal(str);
}

Variables::Variables() {
  this->i1 = new Interpreter();
}

void Variables::InitializeSymbols() {
  // locking map
  mapLock.try_lock();

  simMap["airspeed-indicator_indicated-speed-kt"] =
      new Var(0, "/instrumentation/airspeed-indicator/indicated-speed-kt", false);

  simMap["time_warp"] =
      new Var(0, "/sim/time/warp", false);

  simMap["switches_magnetos"] =
      new Var(0, "/controls/switches/magnetos", false);

  simMap["heading-indicator_offset-deg"] =
      new Var(0, "/instrumentation/heading-indicator/offset-deg", false);

  simMap["altimeter_indicated-altitude-ft"] =
      new Var(0, "/instrumentation/altimeter/indicated-altitude-ft", false);

  simMap["altimeter_pressure-alt-ft"] =
      new Var(0, "/instrumentation/altimeter/pressure-alt-ft", false);

  simMap["attitude-indicator_indicated-pitch-deg"] =
      new Var(0, "/instrumentation/attitude-indicator/indicated-pitch-deg", false);

  simMap["attitude-indicator_indicated-roll-deg"] =
      new Var(0, "/instrumentation/attitude-indicator/indicated-roll-deg", false);

  simMap["attitude-indicator_internal-pitch-deg"] =
      new Var(0, "/instrumentation/attitude-indicator/internal-pitch-deg", false);

  simMap["attitude-indicator_internal-roll-deg"] =
      new Var(0, "/instrumentation/attitude-indicator/internal-roll-deg", false);

  simMap["encoder_indicated-altitude-ft"] =
      new Var(0, "/instrumentation/encoder/indicated-altitude-ft", false);

  simMap["encoder_pressure-alt-ft"] =
      new Var(0, "/instrumentation/encoder/pressure-alt-ft", false);

  simMap["gps_indicated-altitude-ft"] =
      new Var(0, "/instrumentation/gps/indicated-altitude-ft", false);

  simMap["gps_indicated-ground-speed-kt"] =
      new Var(0, "/instrumentation/gps/indicated-ground-speed-kt", false);

  simMap["gps_indicated-vertical-speed"] =
      new Var(0, "/instrumentation/gps/indicated-vertical-speed", false);

  simMap["indicated-heading-deg"] =
      new Var(0, "/instrumentation/heading-indicator/indicated-heading-deg", false);

  simMap["magnetic-compass_indicated-heading-deg"] =
      new Var(0, "/instrumentation/magnetic-compass/indicated-heading-deg", false);

  simMap["slip-skid-ball_indicated-slip-skid"] =
      new Var(0, "/instrumentation/slip-skid-ball/indicated-slip-skid", false);

  simMap["turn-indicator_indicated-turn-rate"] =
      new Var(0, "/instrumentation/turn-indicator/indicated-turn-rate", false);

  simMap["vertical-speed-indicator_indicated-speed-fpm"] =
      new Var(0, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm", false);

  simMap["flight_aileron"] =
      new Var(0, "/controls/flight/aileron", false);

  simMap["flight_elevator"] =
      new Var(0, "/controls/flight/elevator", false);

  simMap["flight_rudder"] =
      new Var(0, "/controls/flight/rudder", false);

  simMap["flight_flaps"] =
      new Var(0, "/controls/flight/flaps", false);

  simMap["engine_throttle"] =
      new Var(0, "/controls/engines/engine/throttle", false);

  simMap["current-engine_throttle"] =
      new Var(0, "/controls/engines/current-engine/throttle", false);

  simMap["switches_master-avionics"] =
      new Var(0, "/controls/switches/master-avionics", false);

  simMap["switches_starter"] =
      new Var(0, "/controls/switches/starter", false);

  simMap["active-engine_auto-start"] =
      new Var(0, "/engines/active-engine/auto-start", false);

  simMap["flight_speedbrake"] =
      new Var(0, "/controls/flight/speedbrake", false);

  simMap["c172p_brake-parking"] =
      new Var(0, "/sim/model/c172p/brake-parking", false);

  simMap["engine_primer"] =
      new Var(0, "/controls/engines/engine/primer", false);

  simMap["current-engine_mixture"] =
      new Var(0, "/controls/engines/current-engine/mixture", false);

  simMap["switches_master-bat"] =
      new Var(0, "/controls/switches/master-bat", false);

  simMap["switches_master-alt"] =
      new Var(0, "/controls/switches/master-alt", false);

  simMap["engine_rpm"] =
      new Var(1, "/engines/engine/rpm", false);

  // unlocking map
  mapLock.unlock();
}
// a function that update the symbols value from the server!
void Variables::UpdateSymbolsValueFromServer(vector<double> vec) {
  vector<double> vec1;

  // lock map
  mapLock.try_lock();

  if (!simMap["airspeed-indicator_indicated-speed-kt"]->isBindedFromRightToLeft()) {
    simMap["airspeed-indicator_indicated-speed-kt"]->setValue(vec[0]);
    if (fromPathToVar.count(simMap["airspeed-indicator_indicated-speed-kt"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["airspeed-indicator_indicated-speed-kt"]->GetSim()]]->setValue(vec[0]);
      i1->setVariables(fromPathToVar[simMap["airspeed-indicator_indicated-speed-kt"]->GetSim()], vec[0]);
    }
  }
  if (!simMap["time_warp"]->isBindedFromRightToLeft()) {
    simMap["time_warp"]->setValue((vec[1]));
    if (fromPathToVar.count(simMap["time_warp"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["time_warp"]->GetSim()]]->setValue(vec[1]);
      i1->setVariables(fromPathToVar[simMap["time_warp"]->GetSim()], vec[1]);
    }
  }
  if (!simMap["switches_magnetos"]->isBindedFromRightToLeft()) {
    simMap["switches_magnetos"]->setValue(vec[2]);
    if (fromPathToVar.count(simMap["switches_magnetos"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["switches_magnetos"]->GetSim()]]->setValue(vec[2]);
      i1->setVariables(fromPathToVar[simMap["switches_magnetos"]->GetSim()], vec[2]);
    }
  }
  if (!simMap["heading-indicator_offset-deg"]->isBindedFromRightToLeft()) {
    simMap["heading-indicator_offset-deg"]->setValue(vec[3]);
    if (fromPathToVar.count(simMap["heading-indicator_offset-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["heading-indicator_offset-deg"]->GetSim()]]->setValue(vec[3]);
      i1->setVariables(fromPathToVar[simMap["heading-indicator_offset-deg"]->GetSim()], vec[3]);
    }
  }
  if (!simMap["altimeter_indicated-altitude-ft"]->isBindedFromRightToLeft()) {
    simMap["altimeter_indicated-altitude-ft"]->setValue(vec[4]);
    if (fromPathToVar.count(simMap["altimeter_indicated-altitude-ft"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["altimeter_indicated-altitude-ft"]->GetSim()]]->setValue(vec[4]);
      i1->setVariables(fromPathToVar[simMap["altimeter_indicated-altitude-ft"]->GetSim()], vec[4]);
    }
  }
  if (!simMap["altimeter_pressure-alt-ft"]->isBindedFromRightToLeft()) {
    simMap["altimeter_pressure-alt-ft"]->setValue(vec[5]);
    if (fromPathToVar.count(simMap["altimeter_pressure-alt-ft"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["altimeter_pressure-alt-ft"]->GetSim()]]->setValue(vec[5]);
      i1->setVariables(fromPathToVar[simMap["altimeter_pressure-alt-ft"]->GetSim()], vec[5]);
    }
  }
  if (!simMap["attitude-indicator_indicated-pitch-deg"]->isBindedFromRightToLeft()) {
    simMap["attitude-indicator_indicated-pitch-deg"]->setValue(vec[6]);
    if (fromPathToVar.count(simMap["attitude-indicator_indicated-pitch-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["attitude-indicator_indicated-pitch-deg"]->GetSim()]]->setValue(vec[6]);
      i1->setVariables(fromPathToVar[simMap["attitude-indicator_indicated-pitch-deg"]->GetSim()], vec[6]);
    }
  }

  if (!simMap["attitude-indicator_indicated-roll-deg"]->isBindedFromRightToLeft()) {
    simMap["attitude-indicator_indicated-roll-deg"]->setValue(vec[7]);
    if (fromPathToVar.count(simMap["attitude-indicator_indicated-roll-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["attitude-indicator_indicated-roll-deg"]->GetSim()]]->setValue(vec[7]);
      i1->setVariables(fromPathToVar[simMap["attitude-indicator_indicated-roll-deg"]->GetSim()], vec[7]);
    }
  }

  if (!simMap["attitude-indicator_internal-pitch-deg"]->isBindedFromRightToLeft()) {
    simMap["attitude-indicator_internal-pitch-deg"]->setValue(vec[8]);
    if (fromPathToVar.count(simMap["attitude-indicator_internal-pitch-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["attitude-indicator_internal-pitch-deg"]->GetSim()]]->setValue(vec[8]);
      i1->setVariables(fromPathToVar[simMap["attitude-indicator_internal-pitch-deg"]->GetSim()], vec[8]);
    }
  }
//
  if (!simMap["attitude-indicator_internal-roll-deg"]->isBindedFromRightToLeft()) {
    simMap["attitude-indicator_internal-roll-deg"]->setValue(vec[9]);
    if (fromPathToVar.count(simMap["attitude-indicator_internal-roll-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["attitude-indicator_internal-roll-deg"]->GetSim()]]->setValue(vec[9]);
      i1->setVariables(fromPathToVar[simMap["attitude-indicator_internal-roll-deg"]->GetSim()], vec[9]);
    }
  }

  if (!simMap["encoder_indicated-altitude-ft"]->isBindedFromRightToLeft()) {
    simMap["encoder_indicated-altitude-ft"]->setValue(vec[10]);
    if (fromPathToVar.count(simMap["encoder_indicated-altitude-ft"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["encoder_indicated-altitude-ft"]->GetSim()]]->setValue(vec[10]);
      i1->setVariables(fromPathToVar[simMap["encoder_indicated-altitude-ft"]->GetSim()], vec[10]);
    }
  }

  if (!simMap["encoder_pressure-alt-ft"]->isBindedFromRightToLeft()) {
    simMap["encoder_pressure-alt-ft"]->setValue(vec[11]);
    if (fromPathToVar.count(simMap["encoder_pressure-alt-ft"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["encoder_pressure-alt-ft"]->GetSim()]]->setValue(vec[11]);
      i1->setVariables(fromPathToVar[simMap["encoder_pressure-alt-ft"]->GetSim()], vec[11]);
    }
  }

  if (!simMap["gps_indicated-altitude-ft"]->isBindedFromRightToLeft()) {
    simMap["gps_indicated-altitude-ft"]->setValue(vec[12]);
    if (fromPathToVar.count(simMap["gps_indicated-altitude-ft"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["gps_indicated-altitude-ft"]->GetSim()]]->setValue(vec[12]);
      i1->setVariables(fromPathToVar[simMap["gps_indicated-altitude-ft"]->GetSim()], vec[12]);
    }
  }

  if (!simMap["gps_indicated-ground-speed-kt"]->isBindedFromRightToLeft()) {
    simMap["gps_indicated-ground-speed-kt"]->setValue(vec[13]);
    if (fromPathToVar.count(simMap["gps_indicated-ground-speed-kt"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["gps_indicated-ground-speed-kt"]->GetSim()]]->setValue(vec[13]);
      i1->setVariables(fromPathToVar[simMap["gps_indicated-ground-speed-kt"]->GetSim()], vec[13]);
    }
  }

  if (!simMap["gps_indicated-vertical-speed"]->isBindedFromRightToLeft()) {
    simMap["gps_indicated-vertical-speed"]->setValue(vec[14]);
    if (fromPathToVar.count(simMap["gps_indicated-vertical-speed"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["gps_indicated-vertical-speed"]->GetSim()]]->setValue(vec[14]);
      i1->setVariables(fromPathToVar[simMap["gps_indicated-vertical-speed"]->GetSim()], vec[14]);
    }
  }

  if (!simMap["indicated-heading-deg"]->isBindedFromRightToLeft()) {
    simMap["indicated-heading-deg"]->setValue(vec[15]);
    if (fromPathToVar.count(simMap["indicated-heading-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["indicated-heading-deg"]->GetSim()]]->setValue(vec[15]);
      i1->setVariables(fromPathToVar[simMap["indicated-heading-deg"]->GetSim()], vec[15]);
    }
  }

  if (!simMap["magnetic-compass_indicated-heading-deg"]->isBindedFromRightToLeft()) {
    simMap["magnetic-compass_indicated-heading-deg"]->setValue(vec[16]);
    if (fromPathToVar.count(simMap["magnetic-compass_indicated-heading-deg"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["magnetic-compass_indicated-heading-deg"]->GetSim()]]->setValue(vec[16]);
      i1->setVariables(fromPathToVar[simMap["magnetic-compass_indicated-heading-deg"]->GetSim()], vec[16]);
    }
  }

  if (!simMap["slip-skid-ball_indicated-slip-skid"]->isBindedFromRightToLeft()) {
    simMap["slip-skid-ball_indicated-slip-skid"]->setValue(vec[17]);
    if (fromPathToVar.count(simMap["slip-skid-ball_indicated-slip-skid"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["slip-skid-ball_indicated-slip-skid"]->GetSim()]]->setValue(vec[17]);
      i1->setVariables(fromPathToVar[simMap["slip-skid-ball_indicated-slip-skid"]->GetSim()], vec[17]);
    }
  }

  if (!simMap["turn-indicator_indicated-turn-rate"]->isBindedFromRightToLeft()) {
    simMap["turn-indicator_indicated-turn-rate"]->setValue(vec[18]);
    if (fromPathToVar.count(simMap["turn-indicator_indicated-turn-rate"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["turn-indicator_indicated-turn-rate"]->GetSim()]]->setValue(vec[18]);
      i1->setVariables(fromPathToVar[simMap["turn-indicator_indicated-turn-rate"]->GetSim()], vec[18]);
    }
  }

  if (!simMap["vertical-speed-indicator_indicated-speed-fpm"]->isBindedFromRightToLeft()) {
    simMap["vertical-speed-indicator_indicated-speed-fpm"]->setValue(vec[19]);
    if (fromPathToVar.count(simMap["vertical-speed-indicator_indicated-speed-fpm"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["vertical-speed-indicator_indicated-speed-fpm"]->GetSim()]]->setValue(vec[19]);
      i1->setVariables(fromPathToVar[simMap["vertical-speed-indicator_indicated-speed-fpm"]->GetSim()], vec[19]);
    }
  }

  if (!simMap["flight_aileron"]->isBindedFromRightToLeft()) {
    simMap["flight_aileron"]->setValue(vec[20]);
    if (fromPathToVar.count(simMap["flight_aileron"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["flight_aileron"]->GetSim()]]->setValue(vec[20]);
      i1->setVariables(fromPathToVar[simMap["flight_aileron"]->GetSim()], vec[20]);
    }
  }

  if (!simMap["flight_elevator"]->isBindedFromRightToLeft()) {
    simMap["flight_elevator"]->setValue(vec[21]);
    if (fromPathToVar.count(simMap["flight_elevator"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["flight_elevator"]->GetSim()]]->setValue(vec[21]);
      i1->setVariables(fromPathToVar[simMap["flight_elevator"]->GetSim()], vec[21]);
    }
  }

  if (!simMap["flight_rudder"]->isBindedFromRightToLeft()) {
    simMap["flight_rudder"]->setValue(vec[22]);
    if (fromPathToVar.count(simMap["flight_rudder"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["flight_rudder"]->GetSim()]]->setValue(vec[22]);
      i1->setVariables(fromPathToVar[simMap["flight_rudder"]->GetSim()], vec[22]);
    }
  }

  if (!simMap["flight_flaps"]->isBindedFromRightToLeft()) {
    simMap["flight_flaps"]->setValue(vec[23]);
    if (fromPathToVar.count(simMap["flight_flaps"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["flight_flaps"]->GetSim()]]->setValue(vec[23]);
      i1->setVariables(fromPathToVar[simMap["flight_flaps"]->GetSim()], vec[23]);
    }
  }

  if (!simMap["engine_throttle"]->isBindedFromRightToLeft()) {
    simMap["engine_throttle"]->setValue(vec[24]);
    if (fromPathToVar.count(simMap["engine_throttle"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["engine_throttle"]->GetSim()]]->setValue(vec[24]);
      i1->setVariables(fromPathToVar[simMap["engine_throttle"]->GetSim()], vec[24]);
    }
  }

  if (!simMap["current-engine_throttle"]->isBindedFromRightToLeft()) {
    simMap["current-engine_throttle"]->setValue(vec[25]);
    if (fromPathToVar.count(simMap["current-engine_throttle"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["current-engine_throttle"]->GetSim()]]->setValue(vec[25]);
      i1->setVariables(fromPathToVar[simMap["current-engine_throttle"]->GetSim()], vec[25]);
    }
  }

  if (!simMap["switches_master-avionics"]->isBindedFromRightToLeft()) {
    simMap["switches_master-avionics"]->setValue(vec[26]);
    if (fromPathToVar.count(simMap["switches_master-avionics"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["switches_master-avionics"]->GetSim()]]->setValue(vec[26]);
      i1->setVariables(fromPathToVar[simMap["switches_master-avionics"]->GetSim()], vec[26]);
    }
  }

  if (!simMap["switches_starter"]->isBindedFromRightToLeft()) {
    simMap["switches_starter"]->setValue(vec[27]);
    if (fromPathToVar.count(simMap["switches_starter"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["switches_starter"]->GetSim()]]->setValue(vec[27]);
      i1->setVariables(fromPathToVar[simMap["switches_starter"]->GetSim()], vec[27]);
    }
  }

  if (!simMap["active-engine_auto-start"]->isBindedFromRightToLeft()) {
    simMap["active-engine_auto-start"]->setValue(vec[28]);
    if (fromPathToVar.count(simMap["active-engine_auto-start"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["active-engine_auto-start"]->GetSim()]]->setValue(vec[28]);
      i1->setVariables(fromPathToVar[simMap["active-engine_auto-start"]->GetSim()], vec[28]);
    }
  }

  if (!simMap["flight_speedbrake"]->isBindedFromRightToLeft()) {
    simMap["flight_speedbrake"]->setValue(vec[29]);
    if (fromPathToVar.count(simMap["flight_speedbrake"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["flight_speedbrake"]->GetSim()]]->setValue(vec[29]);
      i1->setVariables(fromPathToVar[simMap["flight_speedbrake"]->GetSim()], vec[29]);
    }
  }

  if (!simMap["c172p_brake-parking"]->isBindedFromRightToLeft()) {
    simMap["c172p_brake-parking"]->setValue(vec[30]);
    if (fromPathToVar.count(simMap["c172p_brake-parking"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["c172p_brake-parking"]->GetSim()]]->setValue(vec[30]);
      i1->setVariables(fromPathToVar[simMap["c172p_brake-parking"]->GetSim()], vec[30]);
    }
  }

  if (!simMap["engine_primer"]->isBindedFromRightToLeft()) {
    simMap["engine_primer"]->setValue(vec[31]);
    if (fromPathToVar.count(simMap["engine_primer"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["engine_primer"]->GetSim()]]->setValue(vec[31]);
      i1->setVariables(fromPathToVar[simMap["engine_primer"]->GetSim()], vec[31]);
    }
  }

  if (!simMap["current-engine_mixture"]->isBindedFromRightToLeft()) {
    simMap["current-engine_mixture"]->setValue(vec[32]);
    if (fromPathToVar.count(simMap["current-engine_mixture"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["current-engine_mixture"]->GetSim()]]->setValue(vec[32]);
      i1->setVariables(fromPathToVar[simMap["current-engine_mixture"]->GetSim()], vec[32]);
    }
  }

  if (!simMap["switches_master-bat"]->isBindedFromRightToLeft()) {
    simMap["switches_master-bat"]->setValue(vec[33]);
    if (fromPathToVar.count(simMap["switches_master-bat"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["switches_master-bat"]->GetSim()]]->setValue(vec[33]);
      i1->setVariables(fromPathToVar[simMap["switches_master-bat"]->GetSim()], vec[33]);
    }
  }

  if (!simMap["switches_master-alt"]->isBindedFromRightToLeft()) {
    simMap["switches_master-alt"]->setValue(vec[34]);
    if (fromPathToVar.count(simMap["switches_master-alt"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["switches_master-alt"]->GetSim()]]->setValue(vec[34]);
      i1->setVariables(fromPathToVar[simMap["switches_master-alt"]->GetSim()], vec[34]);
    }
  }

  if (!simMap["engine_rpm"]->isBindedFromRightToLeft()) {
    simMap["engine_rpm"]->setValue(vec[35]);
    if (fromPathToVar.count(simMap["engine_rpm"]->GetSim()) > 0) {
      programMap[fromPathToVar[simMap["engine_rpm"]->GetSim()]]->setValue(vec[35]);
      i1->setVariables(fromPathToVar[simMap["engine_rpm"]->GetSim()], vec[35]);
    }
  }

  // unlock map
  mapLock.unlock();

  //  for (int i = 0; i < vec.size(); i++) {
//    symbolsValues[i] = vec[i];
//  }

}
bool Variables::UpdateValueOfProgramVar(string str, double newVal) {
  if (programMap.count(str)) {
    programMap[str]->setValue(newVal);
    return true;
  }
  return false;
}