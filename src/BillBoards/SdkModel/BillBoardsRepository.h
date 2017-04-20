// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma on

#include "Types.h"
#include "BillBoards.h"
#include "RepositoryModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardsRepository : public Repository::IRepositoryModel<BillBoardModel*>,private Eegeo::NonCopyable
            {
            private:
                
                typedef BillBoardModel* TModel;
                Repository::RepositoryModel<TModel> m_repository;
            
            public:
                BillBoardsRepository();
                ~BillBoardsRepository();
                
                void AddItem(const TModel& item);
                
                void RemoveItem(const TModel& item);
                
                size_t GetItemCount() const;
                
                TModel GetItemAtIndex(size_t index)
                {
                    return m_repository.GetItemAtIndex(index);
                }
                
                void InsertItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback);
                
                void RemoveItemAddedCallback(Eegeo::Helpers::ICallback1<TModel>& callback);
                
                void InsertItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback);
                
                void RemoveItemRemovedCallback(Eegeo::Helpers::ICallback1<TModel>& callback);

                
            };
        }
    }
}
