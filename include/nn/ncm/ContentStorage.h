#pragma once

#include "nn.h"
#include "ncm.h"
#include "IContentStorage.h"

namespace nn::ncm
{
	class ContentStorage : public IContentStorage
	{
	public:
		ContentStorage(ContentStorage&&);
		ContentStorage(nn::sf::SharedPointer<IContentStorage>);
		ContentStorage();

		ContentStorage& operator=(ContentStorage&&);
		Result swap(ContentStorage&);

		Result CleanupAllPlaceHolder() override;
		Result CreatePlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentId, const s64 size) override;
		Result Delete(const ContentId& contentId) override;
		Result DeletePlaceHolder(const PlaceHolderId& placeHolderId) override;
		Result Register(const PlaceHolderId& placeHolder, const ContentId& contentId) override;
		Result DisableForcibly() override;
		Result FlushPlaceHolder() override;
		Result GetContentCount(s32*) override;
		Result GetFreeSpaceSize(s64* size) override;
		Result GetRightsId(RightsId* rightsId, const ContentId& contentId) override;
		Result GetRightsId(RightsId* rightsId, const PlaceHolderId& placeHolderId) override;
		Result GetSize(s64* size, const ContentId& contentId) override;
		Result GetSize(s64* size, const PlaceHolderId& placeHolderId) override;
		Result GetTotalSpaceSize(s64* size) override;
		Result Has(bool*, ContentId) override;
		Result HasPlaceHolder(bool* result, const PlaceHolderId& placeHolderId) override;
		Result ListContentId(s32* size, ContentId* contentId, const s32 offset, const s32 maxSize) override;
		Result ListPlaceHolder(s32* size, PlaceHolderId* placeHolderIds, const s32 maxSize) override;
		Result ReadContentIdFile(void* buffer, u64 size, const ContentId& contentId, const s64 offset) override;
		Result RepairInvalidFileAttribute() override;
		Result RevertToPlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentIdA, const ContentId& contentIdB) override;
		Result SetPlaceHolderSize(const PlaceHolderId& placeHolderId, const s64 size) override;
		Result WriteContentForDebug(const ContentId& contentId, const s64 offset, const void* buffer, const u64 size) override;
		Result WritePlaceHolder(const PlaceHolderId& placeHolderId, const s64 offset, const void* buffer, const u64 size) override;
	};
}