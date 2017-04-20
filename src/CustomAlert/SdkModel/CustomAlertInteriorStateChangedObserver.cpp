// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertInteriorStateChangedObserver.h"
#include "CustomAlertModel.h"
#include "InteriorsModelRepository.h"
#include "InteriorsModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace SdkModel
        {
            CustomAlertInteriorStateChangedObserver::CustomAlertInteriorStateChangedObserver(CustomAlertModel& customAlertModel,
                                                                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                                         Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel)
            : m_customAlertModel(customAlertModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorsModelRepository(interiorsModelRepository)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_interiorExplorerEnteredCallback(this, &CustomAlertInteriorStateChangedObserver::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &CustomAlertInteriorStateChangedObserver::OnInteriorExplorerExit)
            {
                m_interiorsExplorerModel.InsertInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.InsertInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
                
            CustomAlertInteriorStateChangedObserver::~CustomAlertInteriorStateChangedObserver()
            {
                m_interiorsExplorerModel.RemoveInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.RemoveInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            void CustomAlertInteriorStateChangedObserver::OnInteriorExplorerEntered()
            {
                const std::string& interiorName = m_interiorSelectionModel.GetSelectedInteriorId().Value();
                
                if (m_interiorsModelRepository.HasInterior(interiorName))
                {
                    Eegeo::Resources::Interiors::InteriorsModel& interiorModel = m_interiorsModelRepository.GetInterior(interiorName);
                    const std::string& sourceVendor = interiorModel.GetSourceVendor();
                    
                    m_customAlertModel.SetId(sourceVendor);
                }
            }
            
            void CustomAlertInteriorStateChangedObserver::OnInteriorExplorerExit()
            {
                m_customAlertModel.SetId(DefaultEegeoCustomAlertId);
            }
        }
    }
}
