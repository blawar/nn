#pragma once

namespace nn::ncm
{
	class IContentStorage
	{
	public:
		IContentStorage(IContentStorage&&);
		IContentStorage(nn::sf::SharedPointer<IContentStorage>);
		IContentStorage();

		virtual Result CleanupAllPlaceHolder() = 0;
		virtual Result CreatePlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentId, const s64 size) = 0;
		virtual Result Delete(const ContentId& contentId) = 0;
		virtual Result DeletePlaceHolder(const PlaceHolderId& placeHolderId) = 0;
		virtual Result DisableForcibly() = 0;
		virtual Result FlushPlaceHolder() = 0;
		virtual Result GetContentCount(s32*) = 0;
		virtual Result GetFreeSpaceSize(s64*) = 0;
		virtual Result GetRightsId(RightsId* rightsId, const ContentId& contentId) = 0;
		virtual Result GetRightsId(RightsId* rightsId, const PlaceHolderId& placeHolderId) = 0;
		virtual Result GetSize(s64* size, const ContentId& contentId) = 0;
		virtual Result GetSize(s64* size, const PlaceHolderId& placeHolderId) = 0;
		virtual Result GetTotalSpaceSize(s64*) = 0;
		virtual Result Has(bool*, ContentId) = 0;
		virtual Result HasPlaceHolder(bool* result, const PlaceHolderId& placeHolderId) = 0;
		virtual Result ListContentId(s32* size, ContentId* contentId, const s32 offset, const s32 maxSize) = 0;
		virtual Result ListPlaceHolder(s32* size, PlaceHolderId* placeHolderIds, const s32 maxSize) = 0;
		virtual Result ReadContentIdFile(void* buffer, u64 size, const ContentId& contentId, const s64 offset) = 0;
		virtual Result Register(const PlaceHolderId& placeHolder, const ContentId& contentId) = 0;
		virtual Result RepairInvalidFileAttribute() = 0;
		virtual Result RevertToPlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentIdA, const ContentId& contentIdB) = 0;
		virtual Result SetPlaceHolderSize(const PlaceHolderId& placeHolderId, const s64 size) = 0;
		virtual Result WriteContentForDebug(const ContentId& contentId, const s64 offset, const void* buffer, const u64 size) = 0;
		virtual Result WritePlaceHolder(const PlaceHolderId& placeHolderId, const s64 offset, const void* buffer, const u64 size) = 0;

		const Service& service() { return m_service; }
	protected:
		Service m_service;
	};
}