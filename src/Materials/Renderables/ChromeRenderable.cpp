// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ChromeRenderable.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            ChromeRenderable::ChromeRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                               const Eegeo::dv3& ecefPosition,
                                               const Eegeo::Rendering::Materials::IMaterial& material,
                                               const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                               Eegeo::Rendering::Mesh& mesh,
                                               bool depthTest,
                                               bool alphaBlend,
                                               bool isReflection,
                                               const Eegeo::v3& lightPositionOffset)
            : LitRenderable(layerId,
                            ecefPosition,
                            material,
                            vertexBinding,
                            mesh,
                            depthTest,
                            alphaBlend,
                            isReflection)
            , m_lightPositionOffset(lightPositionOffset)
            {
                
            }
            
            const Eegeo::v3 ChromeRenderable::GetLightPositionOffset() const
            {
                return Eegeo::v3::MulRotate(m_lightPositionOffset, m_orientationEcef);
            }
            
            const Eegeo::v3 ChromeRenderable::GetSpecularStretchTangent() const
            {
                return m_ecefPosition.Norm().ToSingle();
            }
        }
    }
}
