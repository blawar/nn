#include "nn.h"

namespace nn::ncm
{
	Result ContentStorage::CreatePlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentId, const s64 size)
	{
		return RequestVV<1, Response, ContentId, PlaceHolderId>(contentId, placeHolderId).send(service()).result();
	}

	Result ContentStorage::DeletePlaceHolder(const PlaceHolderId& placeHolderId)
	{
		return RequestV<2, Response, PlaceHolderId>(placeHolderId).send(service()).result();
	}

	Result ContentStorage::HasPlaceHolder(bool* result, const PlaceHolderId& placeHolderId)
	{
		return RequestV<3, ResponseV<bool>, PlaceHolderId>(placeHolderId).send(service()).result(result);
	}

	Result ContentStorage::WritePlaceHolder(const nn::ncm::PlaceHolderId& placeHolderId, const s64 offset, const void* buffer, const u64 size)
	{
		RequestVV<4, Response, PlaceHolderId, s64> request(placeHolderId, offset);
		request.in(buffer, size);
		return request.send(service()).result();
	}

	Result ContentStorage::Register(const PlaceHolderId& placeHolderId, const ContentId& contentId)
	{
		return RequestVV<5, Response, ContentId, PlaceHolderId>(contentId, placeHolderId).send(service()).result();
	}

	Result ContentStorage::Delete(const ContentId& contentId)
	{
		return RequestV<6, Response, ContentId>(contentId).send(service()).result();
	}

	Result ContentStorage::Has(bool* result, ContentId contentId)
	{
		return RequestV<7, ResponseV<bool>, ContentId>(contentId).send(service()).result(result);
	}

	Result ContentStorage::CleanupAllPlaceHolder()
	{
		return Request<10, Response>().send(service()).result();
	}

	Result ContentStorage::ListPlaceHolder(s32* size, PlaceHolderId* placeHolderIds, const s32 maxSize)
	{
		return RequestV<11, ResponseVV<PlaceHolderId, s32>, s32>(maxSize).send(service()).result(placeHolderIds, size);
	}

	Result ContentStorage::GetContentCount(s32* size)
	{
		return Request<12, ResponseV<s32>>().send(service()).result(size);
	}

	Result ContentStorage::ListContentId(s32* size, ContentId* contentId, const s32 offset, const s32 maxSize)
	{
		return RequestVV<13, ResponseVV<s32, ContentId>, s32, s32>(offset, maxSize).send(service()).result(size, contentId);
	}

	Result ContentStorage::GetSize(s64* size, const nn::ncm::ContentId& contentId)
	{
		return RequestV<14, ResponseV<s64>, ContentId>(contentId).send(service()).result(size);
	}

	Result ContentStorage::DisableForcibly()
	{
		return Request<15, Response>().send(service()).result();
	}

	Result ContentStorage::RevertToPlaceHolder(const PlaceHolderId& placeHolderId, const ContentId& contentIdA, const ContentId& contentIdB)
	{
		return RequestVVV<16, Response, PlaceHolderId, ContentId, ContentId>(placeHolderId, contentIdA, contentIdB).send(service()).result();
	}

	Result ContentStorage::SetPlaceHolderSize(const PlaceHolderId& placeHolderId, const s64 size)
	{
		return RequestVV<17, Response, PlaceHolderId, s64>(placeHolderId, size).send(service()).result();
	}

	Result ContentStorage::ReadContentIdFile(void* buffer, u64 size, const nn::ncm::ContentId& contentId, const s64 offset)
	{
		RequestVV<18, Response, ContentId, s64> request(contentId, offset);
		request.out(buffer, size);
		return request.send(service()).result();
	}

	Result ContentStorage::GetRightsId(RightsId* rightsId, const PlaceHolderId& placeHolderId)
	{
		return RequestV<19, ResponseV<RightsId>, PlaceHolderId>(placeHolderId).send(service()).result(rightsId);
	}

	Result ContentStorage::GetRightsId(RightsId* rightsId, const ContentId& contentId)
	{
		return RequestV<20, ResponseV<RightsId>, ContentId>(contentId).send(service()).result(rightsId);
	}

	Result ContentStorage::WriteContentForDebug(const ContentId& contentId, const s64 offset, const void* buffer, const u64 size)
	{
		RequestVV<21, Response, ContentId, s64> request(contentId, offset);
		request.out(buffer, size);
		return request.send(service()).result();
	}

	Result ContentStorage::GetFreeSpaceSize(s64* size)
	{
		return Request<22, ResponseV<s64>>().send(service()).result(size);
	}

	Result ContentStorage::GetTotalSpaceSize(s64* size)
	{
		return Request<23, ResponseV<s64>>().send(service()).result(size);
	}

	Result ContentStorage::FlushPlaceHolder()
	{
		return Request<24, Response>().send(service()).result();
	}

	Result ContentStorage::GetSize(s64* size, const nn::ncm::PlaceHolderId& placeHolderId)
	{
		return RequestV<25, ResponseV<s64>, PlaceHolderId>(placeHolderId).send(service()).result(size);
	}

	Result ContentStorage::RepairInvalidFileAttribute()
	{
		return Request<26, Response>().send(service()).result();
	}
}