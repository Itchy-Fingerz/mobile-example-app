// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "CompassModeObserver.h"
#include "ICompassModel.h"
#include "ICallback.h"
#include "ICameraTransitionController.h"
#include "VectorMath.h"

#define FIXED_MY_LOCATION_INDOOR_ID "98a265e2-b890-4c6b-a28f-948c92e36914"
#define FIXED_MY_LOCATION_FLOOR_INDEX 1
#define FIXED_MY_LOCATION_LATITUDE 33.9433507
#define FIXED_MY_LOCATION_LONGITUDE -118.4087762

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class FixedIndoorLocationCompassModeObserver
            {
            private:
                ICompassModel& m_model;
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::dv3 m_location;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_floorIndex;
                double m_fixedHeadingRadians;
                Eegeo::Helpers::TCallback0<FixedIndoorLocationCompassModeObserver> m_callback;
                
            protected:
                void OnGpsModeChanged();

            public:
                FixedIndoorLocationCompassModeObserver(ICompassModel& model,CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, ExampleAppMessaging::TMessageBus& messageBus);
            };
        }
    }
}
