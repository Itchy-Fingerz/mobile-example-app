// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "EegeoWorld.h"
#include "DebugRenderer.h"

namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        class QuadLine;
        
        class QuadLineFactory
        {
            Eegeo::Modules::Core::RenderingModule& m_renderingModule;
            Eegeo::DebugRendering::DebugRenderer &m_debugRenderer;
            Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
            Eegeo::Rendering::TShaderId m_shaderId;
        public:
            QuadLineFactory(Eegeo::Modules::Core::RenderingModule& renderingModule,
                               Eegeo::DebugRendering::DebugRenderer &debugRenderer,
                               Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
            
            std::string ExampleName() const;
            
            QuadLine* CreateQuadLine(Eegeo::v4 quadColor,
                                       Eegeo::Space::LatLongAltitude fromPosition,
                                       Eegeo::Space::LatLongAltitude toPosition,
                                       float tileLength,
                                       float thickness) const;
        };
    }
    
}
