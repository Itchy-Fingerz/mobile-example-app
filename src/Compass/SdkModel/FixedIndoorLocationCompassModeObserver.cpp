// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "CompassModeObserver.h"
#include "CoordinateConversion.h"
#include "FixedIndoorLocationCompassModeObserver.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            FixedIndoorLocationCompassModeObserver::FixedIndoorLocationCompassModeObserver(ICompassModel& model,CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, ExampleAppMessaging::TMessageBus& messageBus)
            
                : m_model(model)
                , m_callback(this, &FixedIndoorLocationCompassModeObserver::OnGpsModeChanged)
                , m_cameraTransitionController(cameraTransitionController)
                , m_interiorId(FIXED_MY_LOCATION_INDOOR_ID)
                , m_floorIndex(FIXED_MY_LOCATION_FLOOR_INDEX)
                , m_fixedHeadingRadians(Eegeo::Math::Deg2Rad(50.0f))
            {
                Eegeo::Space::LatLongAltitude latLng =  Eegeo::Space::LatLongAltitude::FromDegrees(FIXED_MY_LOCATION_LATITUDE, FIXED_MY_LOCATION_LONGITUDE,0);

                m_location = Eegeo::Space::ConvertLatLongAltitudeToEcef(latLng);
                model.InsertGpsModeChangedCallback(m_callback);
            }

            void FixedIndoorLocationCompassModeObserver::OnGpsModeChanged()
            {
                const GpsMode::Values gpsMode = m_model.GetGpsMode();
                if (gpsMode == GpsMode::GpsFollow || gpsMode == GpsMode::GpsCompassMode)
                {
                    m_cameraTransitionController.StartTransitionTo(m_location,
                                                                   InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance,
                                                                   m_interiorId,
                                                                   m_floorIndex);

                }
            }
        }
    }
}
