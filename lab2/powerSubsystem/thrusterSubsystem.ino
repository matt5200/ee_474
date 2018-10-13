#include "boolean.ino"

typedef struct thrusterSubsystemData {
  unsigned int* thrusterCommand;
  unsigned short* fuelLevel;
} thrusterSubsystemData;


int Direction= = 0; // 1 = left, 2 = right, 3 = up, 4 = down
int ThrustLevel = 0; // 0 = Off, 1 = On, 
int ThrustDuration = 0; // Milliseconds
void thrusterSubsystem (thrusterSubsystemData* thruster) {
  
}
