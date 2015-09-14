// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "LitRenderable.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            class ChromeRenderable : public LitRenderable
            {
            public:
                ChromeRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                 const Eegeo::dv3& ecefPosition,
                                 const Eegeo::Rendering::Materials::IMaterial& material,
                                 const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                 Eegeo::Rendering::Mesh& mesh,
                                 bool depthTest,
                                 bool alphaBlend,
                                 bool isReflection,
                                 const Eegeo::v3& lightPositionOffset);
                
                const Eegeo::v3 GetLightPositionOffset() const;
                const Eegeo::v3 GetSpecularStretchTangent() const;
            private:
                Eegeo::v3 m_lightPositionOffset;
            };
        }
    }
}