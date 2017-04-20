// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "QuadLineFactory.h"
#include "QuadLine.h"
#include "CoreModule.h"
#include "RenderingModule.h"
#include "CoordinateConversion.h"
namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        QuadLineFactory::QuadLineFactory(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                               Eegeo::DebugRendering::DebugRenderer &debugRenderer,
                                               Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
        : m_renderingModule(renderingModule)
        , m_debugRenderer(debugRenderer)
        , m_environmentFlatteningService(environmentFlatteningService)
        {
            
        }
        
        QuadLine* QuadLineFactory::CreateQuadLine(Eegeo::v4 quadColor,
                                                       Eegeo::Space::LatLongAltitude fromPosition,
                                                       Eegeo::Space::LatLongAltitude toPosition,
                                                       float tileLength,
                                                       float thickness) const
        {
            return new ExampleApp::PointingQuadRadialLine::QuadLine(m_renderingModule,
                                                                       m_debugRenderer,
                                                                       m_environmentFlatteningService,
                                                                       quadColor,
                                                                       Eegeo::Space::ConvertLatLongAltitudeToEcef(fromPosition),
                                                                       Eegeo::Space::ConvertLatLongAltitudeToEcef(toPosition),
                                                                       tileLength,
                                                                       thickness);
            
        }

    }
}
