// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardsRepository.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardsRepository::BillBoardsRepository()
            {
            
            }
            BillBoardsRepository::~BillBoardsRepository()
            {
            
            }
            
            void BillBoardsRepository::AddItem(const TModel& item)
            {
                m_repository.AddItem(item);
            }
            
            void BillBoardsRepository::RemoveItem(const TModel& item)
            {
                m_repository.RemoveItem(item);
            }
            
            size_t BillBoardsRepository::GetItemCount() const
            {
                return m_repository.GetItemCount();
            }
                        
            void BillBoardsRepository::InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
            {
                m_repository.InsertItemAddedCallback(callback);
            }
            
            void BillBoardsRepository::RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
            {
                m_repository.RemoveItemAddedCallback(callback);
            }
            
            void BillBoardsRepository::InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
            {
                m_repository.InsertItemRemovedCallback(callback);
            }
            
            void BillBoardsRepository::RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback)
            {
                m_repository.RemoveItemRemovedCallback(callback);
            }
        }
    }
}