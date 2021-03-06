#pragma once
#include "Helpers\Game Internals\Gameplay\World.h"
// (De)Serialization
#include <cereal\details\traits.hpp>
#include <cereal\types\map.hpp>
#include <cereal\types\string.hpp>
#include <cereal\archives\xml.hpp>

struct TimeOfDayLightingPreset {
   bool  RenderSun = true;
   float FogDistanceScale;
   float FogSkyColour[4];
   float FogSkyColourScale;
   float FogHazeColour[4];
   float FogHazeColourScale;
   float FogInLightScatter;
   float FogSunFalloff;
   float AmbientColour[4];
   float DiffuseColour[4];
   float SpecularColour[4];
   float FixedFunctionSkyColour[4];
   float EnvSkyBrightness;
   float CarSpecScale;

   TimeOfDayLightingPreset& operator=(GameInternals::TimeOfDayLighting* todInstance) {
      memcpy_s(SpecularColour, sizeof(float) * 4, todInstance->SpecularColour, sizeof(float) * 4);
      memcpy_s(DiffuseColour, sizeof(float) * 4, todInstance->DiffuseColour, sizeof(float) * 4);
      memcpy_s(AmbientColour, sizeof(float) * 4, todInstance->AmbientColour, sizeof(float) * 4);
      memcpy_s(FogSkyColour, sizeof(float) * 4, todInstance->FogSkyColour, sizeof(float) * 4);
      memcpy_s(FogHazeColour, sizeof(float) * 4, todInstance->FogHazeColour, sizeof(float) * 4);
      memcpy_s(FixedFunctionSkyColour, sizeof(float) * 4, todInstance->FixedFunctionSkyColour, sizeof(float) * 4);
      FogDistanceScale   = todInstance->FogDistanceScale;
      FogSkyColourScale  = todInstance->FogSkyColourScale;
      FogHazeColourScale = todInstance->FogHazeColourScale;
      EnvSkyBrightness   = todInstance->EnvSkyBrightness;
      CarSpecScale       = todInstance->CarSpecScale;
      return *this;
   }

   template <class Archive>
   void serialize(Archive& archive) {
      archive(
         CEREAL_NVP(RenderSun),
         CEREAL_NVP(SpecularColour),
         CEREAL_NVP(DiffuseColour),
         CEREAL_NVP(AmbientColour),
         CEREAL_NVP(FogHazeColour),
         CEREAL_NVP(FixedFunctionSkyColour),
         CEREAL_NVP(FogDistanceScale),
         CEREAL_NVP(FogHazeColourScale),
         CEREAL_NVP(FogSkyColourScale),
         CEREAL_NVP(FogSkyColourScale),
         CEREAL_NVP(EnvSkyBrightness),
         CEREAL_NVP(CarSpecScale),
         CEREAL_NVP(FogSkyColour),
         CEREAL_NVP(FogInLightScatter),
         CEREAL_NVP(FogSunFalloff)
      );
   }
};
// True std::map (de)serialization
namespace cereal {
   template <class Archive, class C, class A,
      traits::EnableIf<traits::is_text_archive<Archive>::value> = traits::sfinae> inline
      void save(Archive& ar, const std::map<std::string, TimeOfDayLightingPreset, C, A>& map) {
      for (const auto& item : map)
         ar(cereal::make_nvp(item.first, item.second));
   }

   template <class Archive, class C, class A,
      traits::EnableIf<traits::is_text_archive<Archive>::value> = traits::sfinae> inline
      void load(Archive& ar, std::map<std::string, TimeOfDayLightingPreset, C, A>& map) {
      map.clear();

      auto hint = map.begin();
      while (true) {
         const auto namePtr = ar.getNodeName();
         if (!namePtr)
            break;

         TimeOfDayLightingPreset value; ar(value);
         hint = map.emplace_hint(hint, std::move(std::string(namePtr)), std::move(value));
      }
   }
}