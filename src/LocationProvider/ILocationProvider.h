#pragma once

#include "ILocationService.h"
#include "ApplicationFixedIndoorLocation.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace LocationProvider
    {
        class ILocationProvider : public Eegeo::Location::ILocationService{
        public:
            virtual void UseNativeLocationService() = 0;
            virtual void EnableFixedLocation(const Eegeo::Space::LatLong& location, const Eegeo::Resources::Interiors::InteriorId & interiorId, const int floorIndex, const double headingDegrees) = 0;
            virtual void EnableFixedLocation(const ExampleApp::ApplicationConfig::SdkModel::ApplicationFixedIndoorLocation& fixedIndoorLocation) = 0;
            virtual void DisableFixedLocation() = 0;
            virtual void UseIPSLocationService(Eegeo::Location::ILocationService& indoorsLocationService) = 0;
        };
    }
}