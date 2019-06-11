#pragma once

#include "nn.h"
#include "ncm.h"
#include "IContentStorage.h"

namespace nn::ncm
{
	class ContentStorage : public IContentStorage
	{
	public:
		ContentStorage(nn::ncm::ContentStorage&&);
		ContentStorage(nn::sf::SharedPointer<nn::ncm::IContentStorage>);
		ContentStorage();

		ContentStorage& operator=(nn::ncm::ContentStorage&&);
		Result swap(nn::ncm::ContentStorage&);

		Result CleanupAllPlaceHolder() override;
		Result CreatePlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentId, const s64 size) override;
		Result Delete(nn::ncm::ContentId) override;
		Result DeletePlaceHolder(const PlaceHolderId& placeHolderId) override;
		Result DisableForcibly() override;
		Result FlushPlaceHolder() override;
		Result GetContentCount(s32*) override;
		Result GetFreeSpaceSize(s64*) override;
		Result GetRightsId(nn::ncm::RightsId*, nn::ncm::ContentId) override;
		Result GetRightsId(nn::ncm::RightsId*, nn::ncm::PlaceHolderId) override;
		Result GetSize(s64*, nn::ncm::ContentId) override;
		Result GetSize(s64*, nn::ncm::PlaceHolderId) override;
		Result GetTotalSpaceSize(s64*) override;
		Result Has(bool*, nn::ncm::ContentId) override;
		Result HasPlaceHolder(bool*, nn::ncm::PlaceHolderId) override;
		Result ListContentId(s32*, nn::ncm::ContentId*, s32, s32) override;
		Result ListPlaceHolder(s32*, nn::ncm::PlaceHolderId*, s32) override;
		Result ReadContentIdFile(void*, u64, nn::ncm::ContentId, s64) override;
		Result Register(nn::ncm::PlaceHolderId, nn::ncm::ContentId) override;
		Result RepairInvalidFileAttribute() override;
		Result RevertToPlaceHolder(nn::ncm::PlaceHolderId, nn::ncm::ContentId, nn::ncm::ContentId) override;
		Result SetPlaceHolderSize(nn::ncm::PlaceHolderId, s64) override;
		Result WriteContentForDebug(nn::ncm::ContentId, s64, const void*, u64) override;
		Result WritePlaceHolder(nn::ncm::PlaceHolderId, s64, const void*, u64) override;
	};
}