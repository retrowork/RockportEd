#pragma once
#include <WinDef.h>

namespace GameInternals {
   struct ObjectData {
      float y_Lift;
      float y_Rotation;
      float x_Lift;
      float x_Rotation;

      float y_Position;
      float z_Position;
      float x_Position;

      BYTE __unk1;
      BYTE __unk2;
      BYTE __unk3;
      BYTE __unk4;

      float y_Velocity;
      float z_Velocity;
      float x_Velocity;

      float Gravity;

      float y_LiftForce;
      float angular_Velocity;
      float x_LiftForce;

      float Grip;
   };

   namespace Gameplay {
      namespace Object {
         static ObjectData* objectDatas = (ObjectData*)(0x5386C8 + 0x400000);

         static bool getObjectData(ObjectData*& out_ObjectData, const int& offset = 0) {
            auto v = &objectDatas[offset];
            if (!v) {
               out_ObjectData = nullptr;
               return false;
            }

            out_ObjectData = v;
            return true;
         }
      }
   }
}