int odeToJoy[] = {
    NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
    NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
    NOTE_E4, NOTE_D4, NOTE_D4,
    NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
    NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
    NOTE_D4, NOTE_C4, NOTE_C4,
    NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4,
    NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
    NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4,
    NOTE_C4, NOTE_D4, 0, 0};

float odeToJoyDurations[] = {
    2, 2, 2, 2,
    2, 2, 2, 2,
    2, 2, 2, 2,
    1.33, 4, 1,
    2, 2, 2, 2,
    2, 2, 2, 2,
    2, 2, 2, 2,
    1.33, 4, 1,
    2, 2, 2, 2,
    2, 4, 4, 2, 2,
    2, 4, 4, 2, 2,
    2, 2, 2, 2};

int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

float noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

int jingleBells[]{
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
    NOTE_E5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
    NOTE_D5, NOTE_G5};

float jingleBellsDurations[] = {
    4, 4, 2,
    4, 4, 2,
    4, 4, 3, 8,
    1,
    4, 4, 4, 4,
    4, 4, 4, 8, 8,
    4, 4, 4, 4,
    2, 2};


int imperial_march[] = {
    NOTE_G4, NOTE_G4, NOTE_G4, NOTE_DS4, NOTE_AS5, NOTE_G4, NOTE_DS4, NOTE_AS5, NOTE_G4,
    NOTE_D5, NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_AS5, NOTE_FS4, NOTE_DS4, NOTE_AS5, NOTE_G4,
    NOTE_G5, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_DS5, REST, NOTE_GS4, NOTE_CS5, NOTE_C5, NOTE_B5,
    NOTE_AS5, NOTE_A5, NOTE_AS5, REST, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_AS5, NOTE_G4, NOTE_AS5, NOTE_D5
};
float imperialMarchDurations[] = {
    4, 4, 4, 16.0/3, 16, 4, 16.0/3, 16, 2,
    4, 4, 4, 16.0/3, 16, 4, 16.0/3, 16, 2,
    4, 16.0/3, 16, 4, 16.0/3, 16, 16, 16, 8, 8, 8, 4, 16.0/3, 16,
    16, 16, 8, 8, 8, 4, 16.0/3, 16, 4, 16.0/3, 16, 2
};