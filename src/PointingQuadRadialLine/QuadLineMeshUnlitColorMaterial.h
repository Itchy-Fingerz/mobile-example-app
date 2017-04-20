// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"
#include "ColorMaterial.h"

namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        class QuadLineMeshUnlitColorMaterial : public Eegeo::Rendering::Materials::ColorMaterial
        {
        public:
            QuadLineMeshUnlitColorMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                             const std::string& name,
                                             Eegeo::Rendering::Shaders::ColorShader& shader,
                                             const Eegeo::v4& initialColor
                                             ) : ColorMaterial (materialId, name, shader, initialColor){}
            void SetState(Eegeo::Rendering::GLState& glState) const;
        };
    }
}