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
            FixedIndoorLocationCompassModeObserver::FixedIndoorLocationCompassModeObserver(ICompassModel& model,Eegeo::Space::LatLongAltitude latlng, Eegeo::Resources::Interiors::InteriorId interiorId, int floorIndex,CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, ExampleAppMessaging::TMessageBus& messageBus)
            
                : m_model(model)
                , m_callback(this, &FixedIndoorLocationCompassModeObserver::OnGpsModeChanged)
                , m_cameraTransitionController(cameraTransitionController)
                , m_location(Eegeo::Space::ConvertLatLongAltitudeToEcef(latlng))
                , m_interiorId(interiorId)
                , m_floorIndex(floorIndex)
                , m_fixedHeadingRadians(Eegeo::Math::Deg2Rad(50.0f))
            {
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
