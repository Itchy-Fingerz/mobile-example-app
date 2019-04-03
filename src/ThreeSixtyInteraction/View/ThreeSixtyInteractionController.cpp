// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionController.h"
#include "ThreeSixtyInteractionMessage.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionController::ThreeSixtyInteractionController(IThreeSixtyInteractionView& view,IThreeSixtyInteractionViewModel& viewModel,ExampleAppMessaging::TMessageBus& messageBus)
            : m_view(view)
            , m_viewModel(viewModel)
            , m_messageBus(messageBus)
            , m_viewModelOpenedCallback(this, &ThreeSixtyInteractionController::OnOpenViewModel)
            , m_viewModelClosedCallback(this, &ThreeSixtyInteractionController::OnCloseViewModel)
            , m_viewClosedCallback(this, &ThreeSixtyInteractionController::OnCloseTapped)
            , m_showThreeSixtyInteractionCallback(this, &ThreeSixtyInteractionController::OnShowThreeSixtyInteraction)

            {
                m_viewModel.InsertOpenedCallback(m_viewModelOpenedCallback);
                m_viewModel.InsertClosedCallback(m_viewModelClosedCallback);
                m_view.InsertCloseTappedCallback(m_viewClosedCallback);
                m_messageBus.SubscribeUi(m_showThreeSixtyInteractionCallback);
            }

            ThreeSixtyInteractionController::~ThreeSixtyInteractionController()
            {
                m_viewModel.RemoveOpenedCallback(m_viewModelOpenedCallback);
                m_viewModel.RemoveClosedCallback(m_viewModelClosedCallback);
                m_view.RemoveCloseTappedCallback(m_viewClosedCallback);
                m_messageBus.UnsubscribeUi(m_showThreeSixtyInteractionCallback);

            }
            void ThreeSixtyInteractionController::OnOpenViewModel(std::string& url)
            {
                m_view.Open(url);
            }
            
            void ThreeSixtyInteractionController::OnCloseViewModel()
            {
                m_view.Close();
            }
            
            void ThreeSixtyInteractionController::OnCloseTapped()
            {
                m_viewModel.Close();
            }
            
            void ThreeSixtyInteractionController::OnShowThreeSixtyInteraction(const ThreeSixtyInteraction::ThreeSixtyInteractionMessage& message)
            {
                std::string url = message.GetUrl();
                m_viewModel.Open(url);
            }
        }
    }
}
