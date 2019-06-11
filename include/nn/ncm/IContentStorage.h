#pragma once

namespace nn::ncm
{
	class IContentStorage
	{
	public:
		IContentStorage(nn::ncm::IContentStorage&&);
		IContentStorage(nn::sf::SharedPointer<nn::ncm::IContentStorage>);
		IContentStorage();

		virtual Result CleanupAllPlaceHolder() = 0;
		virtual Result CreatePlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentId, const s64 size) = 0;
		virtual Result Delete(nn::ncm::ContentId) = 0;
		virtual Result DeletePlaceHolder(const PlaceHolderId& placeHolderId) = 0;
		virtual Result DisableForcibly() = 0;
		virtual Result FlushPlaceHolder() = 0;
		virtual Result GetContentCount(s32*) = 0;
		virtual Result GetFreeSpaceSize(s64*) = 0;
		virtual Result GetRightsId(nn::ncm::RightsId*, nn::ncm::ContentId) = 0;
		virtual Result GetRightsId(nn::ncm::RightsId*, nn::ncm::PlaceHolderId) = 0;
		virtual Result GetSize(s64*, nn::ncm::ContentId) = 0;
		virtual Result GetSize(s64*, nn::ncm::PlaceHolderId) = 0;
		virtual Result GetTotalSpaceSize(s64*) = 0;
		virtual Result Has(bool*, nn::ncm::ContentId) = 0;
		virtual Result HasPlaceHolder(bool*, nn::ncm::PlaceHolderId) = 0;
		virtual Result ListContentId(s32*, nn::ncm::ContentId*, s32, s32) = 0;
		virtual Result ListPlaceHolder(s32*, nn::ncm::PlaceHolderId*, s32) = 0;
		virtual Result ReadContentIdFile(void*, u64, nn::ncm::ContentId, s64) = 0;
		virtual Result Register(nn::ncm::PlaceHolderId, nn::ncm::ContentId) = 0;
		virtual Result RepairInvalidFileAttribute() = 0;
		virtual Result RevertToPlaceHolder(nn::ncm::PlaceHolderId, nn::ncm::ContentId, nn::ncm::ContentId) = 0;
		virtual Result SetPlaceHolderSize(nn::ncm::PlaceHolderId, s64) = 0;
		virtual Result WriteContentForDebug(nn::ncm::ContentId, s64, const void*, u64) = 0;
		virtual Result WritePlaceHolder(nn::ncm::PlaceHolderId, s64, const void*, u64) = 0;

		const Service& service() { return m_service; }
	protected:
		Service m_service;
	};
}