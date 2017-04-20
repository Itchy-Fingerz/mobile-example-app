// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMaterial.h"
#include "VectorMath.h"
#include "VideoAssetReaderService.h"
#include "BillBoardService.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            class BillBoardsMeshUnlitTexturedMaterial : public Eegeo::Rendering::Materials::IMaterial, Eegeo::NonCopyable
            {
            public:
                BillBoardsMeshUnlitTexturedMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                 const std::string& debugName,
                                                 Eegeo::Rendering::Shaders::TexturedUniformColoredShader& shader,
                                                 Eegeo::Rendering::TTextureId textureId,
                                                 BillBoardService &billBoardService,
                                                    bool isVideo);
                ~BillBoardsMeshUnlitTexturedMaterial();
                const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
                const Eegeo::Rendering::Shader& GetShader() const;
                const std::string& GetName() const { return m_debugName; }
                void SetState(Eegeo::Rendering::GLState& glState) const;
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
                void SetAnimatingState(bool isAnimating) const;
                void SetTappedState(bool isTapped) const;
                void SetTextureId(Eegeo::Rendering::TTextureId textureId) const;
                
                bool GetAnimatingState() const;
                
            
            protected:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_debugName;
                BillBoardService &m_billBoardService;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader& m_shader;
                mutable Eegeo::Rendering::TTextureId m_textureId;
                bool m_isVideo;
                mutable bool m_isAnimating;
                mutable double m_currentAlpha;
                mutable bool m_isTapped;
                
            };
        }
    }
}
